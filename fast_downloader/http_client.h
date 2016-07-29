#ifndef http_client_h
#define http_client_h

#include <string>
#include <curl/curl.h>

#include "http_response.h"

typedef std::map<std::string, std::string> _kv;

class HttpClient{

public:
    const char *print_curl_version( void );
    const HttpResponse &Get( const std::string &url );
    const HttpResponse &Get( const std::string &url, const _kv &header );
    const HttpResponse &Post( const std::string &url, const _kv &header, const void *data );
    const HttpResponse &Put( const std::string &url, const _kv &header, const void *data );
private:
    static size_t writefunc( void *ptr, size_t size, size_t nmemb, std::string *str );
    static size_t writeheader( void *ptr, size_t size, size_t nmemb, std::map<std::string, std::string> *map );

private:
    _kv http_header;
};

#endif//http_client_h
