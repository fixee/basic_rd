#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "http_client.h"
#include "http_response.h"

#include <sstream>

#include <aio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <pthread.h>
#include <list>
#include <set>

#include <time.h>
#include <boost/unordered_map.hpp>

using namespace std;

void test_http_client( void )
{
    HttpClient hc;
    cout << hc.print_curl_version() << endl;
    const HttpResponse& resp = hc.Get( "http://t.cn/RtMu74q" );

    cout << resp.http_code << endl;
    cout << resp.location << endl;
    cout << resp.err_msg << endl;
    //cout << resp.body << endl;

    auto it = resp.http_header.begin();
    for(; it != resp.http_header.end(); it++ )
        cout << it->first << ":" << it->second << endl;
}

void test_aio( const char *path )
{
    int fd, ret;
    struct aiocb my_cb;

    if( ( fd = open( path, O_RDONLY ) ) < 0 )
        return;

#define BUFF_SIZE 1024 * 1024 * 100

    memset( &my_cb, 0, sizeof( struct aiocb ) );
    my_cb.aio_buf = malloc( BUFF_SIZE + 1 );
    my_cb.aio_fildes = fd;
    my_cb.aio_nbytes = BUFF_SIZE;
    my_cb.aio_offset = 0;

    ret = aio_read( &my_cb );
    if( ret < 0 ) return;

    while( aio_error( &my_cb ) == EINPROGRESS );

    if( ( ret = aio_return( &my_cb ) ) <= 0 )
        return;

    cout << ret << endl;
}

void test_level_db( const char *path )
{
}

void *consumer( void *data )
{
    //tasklist *_tasklist = ( tasklist *)data;
    return NULL;
}

void *producer( void *data )
{
    return NULL;
}

void *thread_hello( void *data )
{
    int *id = ( int * )data;
    for( int i = 0; i < 1000; i++ )
        cout << *id << ":hello world:" << i << endl;

    return NULL;
}

void test_thread( void )
{
    static const int num = 100;

    pthread_t pid[num];
    int id[num];

    for( int i = 0; i < num; i++ )
    {
        id[i] = i;
        pthread_create( &pid[i], NULL, &thread_hello, &id[i] );
    }

    for( int i = 0; i < num; i++ )
        pthread_join( pid[i], NULL );
}

inline void str_replace( std::string &str, const std::string &pattern, const std::string &replace )
{
    if( pattern.empty() )
        return ;

    size_t pos = 0;
    while( ( pos = str.find( pattern, pos ) ) != std::string::npos )
    {
        str.replace( pos, pattern.size(), replace );
        pos += replace.size();
    }
}

void test_replace( string &orignal_url, int pid )
{
    typedef std::map<std::string, std::string> dict_t;
    static const dict_t rep_pid_3{ {"Sample_Cheetah_app_id","7QBzCW58"}, {"Sample_Cheetah_section_code","5486131"} };
    static const dict_t rep_pid_1{ {"Sample_Cheetah_app_id","YCa5b3c2c8"}, {"Sample_Cheetah_section_code","5486132"} }; 
    static const dict_t rep_default{ {"&app_id=Sample_Cheetah_app_id",""}, {"&sc=Sample_Cheetah_section_code",""} };

    const dict_t *repl = NULL;
    if( pid == 1 )
        repl = &rep_pid_1;
    else if( pid == 3 )
        repl = &rep_pid_3;
    else
        repl = &rep_default;

    for( auto it = repl->begin(); it != repl->end(); it++ )
        str_replace( orignal_url, it->first, it->second );
}

void strkey( const string& language, const string& country, const string &pid )
{
    static const int extra_key_size = 3 + strlen( "_last_modify_time" );

    string key;
    key.reserve( extra_key_size + language.size() + country.size() + pid.size() );
    key.append( language ).append( "_" ).append( country ).append( "_" ).append( pid ).append( "_last_modify_time" );
    cout << key << endl;
}

//class fallback_data_cache {
//public:
//    fallback_data_t *
//
//private:
//    boost::unordered_map<string, fallback_data_t> _data;
//};
//
//-----------------------------------------------------------------------------------------------------------------------

string _get_user_redis_conf_code( const string &pid, const string &uuid ) {

    int hash_count, hash_start, hash_index;
    char hash_char;
    string userlist( "userlist" );

    if( pid == "1" ) {   // pid == 1 表示 CM
        hash_count = 13;
        hash_start = 2;
    } else {
        hash_count = 2;
        hash_start = 0;
    }

    if( uuid.size() > 0 ) {
        hash_char = uuid[ uuid.size() - 1 ];
        if( hash_char >= 'A' && hash_char <= 'Z' )
            hash_char -= 'A';
        hash_index = hash_start + hash_char % hash_count;
    } else {
        hash_index = hash_start;
    }

    return userlist.append( to_string( static_cast<long long>( hash_index ) ) );
}

int main( int argc, char **argv )
{
    //test_aio( "/home/xiongfei/File/jdk-7u79-linux-x64.tar.gz" );
    //test_level_db( "db.db" );
    
    //string orignal_url( "http://finance.yahoo.com/news/orlando-massacre-shows-cracks-u-021122580.html?.gg_forward=true&app_id=Sample_Cheetah_app_id&sc=Sample_Cheetah_section_code" );
    //test_replace( orignal_url, 2 );
    //cout << orignal_url << endl;
    //
    
    //strkey( "aa", "bb", "cc" );
    //string a( "hello world" );
    //cout << a.append( to_string( 11 ) ) << endl;

    //boost::unordered_map<string, string> res;
    //cout << res["aa"] << endl;

    //cout << strlen( "_last_modify_time" ) << endl;
    //cout << time(NULL) << endl;
    //

    //map<string, int> a;
    //for( int i = 0; i < 100; i++ ) 
    //{
    //    int &b = a["hello" + to_string( i )];
    //    cout << b << endl;
    //}
    //cout << a.size() << endl;
    //

    //string a("hello " );
    //a.append( to_string( 1 ) );
    //cout << a << endl;

    string pid( "11" );
    string uuid( "11122" );
    string c = _get_user_redis_conf_code( pid, uuid );
    cout << c << endl;
    cout << c.size() << endl;
    
}
