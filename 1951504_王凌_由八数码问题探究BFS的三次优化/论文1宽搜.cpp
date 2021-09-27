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
map<int,int> vis;//��¼��û�з��ʹ�
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
		if(cur.chess==goal)//�ҵ��˽�� 
		{
			cout<<cur.step<<endl;
			break;
		}
        int sx,sy;//��¼��0λ�õ����� 
        long long temp=cur.chess;
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
            long long next=0;
            for(int j=1;j<=3;j++)
            //��3*3����������ת��Ϊһ��longlong��״̬���м�¼ 
            {
                for(int k=1;k<=3;k++) next=next*10+s[j][k];
            }
            if(vis[next])
			//�Ѿ������ʹ� 
            {
                swap(s[sx][sy],s[xx][yy]);//����Ӱ�� 
                continue;
            }
            vis[next]=1;
            Node nextnode;
			nextnode.step=cur.step+1;
			nextnode.chess=next; 
            q.push(nextnode);//������ 
            swap(s[sx][sy],s[xx][yy]);
			//����Ӱ�죬����cur״̬�µ����飬֮��������������Ҫ���� 
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
