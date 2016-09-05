#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

using namespace std;

class file_utils{
public:
    static bool mk_dir( const string & dir_name );
    static bool is_dir( const string & dir_path );
    static bool is_file( const string & file_path );
    static vector<string> list_dir( const string & dir_path );
};

#endif//FILE_UTILS_H
