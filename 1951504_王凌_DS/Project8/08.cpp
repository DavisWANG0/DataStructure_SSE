#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>
#define INF 0x7fffffff
using namespace std;
class UF//���鼯 
{
public:
	UF(int N)//��ʼ�� 
	{
		for(int i=0;i<N;i++) id.push_back(i);
		count=N;//��ʱÿ���㶼��һ����ͨ���� 
	}
	int find(int p)
	{
		while(p!=id[p])
		{
			//���pԪ�صĸ���ָ��ָ��Ĳ����Լ���˵��p�����Ǽ����еĸ�Ԫ�أ�����Ҫһֱ���ϲ��Һ�·��ѹ��
            //��find��ѯ��Ƕ��һ��·��ѹ������
            id[p]=id[id[p]];
            //pԪ�ز���ѡ��ԭ���ĸ��׽ڵ㣬����ֱ��ѡ���׽ڵ�ĸ��׽ڵ�����Ϊ�Լ��µ�һ�����׽ڵ�
            //�����Ĳ���ʹ�����Ĳ�����ѹ����
            p=id[p];//pѹ����Ϻ���p�����Ǹ��ڵ㣬p���p�µĸ��ڵ�������в��Һ�ѹ����ͬʱ����
    	}
		return p;
	}
	bool connected(int p,int q)//����ǲ�����ͬһ�������� 
	{
		return find(p)==find(q);//�����ڵ���ͬ������ͬһ������֮�� 
	}
	void unionPQ(int p,int q)//����P��Q�������
	{
		int i=find(p),j=find(q);
		if(i==j) return;//��������Ѿ���һ�����������˳� 
		id[j]=i;
		count--;
	}
	//�������ķ�װ���� 
	int getCount()
	{
		return count;
	}
private:
	vector<int> id;//����������
	int count;//��ͨ��������
};
class Graph//ͼ 
{
public: 
	unordered_map<string,int> node_name;
	//�ý�����ֺͽ��������Ӧ 
	Graph(int num):nodeNum(num),edgeNum(0)//�Զ��幹�캯��
	//���ɽ����Ϊnum������Ϊ0��ͼ 
	{
		for(int i=0;i<num;i++)
			for(int j=0;j<num;j++) mapp[i][j]=INF;
	}
	int GetFirstNeighbor(int v)
	//��������λ��Ϊv�ĵ�һ���ڽӶ����λ�� 
	{
		for(int i=0;i<nodeNum;i++)
			if(mapp[v][i]!=INF)	return i;
		return -1;
	}
	int GetNextNeighbor(int v1,int v2)
	//��������v1��ĳ�ڽӶ���v2����һ���ڽӶ��� 
	{
		bool v2_found=false;//��¼�����û�б��ҵ� 
		for(int i=0;i<nodeNum;i++) 
		{
			if(v2_found) if(mapp[v1][i]!=INF) return i;
			//v2���ҵ�֮�����һ����� 
			if(i==v2) v2_found=true;
		}
		return -1;
	}
	bool InsertEdge(string Node1,string Node2,int weight)//����� 
	{
		if((Node1=="?"||Node1=="��") && (Node2=="?"||Node2=="��")&& weight==0)
		//��Ӣ�������µ�?���ܱ�ʶ�� 
		{
			if(isConnected()) return true;
			else 
			{
				cout<<"���ĸ�������֮�䲢δȫ����ͨ����ȷ�����Ľڵ��Ƿ���ȷ\n";
				return false;
			}
		}
		if(Node1==Node2)//��ͬһ����� 
		{
			cout<<"���������Ϣ��ͬ����ȷ�Ϻ�������\n";
			return false;
		}
		if(weight<=0)//�ߵ�Ȩֵ����Ϊ�� 
		{
			cout<<"����������·�Ļ��Ѳ���С�ڵ���0��������ȷ�Ϻ�����\n";
			return false;
		}
		int left_Index=0,right_Index=0;//�ֱ��¼����ΪNode1,Node2�Ľ���� 
		//�����map���е�find���� 
		if(node_name.find(Node1)!=node_name.end()) left_Index=node_name.find(Node1)->second;
		if(node_name.find(Node2)!=node_name.end()) right_Index=node_name.find(Node2)->second;
		if(node_name.find(Node1)==node_name.end() || node_name.find(Node2)==node_name.end()) 
		{
			cout<<"δ�ҵ�����һ����㣬����������\n";
			return false;
		}
		if(mapp[left_Index][right_Index]!=INF)
		{
			cerr<<"������������·�����������Ľڵ��Ƿ�������ȷ\n";
			return false;
		}
		//����ͼ�������ڽӾ����ǶԳƵ� 
		mapp[left_Index][right_Index]=weight;
		mapp[right_Index][left_Index]=weight;
		edgeNum++;
		return false;
	}
	//�����������ķ�װ���ԣ��������漸������ӿ� 
	int GetWeight(int left_Index,int right_Index) 
	{
		return mapp[left_Index][right_Index];
	}
	int GetNodeNum() {return nodeNum;}
	int GetEdgeNum() {return edgeNum;}
private:
	int mapp[1007][1007];//���ڽӾ������ʽ�洢��վ֮��ĳ���
	int nodeNum;
	int edgeNum;
	bool isConnected()//�ж��Ƿ���ͨ 
	{ 
		UF* uf_set=new UF(nodeNum);
		for(int i=0;i<nodeNum;i++)
			for(int j=0;j<nodeNum;j++)
				if(mapp[i][j]!=INF)
					if(!uf_set->connected(i,j)) uf_set->unionPQ(i,j);
					//��i,j����ͬһ�������У�����������֮���б���������union������� 
		if(uf_set->getCount()==1) return 1;//��ͨ����Ϊ1����ͨ 
		else return 0;//��ͨ��������1������ͼ����ͨ 
	}
};
class Edge 
{
public:
	int head;
	int tail;
	int weight;
};
void PrintScreen() 
{
	cout<<"**             �����������ģ��ϵͳ           **"<<endl;
	cout<<"================================================"<<endl;
	cout<<"**                A---������������            **"<<endl;
	cout<<"**                B---��ӵ����ı�            **"<<endl;
	cout<<"**                C---������С������          **"<<endl;
	cout<<"**                D---��ʾ��С������          **"<<endl;
	cout<<"**                E---�˳�����                **"<<endl;
	cout<<"================================================"<<endl;
}
void primTree(Edge* edgeVector,Graph* graph)
//��PRIM������С������ 
{
	int nodeNum=graph->GetNodeNum();
	int edgeNum=graph->GetEdgeNum();
	int count=0;//�Ѿ�����һ������(�׶���0)
	//��ʼ��lowCost��nearVex����
	int *lowCost=new int[nodeNum];
	//������������㼯���ڶ��㵽���������������ĸ����ϵĵ�ǰ��СȨֵ 
	int *nearVex=new int[nodeNum];
	//��¼���������㼯�����������뼯�����ĸ��������
	//��ʼ������������ 
	lowCost[0]=0;
	nearVex[0]=-1;//-1��ʾ�Ѿ������������Ķ���
	for(int i=1;i<nodeNum;i++) 
		{
			lowCost[i]=graph->GetWeight(0,i);//����0������Ĵ��� 
			nearVex[i]=0;
		}
	for(int j=1;j<nodeNum;j++)//ѭ��n-1�Σ�����n-1���� 
	{
		int vIndex=0;
		int minn=INF;
		//���������ⶥ�㵽�������ڶ��������СȨֵ�ı�
		//vIndexΪ��ǰ������СȨֵ�ߵ�λ�� 
		for(int i=0;i<nodeNum;i++) 
		{
			if(nearVex[i]!=-1 && lowCost[i]<minn) 
			{
				vIndex=i;
				minn=lowCost[i];
			}
		}
		//�������߼��벻���������ڼ�¼,���������ⶥ���������
		if(vIndex)//���vIndex==0��ʾ��Ҳ�Ҳ���Ҫ�󶥵��� 
		{
			Edge tempEdge;
			tempEdge.head=vIndex;
			tempEdge.tail=nearVex[vIndex];
			tempEdge.weight=lowCost[vIndex];
			nearVex[vIndex]=-1;//�Ըñ��Ѿ�������������� 
			edgeVector[count++]=tempEdge;//ѡ���ı߼��������� 
			for(int i=1;i<nodeNum;i++)
			{
				if(nearVex[i]!=-1 && graph->GetWeight(vIndex,i)<lowCost[i])
				//i����������֮�� 
				{
					lowCost[i]=graph->GetWeight(vIndex,i);
					nearVex[i]=vIndex;
				}
			}
		}	
	} 
	cout<<"����Prim��С������!\n\n";
	delete[] lowCost;
	delete[] nearVex;
}
int main() 
{
	PrintScreen();
	Graph* G=NULL;
	//UF* uf_set=NULL;
	int num;
	bool AisDone=false,BisDone=false,CisDone=false;
	bool isContinue=true;
	Edge* edgeVector=NULL;
	string name0;
	while(isContinue) 
	{
		cout<<"���������: ";
		char ops;
		cin>>ops;
		switch(ops)
		{
		case 'A':
			//���A�����ˣ��������� 
			if(AisDone) 
			{
				cout<<"��������A����,�������������\n";
			}
			else 
			{
				cout<<"�����붥��ĸ���:";
				cin>>num;
				//uf_set=new UF(num);
				cout<<"��������������������:\n";
				string name0;
				G=new Graph(num);
				edgeVector=new Edge[num+1];
				for(int i=0;i<num;i++) 
				{
					cin>>name0;
					G->node_name[name0]=i;//��ź����ִ���map�� 
				}
				AisDone=true;
			}
			cout<<endl;
			break;
		case 'B': 
		{
			if(!AisDone) cout<<"���Ƚ���A����\n";
			int num=G->GetNodeNum();
			string name1;
			string name2;
			int weight;
			do{
				cout<<"�������������㼰��(�м��ÿո�,��? ? 0��β,��Ӣ���������):";
				cin>>name1>>name2>>weight;
			} while(!G->InsertEdge(name1,name2,weight));
			cout<<endl;
			BisDone=true;
			break;
		}
		case 'C':
			if(!AisDone) 
			{
				cout<<"���Ƚ���A����\n";
				break;
			}
			else if(!BisDone) 
			{
				cout<<"���Ƚ���B����\n";
				break;
			}
			primTree(edgeVector,G);
			CisDone=true;
			break;
		case 'D':
			if(!AisDone) 
			{
				cout<<"���Ƚ���A����\n";
				break;
			}
			else if(!BisDone) 
			{
				cout<<"���Ƚ���B����\n";
				break;
			}
			else if(!CisDone) 
			{
				cout<<"���Ƚ���C����\n";
				break;
			}
			cout<<"��С�������Ķ��㼰��Ϊ: \n";
			for(int i=0;i<G->GetNodeNum()-1;i++) 
			{
				for(auto iter=G->node_name.begin();iter!=G->node_name.end();++iter)
					if(iter->second==edgeVector[i].head)
					//�ҵ����ϵ�ͷ������Ŷ�Ӧ������ 
					{
						cout<<iter->first<<"-<"<<edgeVector[i].weight<<">-";
						break;
					}
				for(auto iter=G->node_name.begin();iter!=G->node_name.end();++iter)
					if(iter->second==edgeVector[i].tail)//�ҵ����ϵ�β������Ŷ�Ӧ������  	
						cout<<iter->first<<"\t\t";
				if((i+1)%4==0) cout<<endl;//һ�������ĸ� 
			}
			cout<<endl<<endl;
			break;
		case 'E':
			isContinue=false;
			break;
		default:
			cout<<"����Ĳ�����,��ȷ�Ϻ�������\n";
			break;
		}
	}
	getchar();
	delete G;
	delete edgeVector;
	return 0;
}
