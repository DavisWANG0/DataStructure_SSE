#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll start,goal=123804765;
ll s[4][4];
map<int,int> dis;//��¼·�����ȣ���״̬�仯�Ĵ��� 
map<int,int> vis;//��¼��û�з��ʹ� 

int dx[5]={1,-1,0,0};
int dy[5]={0,0,1,-1};

void double_BFS()
{
    queue<ll>q;
    if(start==goal)//����������յ㣬�����߾�ֱ����� 
	{
        cout<<"0\n";
        exit(0);
    }
    vis[start]=1;//������������ʹ��ĵ㣬���Ϊ1 
	vis[goal]=2;//���յ��������ʹ��ĵ㣬���Ϊ2 
    dis[start]=0;dis[goal]=0;//��ʼ�� 
    q.push(start);//�����״̬��ʼ�仯 
    q.push(goal);//��Ŀ��״̬����ת�� 
    while(!q.empty())
    {
        ll cur=q.front();//cur��¼����Ԫ�� 
		q.pop();//������ 
        int sx,sy;
        ll temp=cur;
        for(int i=3;i>=1;i--)
		//����longlong��¼״̬ת��Ϊһ��3*3�Ķ�ά���������ٽ��д��� 
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
			//���磬�����˷���ת����һ������
            if(xx<1||xx>3||yy<1||yy>3) continue; 
            swap(s[sx][sy],s[xx][yy]);
            ll next=0;
            for(int j=1;j<=3;j++)
            //��3*3����������ת��Ϊһ��longlong��״̬���м�¼ 
            {
                for(int k=1;k<=3;k++)
                {
                    next=next*10+s[j][k];
                }
            }
            if(vis[cur]==vis[next])
			//������״̬�Ѿ���ͬ�������ڶ��η��� 
			//������ѭ��������������ȥ 
            {
                swap(s[sx][sy],s[xx][yy]);//����Ӱ�� 
                continue;
            }
            if(vis[next]+vis[cur]==3)
			//vis��Ϊ3������£�vis[next]��vis[cur]����һ��Ϊ1һ��Ϊ2
			//��cur״̬ת����next״ֻ̬��Ҫһ����˵���Ѿ��ҵ��˰���������·�� 
            {
                cout<<dis[cur]+dis[next]+1<<endl;
				//cur״̬ת����next״̬��Ҫһ�������Ի�Ҫ��һ 
                exit(0);//�˳����� 
            }
            dis[next]=dis[cur]+1;//״̬�仯����+1 
            vis[next]=vis[cur];
			//�̳����ԣ������ֱ�������Ǵ�������Ļ��Ǵ��յ�仯���� 
            q.push(next);//������ 
            swap(s[sx][sy],s[xx][yy]);
			//����Ӱ�죬����cur״̬�µ����飬֮��������������Ҫ���� 
        }
    }
}
int main()
{
    cin>>start; 
    double_BFS(); 
    return 0;
}
