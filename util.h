/**
* @file util.h
* @author Dounm
* @date 2016-05-09
*/

#include <ext/hash_map>

#include <string>
#include <vector>

#ifndef DOUNM_CPPLDA_UTIL_H
#define DOUNM_CPPLDA_UTIL_H

namespace dounm {
namespace cpplda {

struct str_hash {
    size_t operator() (const std::string& str) const {
        return __gnu_cxx::__stl_hash_string(str.c_str());
    }
};

typedef std::vector<std::string> Str_Vec;
typedef std::vector<int> Int_Vec;
typedef std::vector<double> Double_Vec;
typedef __gnu_cxx::hash_map<std::string, int, str_hash> Str2Int_Hashmap;
typedef __gnu_cxx::hash_map<std::string, int, str_hash>::iterator Str2Int_Hashmap_Iter;
typedef __gnu_cxx::hash_map<int, std::string> Int2Str_Hashmap;

class Util {
public:
    Util() {}
    ~Util() {}
    static void split
            (Str_Vec* split_vec, const std::string& str, char split_flag);
    static void strip(std::string* str_ptr);
};

}
}

#endif
