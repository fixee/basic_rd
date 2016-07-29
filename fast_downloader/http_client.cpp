#include "http_client.h"
#include <string.h>

size_t HttpClient::writefunc( void *ptr, size_t size, size_t nmemb, std::string *str )
{
    str->append( (char *)ptr, size * nmemb );
    return size*nmemb;
}

size_t HttpClient::writeheader( void *ptr, size_t size, size_t nmemb, std::map<std::string, std::string> *map )
{
    size_t length = size *nmemb;
    char *p1 = strchr( (char*)ptr, ':' );
    char *p2 = strstr( (char*)ptr, "\r\n" );
    if( p1 != NULL && p2 != NULL )
    {
        std::string key( (char *)ptr, (size_t)(p1 - (char *)ptr ) );
        std::string value( p1 + 1, (size_t)(p2 - p1 - 1 ) );
        map->insert( std::make_pair( key, value ) );
    }

    return length;
}

const char *HttpClient::print_curl_version( void )
{
    return curl_version(); 
}

const HttpResponse& HttpClient::Get( const std::string &url )
{
    CURL *curl = NULL;
    CURLcode res;
    HttpResponse *resp = new HttpResponse;
    char buffer[4096] = { 0 };

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt( curl, CURLOPT_URL, url.c_str() );
        curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt( curl, CURLOPT_HEADERFUNCTION, HttpClient::writeheader );
        curl_easy_setopt( curl, CURLOPT_HEADERDATA, &resp->http_header );
        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, HttpClient::writefunc );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, &(resp->body) );
             
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);

        curl_easy_getinfo( curl, CURLINFO_RESPONSE_CODE, &resp->http_code );
        if( CURLE_OK == curl_easy_getinfo( curl, CURLINFO_EFFECTIVE_URL, &buffer ) )
            resp->location = std::string((const char*)buffer);

        /* Check for errors */ 
        if(res != CURLE_OK)
            resp->err_msg = std::string( curl_easy_strerror( res ) );
             
        /* always cleanup */ 
        curl_easy_cleanup(curl);
    }

    return *resp;
}
