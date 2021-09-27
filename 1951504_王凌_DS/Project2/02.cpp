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
	bool Empty();//�ж������Ƿ�Ϊ��                                                                                                                       
    T ListDelete(int i);//ɾ����i�����                                                  
    bool ListInsertTail(Node<T> *pNode);//�ѽ������β                            
    void ClearLinkList();//������������н�� 
    T getfirst();//�õ���һ��Ԫ�ص�ֵ����first->data 
private:
    Node<T>* List;//���� 
    int Length;//���� 
};
template <typename T>
LinkList<T>::LinkList()//�Զ��幹�캯�� 
{
    List=new Node<T>;
    List->next=NULL;
    Length=0;
}
template <typename T>
LinkList<T>::~LinkList()//�Զ����������� 
{
    ClearLinkList();
    delete List;
    List=NULL;
}
template <typename T>
bool LinkList<T>::Empty()//���������Ƿ�Ϊ�� 
{
    return 0==Length;
}
template <typename T>
T LinkList<T>::getfirst()//�õ���һ��Ԫ�ص�ֵ����first->data 
{
	return List->next->data;
}
template <typename T>
void LinkList<T>::ClearLinkList()//ɾ�����������н�� 
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
bool LinkList<T>::ListInsertTail(Node<T> *pNode)//�����β 
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
T LinkList<T>::ListDelete(int i)//ɾ����i����� 
{
    if(i<0 || i>=Length)
    {
    	cout<<"λ�������������������"<<endl;
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
    cout<<"�����������֣�ÿ�����־���-1��β��:"<<endl;
    int temp_input;//��ʱ�����ֵ 
    bool second_bool=false;//��û�е��ڶ������ϣ�����û�г��ֵ�һ��-1 
    while(cin>>temp_input)
    {
    	if(temp_input==-1 && second_bool) break;
		Node<int> tempNode(temp_input);
        if(temp_input==-1) second_bool=true;
        else if(!second_bool) listA.ListInsertTail(&tempNode);
		else if(second_bool) listB.ListInsertTail(&tempNode);
    }
    bool Print_bool=false;//��¼���������������˵���޽��������NULL 
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

