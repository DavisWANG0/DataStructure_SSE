#include<iostream>
#include <string>
using namespace std;
template<class T> class Node
{
public:
    T value;
    //用 左子女-右兄弟 的方式来存储树结构 
    Node<T> *NextSibling; 
    Node<T> *FirstChild;
    bool isDelete; 
    Node(T value):value(value),NextSibling(NULL),FirstChild(NULL),isDelete(0){}
};
template<class T>class Tree 
{
public:
    void add(T ancester)//存放祖先 
    {
        root=new Node<T>(ancester);
    }
    void add(T familyName,T childName)
	//给名为familyName的父结点添加子节点 
    {
    	//置空当前结点位置后，存储名字叫fatherName的结点的位置
        currentNode=NULL;
        findName(root,familyName);
		//找到了父节点位置，并存在currentNode之中 
        if(currentNode==NULL || currentNode->isDelete==1) return;
        Node<T> *curChild=currentNode->FirstChild;//父节点的长子节点
        if(curChild==NULL)//如果没有长子，则加一个名字为childName的长子 
        {
            curChild=new Node<T>(childName);
            currentNode->FirstChild=curChild;
        }
        else
		//如果已经有了长子，则在长子的兄弟结点末尾加一个名为childName的兄弟 
        {
            Node<T> *x=curChild;//长子结点 
            while(x->NextSibling!=NULL) x=x->NextSibling;
			//找到长子的兄弟结点链表的末尾，在末尾加新结点 
            x->NextSibling=new Node<T>(childName);
        }
    }

    void deleteName(T fatherName)
    //删除父节点名为familyName的一整棵树 
    //即从家谱中移除familyName和他的所有子女 
    {
        //置空当前结点位置后，存储名字叫fatherName的结点的位置 
		currentNode=NULL;
        findName(root,fatherName);
        if(currentNode==NULL || currentNode->isDelete==1) return;//没找到则返回 
        currentNode->isDelete=1;
        //由于只有后继指针，没有前驱指针，所以该父节点如果直接删除的话，后面的兄弟结点也会被删除
		//所以需要用isDelete变量记录它已经不在树中，其目的是不影响链表上其它兄弟成员的读取，所以不能直接让它直接变为NULL 
        currentNode->FirstChild=NULL;//子女结点对兄弟链表没有影响，直接删除 
  
    }
    void changeName(T preName,T curName)//更改家谱中名为preName的姓名
    {
    	//置空当前结点位置后，存储名字叫fatherName的结点的位置 
        currentNode=NULL;
        findName(root,preName);
        if(currentNode==NULL || currentNode->isDelete==1) return;//没找到则返回 
        Node<T> *cur=currentNode;
        cur->value=curName;
    }

    void display(T familyName)//展示名叫familyName的所有子女 
    {
		int N=0;//子女个数,如果没有输出则输出null 
		//置空当前结点位置后，存储名字叫fatherName的结点的位置 
        currentNode=NULL;
        findName(root,familyName);
        if(currentNode== NULL || currentNode->isDelete==1) return;//没找到则返回
        for (Node<T> *temp=currentNode->FirstChild;temp!= NULL;temp=temp->NextSibling)
        {
            if(temp->isDelete!=1)//这个结点没有被删除 
            {
				++N;
                cout<<temp->value<<" ";
            }
        }
		if(N==0) cout<<"null"<<endl;
    }

    bool findName(T familyName)//判断名字叫familyName的人是否存在 
    {
    	//置空当前结点位置后，存储名字叫fatherName的结点的位置 
        currentNode=NULL;
        findName(root,familyName);
        if(currentNode==NULL || currentNode->isDelete==1) return false;
        else return true;
    }

private:
    void findName(Node<T> *x,T familyName)
    //找到名字叫familyName的人的位置，并将这个位置存在currentNode中 
    {
        if(x==NULL) return;
        if(x->value==familyName)
        {
            currentNode=x;
            return;
        }
        findName(x->FirstChild,familyName);
        for(Node<T> *temp=x->NextSibling;temp!=NULL;temp=temp->NextSibling) findName(temp,familyName);
    }
    Node<T> *root;
    Node<T> *currentNode;
	//当前结点，用来存储名字familyName的结点的位置 
};
class Genealogy//定义家谱类 
{
public:
    void process();
private:
    void buildFamily()
    {
		string fatherName;
        int childCount;
        cout<<"请输入要建立家庭的人的姓名:";
        cin>>fatherName;
		if(familyTree.findName(fatherName))
		//必须先找到父节点位置 
		//如果没有找到，则无法加
		{
			cout<<"请输入"<<fatherName<<"的儿女人数：";
			cin>>childCount;
			cout<<"请依次输入"<<fatherName<<"的儿女的姓名：";
			string childName;
			for(int i=0;i<childCount;i++)
			{
				cin>>childName;
				familyTree.add(fatherName,childName);
			}
			cout<<fatherName<<"的第一代子孙是：";
			familyTree.display(fatherName);
		}
		else cout<<"该人不存在!"; 
	}
    void addChild()
    {
		cout<<"请输入要添加儿子（或女儿）的人的姓名：";
        string fatherName;
        cin>>fatherName;
		if (familyTree.findName(fatherName))
		{
			cout<<"请输入"<<fatherName<<"新添加的儿子（或女儿）的姓名：";
			string childName;
			cin>>childName;
			familyTree.add(fatherName,childName);
			cout<<fatherName<<"的第一代子孙是：";
			familyTree.display(fatherName);
		}
		else cout<<"该人不存在!";
	}
    void breakFamily()
    {
		cout<<"请输入要解散家庭的人的姓名：";
        string fatherName;
        cin>>fatherName;
        //删除操作
        cout<<"要解散家庭的人是"<<fatherName<<endl;
		if (familyTree.findName(fatherName))
		{
			cout<<fatherName<<"的第一代子孙是：";
			familyTree.display(fatherName);
			familyTree.deleteName(fatherName);
		}
		else cout<<"该人不存在!";
	}
    void editName()
    {
		cout<<"请输入更改姓名的人的目前姓名：";
        string fatherName;
        cin>>fatherName;
		if(familyTree.findName(fatherName))
		{
			cout<<"请输入更改后的姓名：";
			string changeName;
			cin>>changeName;
			cout<<fatherName<<"已更名为"<<changeName;
			familyTree.changeName(fatherName,changeName);
		}
		else cout<<"该人不存在!";
	}
    void searchName()
	{
		string fatherName;
        cout<<"请输入要查询人的姓名：";
        cin>>fatherName;
        if(familyTree.findName(fatherName))
        {
            cout<<fatherName<<"的第一代子孙是：";
            familyTree.display(fatherName);
        }
        else cout<<"该人不存在!";
	} 
	Tree<string> familyTree;
};

void Genealogy::process()
{
	cout<<"**            家谱管理系统              **"<<endl;
    cout<<"=========================================="<<endl;
    cout<<"**         请选择要执行的操作           **"<<endl;
    cout<<"**            A---完善家谱              **"<<endl;
    cout<<"**            B---添加家庭成员          **"<<endl;
    cout<<"**            C---解散局部家庭          **"<<endl;
    cout<<"**            D---更改家庭成员姓名      **"<<endl;
    cout<<"**            E---查询家谱              **"<<endl;
    cout<<"**            F---退出程序              **"<<endl;
    cout<<"=========================================="<<endl;
    
    string familyRoot;
    cout<<"首先建立一个家谱!"<<endl;
    cout<<"请输入祖先的姓名："<<endl;
    cin>>familyRoot;
    familyTree.add(familyRoot);
    cout<<"此家谱的祖先是："<<familyRoot<<endl;
    cout<<"请选择要执行的操作:"<<endl;
    char ops;//各项操作对应的编码 
    cin>>ops;
    while(true)
    {
    	switch(ops)//大小写都能识别 
		{
            case 'A':
            case 'a':
                buildFamily();
                break;
            case 'B':
            case 'b':
                addChild();
                break;
            case 'C':
            case 'c':
                breakFamily();
                break;
            case 'D':
            case 'd':
                editName();
                break;
            case 'E':
            case 'e':
                searchName();
                break;
            case 'F':
            case 'f':
            	break;
            default:
            	cout<<"无效操作,请重新输入"<<endl<<endl;
            	break;
		}
        cout<<endl<<"请选择要执行的操作:"<<endl;
        cin>>ops;
    }
}
int main()
{
    Genealogy jiapu;
    jiapu.process();
    system("pause"); 
    return 0;
}

