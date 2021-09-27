#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
template <class T> class Node//结点类 
{
public:
    T data;
    Node<T> *next;
	Node(const T &data,Node<T> *next=NULL):data(data),next(next){}
};
template<class T>class LinkList//链表类 
{
private:
    Node<T> *first;//头指针 
public:
    LinkList():first(NULL){}
    void insert(int pos,T t)//在第pos位前插入 
    {
        if(pos<=0)
        {
        	cout<<"请输入大于等于1的数字"<<endl;
        	int pos0;
			cin>>pos0;
			insert(pos0,t); 
            return;
        }
        else if(pos==1)//在链表头指针前加一个结点，特殊处理  
        {
        	Node<T> *temp=first;
        	first=new Node<T>(t,temp);
		}
        else
        {
            Node<T> *temp=first;
            for(int i=1;i<=pos-2;i++)//搜到插入位置pos前一个位置 
            {
                if(temp->next==NULL)
                {
                	cout<<"未找到该位置，请重新输入小于等于"<<i+1<<"的位置"<<endl;
                	int pos0;
					cin>>pos0;
					insert(pos0,t);  
                	return;
				}
                temp=temp->next;
            }
            Node<T> *newNode=new Node<T>(t,temp->next);
            temp->next=newNode;
        } 
    }
    void pop(const string &id0)//删除考号为id0的结点 
    {
    	if(first==NULL) 
    	{
    		cout<<"链表为空，无法进行删除操作"<<endl; 
			return; 
		}
        else if(id0==first->data.id)//删除头结点要特殊处理 
		{
			cout<<"你要删除的考生信息是:"<<first->data<<endl;
			Node<T> *temp=first;
			first=first->next;
			delete temp;//删除碎片 
		}
        else
        {
        	bool f0=0;
            for(Node<T> *x=first;x!=NULL;x=x->next)
            {
                if(x->next && x->next->data.id==id0)
                {
                	f0=1;
                    Node<T> *temp=x->next;
                    cout<<"你要删除的考生信息是:"<<temp->data<<endl;
                    x->next=x->next->next;
                    delete temp;//删除碎片 
                }
            }
            if(!f0) cout<<"未找到该考号，无法进行删除"<<endl; 
        }
        display();
    }
    void change(const string &id,int choice,string value)//改变考号为id的第choice个信息，改成value的值 
    {
        for(Node<T> *x=first;x!=NULL;x=x->next)
        {
            if(id==x->data.id)
            {
                switch(choice)
                {
                    case 1:
                        x->data.id=value;break;
                    case 2:
                        x->data.name=value;break;
                    case 3:
                        x->data.gender=value;break;
                    case 4:
                        x->data.age=atoi(value.c_str());break;//atoi表示ascii_to_integer，将字符串转换为整型数字 
                    case 5:
                        x->data.Application=value;break;
                    default:
						break;
                }
            }
        }
        display();
    }
    void search(const string &id)//只展示相关id 
    {
        cout<<endl<<"考号\t姓名\t性别\t年龄\t报考类别"<<endl;
        for(Node<T> *x=first;x!=NULL;x=x->next)
        {
            if(id==x->data.id)
            {
                cout<<x->data<<endl;
                return;
            }
        }
        cout<<"没有这个学生"<<endl;
    }
    void display()//全部展示 
    {
    	cout<<endl<<"考号\t姓名\t性别\t年龄\t报考类别"<<endl;
        for(Node<T> *x=first;x!=NULL;x=x->next) cout<<x->data<<endl;
    }

};
class Student//学生类 
{
public:
	Student(){} 
    Student(string &id0,string &name0,string &gender0,int age0,string &Application0):
    	id(id0),name(name0),gender(gender0),age(age0),Application(Application0){}//自定义赋值构造函数 
    friend istream &operator>>(istream &input,Student &student)//重载输入 
    {
    	input>>student.id>>student.name>>student.gender>>student.age>>student.Application;
    	return input;//为了能够连续输出，返回cout类 
	}
	friend ostream &operator<<(ostream &output, const Student &student)//重载输出 
    {
    	output<<student.id<<"\t"<<student.name<<"\t"<<student.gender<<"\t"<<student.age<<"\t"<<student.Application;
    	return output;//为了能够连续输出，返回cout类 
	}
    string id;
    string name;
    string gender;
    int age;
    string Application;//报考类别英文为Application_Type 
};

int main()
{
	cout<<"首先请建立考试信息系统!"<<endl;
    cout<<"首先输入考试人数：";
    int num;
    cin>>num;//输入学生人数
    while(num<0)
	{
		cout<<"请输入大于等于0的考生人数"<<endl;
		cin>>num; 
	} 
    cout<<"请依次输入考生的考号，姓名，性别，年龄和报考类别!"<<endl;
    LinkList<Student> studentList;
    for(int i=1;i<=num;i++)
    {
        string id,name,gender,Application;
        int age;
        Student student;
        cin>>student;
        studentList.insert(i,student);
    }
    studentList.display();
    cout<<"请选择你要进行的操作(1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作)"<<endl<<endl;
	bool is_continue=true;
    while(is_continue)
    {
        cout<<"请选择你要进行的操作：";
        int operatorCode;
        int pos;
        string id,name,gender,Application;
        int age;
        string value;
        Student student;
        cin>>operatorCode;
        switch(operatorCode)//1、2、3、4、5、0分别对应如上的操作 
        {
            case 1:
                cout<<"请输入你要插入的考生的位置：";
                cin>>pos;
                cout<<"请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！"<<endl;
                cin>>student;
                studentList.insert(pos,student);
                studentList.display();
                break;
            case 2:
                cout<<"请输入要删除的考生的考号：";
                cin>>id;
                studentList.pop(id);
                break;
            case 3:
                cout<<"请输入要查找的考生的考号：";
                cin>>id;
                studentList.search(id);
                break;
            case 4:
                cout<<"请输入要修改的考生的考号：";
                cin>>id;
                cout<<"请输入要修改的位置：";
                cin>>pos;
                cout<<"请输入要修改的值：";
                cin>>value;
                studentList.change(id,pos,value);
                break;
            case 5:
                studentList.display();
                break;
            case 0:
                is_continue=false;
                break;
            default:break;
        }
    }
    system("pause"); 
    return 0; 
}
