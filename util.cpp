/**
* @file util.cpp
* @author Dounm
* @date 2016-05-12
*/

#include <time.h>
#include <stdlib.h>

#include <sstream>

#include "dlog/dlog.h"
#include "util.h"

namespace dounm {
namespace cpplda {

bool topwords_cmp(const std::pair<int, double>& a, const std::pair<int, double>& b) {
    if (a.second > b.second) return true;
    return false;
}

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

//TODO: use std::uniform_real_distribution() instead of rand()
double Util::unif_rand(double begin, double end) {
    double r = (double)rand() / RAND_MAX;
    r *= (end - begin);
    r += begin;
    return r;
}

void Util::log_2dims_array(
        const std::string& type, const std::string& array_name,
        void* ptr, size_t dim1, size_t dim2) {
    int** int_arr;
    double**  double_arr;
    if (type == "int") {
        int_arr = (int**) ptr;
    } else {
        double_arr = (double**) ptr;
    }

    std::string str;
    std::stringstream ss;
    for (size_t i = 0; i < dim1; ++i ) {
        for (size_t j = 0; j < dim2; ++j) {
            if (type == "int") {
                ss << int_arr[i][j]; 
            } else {
                ss << double_arr[i][j];
            }
            if (j < dim2 - 1) {
                ss << ' ';
            } else {
                ss << '\n';
            }
        }
    }
    DLOG(INFO) << "------------------------------";
    DLOG(INFO) << "[DEBUG] " << 
        "the content of two-dimensional double array " << array_name << ": \n" <<
        ss.str();
    DLOG(INFO) << "------------------------------";
}

void Util::log_1dim_array(
        const std::string& type, const std::string& array_name,
        void* ptr, size_t dim) {
    int* int_arr;
    double*  double_arr;
    if (type == "int") {
        int_arr = (int*) ptr;
    } else {
        double_arr = (double*) ptr;
    }

    std::string str;
    std::stringstream ss;
    for (size_t i = 0; i < dim; ++i ) {
        if (type == "int") {
            ss << int_arr[i]; 
        } else {
            ss << double_arr[i];
        }
        if (i < dim - 1) {
            ss << ' ';
        } else {
            ss << '\n';
        }
    }
    DLOG(INFO) << "------------------------------";
    DLOG(INFO) << "[DEBUG] " << 
        "the content of one-dimensional double array " << array_name << ": \n" <<
        ss.str();
    DLOG(INFO) << "------------------------------";
}

}
}
