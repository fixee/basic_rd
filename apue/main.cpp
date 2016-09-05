#include <iostream>
#include <fcntl.h>
#include <errno.h>

using namespace std;

int main( int argc, char **argv )
{
    int fd = open( "aa", O_RDONLY );
}
