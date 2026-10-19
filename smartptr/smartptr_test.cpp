#include<iostream>
#include"myuniqueptr.hpp"
#include"mysharedptr.hpp"
#include"../queue/test_check.hpp"

using namespace std;


static int g_alive = 0;
static int g_dtor = 0;

struct Counted{
    Counted(){ ++g_alive;}
    ~Counted(){
        ++g_dtor;
        --g_alive;
    }
};
void reset_counters() { g_alive = 0; g_dtor = 0; }

void test_unique_dtor() {
    reset_counters();
    {
        MyUniquePtr<Counted> p(new Counted());
        CHECK(g_alive == 1);          // 新建了，活着
        CHECK(g_dtor  == 0);          // 还没死
    }                                  // ← 出作用域，p 析构
    CHECK(g_alive == 0);              // 对象死了
    CHECK(g_dtor  == 1);              // 而且恰好一次
}

void test_unique_move(){
    reset_counters();
    {
        MyUniquePtr<Counted> p(new Counted());
        CHECK(g_alive ==1);
        CHECK(g_dtor ==0);
        MyUniquePtr<Counted> q = move(p);
        CHECK(p.get() == nullptr);
        CHECK(g_dtor == 0);

    }
    CHECK(g_alive == 0);
    CHECK(g_dtor== 1);
}

void test_shared_count(){
    reset_counters();    
    MySharedPtr<Counted> p (new Counted());
    CHECK(g_alive == 1);
    CHECK(g_dtor == 0);
    {
        MySharedPtr<Counted> q = p;
        CHECK(g_alive ==1);
        CHECK(q.count() == 2);
    }
    CHECK(g_alive == 1);

}

void test_shared_last(){
    reset_counters();    
    {
        MySharedPtr<Counted> p(new Counted());
        {
            MySharedPtr<Counted> q = p;        // count 2
            CHECK(q.count() == 2);
        }                                       // ← q 先走
    CHECK(g_dtor == 0);                     // ★ 关键：还有 p 在，绝不能删
    CHECK(p.count() == 1);
    }                                           // ← p 最后走
    CHECK(g_dtor == 1);                         // ← 这时才删
}     

int main() {
    test_unique_dtor();
    test_unique_move();
    test_shared_count();
    test_shared_last();

    if (g_failures == 0) cout << "全部通过\n";
    else                 cout << g_failures << " 条失败\n";

    return g_failures == 0 ? 0 : 1;      // 给 CI 看的退出码
}