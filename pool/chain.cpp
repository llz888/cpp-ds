#include <iostream>
using namespace std;
struct FreeNode{
    FreeNode* next;
};

int main() {
    char* mem = new char[32 * 3];     // ① 申请 96 字节
    FreeNode* head = nullptr;
    char* p = mem;
    for(int i = 0;i<3;++i){
        FreeNode* node = (FreeNode*) p;
        node->next = head;
        head = node;
        p += 32;

    }
    for(FreeNode* n=head;n!=nullptr;n=n->next)
        cout << (void*)n<<'\n';

    delete[] mem;                     // ③ 还掉
    return 0;
}