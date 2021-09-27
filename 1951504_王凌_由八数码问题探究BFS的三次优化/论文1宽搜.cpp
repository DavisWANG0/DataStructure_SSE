#include<bits/stdc++.h>
using namespace std;
long long goal=123804765,start;
class Node
{
public:
    long long chess;
    int step;
};
int dx[5]={1,-1,0,0};
int dy[5]={0,0,1,-1};
int s[4][4];
map<int,int> vis;//记录有没有访问过
queue<Node> q;
void BFS()
{
    Node head;
    head.chess=start;
	head.step=0;
    q.push(head);
    vis[start]=1;
    while(!q.empty())
    {
        Node cur=q.front();
		q.pop();
		if(cur.chess==goal)//找到了结果 
		{
			cout<<cur.step<<endl;
			break;
		}
        int sx,sy;//记录的0位置的坐标 
        long long temp=cur.chess;
        for(int i=3;i>=1;i--)
		//将用longlong记录状态转化为一个3*3的二维数组棋盘再进行处理 
        {
            for(int j=3;j>=1;j--)
            {
                s[i][j]=temp%10;
				temp/=10;
                if(!s[i][j]) sx=i,sy=j;	
            }
        }
        for(int i=0;i<4;i++)
        {
            int xx=sx+dx[i],yy=sy+dy[i];
			//出界，放弃此方向，转到下一个方向
            if(xx<1||xx>3||yy<1||yy>3) continue; 
            swap(s[sx][sy],s[xx][yy]);
            long long next=0;
            for(int j=1;j<=3;j++)
            //将3*3的数组棋盘转化为一串longlong的状态进行记录 
            {
                for(int k=1;k<=3;k++) next=next*10+s[j][k];
            }
            if(vis[next])
			//已经被访问过 
            {
                swap(s[sx][sy],s[xx][yy]);//消除影响 
                continue;
            }
            vis[next]=1;
            Node nextnode;
			nextnode.step=cur.step+1;
			nextnode.chess=next; 
            q.push(nextnode);//进队列 
            swap(s[sx][sy],s[xx][yy]);
			//消除影响，返回cur状态下的数组，之后还有其他方向需要搜索 
        }
    } 
}

int main()
{
    cin>>start;	
    if(start==goal) 
	{
        cout<<"0\n";
        return 0;
    }
    BFS();
    return 0;
}
