#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

typedef void *(* TaskFunc)( void * );

typedef struct _task {
    TaskFunc f;
    void *data;
} task_t;

class tasklist{
public:
    task_t *get_task();
    void add_task( TaskFunc f, void *data );
};

typedef struct _ctrl {
    bool running;
} ctrl_t;

void* hello( void* data )
{
    ctrl_t *ctrl = (ctrl_t *)data;

    while( ctrl->running )
    {
        cout << "hello world" << endl;
    }

    return NULL;
}

void test_pthread( void )
{
    pthread_t pid;
    ctrl_t _ctr;
    _ctr.running = true;

    pthread_create( &pid, NULL, &hello, &_ctr );

    sleep(1);
}

int main( int argc, char **argv )
{
    test_pthread();

    return 0;
}
