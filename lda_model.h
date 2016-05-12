/**
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
    LDAModel(){}
    ~LDAModel();
    LDAModel(const LDAModel& other);

    LDAModel(const Dataset& dataset);

    void init_paras();

private:
    
private:
    size_t _m;   // means number of documents in papers by convection
    size_t _v;   // means number of words in papers by convention
    size_t _k;   // means number of topics in papers by convection
    double _alpha;
    double _beta;
    int** _z;  //Dims: m*k   topic assignment for each word
    int** _nw; //Dims: v*k   nw[i][j]: number of instances of word i assigned to topic j
    int** _nd; //Dims: m*k   nd[i][j]: number of words in document i assigned to topic j
    int* _nwsum; //Dims: v   nwsum[j]: total number of words assigned to topic j
    int* _ndsum; //Dims: m   ndsum[i]: number of words in doc i
    
    double** _theta;
    double** _phi; 

    size_t _iter_num;
};

}
}

#endif
