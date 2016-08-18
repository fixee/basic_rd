#ifndef config_h
#define config_h

#include <string>
#include <libconfig.h++>

class config_t {
private:
    libconfig::Config _config;
    config_t();

public:
    static config_t & get_instance();
    ~config_t();

    int load_config( const std::string & path );
    std::string get_string( const std::string & key );
};

#endif//config_h
