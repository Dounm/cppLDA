/**
* @file dlog.h
* @author Chong Niu <niuchong893184@gmail.com>
*/

#ifndef DLOG_DLOG_H
#define DLOG_DLOG_H

#include <pthread.h>

#include <fstream>
#include <string>

#define DCHECK_NOTNULL(ptr) dlog::check_ptr(ptr, __FILE__, __LINE__)
#define DCHECK(exp) dlog::LogMessage \
    (__FILE__, __LINE__, dlog::FATAL, !(exp)).stream()

#define DLOG(severity) DLOG_ ## severity.stream()
#define DLOG_INFO dlog::LogMessage \
    (__FILE__, __LINE__, dlog::INFO, true)
#define DLOG_WARNING dlog::LogMessage \
    (__FILE__, __LINE__, dlog::WARNING, true)
#define DLOG_ERROR dlog::LogMessage \
    (__FILE__, __LINE__, dlog::ERROR, true)
#define DLOG_FATAL dlog::LogMessage \
    (__FILE__, __LINE__, dlog::FATAL, true)

namespace dlog{
    
enum Severity {
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class LogMessage{
public:
    LogMessage(const char *file, int line, Severity sever, bool is_output);
    ~LogMessage();

    std::ofstream& stream() {
        return _stream;
    }

private:
    void init(const char *file, int line);

private:
    std::ofstream _stream;
    Severity _sever;
    bool _is_output;
    static pthread_mutex_t _s_write_lock;
    static std::string _s_info_logfile;
    static std::string _s_warning_logfile;
    static std::string _s_error_logfile;
    static std::string _s_fatal_logfile;
};

extern void check_ptr(void* ptr, const char* file, int line);

}

#endif
