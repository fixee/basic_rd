/*
 * 要锻炼自己的网络编程的能力
 * .......
 *
 */

#include <iostream>
#include <string>
#include <bitset>
#include "MurmurHash3.h"
#include "BloomFilter.h"


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;

int main( int argc, char **argv )
{
    cout << "最大连接队列 :" << SOMAXCONN << endl;
    // 判断 大端 和 小端
    uint32_t x = 1;
    if( *( (char *)&x) == 0 )
        cout << "大端" << endl;
    else
        cout << "小端" << endl;

    x = htonl( x );
    if( *( (char *)&x) == 0 )
        cout << "大端" << endl;
    else
        cout << "小端" << endl;

    int ret;
    int fd = socket( AF_INET, SOCK_STREAM, 0 );

    struct sockaddr_in addr;   // Linux 下面端addr
    memset( &addr, 0, sizeof( addr ) );
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl( INADDR_ANY );
    addr.sin_port = htons( 8088 );

    ret = bind( fd, (struct sockaddr *)&addr, sizeof( addr ) );
    cout << ret << endl;
    ret = listen( fd, 1024 );    // 待连接缓冲区大小为 1024
    cout << ret << endl;

    struct sockaddr_in client_addr;
    int client;
    socklen_t client_addr_size;

    int count = 0;
    while( true )
    {
        memset( &client_addr, 0, sizeof( client_addr ) );
        client_addr_size = sizeof( client_addr );

        client = accept( fd, (struct sockaddr *)&client_addr, &client_addr_size );
        //write( client, "hello", 5 );
        cout << ++count << endl;

        //cout << client << endl;
        //ip = ntohl( client_addr.sin_addr.s_addr );
        //cout << ip << endl;
        //cout << ( ( ip >> 24 ) & 0xFF ) << "." << ( ( ip >> 16 ) & 0xFF ) << "." << ( ( ip >> 8 ) & 0xFF ) << "." << ( ip & 0xFF ) << endl;
        //cout << inet_ntoa( client_addr.sin_addr ) << endl;
        //cout << client_addr.sin_port << endl;
        close( client );
    }

    close( fd );
}
