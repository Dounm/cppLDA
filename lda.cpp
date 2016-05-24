/**
* @file lda.cpp
* @author Dounm
* @date 2016-05-15
*/

#include <iostream>
#include <sstream>

#include "lda_model.h"

using namespace dounm::cpplda; 
using namespace std;

int main(int argc, char* argv[]) {
    std::stringstream ss;
    std::string train_file(argv[1]);
    size_t k = 0;
    size_t iter_num  = 0;
    double alpha = 0;
    double beta = 0;
    convert<char*, size_t>(ss, argv[2], &k);
    convert<char*, size_t>(ss, argv[3], &iter_num);
    convert<char*, double>(ss, argv[4], &alpha);
    convert<char*, double>(ss, argv[5], &beta);
    cout << train_file << endl;
    cout << k << endl;
    cout << iter_num << endl;
    cout << alpha << endl;
    cout << beta << endl;

    Dataset dset(train_file);
    LDAModel model(dset, k, "lda_test");
    model.run(iter_num, alpha, beta);
    return 0;
}

