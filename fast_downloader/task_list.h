#ifndef task_list_h
#define task_list_h

class tasklist {
public:
    tasklist(){}
    ~tasklist(){}
public:
    void set_task( int val );
    int get_task( void );
    
private:
    pthread_cond_t _cond;
    pthread_mutex_t _mutex;
    list<int> _list;
};


#endif//task_list_h
