#include<iostream>
using namespace std; 
template <typename T>
class Node
{
public:
    T data;
    Node<T>* next;
};
template <typename T>
class LinkList
{
public:
	LinkList(); 
	~LinkList();                                               
    bool Empty();//判断链表是否为空                                           
    int GetLength();//返回长度                           
    T GetData(int i);//返回第i个结点的数据                                                                                       
    T ListDelete(int i);//删除第i个结点                                                  
    bool ListInsertTail(Node<T> *pNode);//把结点插入队尾                            
    void ClearLinkList();//清空链表上所有结点 
private:
    Node<T>* List;//链表 
    int Length;//长度 
};

template <typename T>
LinkList<T>::LinkList()//自定义构造函数 
{
    List=new Node<T>;
    List->next=NULL;
    Length=0;
}
template <typename T>
LinkList<T>::~LinkList()//自定义析构函数 
{
    ClearLinkList();
    delete List;
    List=NULL;
}
template <typename T>
void LinkList<T>::ClearLinkList()//删除链表上所有结点 
{
    Node<T>* currentNode=List->next;
    while(currentNode!=NULL)
    {
        Node<T>* temp=currentNode->next;
        delete currentNode;
        currentNode=temp;
    }
    List->next=NULL;
}

template <typename T>
bool LinkList<T>::Empty()//返回链表是否为空 
{
    return 0==Length;
}

template <typename T>
int LinkList<T>::GetLength()//返回链表长度 
{
    return Length;
}
template <typename T>
bool LinkList<T>::ListInsertTail(Node<T> *pNode)//插入队尾 
{
    Node<T>* currentNode=List;
    while (currentNode->next!=NULL)	currentNode=currentNode->next;
    Node<T>* newNode=new Node<T>;
    newNode->data=pNode->data;
    newNode->next=NULL;
    currentNode->next=newNode;
    Length++;
    return 1;
}

template <typename T>
T LinkList<T>::ListDelete(int i)//删除第i个结点 
{
    if(i<0 || i>=Length)
    {
    	cout<<"位置输入错误，请重新输入"<<endl;
		int i0;
		cin>>i0;
		ListDelete(i0);
        return false;
    }
    Node<T>* currentNode=List;
    Node<T>* currentNodeBefore=NULL;
    for (int k=0;k<=i;k++)
    {
        currentNodeBefore=currentNode;
        currentNode=currentNode->next;
    }
    currentNodeBefore->next=currentNode->next;
    T temp=currentNode->data;
    delete currentNode;
    currentNode=NULL;
    Length--;
    return temp;
}

template <typename T>
T LinkList<T>::GetData(int i)//返回第i个结点的值 
{
    if (i<0 || i>=Length)
    {
    	cout<<"位置输入错误，请重新输入"<<endl;
		int i0;
		cin>>i0;
		GetData(i0); 
        return false;
    }
    Node<T>* currentNode=List;
    for (int k=0;k<=i;k++)
        currentNode=currentNode->next;
    return currentNode->data;
}
int main()
{
	cout<<"输入人数及其各人的编号"<<endl; 
	int n;
	cin>>n;
	LinkList<int> listA,listB;
	for(int i=1;i<=n;i++)
	{
		int num;
		cin>>num;
		Node<int> temp;
		temp.data=num;
		if(num%2==1) listA.ListInsertTail(&temp);//编号为奇数插入链表A队尾 
		else listB.ListInsertTail(&temp);//编号为偶数插入链表B队尾 
	}
	while(!listA.Empty() || !listB.Empty())
	{
		if(!listA.Empty())
		{
			//为了使得最后一位输出时不带空格要加一个判断，即listA.GetLength()+listB.GetLength()是否为1 
			//因为长度不是负数，所以当listA的长度加listB的长度为1的时候说明还剩最后一位没有输出 
			if(listA.GetLength()+listB.GetLength()==1) cout<<listA.GetData(0);
			else cout<<listA.GetData(0)<<" ";
			listA.ListDelete(0);
		}
		if(!listA.Empty())
		{
			if(listA.GetLength()+listB.GetLength()==1) cout<<listA.GetData(0);
			else cout<<listA.GetData(0)<<" ";
			listA.ListDelete(0);
		}
		if(!listB.Empty())
		{
			if(listA.GetLength()+listB.GetLength()==1) cout<<listB.GetData(0);
			else cout<<listB.GetData(0)<<" ";
			listB.ListDelete(0);
		}
	}
	system("pause"); 
	return 0; 
} 

