/**
* @file dlog.cpp
* @author Chong Niu <niuchong893184@gmail.com>
*/

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "util.h"
#include "dlog.h"

namespace dlog{

void check_ptr(void* ptr, const char* file, int line) {
    if (ptr == NULL) {
        LogMessage(file, line, FATAL, true).stream() << "[DLOG][FATAL] pointer is NULL";
    }
}

pthread_mutex_t LogMessage::_s_write_lock;
std::string LogMessage::_s_info_logfile("");
std::string LogMessage::_s_warning_logfile("");
std::string LogMessage::_s_error_logfile("");
std::string LogMessage::_s_fatal_logfile("");

LogMessage::LogMessage(const char *file, int line, Severity sever, bool is_output) :
    _stream(), _sever(sever), _is_output(is_output) {

    pthread_mutex_lock(&_s_write_lock);
    if (_is_output == true) {
        init(file, line);
    }
}

LogMessage::~LogMessage() {
    _stream << std::endl;
    if (_is_output == true && _sever == FATAL) {
        exit(1);
    }
    pthread_mutex_unlock(&_s_write_lock);
}

//private func

void LogMessage::init(const char* file, int line) {
    time_t t = time(0);
    char tmp[100];
    strftime(tmp, sizeof(tmp), "%Y%m%d-%H%M%S", localtime(&t));

    if (_s_info_logfile == "") {
        std::string pid;
        std::string proc_name;
        get_curr_proc_info(&pid, &proc_name);

        _s_info_logfile = std::string("DLOG." + proc_name + 
            ".log.INFO." + tmp + "." + pid);
        _s_warning_logfile = std::string("DLOG." + proc_name + 
            ".log.WARNING." + tmp + "." + pid);
        _s_error_logfile = std::string("DLOG." + proc_name + 
            ".log.ERROR." + tmp + "." + pid);
        _s_fatal_logfile = std::string("DLOG." + proc_name + 
            ".log.FATAL." + tmp + "." + pid);
    }

    if (_sever == INFO) {
        _stream.open(_s_info_logfile.c_str(), std::ios::out | std::ios::app);
    } else if (_sever == WARNING) {
        _stream.open(_s_warning_logfile.c_str(), std::ios::out | std::ios::app);
    } else if (_sever == ERROR) {
        _stream.open(_s_error_logfile.c_str(), std::ios::out | std::ios::app);
    } else {
        _stream.open(_s_fatal_logfile.c_str(), std::ios::out | std::ios::app);
    }

    _stream << tmp << " " << file << " line " << line << ": ";
    _stream << std::flush;
}

}
