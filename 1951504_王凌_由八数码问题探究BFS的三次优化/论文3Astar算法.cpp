#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[15];
string goal="123804765";
int h_star(string cur)//���ۺ��� 
{
	int difference=0;
	for(int i=0;i<9;i++) 
		if(goal[i]!=cur[i] && goal[i]!=0) difference++;
		//����0λ��֮������״̬��Ŀ��״̬������� 
	return difference;
} 

class Node
{
public:  
    int f_star,step;
    string current; 
    // ���ڶ���С�������˶�����Node��priority_queue,vector,greater�ϵĿ�
    // Node����Ҫ����������Ҫ����>��<�� 
	bool operator<(const Node &x) const
	{  
        return f_star<x.f_star;
    }
    bool operator>(const Node &x) const
	{  
        return f_star>x.f_star;
    }
};
priority_queue<Node,vector<Node>,greater<Node> > q;//����С���ѣ�ÿ��ȡf_star��С�Ľ�� 
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
	       	if(cur[i]-'0'==0) sx=i/3+1,sy=i%3+1;//�ҵ���ǰ״̬0������ 
		int tmapp1=(sx-1)*3+sy-1;//0�ŵ�����֮�е�λ�� 
		for(int i=0;i<4;i++)
		{
			int xx=dx[i]+sx,yy=dy[i]+sy;			
			if(xx<1 || xx>3 || yy<1 || yy>3) continue;//Խ�� 
			int tmapp2=(xx-1)*3+yy-1;//����Ϊ��xx,yy���ĵ�ŵ�����֮�е�λ�� 
			swap(cur[tmapp1],cur[tmapp2]);//�ƶ���cur�ַ��������仯 
			if(mapp[cur]==0 || (mapp[cur]==1&&(t.step+1)<dis[cur]) )
			//���ƶ����cur����״̬û�з��ʹ� ���� ��Ȼ���ʹ�����������״̬�任�������� 
			{
				dis[cur]=t.step+1;//���²��� 
				q.push((Node){h_star(cur)+t.step+1,t.step+1,cur});//������
				mapp[cur]=1;//���·���״̬ 
			}
			swap(cur[tmapp1],cur[tmapp2]);//����Ӱ�죬����ԭ״̬ 
		}
	}
}

int main() 
{
    cin>>s; 
    if(h_star(s)==0)
	//�����ֵ�����ж���ǰ״̬��Ŀ��״̬���Ϊ0����һ�������0�� 
	{
		cout<<0<<endl;
		return 0;
	}
	q.push((Node){h_star(s),0,s});//�����״̬������� 
	mapp[s]=1;
	dis[s]=0;
	A_STAR();
	return 0;
}
