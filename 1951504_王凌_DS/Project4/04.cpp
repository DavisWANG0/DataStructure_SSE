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
    T list[SIZE];//数组，用于存放栈的元素
    int top0;//栈顶位置（数组下标）
public:
    Stack();//构造函数，初始化栈
    void push(const T &item);//将元素item压入栈
    T pop();//将栈顶元素弹出栈
    void clear();//将栈清空
    const T &top() const;//访问栈顶元素
    bool empty() const;//测试是否栈满
    bool isFull() const;//测试是否栈空
    int size() const;//输出栈的大小
};
template <class T,int SIZE>
Stack<T,SIZE>::Stack():top0(-1){}//构造函数，栈顶初始化为-1
template <class T,int SIZE>
void Stack<T,SIZE>::push(const T &item)//将元素item压入栈 
{
    list[++top0]=item;//将新元素压入栈顶
}
template <class T,int SIZE>
T Stack<T,SIZE>::pop()//将栈顶元素弹出栈
{
    return list[top0--];//返回栈顶元素，并将其弹出栈顶
}
template <class T,int SIZE>
const T &Stack<T,SIZE>::top() const//访问栈顶元素 
{   
    return list[top0];//返回栈顶元素
} 
template <class T,int SIZE>
bool Stack<T,SIZE>::empty() const//测试栈是否空 
{    
    return top0==-1;//空的话返回1 
} 
template <class T,int SIZE>
bool Stack<T,SIZE>::isFull() const//测试是否栈满 
{ 
    return top0==SIZE-1;
}
template <class T,int SIZE>
void Stack<T,SIZE>::clear()//清空栈
{    
    top0=-1;
}
template <class T,int SIZE>
int Stack<T,SIZE>::size() const//输出栈的大小
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
bool isValid(const string &expr)//判断中缀表达式是否合理 
{
	//首先是括号匹配问题，需要用栈来记录括号的位置
	//如果不匹配将输出括号不匹配处的位置 
    int N=expr.length();
    Stack<int> s0;
    for(int i=1;i<N;i++)//在表达式之中搜索左右括号 
    {
    	if(expr[i-1]=='(') s0.push(i);//左括号位置进栈 
    	if(expr[i-1]==')')
    	{
    		if(s0.empty()==false) s0.pop();//栈不为空的时候 
    		else// if(s0.empty())
			  {
			  	cout<<"没有与第"<<i<<"个位置的右括号匹配的左括号！"<<endl; 
			  	return 0;
			  }
		}
	}
	while(!s0.empty())//栈中还有左括号 
	{
		cout<<"没有与第"<<s0.top()<<"个位置的左括号匹配的右括号！"<<endl;
		s0.pop(); 
		return 0; 
	}
    for(int i=0;i<N;i++)
    {
    	//排除法 
        if(expr[i]!='+'&&expr[i]!='-'&&expr[i]!='*'&&expr[i]!='/'&&expr[i]!='%'&&expr[i]!='^'&&expr[i]!='('&&expr[i]!=')'&&expr[i]!='='&&!(expr[i]<='9'&&expr[i]>='0')&&expr[i]!='.')
        {
            cout<<"表达式含有非法字符，注意必须在英文输入法下输入括号"<<endl;
            return 0;
        }
        if(expr[i]=='(' && i+1<N && expr[i+1]==')')//判断是否出现了连续的左右括号 
        {
            cout<<"出现了空括号()"<<endl;
            return 0;
        }
        if(expr[i]=='+' || expr[i]=='-')
            if(i==0 || expr[i-1]=='(')
            {
                if(!(i+1<N && ((expr[i+1]=='(') || (expr[i+1]<='9' && expr[i+1]>='0'))))
                {
                    cout<<"+-后面没有数字或者("<<endl;
                    return 0;
                }
            }
            //只有"i+1<N,并且左边是)或者数字,并且右边是(或者数字"这种情况是合理的，排除这种情况之后，其它情况是不合理的 
            else if(!(i+1<N && (expr[i-1]==')' || (expr[i-1]<='9'&&expr[i-1]>='0')) && ((expr[i+1]=='(')||(expr[i+1]<='9'&&expr[i+1]>='0'))))
            {
                cout<<"不合理的+-"<<endl;
                return 0;
            }
        if(expr[i]=='^' || expr[i]=='%' || expr[i]=='*' || expr[i]=='/')
        	//只有"i-1>=0,i+1<N,并且左边是)或者数字,并且右边是(或者数字"这种情况是合理的，排除这种情况之后，其它情况是不合理的
            if(!(i-1>=0 && i+1<N && ((expr[i-1]==')' || (expr[i-1]<='9'&&expr[i-1]>='0'))&& ((expr[i+1]=='(')||(expr[i+1]<='9'&&expr[i+1]>='0')))))
            {
                cout<<"不合理的*/^%"<<endl;
                return 0;
            }
        if(i==N-1 && expr[i]!='=')//判断最后一位是否是= 
        {
            cout<<"不以=结尾"<<endl;
            return 0;
        }
        if(i!=N-1 && expr[i]=='=')//判断除了最后一位还有没有其它位置出现= 
        {
            cout<<"表达式中出现了="<<endl;
            return 0;
        }
    }
	return 1;
}

Stack<int> num_stack;//数字栈 
int calculation(const string &expr)
{
    map<char,int> priority;//存储运算符的优先级
    priority['(']=1;
    priority['+']=2;priority['-']=2;
    priority['*']=3;priority['/']=3;
    priority['%']=4;priority['^']=5;
    Stack<char> sig;//存储运算符
    for(int i=0;i<expr.length()-1;i++)//不读空格 
    {
        //处理单目运算符
        bool f0=0;//记录数字的正负，等于0的时候为正 
        if((expr[i]=='+' || expr[i]=='-') && (i == 0 || expr[i - 1]=='('))//当+-被当做正负来用时 
            if(expr[i]!='+')//当-为符号时
            {
            	i++;//这个符号不压栈 
            	f0=1;//记录这个数为负数（记录f0=1）
			}
			else i++; 
        if(expr[i]<='9' && expr[i]>='0')//把字符串转换为数字 
        {
			int pos=i+1;//初始化，pos指向数字的第一位 
			while(1) 
			{
				if(pos<expr.length() && expr[pos]<='9' && expr[pos]>='0') pos++;
				else break;
			}
			int number=0;
			number=atoi(expr.substr(i,pos-i).c_str());//atoi是将字符串转化为整型数字 
            if(f0) number*=(-1);//如果-为负号，则让数字乘以负一 
            num_stack.push(number);
			i=pos-1;//更新已经操作到的字符数组的位置 
        }
        else if(expr[i]=='(') sig.push(expr[i]);//左括号直接压入 
        else if(expr[i]!=')')
        {
            if(sig.empty()) sig.push(expr[i]);//栈为空直接入栈 
            else
            {
                //与栈顶符号比较优先级
                int topStackPriority=priority[sig.top()];
                if(priority[expr[i]]>topStackPriority) sig.push(expr[i]);
                else
                {
                    //优先级小于等于前者,必将弹出之前所有大于等于他优先级的运算符,再加入这个运算符
                    while(!sig.empty() && priority[expr[i]]<=topStackPriority)
                    {
                        //a左,b右
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
        else if(expr[i]==')')//等于右括号的时候一直做到左括号处 
		        {
		        	int topStackPriority=priority[sig.top()];
		            while(!sig.empty() && priority[expr[i]]<=topStackPriority && sig.top()!='(')
                    {
                        topStackPriority=priority[sig.top()];
                        //a左,b右
			            int b=num_stack.top();
			            num_stack.pop();
			            int a=num_stack.top();
			            num_stack.pop();
				        num_stack.push(compute(sig.top(),a,b)); 
			            sig.pop();   
                    }
		            sig.pop();//把(弹出去
		        }
    }
    //当做到最后还有一个=号的时候，还需要把剩余没做完的做完 
	int topStackPriority=priority[sig.top()];
	while(!sig.empty() && priority['=']<=topStackPriority)
	{
		if(sig.top()!='=')
		{
		    topStackPriority=priority[sig.top()];
		    //a左,b右
			int b=num_stack.top();
			num_stack.pop();
			int a=num_stack.top();
			num_stack.pop();
			num_stack.push(compute(sig.top(),a,b));
		}
		sig.pop();   
    }    
    return num_stack.top();//最后剩下的值就是所求的值 
}

int main()
{
	while(true)
    {	
    	num_stack.clear();
		cout<<"输入表达式：(表达式中间,包括=符号之后都不能出现空格)"<<endl;
        string str="\n";
        cin.clear(); cin.sync();
        getline(cin,str);
        if(isValid(str))
            cout<<calculation(str)<<endl;
        cout<<"是否继续（y，n）？"<<endl;
        char isContinue;
        cin>>isContinue;
        while(isContinue!='y' && isContinue!='n')
        {
        	cout<<"没有这个选项，请重新输入（y，n）："<<endl;
			cin>>isContinue; 
		}
        if(isContinue=='n')	break;
    }
    system("pause"); 
    return 0;
} 
