#include<iostream>
#include <string>
using namespace std;
template<class T> class Node
{
public:
    T value;
    //�� ����Ů-���ֵ� �ķ�ʽ���洢���ṹ 
    Node<T> *NextSibling; 
    Node<T> *FirstChild;
    bool isDelete; 
    Node(T value):value(value),NextSibling(NULL),FirstChild(NULL),isDelete(0){}
};
template<class T>class Tree 
{
public:
    void add(T ancester)//������� 
    {
        root=new Node<T>(ancester);
    }
    void add(T familyName,T childName)
	//����ΪfamilyName�ĸ��������ӽڵ� 
    {
    	//�ÿյ�ǰ���λ�ú󣬴洢���ֽ�fatherName�Ľ���λ��
        currentNode=NULL;
        findName(root,familyName);
		//�ҵ��˸��ڵ�λ�ã�������currentNode֮�� 
        if(currentNode==NULL || currentNode->isDelete==1) return;
        Node<T> *curChild=currentNode->FirstChild;//���ڵ�ĳ��ӽڵ�
        if(curChild==NULL)//���û�г��ӣ����һ������ΪchildName�ĳ��� 
        {
            curChild=new Node<T>(childName);
            currentNode->FirstChild=curChild;
        }
        else
		//����Ѿ����˳��ӣ����ڳ��ӵ��ֵܽ��ĩβ��һ����ΪchildName���ֵ� 
        {
            Node<T> *x=curChild;//���ӽ�� 
            while(x->NextSibling!=NULL) x=x->NextSibling;
			//�ҵ����ӵ��ֵܽ�������ĩβ����ĩβ���½�� 
            x->NextSibling=new Node<T>(childName);
        }
    }

    void deleteName(T fatherName)
    //ɾ�����ڵ���ΪfamilyName��һ������ 
    //���Ӽ������Ƴ�familyName������������Ů 
    {
        //�ÿյ�ǰ���λ�ú󣬴洢���ֽ�fatherName�Ľ���λ�� 
		currentNode=NULL;
        findName(root,fatherName);
        if(currentNode==NULL || currentNode->isDelete==1) return;//û�ҵ��򷵻� 
        currentNode->isDelete=1;
        //����ֻ�к��ָ�룬û��ǰ��ָ�룬���Ըø��ڵ����ֱ��ɾ���Ļ���������ֵܽ��Ҳ�ᱻɾ��
		//������Ҫ��isDelete������¼���Ѿ��������У���Ŀ���ǲ�Ӱ�������������ֵܳ�Ա�Ķ�ȡ�����Բ���ֱ������ֱ�ӱ�ΪNULL 
        currentNode->FirstChild=NULL;//��Ů�����ֵ�����û��Ӱ�죬ֱ��ɾ�� 
  
    }
    void changeName(T preName,T curName)//���ļ�������ΪpreName������
    {
    	//�ÿյ�ǰ���λ�ú󣬴洢���ֽ�fatherName�Ľ���λ�� 
        currentNode=NULL;
        findName(root,preName);
        if(currentNode==NULL || currentNode->isDelete==1) return;//û�ҵ��򷵻� 
        Node<T> *cur=currentNode;
        cur->value=curName;
    }

    void display(T familyName)//չʾ����familyName��������Ů 
    {
		int N=0;//��Ů����,���û����������null 
		//�ÿյ�ǰ���λ�ú󣬴洢���ֽ�fatherName�Ľ���λ�� 
        currentNode=NULL;
        findName(root,familyName);
        if(currentNode== NULL || currentNode->isDelete==1) return;//û�ҵ��򷵻�
        for (Node<T> *temp=currentNode->FirstChild;temp!= NULL;temp=temp->NextSibling)
        {
            if(temp->isDelete!=1)//������û�б�ɾ�� 
            {
				++N;
                cout<<temp->value<<" ";
            }
        }
		if(N==0) cout<<"null"<<endl;
    }

    bool findName(T familyName)//�ж����ֽ�familyName�����Ƿ���� 
    {
    	//�ÿյ�ǰ���λ�ú󣬴洢���ֽ�fatherName�Ľ���λ�� 
        currentNode=NULL;
        findName(root,familyName);
        if(currentNode==NULL || currentNode->isDelete==1) return false;
        else return true;
    }

private:
    void findName(Node<T> *x,T familyName)
    //�ҵ����ֽ�familyName���˵�λ�ã��������λ�ô���currentNode�� 
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
	//��ǰ��㣬�����洢����familyName�Ľ���λ�� 
};
class Genealogy//��������� 
{
public:
    void process();
private:
    void buildFamily()
    {
		string fatherName;
        int childCount;
        cout<<"������Ҫ������ͥ���˵�����:";
        cin>>fatherName;
		if(familyTree.findName(fatherName))
		//�������ҵ����ڵ�λ�� 
		//���û���ҵ������޷���
		{
			cout<<"������"<<fatherName<<"�Ķ�Ů������";
			cin>>childCount;
			cout<<"����������"<<fatherName<<"�Ķ�Ů��������";
			string childName;
			for(int i=0;i<childCount;i++)
			{
				cin>>childName;
				familyTree.add(fatherName,childName);
			}
			cout<<fatherName<<"�ĵ�һ�������ǣ�";
			familyTree.display(fatherName);
		}
		else cout<<"���˲�����!"; 
	}
    void addChild()
    {
		cout<<"������Ҫ��Ӷ��ӣ���Ů�������˵�������";
        string fatherName;
        cin>>fatherName;
		if (familyTree.findName(fatherName))
		{
			cout<<"������"<<fatherName<<"����ӵĶ��ӣ���Ů������������";
			string childName;
			cin>>childName;
			familyTree.add(fatherName,childName);
			cout<<fatherName<<"�ĵ�һ�������ǣ�";
			familyTree.display(fatherName);
		}
		else cout<<"���˲�����!";
	}
    void breakFamily()
    {
		cout<<"������Ҫ��ɢ��ͥ���˵�������";
        string fatherName;
        cin>>fatherName;
        //ɾ������
        cout<<"Ҫ��ɢ��ͥ������"<<fatherName<<endl;
		if (familyTree.findName(fatherName))
		{
			cout<<fatherName<<"�ĵ�һ�������ǣ�";
			familyTree.display(fatherName);
			familyTree.deleteName(fatherName);
		}
		else cout<<"���˲�����!";
	}
    void editName()
    {
		cout<<"����������������˵�Ŀǰ������";
        string fatherName;
        cin>>fatherName;
		if(familyTree.findName(fatherName))
		{
			cout<<"��������ĺ��������";
			string changeName;
			cin>>changeName;
			cout<<fatherName<<"�Ѹ���Ϊ"<<changeName;
			familyTree.changeName(fatherName,changeName);
		}
		else cout<<"���˲�����!";
	}
    void searchName()
	{
		string fatherName;
        cout<<"������Ҫ��ѯ�˵�������";
        cin>>fatherName;
        if(familyTree.findName(fatherName))
        {
            cout<<fatherName<<"�ĵ�һ�������ǣ�";
            familyTree.display(fatherName);
        }
        else cout<<"���˲�����!";
	} 
	Tree<string> familyTree;
};

void Genealogy::process()
{
	cout<<"**            ���׹���ϵͳ              **"<<endl;
    cout<<"=========================================="<<endl;
    cout<<"**         ��ѡ��Ҫִ�еĲ���           **"<<endl;
    cout<<"**            A---���Ƽ���              **"<<endl;
    cout<<"**            B---��Ӽ�ͥ��Ա          **"<<endl;
    cout<<"**            C---��ɢ�ֲ���ͥ          **"<<endl;
    cout<<"**            D---���ļ�ͥ��Ա����      **"<<endl;
    cout<<"**            E---��ѯ����              **"<<endl;
    cout<<"**            F---�˳�����              **"<<endl;
    cout<<"=========================================="<<endl;
    
    string familyRoot;
    cout<<"���Ƚ���һ������!"<<endl;
    cout<<"���������ȵ�������"<<endl;
    cin>>familyRoot;
    familyTree.add(familyRoot);
    cout<<"�˼��׵������ǣ�"<<familyRoot<<endl;
    cout<<"��ѡ��Ҫִ�еĲ���:"<<endl;
    char ops;//���������Ӧ�ı��� 
    cin>>ops;
    while(true)
    {
    	switch(ops)//��Сд����ʶ�� 
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
            	cout<<"��Ч����,����������"<<endl<<endl;
            	break;
		}
        cout<<endl<<"��ѡ��Ҫִ�еĲ���:"<<endl;
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

