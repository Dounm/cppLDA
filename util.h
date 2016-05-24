/**
* @file util.h
* @author Dounm
* @date 2016-05-09
*/

#include <ext/hash_map>

#include <string>
#include <vector>
#include <sstream>

#ifndef DOUNM_CPPLDA_UTIL_H
#define DOUNM_CPPLDA_UTIL_H

namespace dounm {
namespace cpplda {

struct str_hash {
    size_t operator() (const std::string& str) const {
        return __gnu_cxx::__stl_hash_string(str.c_str());
    }
};

template <class From, class To>
void convert(std::stringstream& ss, From from, To* to) {
    ss.clear();
    ss.str("");
    ss << from;
    ss >> *to;
}

typedef std::vector<std::string> Str_Vec;
typedef std::vector<int> Int_Vec;
typedef std::vector<double> Double_Vec;
typedef std::pair<int, double> Int_Double_Pair;
typedef __gnu_cxx::hash_map<std::string, int, str_hash> Str2Int_Hashmap;
typedef __gnu_cxx::hash_map<std::string, int, str_hash>::iterator Str2Int_Hashmap_Iter;
typedef __gnu_cxx::hash_map<int, std::string> Int2Str_Hashmap;


bool topwords_cmp(const Int_Double_Pair& a, const Int_Double_Pair& b); 

class Util {
public:
    Util() {}
    ~Util() {}
    static void split
            (Str_Vec* split_vec, const std::string& str, char split_flag);
    static void strip(std::string* str_ptr);

    /**
    * @brief generate a random double number in [begin, end) by uniform distribution
    * @param begin
    * @param end
    * @return  generated result
    */
    static double unif_rand(double begin, double end);
    static void log_2dims_array(
        const std::string& type, const std::string& array_name, 
        void* a, size_t dim1, size_t dim2);
    static void log_1dim_array(
        const std::string& type, const std::string& array_name, 
        void* a, size_t dim);
};

}
}

#endif
