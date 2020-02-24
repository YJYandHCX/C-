#ifndef LEAKDETECTOR_H_INCLUDED
#define LEAKDETECTOR_H_INCLUDED

#include <iostream>
#include <vector>
#include <functional>
#include <ucontext.h>
#include <unordered_map>
#define COROUTINE_STACK_SIZE 8096
//如果需要修改协程栈的大小，在这里修改



namespace coroutine{

enum state {running = 0,waiting = 1};

//协程类
class coroutine_{
public:
    ucontext_t fat,child;
	
    char st[COROUTINE_STACK_SIZE];
	
    state cor_statue;
    
	coroutine_(int pid_id, void(*func1)() );
    
	private:
    
	int id;

};

//线程调度器，使用单例模式，饿汉模式
class cor_sch{
    public:
    
		std::unordered_map<int,coroutine_*> coroutines;
        
		int now_id;
        
		int cor_size;
        
		ucontext_t main_u;
        
		static cor_sch* c_d;

    private:
        cor_sch();
};

//用于创建协程
void coroutine_create(int id, void(*f)());

//挂起协程
void coroutine_yield();

//恢复协程
void coroutine_resume(int id);

//返回所有挂起的协程的id
std::vector<int> suspend_coroutines();

//显示所有挂起的协程id
void show_suspend_coroutines();

//是否还有协程没有完成
bool is_all_finished();

//返回一个没有用过的id数字
int give_avaliable_id();
}
#endif // LEAKDETECTOR_H_INCLUDED
