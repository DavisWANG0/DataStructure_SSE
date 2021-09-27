#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;
void BubbleSort(vector<int> &data,int &cnt)//ð������ 
{
	int n=data.size();
	for(int i=0;i<n-1;i++) 
	{
		for(int j=0;j<n-i-1;j++) 
		{
			if(data[j]>data[j+1]) 
			{  
				//���Ԫ�����ϸ���С��Ԫ�س����� 
				swap(data[j],data[j+1]);
				cnt++;
			}
		}
	}
}
void SelectSort(vector<int> &data,int &cnt)//ѡ������ 
{
	int min_pos,n=data.size();//min_pos��¼���ǵ�ǰ��Сֵλ��
	for(int i=0;i<n-1;i++) 
	{
		min_pos=i;
		for(int j=i+1;j<n;j++)
			if(data[min_pos]>data[j]) min_pos=j;//�Ƚϴ�С������min_posֵ
		if(min_pos!= i) 
		{
			swap(data[min_pos],data[i]);//����Сֵ���������������
			cnt++;
		}
	}
}

void InsertSort(vector<int> &data,int &cnt)//ֱ�Ӳ������� 
{
	int n=data.size();
	for(int i=1;i<n;i++) 
	{
		//data[1]~data[j-1]Ϊ�������У�data[j]��data[n]Ϊ��������
		//�����ʱ���ǽ��������е�һ��Ԫ��data[j]���뵽��� 
		for(int j=i;j>=1 && data[j]<data[j-1];j--)
		//�����������ν�����ֱ���޷�����Ϊֹ����ʱ���������� 
		{
			swap(data[j],data[j-1]); 
            cnt++;
		} 
	}
}
void ShellSort(vector<int> &data,int &cnt)
{
	int gap,n=data.size();
	bool f=1;
	while(f)
	//��gap==1ʱ��f��Ϊ0��������һ�ξͽ��� 
	{
		if(gap==1) f=0;
		//ֱ�Ӳ������򣬼��Ϊgap 
		for(int i=gap;i<n;i++) 
		{ 
			//��Ϊi��ߵ��������򣬽�data[i]����ߵ���һ�����в��� 
			int j=i-gap; 
			int temp=data[i]; 
			for(;j>=0;j-=gap) 
			{ 
				if(data[j]>temp) 
				{ 
					data[j+gap]=data[j];
					cnt++; 
				}
				else break;
			}
			data[j+gap]=temp; 
			cnt++; 
		}
		gap=gap/3+1;//knuth���gapȡ(gap/3+1)ʱ��� 
	}	
}
void QuickSort(vector<int> &data,int left,int right,int &cnt)//�������� 
{
	if(left>=right) return;
	int i=left,j=right;
	int base=data[left];//ȡ����ߵ���Ϊ��׼��
	//ͨ������whileѭ���������������
	//ʹ�û�׼����ߵı���С���ұߵı����� 
	while(i<j)
	{
		while(data[j]>=base && i<j) j--;
		//���������ҵ���һ���Ȼ�׼��С��λ�� 
		while(data[i]<=base && i<j) i++;
		//���������ҵ���һ���Ȼ�׼�����λ�� 
		if(i<j) 
		{
			swap(data[i],data[j]);
			cnt++;
		}
	}
	
	swap(data[left],data[i]);
	cnt++;
	//��Ϊ��׼��һֱ��data[left]�� 
	//�����������Ϊ���û�׼����λ����iλС�ڻ�׼������i+1Ҳ���ǵ�jλ���ڻ�׼�� 
	
	//�Ի�׼����λ��Ϊ��׼���ҷֱ�ݹ� 
	QuickSort(data,left,i-1,cnt);//�ݹ��׼�����
	QuickSort(data,i+1,right,cnt);//�ݹ��׼���ұ�
}

void Siftdown(vector<int> &array,int size,int pos,int &cnt)//�ѻ�
{
	int left_child=pos*2+1,right_child=pos*2+2;
	while(right_child<size)//������к��ӵ�ʱ��һֱ�� 
	{
		if(array[pos]>=array[left_child] && array[pos]>=array[right_child]) return;
		if(array[left_child]>=array[right_child]) 
		{
			swap(array[pos],array[left_child]);
			pos=left_child;
			cnt++;
		}
		else 
		{
			swap(array[pos],array[right_child]);
			pos=right_child;
			cnt++;
		}
		left_child=pos*2+1,right_child=pos*2+2;
	}
	if(left_child<size&&array[left_child]>array[pos])
	//���ӻ������ڳ����ڣ��ж��Ƿ���Ҫ���� 
	{
		swap(array[pos],array[left_child]);
		cnt++;
	}
	return;
}
void HeapSort(vector<int> &data,int &cnt)
{
	int n=data.size();
	for(int i=n-1;i>=0;i--) Siftdown(data,n,i,cnt);//��ʼ�� 
	while(n>0)//�ؽ����� 
	{
		swap(data[n-1],data[0]);
		n--;
		Siftdown(data,n,0,cnt);
	}
}

void Merge(vector<int> &data,vector<int> &output,int first,int mid,int last,int &cnt) 
{
	int left=first,right=mid+1;
	int tail=first;//��¼outputĩβ��λ�� 
	while(left<=mid && right<=last) 
	{
		if(data[left]<=data[right]) 
		{
			output[tail++]=data[left++];
			cnt++;
		}
		else if(data[right]<data[left]) 
		{
			output[tail++]=data[right++];
			cnt++;
		}
	}
	while(left<=mid) output[tail++]=data[left++];
	//���������δ��ͷ�����������Ѿ�����
	while(right<=last) output[tail++]=data[right++];
	//���������δ��ͷ�����������Ѿ�����
}

//ͨ���ݹ齫���������в��϶��֣���������
void Msort(vector<int> &data,vector<int> &output,int s,int t,int &cnt)//�鲢���� 
{
	vector<int> temp(data.size());
	if(s==t) output[s]=data[s];
	else 
	{
		int m=(s+t)/2;
		Msort(data,temp,s,m,cnt);//����ߵ� 
		Msort(data,temp,m+1,t,cnt);//���ұߵ� 
		Merge(temp,output,s,m,t,cnt);//��� 
	}
}
void MergeSort(vector<int> &data,int &cnt)//�������� 
{
	int n=data.size();
	vector<int> output(n);
	Msort(data,output,0,n-1,cnt);
	data=output;
}

int MaxBit(vector<int> &data)//�������������λ��
{
	int maxx=1,flag=10;
	for(int i=0;i<data.size();i++) 
	{
		while(data[i]>flag) 
		{
			flag*=10;
			maxx++;
		}
	}
	return maxx;
}

void RadixSort(vector<int> &data,int &cnt)
{
	int n=data.size(),maxx=MaxBit(data),radix=1;
	int i,j,k;
	vector<int> temp(n),count(10);
	for(i=1;i<=maxx;i++)//�������λ������������� 
	{
		for(j=0;j<10;j++) count[j]=0;//ÿ�η���ǰ��ռ����� 
		for(j=0;j<n;j++)//ͳ����һλ������0~9�ĸ���
		{
			k=(data[j]/radix)%10;
			count[k]++;
		}
		for(j=1;j<10;j++) count[j]=count[j-1]+count[j];//��temp�е�λ�����η���
		for(j=n-1;j>=0;j--)//�����м�¼�����ռ���temp��
		{
			k=(data[j]/radix)%10;
			temp[count[k]-1]=data[j];
			cnt++;
			count[k]--;
		}
		data=temp;//����ʱ��������ݸ��Ƶ�data��
		radix*=10;
	}
}
int main()
{
	vector<string> SortIndex=
	{"","ð������","ѡ������","ֱ�Ӳ�������","ϣ������","��������","������ ","�鲢����","��������"};
    cout<<"**            �����㷨�Ƚ�            **"<<endl;
    cout<<"========================================"<<endl;
    cout<<"**            1---ð������            **"<<endl;
    cout<<"**            2---ѡ������            **"<<endl;
    cout<<"**            3---ֱ�Ӳ�������        **"<<endl;
    cout<<"**            4---ϣ������            **"<<endl;
    cout<<"**            5---��������            **"<<endl;
    cout<<"**            6---������              **"<<endl;
    cout<<"**            7---�鲢����            **"<<endl;
    cout<<"**            8---��������            **"<<endl;
    cout<<"**            9---�˳�����            **"<<endl;
    cout<<"========================================"<<endl;
	cout<<endl<<endl<<"������Ҫ������������ĸ���"<<endl;
	int n,choice=0;
	bool is_continue=true;
	cin>>n;
	while(is_continue)
	{
		vector<int> data(n);
		srand((unsigned)time(NULL));
		data=*new vector<int>();
		for(int i=0;i<n;i++) data.push_back(rand());
		cout<<endl<<"��ѡ�������㷨��";
		cin>>choice;
		int cnt=0;
		clock_t start=clock();
		switch(choice)
		{
		case 1:
			BubbleSort(data,cnt);
			break;
		case 2:
			SelectSort(data,cnt);
			break;
		case 3:
			InsertSort(data,cnt);
			break;
		case 4:
			ShellSort(data,cnt);
			break;
		case 5:
			QuickSort(data,0,data.size()-1,cnt);
			break;
		case 6:
			HeapSort(data,cnt);
			break;
		case 7:
			MergeSort(data,cnt);
			break;
		case 8:
			RadixSort(data,cnt);
			break;
		case 9:
			is_continue=false;
			break;
		default: 
			cout<<"û�����ѡ�����������"<<endl;
			break;
			 
		}
		if(choice>=1 && choice<=8)
		{
			clock_t end=clock();
			cout<<SortIndex[choice]<<"����ʱ��:\t"<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
			cout<<SortIndex[choice]<<"��������:\t"<<cnt<<endl;
		}
	}
	system("pause"); 
	return 0;
}
