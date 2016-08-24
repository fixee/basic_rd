#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <string>
#include <fstream>

class logger {
private:
    static logger *_logger;
    logger();

public:
    static logger &get_instance();
    ~logger();

public:
    bool init_logger( const std::string & conf );
    void print( const std::string & module, const char *msg );
    void print( const std::string & module, const std::string &msg );

private:
    bool inited;
    time_t last_modify;
    int last_year;
    int last_month;
    int last_day;
    int last_hour;
    char path[1024];
    char tm_prefix[1024];
    std::ofstream _log_file;
    std::string _dir;
    std::string _module;
};

#endif//LOGGER_H
