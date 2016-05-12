/**
* @file document.h
* @author Dounm
* @date 2016-05-07
*/

#include <string>
#include <vector>

#include "dlog/dlog.h"
#include "util.h"

#ifndef DOUNM_CPPLDA_DOCUMENT_H
#define DOUNM_CPPLDA_DOCUMENT_H

namespace dounm {
namespace cpplda {

class Document{
public:
    Document() : _word_vec(), _wordid_vec() {}
    Document(const std::string& doc);
    ~Document() {}
    Document(const Document& other) : 
            _word_vec(other._word_vec), 
            _wordid_vec(other._wordid_vec) {}
    Document& operator=(const Document& other);

    size_t get_doc_word_num() const {
        return _word_vec.size();
    }

    void set_wordid_vec(Str2Int_Hashmap* word2id_hm, Str_Vec* id2word_vec);
    /**
    * @brief get the wordid of the ith word in the document 
    * @param i the index
    * @return  wordid of the ith word
    */
    size_t operator[](int i) const {
        return _wordid_vec.at(i);
    }

private:
    Str_Vec _word_vec;
    Int_Vec _wordid_vec;    //store the word index in word_id_map
};

}
}

#endif
