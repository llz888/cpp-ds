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
    Student(const Student& other){
        cout<< ">> 拷贝构造\n";
        name_ = new char[strlen(other.name_)+1];
        strcpy(name_,other.name_);
        id_ = other.id_;
        score_ = other.score_;
    }
    Student(Student&& other){
        cout << ">>移动构造\n";
        name_ = other.name_;
         
        id_ = other.id_;
        score_=other.score_;
        other.name_ = nullptr;
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
    vector<Student> v;
    char name[] = "多吉";
    for(int i = 0;i<5;++i)
        v.push_back(Student(name,i)); 
    cout << "vector 里现在有 " << v.size() << " 个元素\n";
    return 0;
  }