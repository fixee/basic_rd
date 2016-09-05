#include "file_utils.h"
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

bool file_utils::mk_dir( const string & dir_name )
{
    int ret = mkdir( dir_name.c_str(), 0755 );
    return ret == 0;
}

bool file_utils::is_dir( const string & dir_path )
{
    struct stat buff;
    stat( dir_path.c_str(), &buff );
    return S_ISDIR( buff.st_mode );
}

bool file_utils::is_file( const string & file_path )
{
    struct stat buff;
    stat( file_path.c_str(), &buff );
    return S_ISREG( buff.st_mode );
}

vector<string> file_utils::list_dir( const string & dir_path )
{
    vector<string> vec;
    DIR *p_dir = opendir( dir_path.c_str() );
    struct dirent *_ent = NULL;
    while( ( _ent = readdir( p_dir ) ) != NULL )
    {
        if( strcmp( _ent->d_name, "." ) == 0 || strcmp( _ent->d_name, ".." ) )
            continue;
        vec.push_back( _ent->d_name );
    }

    return vec;
}
