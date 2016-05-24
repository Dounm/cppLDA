/*
* @file lda_model.h
* @brief 
* @author Dounm
* @date 2016-05-09
*/

#include <string>
#include <vector>

#include "dlog/dlog.h"
#include "dataset.h"

#ifndef DOUNM_CPPLDA_LDA_MODEL_H
#define DOUNM_CPPLDA_LDA_MODEL_H

namespace dounm {
namespace cpplda {

class LDAModel {
public:
    LDAModel() {}
    ~LDAModel();
    LDAModel(const LDAModel& other);

    LDAModel(const Dataset& dataset, size_t k, const std::string& model_name);

    void run(size_t iter_num, double alpha, double beta, size_t topword_num = 10) {
        init_estimation();
        estimate(iter_num, alpha, beta, topword_num);
    }

private:
    void init_estimation();
    void estimate(size_t iter_num, double alpha, double beta, size_t topword_num);
    size_t sample(size_t doc_idx, size_t word_idx);
    void cal_topwords();
    void save_model();

    void debug();
    
private:
    std::string _model_name;
    size_t _iter_num;
    size_t _topword_num;
    Str_Vec _topword_vec;

   
    size_t _m;   // means number of documents in papers by convection
    size_t _v;   // means number of words in papers by convention
    size_t _k;   // means number of topics in papers by convection
    double _alpha;
    double _beta;
    int** _z;  //Dims: m*doc.size   topic assignment for each word in each doc
    int** _nw; //Dims: v*k   nw[i][j]: number of instances of word i assigned to topic j
    int** _nd; //Dims: m*k   nd[i][j]: number of words in document i assigned to topic j
    int* _nwsum; //Dims: k   nwsum[j]: total number of words assigned to topic j
    int* _ndsum; //Dims: m   ndsum[i]: number of words in doc i

    double* _p; //Dims: k   store temporary variables when sampling
    
    double** _theta;
    double** _phi; 

    const Dataset* _dset;
};

}
}

#endif
