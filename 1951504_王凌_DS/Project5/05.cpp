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
    bool Empty();//�ж������Ƿ�Ϊ��                                           
    int GetLength();//���س���                           
    T GetData(int i);//���ص�i����������                                                                                       
    T ListDelete(int i);//ɾ����i�����                                                  
    bool ListInsertTail(Node<T> *pNode);//�ѽ������β                            
    void ClearLinkList();//������������н�� 
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
bool LinkList<T>::Empty()//���������Ƿ�Ϊ�� 
{
    return 0==Length;
}

template <typename T>
int LinkList<T>::GetLength()//���������� 
{
    return Length;
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

template <typename T>
T LinkList<T>::GetData(int i)//���ص�i������ֵ 
{
    if (i<0 || i>=Length)
    {
    	cout<<"λ�������������������"<<endl;
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
	cout<<"��������������˵ı��"<<endl; 
	int n;
	cin>>n;
	LinkList<int> listA,listB;
	for(int i=1;i<=n;i++)
	{
		int num;
		cin>>num;
		Node<int> temp;
		temp.data=num;
		if(num%2==1) listA.ListInsertTail(&temp);//���Ϊ������������A��β 
		else listB.ListInsertTail(&temp);//���Ϊż����������B��β 
	}
	while(!listA.Empty() || !listB.Empty())
	{
		if(!listA.Empty())
		{
			//Ϊ��ʹ�����һλ���ʱ�����ո�Ҫ��һ���жϣ���listA.GetLength()+listB.GetLength()�Ƿ�Ϊ1 
			//��Ϊ���Ȳ��Ǹ��������Ե�listA�ĳ��ȼ�listB�ĳ���Ϊ1��ʱ��˵����ʣ���һλû����� 
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

