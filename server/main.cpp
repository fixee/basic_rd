#include<iostream>
#include "Block.h"

using namespace std;

int main( int argc, char **argv )
{
    char *data = new char[4096];
    Block *block = new Block( data, 4096 );

    for( int i = 0; i < 100; i++ )
        block->put_message( "hello", 6 );

    char *buffer = new char[1024];
    int len = 1024;
    while( block->get_message( &buffer, &len ) )
    {
        cout << buffer << endl;
    }

    return 0;
}
