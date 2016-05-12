/**
* @file lda_model.cpp
* @author Dounm
* @date 2016-05-12
*/

#include "dlog/dlog.h"
#include "util.h"
#include "lda_model.h"

namespace dounm {
namespace cpplda {

LDAModel::LDAModel(const Dataset& dset) : 
        _m(dset.)

LDAModel::~LDAModel() {
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

    for (size_t i = 0;i < m; ++i) {
        delete [] _theta[i];
    }
    delete[] _theta;

    for (size_t i = 0;i < k; ++i) {
        delete [] _phi[i];
    }
    delete[] _phi;
}

}
}
