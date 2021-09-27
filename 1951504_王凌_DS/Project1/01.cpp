#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
template <class T> class Node//����� 
{
public:
    T data;
    Node<T> *next;
	Node(const T &data,Node<T> *next=NULL):data(data),next(next){}
};
template<class T>class LinkList//������ 
{
private:
    Node<T> *first;//ͷָ�� 
public:
    LinkList():first(NULL){}
    void insert(int pos,T t)//�ڵ�posλǰ���� 
    {
        if(pos<=0)
        {
        	cout<<"��������ڵ���1������"<<endl;
        	int pos0;
			cin>>pos0;
			insert(pos0,t); 
            return;
        }
        else if(pos==1)//������ͷָ��ǰ��һ����㣬���⴦��  
        {
        	Node<T> *temp=first;
        	first=new Node<T>(t,temp);
		}
        else
        {
            Node<T> *temp=first;
            for(int i=1;i<=pos-2;i++)//�ѵ�����λ��posǰһ��λ�� 
            {
                if(temp->next==NULL)
                {
                	cout<<"δ�ҵ���λ�ã�����������С�ڵ���"<<i+1<<"��λ��"<<endl;
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
    void pop(const string &id0)//ɾ������Ϊid0�Ľ�� 
    {
    	if(first==NULL) 
    	{
    		cout<<"����Ϊ�գ��޷�����ɾ������"<<endl; 
			return; 
		}
        else if(id0==first->data.id)//ɾ��ͷ���Ҫ���⴦�� 
		{
			cout<<"��Ҫɾ���Ŀ�����Ϣ��:"<<first->data<<endl;
			Node<T> *temp=first;
			first=first->next;
			delete temp;//ɾ����Ƭ 
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
                    cout<<"��Ҫɾ���Ŀ�����Ϣ��:"<<temp->data<<endl;
                    x->next=x->next->next;
                    delete temp;//ɾ����Ƭ 
                }
            }
            if(!f0) cout<<"δ�ҵ��ÿ��ţ��޷�����ɾ��"<<endl; 
        }
        display();
    }
    void change(const string &id,int choice,string value)//�ı俼��Ϊid�ĵ�choice����Ϣ���ĳ�value��ֵ 
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
                        x->data.age=atoi(value.c_str());break;//atoi��ʾascii_to_integer�����ַ���ת��Ϊ�������� 
                    case 5:
                        x->data.Application=value;break;
                    default:
						break;
                }
            }
        }
        display();
    }
    void search(const string &id)//ֻչʾ���id 
    {
        cout<<endl<<"����\t����\t�Ա�\t����\t�������"<<endl;
        for(Node<T> *x=first;x!=NULL;x=x->next)
        {
            if(id==x->data.id)
            {
                cout<<x->data<<endl;
                return;
            }
        }
        cout<<"û�����ѧ��"<<endl;
    }
    void display()//ȫ��չʾ 
    {
    	cout<<endl<<"����\t����\t�Ա�\t����\t�������"<<endl;
        for(Node<T> *x=first;x!=NULL;x=x->next) cout<<x->data<<endl;
    }

};
class Student//ѧ���� 
{
public:
	Student(){} 
    Student(string &id0,string &name0,string &gender0,int age0,string &Application0):
    	id(id0),name(name0),gender(gender0),age(age0),Application(Application0){}//�Զ��帳ֵ���캯�� 
    friend istream &operator>>(istream &input,Student &student)//�������� 
    {
    	input>>student.id>>student.name>>student.gender>>student.age>>student.Application;
    	return input;//Ϊ���ܹ��������������cout�� 
	}
	friend ostream &operator<<(ostream &output, const Student &student)//������� 
    {
    	output<<student.id<<"\t"<<student.name<<"\t"<<student.gender<<"\t"<<student.age<<"\t"<<student.Application;
    	return output;//Ϊ���ܹ��������������cout�� 
	}
    string id;
    string name;
    string gender;
    int age;
    string Application;//�������Ӣ��ΪApplication_Type 
};

int main()
{
	cout<<"�����뽨��������Ϣϵͳ!"<<endl;
    cout<<"�������뿼��������";
    int num;
    cin>>num;//����ѧ������
    while(num<0)
	{
		cout<<"��������ڵ���0�Ŀ�������"<<endl;
		cin>>num; 
	} 
    cout<<"���������뿼���Ŀ��ţ��������Ա�����ͱ������!"<<endl;
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
    cout<<"��ѡ����Ҫ���еĲ���(1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ������)"<<endl<<endl;
	bool is_continue=true;
    while(is_continue)
    {
        cout<<"��ѡ����Ҫ���еĲ�����";
        int operatorCode;
        int pos;
        string id,name,gender,Application;
        int age;
        string value;
        Student student;
        cin>>operatorCode;
        switch(operatorCode)//1��2��3��4��5��0�ֱ��Ӧ���ϵĲ��� 
        {
            case 1:
                cout<<"��������Ҫ����Ŀ�����λ�ã�";
                cin>>pos;
                cout<<"����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������"<<endl;
                cin>>student;
                studentList.insert(pos,student);
                studentList.display();
                break;
            case 2:
                cout<<"������Ҫɾ���Ŀ����Ŀ��ţ�";
                cin>>id;
                studentList.pop(id);
                break;
            case 3:
                cout<<"������Ҫ���ҵĿ����Ŀ��ţ�";
                cin>>id;
                studentList.search(id);
                break;
            case 4:
                cout<<"������Ҫ�޸ĵĿ����Ŀ��ţ�";
                cin>>id;
                cout<<"������Ҫ�޸ĵ�λ�ã�";
                cin>>pos;
                cout<<"������Ҫ�޸ĵ�ֵ��";
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
