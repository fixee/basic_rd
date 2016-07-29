#ifndef http_response_h
#define http_response_h

#include <string>
#include <map>

class HttpResponse{
public:
    HttpResponse():http_code(0){}
    ~HttpResponse(){}

public:
    long http_code;
    std::map<std::string, std::string> http_header;
    std::string body;

    std::string location;
    std::string err_msg;

private:
    
};

#endif//http_response_h
