#include <iostream>
#include "logger.h"
#include "config.h"

logger* logger::_logger = new logger();

logger& logger::get_instance(){
    return *_logger;
}

logger::logger() : inited( false ), last_modify( 0 ), last_year( 0 ), 
    last_month( 0 ), last_day( 0 ), last_hour( 0 ){
}

logger::~logger(){
}

bool logger::init_logger( const std::string & conf ){
    config_t &config = config_t::get_instance();
    config.load_config( conf );

    inited = true;
    return inited == true;
}

void logger::print( const std::string & module, const std::string &msg )
{
    if( !inited ) return;

    time_t current = time( NULL );
    if( current - last_modify > 1 ){
        // 取年月日小时作为suffix
        struct tm *tm_local = localtime( &current );
        if( tm_local->tm_hour  != last_hour  ||
            tm_local->tm_mday  != last_day   ||
            tm_local->tm_mon   != last_month ||
            tm_local->tm_year  != last_year ){
            last_year  = tm_local->tm_year;
            last_month = tm_local->tm_mon;
            last_day   = tm_local->tm_mday;
            last_hour  = tm_local->tm_hour;
            snprintf( path, 1024, "%s/%s-%04d%02d%02d%02d.log", 
                    _dir.c_str(), _module.c_str(), last_year + 1900, last_month + 1, last_day, last_hour );
            _log_file.open( path, std::ios::app );
        }

        snprintf( tm_prefix, 1024, "[%s] [%04d-%02d-%02d %02d:%02d:%02d] | ", 
                _module.c_str(),
                tm_local->tm_year + 1900,
                tm_local->tm_mon  + 1,
                tm_local->tm_mday,
                tm_local->tm_hour,
                tm_local->tm_min,
                tm_local->tm_sec );
    }

    _log_file << tm_prefix << msg << std::endl;
}
