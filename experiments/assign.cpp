#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

class Student{
public:
    
    Student(char* name,int id): id_(id),score_(0){
        name_ = new char[strlen(name)+1];
        strcpy(name_,name);

    }
    //拷贝构造
    Student(const Student& other){
        cout<< ">> 拷贝构造\n";
        name_ = new char[strlen(other.name_)+1];
        strcpy(name_,other.name_);
        id_ = other.id_;
        score_ = other.score_;
    }
    //移动构造
    Student(Student&& other){
        cout << ">>移动构造\n";
        name_ = other.name_;
         
        id_ = other.id_;
        score_=other.score_;
        other.name_ = nullptr;
    }
    //拷贝赋值
    Student& operator=(const Student& other){
        if(this == &other)  return *this;
        delete[] name_;
        name_ = new char[strlen(other.name_)+1];
        strcpy(name_,other.name_);
        id_ = other.id_;
        score_ = other.score_;
        return *this;
    }
    Student& operator=(Student&& other)noexcept{
        
        cout<<">>移动赋值\n";
        delete[] name_;
        name_=other.name_;
        id_ =other.id_;
        score_=other.score_;
        other.name_ = nullptr;
        return *this;
    }
    ~Student(){
        delete[] name_;
    }
    

    int get_score(int score){
        score_=score;

        return score_;
    }
    void print_score(){cout<<name_<<"的分数是："<<score_<<"\n";}
private:
    char* name_;
    int id_,score_;
    
};

/*int main(){
    
    int a;
    char name[100];
    int id;
    cout<<"请输入学生姓名和id\n";
    
    cin >>name>>id;
    Student s1(name,id);
    Student s2 =s1;
    s1.print_score();
    s2.print_score();
    while(true){
        cout<<"请选择功能：1.录入成绩  2.打印成绩  3.退出\n";
        cin >> a;
        if(a == 1){
            int score;
            cout<< "请输入成绩：";
            cin >> score;
            s1.get_score(score);

        }
        if(a==2){
            s1.print_score();
        }
        if(a == 3)
            break;
    }
    return 0;
}*/

   int main() {
      char n1[] = "多吉";
      char n2[] = "老王";

      Student s1(n1, 1);
      Student s2(n2, 2);
      s1.get_score(99);

      cout << "--- 测试1：拷贝赋值 ---\n";
      s2 = s1;
      cout << "s2: "; s2.print_score();      // 应打印 多吉 99

      cout << "--- 测试2：自赋值 ---\n";
      s2 = s2;
      cout << "s2: "; s2.print_score();      // 应打印 多吉 99

      cout << "--- 测试3：移动赋值 ---\n";
      Student s4(n2, 4);
      s4 = std::move(s1);
      cout << "s4: "; s4.print_score();      // 应打印 多吉 99

      return 0;
  }