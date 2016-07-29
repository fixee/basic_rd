#ifndef _block_h_
#define _block_h_

class Block{
private:
    int pos;
    int append_pos;

    char *data;
    int data_len;
    
public:
    Block( char *block_data, int data_len );
    ~Block();

    bool get_message( char **data, int *data_len );
    bool put_message( const char *data, int data_len );
};

struct block{
    int pos;
    char *data;
};

#endif//_block_h_
