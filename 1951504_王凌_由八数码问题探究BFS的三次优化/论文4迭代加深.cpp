#include<bits/stdc++.h>
using namespace std;
char s[15];
char goal[]={'1','2','3','8','0','4','7','6','5'};
int maxdepth;
int h(char *cur)//估价函数 
{
	int difference=0;
	for(int i=0;i<9;i++) 
		if(goal[i]!=cur[i] && cur[i]!=0) difference++;
		//除了0位置之外现在状态和目标状态差几个棋子
	return difference;
}
int dx[]={0,1,-1,0};
//dx[0]与dx[3]方向相反，dx[1]与dx[2]方向相反
//即下标相加等于3的方向相反，后有剪枝 
int dy[]={1,0,0,-1};
bool ida_star(int depth,char *a,int pre) 
{
	if(h(a)==0) return true;
	//估值函数h(a)==0，说明当前状态和最终状态相同 
	if(depth+h(a)-1>maxdepth) return false;
	//剪枝，如果当前深度加上估值步数超过当前定义的最大深度那么就退出
	int sx,sy;
	for(int i=0;i<9;i++)
		if(a[i]=='0') sx=i/3+1,sy=i%3+1;
	//找到0的坐标(sx,sy) 
	for(int i=0;i<4;i++)//枚举可达状态 
	{
		int xx=dx[i]+sx,yy=dy[i]+sy;
		if(xx<1 || xx>3 || yy<1 || yy>3 || pre+i==3) continue;
		//前面四个是判断有没有越界，如果越界退出 
		//pre+i==3是一个小的剪枝，判断有无返回原来的状态 
		swap(a[(xx-1)*3+yy-1],a[(sx-1)*3+sy-1]); 
		if(ida_star(depth+1,a,i)) return true;//深搜 
		swap(a[(xx-1)*3+yy-1],a[(sx-1)*3+sy-1]);//回溯 
	}
	return false;
}
int main() 
{
	cin>>s; 
	if(h(s)==0)
	//如果一开始估价函数为0，说明不需要移动 
	{
		cout<<"0"<<endl;
		system("pause");
		return 0;
	}
	for(maxdepth=1;;maxdepth++) 
	//从1开始枚举maxdepth的大小，以达到一层一层深搜的目的 
	{
		if(ida_star(0,s,-1)) 
		{
			cout<<maxdepth<<endl;
			//maxdepth就是最多走几步 
			system("pause");
			return 0;
		}
	}
	return 0;
}
