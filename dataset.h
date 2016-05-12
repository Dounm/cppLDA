/**
* @file dataset.h
* @author Dounm
* @date 2016-05-09
*/

#include <ext/hash_map>

#include <string>
#include <vector>

#include "dlog/dlog.h"
#include "util.h"
#include "document.h"

#ifndef DOUNM_CPPLDA_DATASET_H
#define DOUNM_CPPLDA_DATASET_H

namespace dounm {
namespace cpplda {

class Dataset {
public:
    Dataset() : _doc_num(0), _total_word_num(0), _doc_vec(), 
            _word2id_hm(), _id2word_vec() {}
    Dataset(const std::string& train_file);
    ~Dataset() {}

    //For Dataset class, we do not need any copy constructor,
    //so I declare a copy constructor but do not define it.
    Dataset(const Dataset& other);

    size_t get_doc_num() const {
        return _doc_num;
    }
    size_t get_total_word_num() const {
        return _total_word_num;
    }

    void read_train_file(const std::string& train_file);

private:
    size_t _doc_num;
    size_t _total_word_num;     //number of unique words of all documents
    std::vector<Document> _doc_vec;
    Str2Int_Hashmap _word2id_hm;    //word to id hashmap
    Str_Vec _id2word_vec;    //id to word vector 
};

}
}

#endif
