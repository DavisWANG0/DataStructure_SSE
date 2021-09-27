#include<iostream>
using namespace std;
#define stacksize 10007
void assert(bool num)//声明:报错 
{
	if(num==0)	cout<<"错误"<<endl; 
}
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
};
template <class T,int SIZE>
Stack<T,SIZE>::Stack():top0(-1){}//构造函数，栈顶初始化为-1
template <class T,int SIZE>
void Stack<T,SIZE>::push(const T &item)//将元素item压入栈 
{
    assert(!isFull());//如果栈满了，则报错
    list[++top0]=item;//将新元素压入栈顶
}
template <class T,int SIZE>
T Stack<T,SIZE>::pop()//将栈顶元素弹出栈
{
    assert(!empty());//如果栈为空，则报错
    return list[top0--];//返回栈顶元素，并将其弹出栈顶
}
template <class T,int SIZE>
const T &Stack<T,SIZE>::top() const//访问栈顶元素 
{   
    assert(!empty());//如果栈为空，则报错
    return list[top0];//返回栈顶元素
} 
template <class T,int SIZE>
bool Stack<T,SIZE>::empty() const//测试栈是否空 
{    
    return top0==-1;
} 
template <class T,int SIZE>
bool Stack<T,SIZE>::isFull() const//测试是否栈满 
{ 
    return top0==SIZE-1;
}
template <class T,int SIZE>
void Stack<T, SIZE>::clear()//清空栈
{    
    top0=-1;
}
 char mapp[10007][10007];
 //(dx,dy)为向量 
 int dx[5]={0,0,1,0,-1}; 
 int dy[5]={0,1,0,-1,0};
 int map_a,map_b;
 bool map_bool[10007][10007];
 typedef pair<int,int> P;
 Stack<P> path;
 void print()
 {
 	cout<<"迷宫路径:"<<endl;
	//path栈里的路径直接输出的话是从终点到起点
	//所以要先把path栈里的内容先压到path_out栈之中 
 	Stack<P> path_out; 
 	while(!path.empty())
 	{
 		path_out.push(path.top());//path_out压栈path.top()元素 
 		if(!path.empty()) path.pop();//path出栈 
	}
	P temp=path_out.top();
	int cnt=1; 
	cout<<"<"<<temp.first<<","<<temp.second<<">";
	path_out.pop();
	while(!path_out.empty())//path_out栈不为空，一直输出 
	{
		if(cnt%4==0) cout<<endl;
		cnt++;
		temp=path_out.top();
		cout<<" ---> <"<<temp.first<<","<<temp.second<<">";
		if(!path_out.empty()) path_out.pop();
	}
 }
 bool flagg=0;
 void dfs(int x,int y,int tx,int ty)//当前坐标(x,y)，终点坐标(tx,ty) 
 {
 	if(x==tx && y==ty) 
	{
		print();
		flagg=1;
	}
 	else for(int i=1;i<=4;i++)
 	{
 		int nx=x+dx[i],ny=y+dy[i];//走的下一步坐标(nx,ny) 
 		if(nx>=1 && nx<=map_a && ny>=1 && ny<=map_b && map_bool[nx][ny]==0)
		//判断，在不越界和没有墙的时候继续进行 
 		{
 			if(!flagg) path.push(P(nx,ny));//如果没有到达终点的话继续压栈 
 			map_bool[nx][ny]=1;//标记、染色走过的路径 
			dfs(nx,ny,tx,ty);//继续深搜 
			if(!flagg)//如果没有到达终点 
			{
				map_bool[nx][ny]=0;//回溯，消除走过的路径的标记 
				path.pop();//出栈 
			}
		}	
	}
	return;
 }
 bool isValid(int sx,int sy,int tx,int ty)
{
	bool ff=1; 
    if(sx<1 || sx>map_a || sy<1 || sy>map_b) cout<<"起点不在迷宫里面",ff=0;
    	else if(map_bool[sx][sy]==1) cout<<"起点为墙",ff=0;
    if(tx<1 || tx>map_a || ty<1 || ty>map_b) cout<<"终点不在迷宫里面",ff=0;
   		else if(map_bool[tx][ty]==1) cout<<"终点为墙",ff=0;
   	return ff;
}
int main()
{
	cout<<"输入地图的长和宽:"<<endl;
	cin>>map_a>>map_b;
	cout<<"输入地图,用0代表路、1代表墙"<<endl;
	for(int i=1;i<=map_a;i++)
		for(int j=1;j<=map_b;j++) cin>>map_bool[i][j];
	//转化为字符数组地图
	for(int i=0;i<=map_a+1;i++)
	  for(int j=0;j<=map_b+1;j++)
	  {
	  	if(i==0||i==map_a+1||j==0||j==map_b+1) mapp[i][j]='#';
	  	else if(map_bool[i][j]==1) mapp[i][j]='#';
	  	else if(map_bool[i][j]==0) mapp[i][j]='0';
	  }
	//输出地图 
	cout<<"迷宫地图:"<<endl;
	printf("\t");
	for(int j=0;j<=map_b+1;j++) printf("%d列\t",j);
	printf("\n"); 
	for(int i=0;i<=map_a+1;i++)
	{
	  printf("%d行\t",i);
	  for(int j=0;j<=map_b+1;j++) printf("%c\t",mapp[i][j]);
	  printf("\n"); 
	}
	printf("\n");
	
	int sx,sy,tx,ty;
	cout<<"输入起点（sx,sy）";
	cin>>sx>>sy; 
	cout<<endl;
	cout<<"输入终点（tx,ty）";
	cin>>tx>>ty; 
	cout<<endl;
	if(isValid(sx,sy,tx,ty)==0) return 0;
	path.push(P(sx,sy));
	map_bool[sx][sy]=1; 
	dfs(sx,sy,tx,ty);
	if(flagg==0) cout<<"没有路径！"<<endl;
	system("pause"); 
	return 0;
}
