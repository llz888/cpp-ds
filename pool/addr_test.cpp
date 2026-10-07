#include <iostream>
using namespace std;

int main() {
    // ============ 实验 1：同一段内存，两种解释 ============
    char* buf = new char[4];          // 4 个字节。注意：它现在"什么都不是"
    *(int*)buf = 0x44434241;          // 往这 4 个字节里写一个 int
    cout << "写成 int 看：  " << *(int*)buf << "   （十进制，不重要）\n";
    cout << "写成 char 看： " << buf[0] << buf[1] << buf[2] << buf[3] << "\n";
    delete[] buf;

    // ============ 实验 2：把一段地址当成「装指针的格子」 ============
    char* mem = new char[16];
    void** slot = (void**)(mem + 8);  // mem 往后数 8 个字节，当成一个「能装指针的格子」
    *slot = mem;                      // 往那个格子里存一个指针

    cout << "存进去的：  " << *slot << "\n";
    cout << "mem 自己：  " << (void*)mem << "\n";
    delete[] mem;
}