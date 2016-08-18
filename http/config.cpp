#include "config.h"

config_t::config_t() {
}

config_t::~config_t() {
}

config_t & config_t::get_instance() {
    static config_t _config;
    return _config;
}

int config_t::load_config( const std::string & path ) {
    try {
        _config.readFile( path.c_str() );
    } catch( const libconfig::FileIOException &fioex ) {
        return -1;
    } catch( const libconfig::ParseException &pex ) {
        return -1;
    }

    return 0;
}

std::string config_t::get_string( const std::string & key ) {
    std::string value;
    _config.lookupValue( key, value );

    return value;
}
