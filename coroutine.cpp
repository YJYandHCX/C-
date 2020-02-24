#include "coroutine.h"

namespace coroutine{
	

coroutine_::coroutine_(int pid_id, void(*func1)() ){
        
		
		pid_id = id;
        
		cor_statue = running;
        
		getcontext(&child);
        
		child.uc_stack.ss_sp = st;
        
		child.uc_stack.ss_flags = 0;
        
		child.uc_stack.ss_size = sizeof(st);
        //设置child运行完做什么
		child.uc_link = &fat;

		//绑定函数
        makecontext(&child,func1,0);
}
cor_sch::cor_sch(){
            now_id = -1;
            cor_size = 0;
            getcontext(&main_u);
}

void coroutine_create(int id, void(*f)()){
	
    getcontext(&(cor_sch::c_d->main_u));
    //std::cout<<"I am OK"<<std::endl;
    
	//这里是清除上一个已经完成的协程
	if (cor_sch::c_d->now_id!=-1){

        int now = cor_sch::c_d->now_id;

        auto q = cor_sch::c_d->coroutines.find(now);
        if (q != cor_sch::c_d->coroutines.end()){
            cor_sch::c_d->coroutines.erase(q);
        }
        cor_sch::c_d->cor_size-=1;
        cor_sch::c_d->now_id = -1;
    }

	//如果给的id已经存在，那么放弃后边的行为
    if ((cor_sch::c_d->coroutines).count(id)!=0) return;
    
	//创建一个协程对象
	auto p = new coroutine_(id,f);

    (cor_sch::c_d->coroutines).insert({id,p});

    cor_sch::c_d->now_id = id;
    cor_sch::c_d->cor_size += 1;
	
	//开始运行协程的函数
    swapcontext(&(p->fat),&(p->child));

}
void coroutine_yield(){
    
	int id = cor_sch::c_d->now_id;
    
	if (id == -1) return;


    cor_sch::c_d->now_id = -1;
    auto p = cor_sch::c_d->coroutines.find(id);
    if (p == cor_sch::c_d->coroutines.end()) return;

    auto t = p->second;
    t->cor_statue = waiting;
    swapcontext(&(t->child),&(cor_sch::c_d->main_u));
}
void coroutine_resume(int id){
    if (cor_sch::c_d->now_id!=-1){

        int now = cor_sch::c_d->now_id;

        auto q = cor_sch::c_d->coroutines.find(now);
        if (q != cor_sch::c_d->coroutines.end()){
            cor_sch::c_d->coroutines.erase(q);
        }
        cor_sch::c_d->cor_size-=1;
        cor_sch::c_d->now_id = -1;
    }

    auto p = cor_sch::c_d->coroutines.find(id);
    if (p == cor_sch::c_d->coroutines.end()) return;


    //cout<<"PPPPPP"<<endl;
    auto t = p->second;
    t->cor_statue = running;
    cor_sch::c_d->now_id = id;

    swapcontext(&(t->fat),&(t->child));
}
std::vector<int> suspend_coroutines(){
    if (cor_sch::c_d->now_id!=-1){

        int now = cor_sch::c_d->now_id;

        auto q = cor_sch::c_d->coroutines.find(now);
        if (q != cor_sch::c_d->coroutines.end()){
            cor_sch::c_d->coroutines.erase(q);
        }
        cor_sch::c_d->cor_size-=1;
        cor_sch::c_d->now_id = -1;
    }
	//遍历这个哈希表里边存的协程，
    std::vector<int> res;
    for(auto i = cor_sch::c_d->coroutines.begin();i!=cor_sch::c_d->coroutines.end();i++){
        res.push_back(i->first);
    }
    return res;
}
void show_suspend_coroutines(){
    if (cor_sch::c_d->now_id!=-1){

        int now = cor_sch::c_d->now_id;

        auto q = cor_sch::c_d->coroutines.find(now);
        if (q != cor_sch::c_d->coroutines.end()){
            cor_sch::c_d->coroutines.erase(q);
        }
        cor_sch::c_d->cor_size-=1;
        cor_sch::c_d->now_id = -1;
    }

    for(auto i = cor_sch::c_d->coroutines.begin();i!=cor_sch::c_d->coroutines.end();i++){
        std::cout<<"id "<<(i->first)<<"is suspend"<<std::endl;;
    }
    return;

}
bool is_all_finished(){
	
	//清除完成了的协程
     if (cor_sch::c_d->now_id!=-1){

        int now = cor_sch::c_d->now_id;

        auto q = cor_sch::c_d->coroutines.find(now);
        if (q != cor_sch::c_d->coroutines.end()){
            cor_sch::c_d->coroutines.erase(q);
        }
        cor_sch::c_d->cor_size-=1;
        cor_sch::c_d->now_id = -1;
    }
	
	//如果调度器的中的cor——size 为 0那么就没有还没完成的了
    if (cor_sch::c_d->cor_size == 0) {
        std::cout<<"No coroutine working"<<std::endl;
        return true;
    }
    if (cor_sch::c_d->cor_size>=1){
        std::cout<<"There are coroutine are working"<<std::endl;
        return false;
    }

}

int give_avaliable_id(){
    
	int res = rand();
    //检查这一个id被用过没有，用过就再生成一个
	
	while(cor_sch::c_d->coroutines.count(res) != 0) res = rand();
    return res;

}
cor_sch* cor_sch::c_d = new cor_sch;
}
