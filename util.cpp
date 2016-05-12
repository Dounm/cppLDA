/**
* @file util.cpp
* @author Dounm
* @date 2016-05-12
*/

#include "dlog/dlog.h"
#include "util.h"

namespace dounm {
namespace cpplda {

void Util::split(Str_Vec* split_vec, 
        const std::string& str, char split_flag) {
    DCHECK_NOTNULL(split_vec);
    
    size_t s_pos = 0;
    size_t e_pos = 0;
    for (size_t i = 0;i < str.size(); ++i) {
        if (str.at(i) == split_flag) {
            e_pos = i - 1;
            split_vec->push_back(str.substr(s_pos, e_pos-s_pos+1));
            s_pos = i+1;
        }
    }
    e_pos = str.size() - 1;
    split_vec->push_back(str.substr(s_pos, e_pos-s_pos+1));
}

void Util::strip(std::string* str_ptr) {
    DCHECK_NOTNULL(str_ptr);
    std::string& str = *str_ptr;
    size_t s_pos;
    size_t e_pos;
    for (s_pos = 0;s_pos < str.size(); ++s_pos ) {
        if (str[s_pos] == ' ' || str[s_pos] == '\n' || str[s_pos] == '\t') continue;
        break;
    }
    for (e_pos = str.size() - 1; e_pos >= 0; --e_pos) {
        if (e_pos < s_pos) {
            str = std::string();
            return;
        }
        if (str[e_pos] == ' ' || str[e_pos] == '\n' || str[e_pos] == '\t') continue;
        break;
    }
    str = str.substr(s_pos, e_pos-s_pos+1);
}

}
}
