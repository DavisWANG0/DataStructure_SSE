#include<iostream>
using namespace std; 
template <typename T>
class Node
{
public:
    T data;
    Node<T>* next;
    Node(const T &value,Node<T> *next=NULL):data(value),next(next){}
    Node(Node<T> *next=NULL):next(next){}
};
template <typename T>
class LinkList
{
public:
	LinkList(); 
	~LinkList();         
	bool Empty();//判断链表是否为空                                                                                                                       
    T ListDelete(int i);//删除第i个结点                                                  
    bool ListInsertTail(Node<T> *pNode);//把结点插入队尾                            
    void ClearLinkList();//清空链表上所有结点 
    T getfirst();//得到第一个元素的值，即first->data 
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
bool LinkList<T>::Empty()//返回链表是否为空 
{
    return 0==Length;
}
template <typename T>
T LinkList<T>::getfirst()//得到第一个元素的值，即first->data 
{
	return List->next->data;
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
int main()
{
	LinkList<int> listA,listB;
    cout<<"输入两行数字（每行数字均以-1结尾）:"<<endl;
    int temp_input;//临时输入的值 
    bool second_bool=false;//有没有到第二个集合，即有没有出现第一个-1 
    while(cin>>temp_input)
    {
    	if(temp_input==-1 && second_bool) break;
		Node<int> tempNode(temp_input);
        if(temp_input==-1) second_bool=true;
        else if(!second_bool) listA.ListInsertTail(&tempNode);
		else if(second_bool) listB.ListInsertTail(&tempNode);
    }
    bool Print_bool=false;//记录有无输出，若无则说明无交集，输出NULL 
    while(!listA.Empty() && !listB.Empty())
    {
        if(listA.getfirst() < listB.getfirst()) listA.ListDelete(0);
        else if(listA.getfirst() > listB.getfirst()) listB.ListDelete(0);
        else
        {
            Print_bool=true;
            cout<<listA.getfirst()<<" ";
            listA.ListDelete(0);
        }
    }
    if(!Print_bool) cout<<"NULL";
    system("pause"); 
    return 0;
} 

