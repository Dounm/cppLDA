/**
* @file dataset.cpp
* @author Dounm
* @date 2016-05-09
*/

#include <string>
#include <fstream>
#include <sstream>

#include "dlog/dlog.h"
#include "dataset.h"

namespace dounm {
namespace cpplda {

Dataset::Dataset(const std::string& train_file) : 
        _doc_num(0), _total_word_num(0), _doc_vec(), 
        _word2id_hm(), _id2word_vec() {
    read_train_file(train_file);
}

void Dataset::read_train_file(const std::string& train_file) {
    std::ifstream fin(train_file.c_str());
    DCHECK(fin.good()) << "[CPPLDA] cannot open the train_file: " << train_file;

    std::string line;
    std::stringstream ss;

    getline(fin, line);
    ss << line;
    ss >> _doc_num;

    while (getline(fin, line)) {
        //TODO: reduce the cost of temporary Document objecet here
        _doc_vec.push_back(Document(line));
        _doc_vec.back().set_wordid_vec(&_word2id_hm, &_id2word_vec);
    }
    _doc_num = _doc_vec.size();
    _total_word_num = _id2word_vec.size();
}

}
}
