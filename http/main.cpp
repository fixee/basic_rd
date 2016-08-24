#include <iostream>
#include <hiredis/hiredis.h>
#include <evhtp.h>
#include <time.h>

#include "config.h"
#include <vector>
#include <map>
#include <logger.h>

using namespace std;

struct string_t{
    char *data;
    size_t data_len;
};

int process_body( evhtp_request_t * req )
{
    size_t data_len = evbuffer_get_length( req->buffer_in );
    string body;
    body.resize( data_len );

    if( evbuffer_copyout( req->buffer_in, &body[0], data_len ) == -1 ){
        return 0;
    }

    cout << body << endl;
    cout << body.size() << endl;

    return 0;
}

void build_filter_cb(evhtp_request_t * req, void * a)
{
    process_body( req );
    evbuffer_add(req->buffer_out, "foobar", 6);
    evhtp_send_reply(req, EVHTP_RES_OK);
}

void get_cb( evhtp_request_t *req, void *data )
{
};

int main( int argc, char **argv )
{
    int ret;

    ret = config_t::get_instance().load_config( "conf/server.conf" );
    cout << ret << endl;
    string value = config_t::get_instance().get_string( "server.ip" );
    cout << value << endl;

    //context = 
    //evbase_t * evbase = event_base_new();
    //evhtp_t  * htp    = evhtp_new(evbase, NULL);

    //evhtp_set_cb(htp, "/build", build_filter_cb, NULL);
    //evhtp_set_max_body_size( htp, 20 );

    //evhtp_bind_socket(htp, "0.0.0.0", 8081, 1024);
    //event_base_loop(evbase, 0);

    return 0;
}
