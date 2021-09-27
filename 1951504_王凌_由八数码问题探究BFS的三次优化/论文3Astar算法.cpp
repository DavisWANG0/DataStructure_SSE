#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[15];
string goal="123804765";
int h_star(string cur)//估价函数 
{
	int difference=0;
	for(int i=0;i<9;i++) 
		if(goal[i]!=cur[i] && goal[i]!=0) difference++;
		//除了0位置之外现在状态和目标状态差几个棋子 
	return difference;
} 

class Node
{
public:  
    int f_star,step;
    string current; 
    // 由于定义小根堆用了定义在Node上priority_queue,vector,greater上的库
    // Node类需要排序，所以需要重载>与<号 
	bool operator<(const Node &x) const
	{  
        return f_star<x.f_star;
    }
    bool operator>(const Node &x) const
	{  
        return f_star>x.f_star;
    }
};
priority_queue<Node,vector<Node>,greater<Node> > q;//定义小根堆，每次取f_star最小的结点 
map<string,bool> mapp;
map<string,int> dis;
int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};

void A_STAR()
{
	while(!q.empty())
	{
		Node t=q.top();
		q.pop();
		string cur=t.current;
		if(cur=="123804765") 
		{
			printf("%d\n",t.step);
			exit(0);
		}
		int sx,sy;
		for(int i=0;i<9;i++)
	       	if(cur[i]-'0'==0) sx=i/3+1,sy=i%3+1;//找到当前状态0的坐标 
		int tmapp1=(sx-1)*3+sy-1;//0放到数组之中的位置 
		for(int i=0;i<4;i++)
		{
			int xx=dx[i]+sx,yy=dy[i]+sy;			
			if(xx<1 || xx>3 || yy<1 || yy>3) continue;//越界 
			int tmapp2=(xx-1)*3+yy-1;//坐标为（xx,yy）的点放到数组之中的位置 
			swap(cur[tmapp1],cur[tmapp2]);//移动，cur字符串发生变化 
			if(mapp[cur]==0 || (mapp[cur]==1&&(t.step+1)<dis[cur]) )
			//当移动后的cur这种状态没有访问过 或者 虽然访问过，但是这种状态变换步数更少 
			{
				dis[cur]=t.step+1;//更新步数 
				q.push((Node){h_star(cur)+t.step+1,t.step+1,cur});//进队列
				mapp[cur]=1;//更新访问状态 
			}
			swap(cur[tmapp1],cur[tmapp2]);//消除影响，返回原状态 
		}
	}
}

int main() 
{
    cin>>s; 
    if(h_star(s)==0)
	//如果估值函数判定当前状态和目标状态相差为0，即一样则输出0步 
	{
		cout<<0<<endl;
		return 0;
	}
	q.push((Node){h_star(s),0,s});//将起点状态进入队列 
	mapp[s]=1;
	dis[s]=0;
	A_STAR();
	return 0;
}
