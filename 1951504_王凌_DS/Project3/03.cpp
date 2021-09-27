#include<iostream>
using namespace std;
#define stacksize 10007
void assert(bool num)//����:���� 
{
	if(num==0)	cout<<"����"<<endl; 
}
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
};
template <class T,int SIZE>
Stack<T,SIZE>::Stack():top0(-1){}//���캯����ջ����ʼ��Ϊ-1
template <class T,int SIZE>
void Stack<T,SIZE>::push(const T &item)//��Ԫ��itemѹ��ջ 
{
    assert(!isFull());//���ջ���ˣ��򱨴�
    list[++top0]=item;//����Ԫ��ѹ��ջ��
}
template <class T,int SIZE>
T Stack<T,SIZE>::pop()//��ջ��Ԫ�ص���ջ
{
    assert(!empty());//���ջΪ�գ��򱨴�
    return list[top0--];//����ջ��Ԫ�أ������䵯��ջ��
}
template <class T,int SIZE>
const T &Stack<T,SIZE>::top() const//����ջ��Ԫ�� 
{   
    assert(!empty());//���ջΪ�գ��򱨴�
    return list[top0];//����ջ��Ԫ��
} 
template <class T,int SIZE>
bool Stack<T,SIZE>::empty() const//����ջ�Ƿ�� 
{    
    return top0==-1;
} 
template <class T,int SIZE>
bool Stack<T,SIZE>::isFull() const//�����Ƿ�ջ�� 
{ 
    return top0==SIZE-1;
}
template <class T,int SIZE>
void Stack<T, SIZE>::clear()//���ջ
{    
    top0=-1;
}
 char mapp[10007][10007];
 //(dx,dy)Ϊ���� 
 int dx[5]={0,0,1,0,-1}; 
 int dy[5]={0,1,0,-1,0};
 int map_a,map_b;
 bool map_bool[10007][10007];
 typedef pair<int,int> P;
 Stack<P> path;
 void print()
 {
 	cout<<"�Թ�·��:"<<endl;
	//pathջ���·��ֱ������Ļ��Ǵ��յ㵽���
	//����Ҫ�Ȱ�pathջ���������ѹ��path_outջ֮�� 
 	Stack<P> path_out; 
 	while(!path.empty())
 	{
 		path_out.push(path.top());//path_outѹջpath.top()Ԫ�� 
 		if(!path.empty()) path.pop();//path��ջ 
	}
	P temp=path_out.top();
	int cnt=1; 
	cout<<"<"<<temp.first<<","<<temp.second<<">";
	path_out.pop();
	while(!path_out.empty())//path_outջ��Ϊ�գ�һֱ��� 
	{
		if(cnt%4==0) cout<<endl;
		cnt++;
		temp=path_out.top();
		cout<<" ---> <"<<temp.first<<","<<temp.second<<">";
		if(!path_out.empty()) path_out.pop();
	}
 }
 bool flagg=0;
 void dfs(int x,int y,int tx,int ty)//��ǰ����(x,y)���յ�����(tx,ty) 
 {
 	if(x==tx && y==ty) 
	{
		print();
		flagg=1;
	}
 	else for(int i=1;i<=4;i++)
 	{
 		int nx=x+dx[i],ny=y+dy[i];//�ߵ���һ������(nx,ny) 
 		if(nx>=1 && nx<=map_a && ny>=1 && ny<=map_b && map_bool[nx][ny]==0)
		//�жϣ��ڲ�Խ���û��ǽ��ʱ��������� 
 		{
 			if(!flagg) path.push(P(nx,ny));//���û�е����յ�Ļ�����ѹջ 
 			map_bool[nx][ny]=1;//��ǡ�Ⱦɫ�߹���·�� 
			dfs(nx,ny,tx,ty);//�������� 
			if(!flagg)//���û�е����յ� 
			{
				map_bool[nx][ny]=0;//���ݣ������߹���·���ı�� 
				path.pop();//��ջ 
			}
		}	
	}
	return;
 }
 bool isValid(int sx,int sy,int tx,int ty)
{
	bool ff=1; 
    if(sx<1 || sx>map_a || sy<1 || sy>map_b) cout<<"��㲻���Թ�����",ff=0;
    	else if(map_bool[sx][sy]==1) cout<<"���Ϊǽ",ff=0;
    if(tx<1 || tx>map_a || ty<1 || ty>map_b) cout<<"�յ㲻���Թ�����",ff=0;
   		else if(map_bool[tx][ty]==1) cout<<"�յ�Ϊǽ",ff=0;
   	return ff;
}
int main()
{
	cout<<"�����ͼ�ĳ��Ϳ�:"<<endl;
	cin>>map_a>>map_b;
	cout<<"�����ͼ,��0����·��1����ǽ"<<endl;
	for(int i=1;i<=map_a;i++)
		for(int j=1;j<=map_b;j++) cin>>map_bool[i][j];
	//ת��Ϊ�ַ������ͼ
	for(int i=0;i<=map_a+1;i++)
	  for(int j=0;j<=map_b+1;j++)
	  {
	  	if(i==0||i==map_a+1||j==0||j==map_b+1) mapp[i][j]='#';
	  	else if(map_bool[i][j]==1) mapp[i][j]='#';
	  	else if(map_bool[i][j]==0) mapp[i][j]='0';
	  }
	//�����ͼ 
	cout<<"�Թ���ͼ:"<<endl;
	printf("\t");
	for(int j=0;j<=map_b+1;j++) printf("%d��\t",j);
	printf("\n"); 
	for(int i=0;i<=map_a+1;i++)
	{
	  printf("%d��\t",i);
	  for(int j=0;j<=map_b+1;j++) printf("%c\t",mapp[i][j]);
	  printf("\n"); 
	}
	printf("\n");
	
	int sx,sy,tx,ty;
	cout<<"������㣨sx,sy��";
	cin>>sx>>sy; 
	cout<<endl;
	cout<<"�����յ㣨tx,ty��";
	cin>>tx>>ty; 
	cout<<endl;
	if(isValid(sx,sy,tx,ty)==0) return 0;
	path.push(P(sx,sy));
	map_bool[sx][sy]=1; 
	dfs(sx,sy,tx,ty);
	if(flagg==0) cout<<"û��·����"<<endl;
	system("pause"); 
	return 0;
}
