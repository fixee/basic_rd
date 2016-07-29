#include "Block.h"
#include <string.h>

Block::Block( char *data, int data_len )
{
    this->pos = 0;
    this->append_pos = 0;

    this->data = data;
    this->data_len = data_len;
}

bool Block::put_message( const char *data, int data_len )
{
    if( this->append_pos +  sizeof( data_len ) + data_len > this->data_len )
        return false;

    memcpy( this->data + this->append_pos, (void*)(&data_len), sizeof( data_len ) );
    memcpy( this->data + this->append_pos + sizeof( data_len ), data, data_len );

    this->append_pos += data_len + sizeof( data_len );

    return true;
}

bool Block::get_message( char **data, int *data_len )
{
    if( this->pos == this->append_pos )
        return false;

    int *len = (int*)(this->data + this->pos );
    if( *len > *data_len )
        return false;

    *data_len = *len;
    memcpy( (void*)(*data), (void*)( this->data + this->pos + sizeof( int ) ), *len );
    this->pos += *len + sizeof( int );

    return true;
}
