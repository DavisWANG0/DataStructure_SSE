#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>
#define INF 0x7fffffff
using namespace std;
class UF//并查集 
{
public:
	UF(int N)//初始化 
	{
		for(int i=0;i<N;i++) id.push_back(i);
		count=N;//此时每个点都是一个连通分量 
	}
	int find(int p)
	{
		while(p!=id[p])
		{
			//如果p元素的父亲指针指向的不是自己，说明p并不是集合中的根元素，还需要一直向上查找和路径压缩
            //在find查询中嵌入一个路径压缩操作
            id[p]=id[id[p]];
            //p元素不再选择原来的父亲节点，而是直接选择父亲节点的父亲节点来做为自己新的一个父亲节点
            //这样的操作使得树的层数被压缩了
            p=id[p];//p压缩完毕后且p并不是根节点，p变成p新的父节点继续进行查找和压缩的同时操作
    	}
		return p;
	}
	bool connected(int p,int q)//检测是不是在同一个集合里 
	{
		return find(p)==find(q);//若父节点相同，则在同一个集合之中 
	}
	void unionPQ(int p,int q)//连接P、Q两个结点
	{
		int i=find(p),j=find(q);
		if(i==j) return;//如果两个已经在一个集合了则退出 
		id[j]=i;
		count--;
	}
	//面向对象的封装特性 
	int getCount()
	{
		return count;
	}
private:
	vector<int> id;//父链接数组
	int count;//连通分量数量
};
class Graph//图 
{
public: 
	unordered_map<string,int> node_name;
	//让结点名字和结点序号相对应 
	Graph(int num):nodeNum(num),edgeNum(0)//自定义构造函数
	//生成结点数为num，边数为0的图 
	{
		for(int i=0;i<num;i++)
			for(int j=0;j<num;j++) mapp[i][j]=INF;
	}
	int GetFirstNeighbor(int v)
	//给出顶点位置为v的第一个邻接顶点的位置 
	{
		for(int i=0;i<nodeNum;i++)
			if(mapp[v][i]!=INF)	return i;
		return -1;
	}
	int GetNextNeighbor(int v1,int v2)
	//给出顶点v1的某邻接顶点v2的下一个邻接顶点 
	{
		bool v2_found=false;//记录结点有没有被找到 
		for(int i=0;i<nodeNum;i++) 
		{
			if(v2_found) if(mapp[v1][i]!=INF) return i;
			//v2被找到之后的下一个结点 
			if(i==v2) v2_found=true;
		}
		return -1;
	}
	bool InsertEdge(string Node1,string Node2,int weight)//插入边 
	{
		if((Node1=="?"||Node1=="？") && (Node2=="?"||Node2=="？")&& weight==0)
		//中英文输入下的?都能被识别 
		{
			if(isConnected()) return true;
			else 
			{
				cout<<"您的各个电网之间并未全部连通，请确认您的节点是否正确\n";
				return false;
			}
		}
		if(Node1==Node2)//是同一个结点 
		{
			cout<<"两个结点信息相同，请确认后在输入\n";
			return false;
		}
		if(weight<=0)//边的权值必须为正 
		{
			cout<<"两个城市线路的花费不能小于等于0，请重新确认后输入\n";
			return false;
		}
		int left_Index=0,right_Index=0;//分别记录名字为Node1,Node2的结点标号 
		//红黑树map库中的find函数 
		if(node_name.find(Node1)!=node_name.end()) left_Index=node_name.find(Node1)->second;
		if(node_name.find(Node2)!=node_name.end()) right_Index=node_name.find(Node2)->second;
		if(node_name.find(Node1)==node_name.end() || node_name.find(Node2)==node_name.end()) 
		{
			cout<<"未找到其中一个结点，请重新输入\n";
			return false;
		}
		if(mapp[left_Index][right_Index]!=INF)
		{
			cerr<<"两个结点间已有路径，请检查您的节点是否输入正确\n";
			return false;
		}
		//无向图，所以邻接矩阵是对称的 
		mapp[left_Index][right_Index]=weight;
		mapp[right_Index][left_Index]=weight;
		edgeNum++;
		return false;
	}
	//由于面向对象的封装特性，定义下面几个对外接口 
	int GetWeight(int left_Index,int right_Index) 
	{
		return mapp[left_Index][right_Index];
	}
	int GetNodeNum() {return nodeNum;}
	int GetEdgeNum() {return edgeNum;}
private:
	int mapp[1007][1007];//以邻接矩阵的形式存储电站之间的长度
	int nodeNum;
	int edgeNum;
	bool isConnected()//判断是否连通 
	{ 
		UF* uf_set=new UF(nodeNum);
		for(int i=0;i<nodeNum;i++)
			for(int j=0;j<nodeNum;j++)
				if(mapp[i][j]!=INF)
					if(!uf_set->connected(i,j)) uf_set->unionPQ(i,j);
					//若i,j不在同一个集合中，但是两个点之间有边相连，则union两个结点 
		if(uf_set->getCount()==1) return 1;//连通分量为1则连通 
		else return 0;//连通分量大于1则整个图不连通 
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
	cout<<"**             电网建设造价模拟系统           **"<<endl;
	cout<<"================================================"<<endl;
	cout<<"**                A---创建电网顶点            **"<<endl;
	cout<<"**                B---添加电网的边            **"<<endl;
	cout<<"**                C---构造最小生成树          **"<<endl;
	cout<<"**                D---显示最小生成树          **"<<endl;
	cout<<"**                E---退出程序                **"<<endl;
	cout<<"================================================"<<endl;
}
void primTree(Edge* edgeVector,Graph* graph)
//用PRIM建立最小生成树 
{
	int nodeNum=graph->GetNodeNum();
	int edgeNum=graph->GetEdgeNum();
	int count=0;//已经分离一个顶点(首顶点0)
	//初始化lowCost与nearVex数组
	int *lowCost=new int[nodeNum];
	//存放生成树顶点集合内顶点到生成树外各个顶点的各边上的当前最小权值 
	int *nearVex=new int[nodeNum];
	//记录生成树顶点集合外各顶点距离集合内哪个顶点最近
	//初始化这两个数组 
	lowCost[0]=0;
	nearVex[0]=-1;//-1表示已经加入生成树的顶点
	for(int i=1;i<nodeNum;i++) 
		{
			lowCost[i]=graph->GetWeight(0,i);//顶点0到各点的代价 
			nearVex[i]=0;
		}
	for(int j=1;j<nodeNum;j++)//循环n-1次，加入n-1条边 
	{
		int vIndex=0;
		int minn=INF;
		//求生成树外顶点到生成树内顶点具有最小权值的边
		//vIndex为当前具有最小权值边的位置 
		for(int i=0;i<nodeNum;i++) 
		{
			if(nearVex[i]!=-1 && lowCost[i]<minn) 
			{
				vIndex=i;
				minn=lowCost[i];
			}
		}
		//把这条边加入不定长数组内记录,并将该树外顶点加入树内
		if(vIndex)//如果vIndex==0表示再也找不到要求顶点了 
		{
			Edge tempEdge;
			tempEdge.head=vIndex;
			tempEdge.tail=nearVex[vIndex];
			tempEdge.weight=lowCost[vIndex];
			nearVex[vIndex]=-1;//对该边已经加入生成树标记 
			edgeVector[count++]=tempEdge;//选出的边加入生成树 
			for(int i=1;i<nodeNum;i++)
			{
				if(nearVex[i]!=-1 && graph->GetWeight(vIndex,i)<lowCost[i])
				//i不在生成树之中 
				{
					lowCost[i]=graph->GetWeight(vIndex,i);
					nearVex[i]=vIndex;
				}
			}
		}	
	} 
	cout<<"生成Prim最小生成树!\n\n";
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
		cout<<"请输入操作: ";
		char ops;
		cin>>ops;
		switch(ops)
		{
		case 'A':
			//如果A做过了，给出提醒 
			if(AisDone) 
			{
				cout<<"您已做完A操作,请进行其他操作\n";
			}
			else 
			{
				cout<<"请输入顶点的个数:";
				cin>>num;
				//uf_set=new UF(num);
				cout<<"请依次输入各顶点的名称:\n";
				string name0;
				G=new Graph(num);
				edgeVector=new Edge[num+1];
				for(int i=0;i<num;i++) 
				{
					cin>>name0;
					G->node_name[name0]=i;//序号和名字存入map中 
				}
				AisDone=true;
			}
			cout<<endl;
			break;
		case 'B': 
		{
			if(!AisDone) cout<<"请先进行A操作\n";
			int num=G->GetNodeNum();
			string name1;
			string name2;
			int weight;
			do{
				cout<<"请输入两个顶点及边(中间用空格,以? ? 0结尾,中英文输入均可):";
				cin>>name1>>name2>>weight;
			} while(!G->InsertEdge(name1,name2,weight));
			cout<<endl;
			BisDone=true;
			break;
		}
		case 'C':
			if(!AisDone) 
			{
				cout<<"请先进行A操作\n";
				break;
			}
			else if(!BisDone) 
			{
				cout<<"请先进行B操作\n";
				break;
			}
			primTree(edgeVector,G);
			CisDone=true;
			break;
		case 'D':
			if(!AisDone) 
			{
				cout<<"请先进行A操作\n";
				break;
			}
			else if(!BisDone) 
			{
				cout<<"请先进行B操作\n";
				break;
			}
			else if(!CisDone) 
			{
				cout<<"请先进行C操作\n";
				break;
			}
			cout<<"最小生成树的顶点及边为: \n";
			for(int i=0;i<G->GetNodeNum()-1;i++) 
			{
				for(auto iter=G->node_name.begin();iter!=G->node_name.end();++iter)
					if(iter->second==edgeVector[i].head)
					//找到边上的头结点的序号对应的名字 
					{
						cout<<iter->first<<"-<"<<edgeVector[i].weight<<">-";
						break;
					}
				for(auto iter=G->node_name.begin();iter!=G->node_name.end();++iter)
					if(iter->second==edgeVector[i].tail)//找到边上的尾结点的序号对应的名字  	
						cout<<iter->first<<"\t\t";
				if((i+1)%4==0) cout<<endl;//一行输入四个 
			}
			cout<<endl<<endl;
			break;
		case 'E':
			isContinue=false;
			break;
		default:
			cout<<"错误的操作符,请确认后再输入\n";
			break;
		}
	}
	getchar();
	delete G;
	delete edgeVector;
	return 0;
}
