#include<bits/stdc++.h>
using namespace std;
char s[15];
char goal[]={'1','2','3','8','0','4','7','6','5'};
int maxdepth;
int h(char *cur)//���ۺ��� 
{
	int difference=0;
	for(int i=0;i<9;i++) 
		if(goal[i]!=cur[i] && cur[i]!=0) difference++;
		//����0λ��֮������״̬��Ŀ��״̬�������
	return difference;
}
int dx[]={0,1,-1,0};
//dx[0]��dx[3]�����෴��dx[1]��dx[2]�����෴
//���±���ӵ���3�ķ����෴�����м�֦ 
int dy[]={1,0,0,-1};
bool ida_star(int depth,char *a,int pre) 
{
	if(h(a)==0) return true;
	//��ֵ����h(a)==0��˵����ǰ״̬������״̬��ͬ 
	if(depth+h(a)-1>maxdepth) return false;
	//��֦�������ǰ��ȼ��Ϲ�ֵ����������ǰ�������������ô���˳�
	int sx,sy;
	for(int i=0;i<9;i++)
		if(a[i]=='0') sx=i/3+1,sy=i%3+1;
	//�ҵ�0������(sx,sy) 
	for(int i=0;i<4;i++)//ö�ٿɴ�״̬ 
	{
		int xx=dx[i]+sx,yy=dy[i]+sy;
		if(xx<1 || xx>3 || yy<1 || yy>3 || pre+i==3) continue;
		//ǰ���ĸ����ж���û��Խ�磬���Խ���˳� 
		//pre+i==3��һ��С�ļ�֦���ж����޷���ԭ����״̬ 
		swap(a[(xx-1)*3+yy-1],a[(sx-1)*3+sy-1]); 
		if(ida_star(depth+1,a,i)) return true;//���� 
		swap(a[(xx-1)*3+yy-1],a[(sx-1)*3+sy-1]);//���� 
	}
	return false;
}
int main() 
{
	cin>>s; 
	if(h(s)==0)
	//���һ��ʼ���ۺ���Ϊ0��˵������Ҫ�ƶ� 
	{
		cout<<"0"<<endl;
		system("pause");
		return 0;
	}
	for(maxdepth=1;;maxdepth++) 
	//��1��ʼö��maxdepth�Ĵ�С���Դﵽһ��һ�����ѵ�Ŀ�� 
	{
		if(ida_star(0,s,-1)) 
		{
			cout<<maxdepth<<endl;
			//maxdepth��������߼��� 
			system("pause");
			return 0;
		}
	}
	return 0;
}
