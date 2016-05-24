/**
* @file lda_model.cpp
* @author Dounm
* @date 2016-05-12
*/

#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>

#include "dlog/dlog.h"
#include "util.h"
#include "lda_model.h"

namespace dounm {
namespace cpplda {

LDAModel::LDAModel(const Dataset& dset, size_t k, const std::string& model_name) : 
        _model_name(model_name),
        _m(dset.get_doc_num()),
        _v(dset.get_total_word_num()),
        _k(k) {

    DLOG(INFO) << "_model_name: " << _model_name;
    DLOG(INFO) << "_m: " << _m;
    DLOG(INFO) << "_v: " << _v;
    DLOG(INFO) << "_k: " << _k;
    _dset = &dset;
}

void LDAModel::init_estimation() {
    _nw = new int*[_v]();
    for (size_t i = 0;i < _v ;++i)
        _nw[i] = new int [_k]();
    _nd = new int*[_m]();
    for (size_t i = 0;i < _m ;++i)
        _nd[i] = new int[_k]();

    _nwsum = new int[_k]();
    _ndsum = new int[_m]();
    _p = new double[_k]();

    _z = new int*[_m]();
    srand(time(NULL));
    for (size_t i = 0;i < _m;++i) {
        const Document& cur_doc = _dset->get_ith_doc(i);
        size_t cur_doc_len = cur_doc.get_doc_word_num();
        _z[i] = new int[cur_doc_len]();
        _ndsum[i] = cur_doc_len;
        for (size_t j = 0;j < cur_doc_len; ++j) {
            size_t topic = rand() % _k;
            _z[i][j] = topic;
            _nw[cur_doc[j]][topic]++;
            _nd[i][topic]++;
            _nwsum[topic]++;
        }
    }

    _theta = new double*[_m]();
    for (size_t i = 0;i < _m ;++i)
        _theta[i] = new double[_k]();

    _phi = new double*[_k]();
    for (size_t i = 0;i < _k ;++i)
        _phi[i] = new double[_v]();

}

LDAModel::~LDAModel() {
    debug();
    for (size_t i = 0; i < _m; ++i) {
        delete [] _z[i];
    }
    delete [] _z;

    for (size_t i = 0; i < _v; ++i) {
        delete [] _nw[i];
    }
    delete [] _nw;

    for (size_t i = 0; i < _m; ++i) {
        delete [] _nd[i];
    }
    delete [] _nd;

    delete [] _nwsum;

    delete [] _ndsum;

    delete [] _p;

    for (size_t i = 0;i < _m; ++i) {
        delete [] _theta[i];
    }
    delete[] _theta;

    for (size_t i = 0;i < _k; ++i) {
        delete [] _phi[i];
    }
    delete[] _phi;
}

void LDAModel::estimate(size_t iter_num, double alpha, double beta, 
        size_t topword_num = 10) {
    _topword_num = topword_num;
    if (_topword_num > _v) {
        _topword_num = _v;
    }
#ifdef _for_debug
    DLOG(INFO) << "[DEBUG]Iterations: " << iter_num;
    DLOG(INFO) << "[DEBUG]Alpha: " << alpha;
    DLOG(INFO) << "[DEBUG]Beta: " << beta;
    DLOG(INFO) << "[DEBUG]Topword_num: " << topword_num;
#endif
    DLOG(INFO) << "Sampling " << iter_num << " iterations";
    debug();
    for (size_t iter = 0;iter < iter_num; ++iter) {
        for (size_t i = 0;i < _m; ++i) {
            const Document& cur_doc = _dset->get_ith_doc(i);
            for (size_t j = 0;j < cur_doc.get_doc_word_num(); ++j) {
                size_t topic = sample(i, j);
                _z[i][j] = topic;
            }
        }
        DLOG(INFO) << iter << " iteration done!";
    }
    DLOG(INFO) << "End Sampling";

    for (size_t i = 0;i < _m; ++i) {
        for (size_t j = 0;j < _k; ++j) {
            _theta[i][j] = (_nd[i][j] + _alpha) / (_ndsum[i] + _k*_alpha);
        }
    }
    DLOG(INFO) << "Compute theta done!";

    for (size_t i = 0;i < _k; ++i) {
        for (size_t j = 0;j < _v; ++j) {
            _phi[i][j] = (_nw[j][i] + _beta) / (_nwsum[i] + _v*_beta);
        }
    }
    DLOG(INFO) << "Compute phi done!";
    
    save_model();
    DLOG(INFO) << "Save model done!";
}

size_t LDAModel::sample(size_t doc_idx, size_t word_idx) {
    size_t topic = _z[doc_idx][word_idx];
    const Document& cur_doc = _dset->get_ith_doc(doc_idx);
    size_t wordid = cur_doc[word_idx];

    _nw[wordid][topic] --;
    _nd[doc_idx][topic] --;
    _nwsum[topic]--;
    _ndsum[doc_idx] --;

    double vbeta = _v * _beta;
    double kalpha = _k * _alpha;
    for (size_t i = 0;i < _k; ++i) {
        _p[i] = (_nw[wordid][i] + _beta) / (_nwsum[i] + vbeta) * 
                (_nd[doc_idx][i] + _alpha) / (_ndsum[doc_idx] + kalpha);
    }

    //Util::log_1dim_array("double", "p" ,_p, _k);
    for (size_t i = 1;i < _k; ++i) {
        _p[i] += _p[i-1];
    }
    double r = Util::unif_rand(0, _p[_k-1]);
    for (topic = 0; topic < _k; ++topic) {
        if (_p[topic] > r) {
            break;
        }
    }
    if (topic == _k) 
        topic = _k-1;
    _nw[wordid][topic] ++;
    _nd[doc_idx][topic] ++;
    _nwsum[topic]++;
    _ndsum[doc_idx] ++;
    return topic;
}

void LDAModel::save_model() {
    std::string file(_model_name + ".theta");
    std::ofstream ftheta(file.c_str());
    for (size_t i = 0;i < _m; ++i) {
        for (size_t j = 0;j < _k; ++j) {
            ftheta << _theta[i][j];
            if (j == _k-1) {
                ftheta << std::endl;
            } else {
                ftheta << ' ';
            }
        }
    }
    ftheta.close();
    
    file = _model_name + ".phi";
    std::ofstream fphi(file.c_str());
    for (size_t i = 0;i < _k; ++i) {
        for (size_t j = 0;j < _v; ++j) {
            fphi << _phi[i][j];
            if (j == _v-1) {
                fphi << std::endl;
            } else {
                fphi << ' ';
            }
        }
    }
    fphi.close();

    file = _model_name + ".topwords";
    std::ofstream ftopwords(file.c_str());
    Int_Double_Pair* tmp = new Int_Double_Pair[_v];
    for (size_t i = 0;i < _k; ++i) {
        for (size_t j = 0;j < _v; ++j) {
            tmp[j].first = j;
            tmp[j].second = _phi[i][j];
        }
        sort(tmp, tmp+_v, topwords_cmp);
        for (size_t j = 0;j < _topword_num; ++j) {
            std::string word = _dset->get_word_by_wordid(tmp[j].first);                    
            ftopwords << word;
            if (j == _topword_num-1) {
                ftopwords << std::endl;
            } else {
                ftopwords << '\t';
            }
        }
    }
    ftopwords.close();
    delete [] tmp;
}

void LDAModel::debug() {
    Util::log_2dims_array("int", "nw", _nw, _v, _k);
    //Util::log_2dims_array("int", "nd", _nd, _m, _k);
    Util::log_1dim_array("int", "nwsum", _nwsum, _k);
    //Util::log_1dim_array("int", "ndsum", _ndsum, _m);
    //Util::log_2dims_array("double", "theta", _theta, _m, _k);
    //Util::log_2dims_array("double", "phi", _phi, _k, _v);
}

}
}
