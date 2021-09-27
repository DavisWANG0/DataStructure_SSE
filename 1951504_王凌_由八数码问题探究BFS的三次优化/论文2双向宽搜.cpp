#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll start,goal=123804765;
ll s[4][4];
map<int,int> dis;//记录路径长度，即状态变化的次数 
map<int,int> vis;//记录有没有访问过 

int dx[5]={1,-1,0,0};
int dy[5]={0,0,1,-1};

void double_BFS()
{
    queue<ll>q;
    if(start==goal)//如果起点等于终点，则不用走就直接输出 
	{
        cout<<"0\n";
        exit(0);
    }
    vis[start]=1;//从起点搜索访问过的点，标记为1 
	vis[goal]=2;//从终点搜索访问过的点，标记为2 
    dis[start]=0;dis[goal]=0;//初始化 
    q.push(start);//从起点状态开始变化 
    q.push(goal);//从目标状态往回转移 
    while(!q.empty())
    {
        ll cur=q.front();//cur记录队首元素 
		q.pop();//出队列 
        int sx,sy;
        ll temp=cur;
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
            ll next=0;
            for(int j=1;j<=3;j++)
            //将3*3的数组棋盘转化为一串longlong的状态进行记录 
            {
                for(int k=1;k<=3;k++)
                {
                    next=next*10+s[j][k];
                }
            }
            if(vis[cur]==vis[next])
			//如果这个状态已经被同起点出发第二次访问 
			//则跳过循环，不继续做下去 
            {
                swap(s[sx][sy],s[xx][yy]);//消除影响 
                continue;
            }
            if(vis[next]+vis[cur]==3)
			//vis和为3的情况下，vis[next]和vis[cur]其中一个为1一个为2
			//从cur状态转化到next状态只需要一步，说明已经找到了八数码的最短路径 
            {
                cout<<dis[cur]+dis[next]+1<<endl;
				//cur状态转化到next状态需要一步，所以还要加一 
                exit(0);//退出程序 
            }
            dis[next]=dis[cur]+1;//状态变化次数+1 
            vis[next]=vis[cur];
			//继承属性，用来分辨这个点是从起点来的还是从终点变化来的 
            q.push(next);//进队列 
            swap(s[sx][sy],s[xx][yy]);
			//消除影响，返回cur状态下的数组，之后还有其他方向需要搜索 
        }
    }
}
int main()
{
    cin>>start; 
    double_BFS(); 
    return 0;
}
