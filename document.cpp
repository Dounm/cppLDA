/**
* @file document.cpp
* @author Dounm
* @date 2016-05-09
*/

#include "dlog/dlog.h"
#include "util.h"

#include "document.h"

namespace dounm {
namespace cpplda {

Document::Document(const std::string& doc) {
    std::string tmpstr(doc);
    Util::strip(&tmpstr);
    Util::split(&_word_vec, tmpstr, ' ');
}

Document& Document::operator=(const Document& other) {
    _word_vec = other._word_vec;
    _wordid_vec = other._wordid_vec;
    return *this;
}

void Document::set_wordid_vec(Str2Int_Hashmap* word2id_hm,  
        Str_Vec* id2word_vec) {
    size_t unique_word_num = id2word_vec->size();
    for (size_t i = 0;i < _word_vec.size(); ++i) {
        std::string cur_word = _word_vec[i];
        Str2Int_Hashmap_Iter it = word2id_hm->find(cur_word);
        if (it == word2id_hm->end()) {
            // if the word hasn't appeared yet, then record it
            (*word2id_hm)[cur_word] = unique_word_num;
            _wordid_vec[i] = unique_word_num;
            id2word_vec->push_back(cur_word);
            unique_word_num ++;
        } else {
            size_t cur_word_id = it->second;
            _wordid_vec[i] = cur_word_id;
        }
    }
}

}
}

