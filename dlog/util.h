/**
* @file util.cpp
* @author Chong Niu <niuchong893184@gmail.com>
*/

#include <unistd.h>
#include <sstream>

extern char* __progname;

namespace dlog {
    
void get_curr_proc_info(std::string* pid, std::string* proc_name) {
    std::stringstream ss;
    ss << getpid();
    ss >> *pid;
    *proc_name = ::__progname;
}

}
