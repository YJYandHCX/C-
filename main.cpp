#include <iostream>
#include "coroutine.h"
using namespace std;

void f1r() {

    cout<<"I am id 1"<<endl;;
    coroutine::coroutine_yield();
    cout<<"id 1 is over"<<endl;
}
void f2r() {

    cout<<"I am id 2"<<endl;;

    coroutine::coroutine_yield();
    cout<<"id 2 is over"<<endl;
}

int main()
{
    //getcontext(&(cor_sch::c_d->main_u));
    //auto p = new coroutine_(1,f1r);

    coroutine::coroutine_create(1,f1r);
    coroutine::coroutine_create(2,f2r);
    cout<<"I am back"<<endl;

    coroutine::show_suspend_coroutines();
    cout<<"Will go to id 1"<<endl;
    coroutine::coroutine_resume(1);
    cout<<"will go to id 2"<<endl;
    coroutine::coroutine_resume(2);
    coroutine::show_suspend_coroutines();

    //swapcontext(&fat,&(p->child));
    //cout<<c_d->cor_size<<endl;
    //cout<<c_d->now_id<<endl;
    coroutine::is_all_finished();
    getchar();
    //cout<<t()<<endl;
    return 0;
}
