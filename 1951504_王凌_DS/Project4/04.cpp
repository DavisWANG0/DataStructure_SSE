#include<iostream>
#include<string.h>
#include<map> 
#include<stdlib.h>
#include<cmath>
using namespace std;
#define stacksize 10007
struct post_queue
{
	int num;
	char c;
};
template <class T,int SIZE=stacksize>
class Stack 
{
private:
    T list[SIZE];//���飬���ڴ��ջ��Ԫ��
    int top0;//ջ��λ�ã������±꣩
public:
    Stack();//���캯������ʼ��ջ
    void push(const T &item);//��Ԫ��itemѹ��ջ
    T pop();//��ջ��Ԫ�ص���ջ
    void clear();//��ջ���
    const T &top() const;//����ջ��Ԫ��
    bool empty() const;//�����Ƿ�ջ��
    bool isFull() const;//�����Ƿ�ջ��
    int size() const;//���ջ�Ĵ�С
};
template <class T,int SIZE>
Stack<T,SIZE>::Stack():top0(-1){}//���캯����ջ����ʼ��Ϊ-1
template <class T,int SIZE>
void Stack<T,SIZE>::push(const T &item)//��Ԫ��itemѹ��ջ 
{
    list[++top0]=item;//����Ԫ��ѹ��ջ��
}
template <class T,int SIZE>
T Stack<T,SIZE>::pop()//��ջ��Ԫ�ص���ջ
{
    return list[top0--];//����ջ��Ԫ�أ������䵯��ջ��
}
template <class T,int SIZE>
const T &Stack<T,SIZE>::top() const//����ջ��Ԫ�� 
{   
    return list[top0];//����ջ��Ԫ��
} 
template <class T,int SIZE>
bool Stack<T,SIZE>::empty() const//����ջ�Ƿ�� 
{    
    return top0==-1;//�յĻ�����1 
} 
template <class T,int SIZE>
bool Stack<T,SIZE>::isFull() const//�����Ƿ�ջ�� 
{ 
    return top0==SIZE-1;
}
template <class T,int SIZE>
void Stack<T,SIZE>::clear()//���ջ
{    
    top0=-1;
}
template <class T,int SIZE>
int Stack<T,SIZE>::size() const//���ջ�Ĵ�С
{
	return top0;
} 
int compute(char c,int a,int b)
{
	switch(c)
	{
		case '+':return(a+b);break;
		case '-':return(a-b);break;
		case '*':return(a*b);break;
		case '/':return(a/b);break;
		case '^':return(pow(a,b));break;
		case '%':return(((int)a)%((int)b));break;
		default:return 0;
	}
}
bool isValid(const string &expr)//�ж���׺���ʽ�Ƿ���� 
{
	//����������ƥ�����⣬��Ҫ��ջ����¼���ŵ�λ��
	//�����ƥ�佫������Ų�ƥ�䴦��λ�� 
    int N=expr.length();
    Stack<int> s0;
    for(int i=1;i<N;i++)//�ڱ��ʽ֮�������������� 
    {
    	if(expr[i-1]=='(') s0.push(i);//������λ�ý�ջ 
    	if(expr[i-1]==')')
    	{
    		if(s0.empty()==false) s0.pop();//ջ��Ϊ�յ�ʱ�� 
    		else// if(s0.empty())
			  {
			  	cout<<"û�����"<<i<<"��λ�õ�������ƥ��������ţ�"<<endl; 
			  	return 0;
			  }
		}
	}
	while(!s0.empty())//ջ�л��������� 
	{
		cout<<"û�����"<<s0.top()<<"��λ�õ�������ƥ��������ţ�"<<endl;
		s0.pop(); 
		return 0; 
	}
    for(int i=0;i<N;i++)
    {
    	//�ų��� 
        if(expr[i]!='+'&&expr[i]!='-'&&expr[i]!='*'&&expr[i]!='/'&&expr[i]!='%'&&expr[i]!='^'&&expr[i]!='('&&expr[i]!=')'&&expr[i]!='='&&!(expr[i]<='9'&&expr[i]>='0')&&expr[i]!='.')
        {
            cout<<"���ʽ���зǷ��ַ���ע�������Ӣ�����뷨����������"<<endl;
            return 0;
        }
        if(expr[i]=='(' && i+1<N && expr[i+1]==')')//�ж��Ƿ�������������������� 
        {
            cout<<"�����˿�����()"<<endl;
            return 0;
        }
        if(expr[i]=='+' || expr[i]=='-')
            if(i==0 || expr[i-1]=='(')
            {
                if(!(i+1<N && ((expr[i+1]=='(') || (expr[i+1]<='9' && expr[i+1]>='0'))))
                {
                    cout<<"+-����û�����ֻ���("<<endl;
                    return 0;
                }
            }
            //ֻ��"i+1<N,���������)��������,�����ұ���(��������"��������Ǻ���ģ��ų��������֮����������ǲ������ 
            else if(!(i+1<N && (expr[i-1]==')' || (expr[i-1]<='9'&&expr[i-1]>='0')) && ((expr[i+1]=='(')||(expr[i+1]<='9'&&expr[i+1]>='0'))))
            {
                cout<<"�������+-"<<endl;
                return 0;
            }
        if(expr[i]=='^' || expr[i]=='%' || expr[i]=='*' || expr[i]=='/')
        	//ֻ��"i-1>=0,i+1<N,���������)��������,�����ұ���(��������"��������Ǻ���ģ��ų��������֮����������ǲ������
            if(!(i-1>=0 && i+1<N && ((expr[i-1]==')' || (expr[i-1]<='9'&&expr[i-1]>='0'))&& ((expr[i+1]=='(')||(expr[i+1]<='9'&&expr[i+1]>='0')))))
            {
                cout<<"�������*/^%"<<endl;
                return 0;
            }
        if(i==N-1 && expr[i]!='=')//�ж����һλ�Ƿ���= 
        {
            cout<<"����=��β"<<endl;
            return 0;
        }
        if(i!=N-1 && expr[i]=='=')//�жϳ������һλ����û������λ�ó���= 
        {
            cout<<"���ʽ�г�����="<<endl;
            return 0;
        }
    }
	return 1;
}

Stack<int> num_stack;//����ջ 
int calculation(const string &expr)
{
    map<char,int> priority;//�洢����������ȼ�
    priority['(']=1;
    priority['+']=2;priority['-']=2;
    priority['*']=3;priority['/']=3;
    priority['%']=4;priority['^']=5;
    Stack<char> sig;//�洢�����
    for(int i=0;i<expr.length()-1;i++)//�����ո� 
    {
        //����Ŀ�����
        bool f0=0;//��¼���ֵ�����������0��ʱ��Ϊ�� 
        if((expr[i]=='+' || expr[i]=='-') && (i == 0 || expr[i - 1]=='('))//��+-��������������ʱ 
            if(expr[i]!='+')//��-Ϊ����ʱ
            {
            	i++;//������Ų�ѹջ 
            	f0=1;//��¼�����Ϊ��������¼f0=1��
			}
			else i++; 
        if(expr[i]<='9' && expr[i]>='0')//���ַ���ת��Ϊ���� 
        {
			int pos=i+1;//��ʼ����posָ�����ֵĵ�һλ 
			while(1) 
			{
				if(pos<expr.length() && expr[pos]<='9' && expr[pos]>='0') pos++;
				else break;
			}
			int number=0;
			number=atoi(expr.substr(i,pos-i).c_str());//atoi�ǽ��ַ���ת��Ϊ�������� 
            if(f0) number*=(-1);//���-Ϊ���ţ��������ֳ��Ը�һ 
            num_stack.push(number);
			i=pos-1;//�����Ѿ����������ַ������λ�� 
        }
        else if(expr[i]=='(') sig.push(expr[i]);//������ֱ��ѹ�� 
        else if(expr[i]!=')')
        {
            if(sig.empty()) sig.push(expr[i]);//ջΪ��ֱ����ջ 
            else
            {
                //��ջ�����űȽ����ȼ�
                int topStackPriority=priority[sig.top()];
                if(priority[expr[i]]>topStackPriority) sig.push(expr[i]);
                else
                {
                    //���ȼ�С�ڵ���ǰ��,�ؽ�����֮ǰ���д��ڵ��������ȼ��������,�ټ�����������
                    while(!sig.empty() && priority[expr[i]]<=topStackPriority)
                    {
                        //a��,b��
			            int b=num_stack.top();
			            num_stack.pop();
			            int a=num_stack.top();
			            num_stack.pop();
				        num_stack.push(compute(sig.top(),a,b));
			            sig.pop();   
			            topStackPriority=priority[sig.top()];
                    }
					sig.push(expr[i]);
                }
                
            }
        }
        else if(expr[i]==')')//���������ŵ�ʱ��һֱ���������Ŵ� 
		        {
		        	int topStackPriority=priority[sig.top()];
		            while(!sig.empty() && priority[expr[i]]<=topStackPriority && sig.top()!='(')
                    {
                        topStackPriority=priority[sig.top()];
                        //a��,b��
			            int b=num_stack.top();
			            num_stack.pop();
			            int a=num_stack.top();
			            num_stack.pop();
				        num_stack.push(compute(sig.top(),a,b)); 
			            sig.pop();   
                    }
		            sig.pop();//��(����ȥ
		        }
    }
    //�����������һ��=�ŵ�ʱ�򣬻���Ҫ��ʣ��û��������� 
	int topStackPriority=priority[sig.top()];
	while(!sig.empty() && priority['=']<=topStackPriority)
	{
		if(sig.top()!='=')
		{
		    topStackPriority=priority[sig.top()];
		    //a��,b��
			int b=num_stack.top();
			num_stack.pop();
			int a=num_stack.top();
			num_stack.pop();
			num_stack.push(compute(sig.top(),a,b));
		}
		sig.pop();   
    }    
    return num_stack.top();//���ʣ�µ�ֵ���������ֵ 
}

int main()
{
	while(true)
    {	
    	num_stack.clear();
		cout<<"������ʽ��(���ʽ�м�,����=����֮�󶼲��ܳ��ֿո�)"<<endl;
        string str="\n";
        cin.clear(); cin.sync();
        getline(cin,str);
        if(isValid(str))
            cout<<calculation(str)<<endl;
        cout<<"�Ƿ������y��n����"<<endl;
        char isContinue;
        cin>>isContinue;
        while(isContinue!='y' && isContinue!='n')
        {
        	cout<<"û�����ѡ����������루y��n����"<<endl;
			cin>>isContinue; 
		}
        if(isContinue=='n')	break;
    }
    system("pause"); 
    return 0;
} 
