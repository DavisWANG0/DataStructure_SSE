#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;
void BubbleSort(vector<int> &data,int &cnt)//冒泡排序 
{
	int n=data.size();
	for(int i=0;i<n-1;i++) 
	{
		for(int j=0;j<n-i-1;j++) 
		{
			if(data[j]>data[j+1]) 
			{  
				//大的元素向上浮，小的元素沉下来 
				swap(data[j],data[j+1]);
				cnt++;
			}
		}
	}
}
void SelectSort(vector<int> &data,int &cnt)//选择排序 
{
	int min_pos,n=data.size();//min_pos记录的是当前最小值位置
	for(int i=0;i<n-1;i++) 
	{
		min_pos=i;
		for(int j=i+1;j<n;j++)
			if(data[min_pos]>data[j]) min_pos=j;//比较大小，更新min_pos值
		if(min_pos!= i) 
		{
			swap(data[min_pos],data[i]);//将最小值交换到数组最左端
			cnt++;
		}
	}
}

void InsertSort(vector<int> &data,int &cnt)//直接插入排序 
{
	int n=data.size();
	for(int i=1;i<n;i++) 
	{
		//data[1]~data[j-1]为有序数列，data[j]到data[n]为无序数列
		//排序的时候是将无序数列第一个元素data[j]插入到左边 
		for(int j=i;j>=1 && data[j]<data[j-1];j--)
		//从右往左依次交换，直到无法交换为止，此时插入过程完成 
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
	//当gap==1时，f变为0，做完这一次就结束 
	{
		if(gap==1) f=0;
		//直接插入排序，间隔为gap 
		for(int i=gap;i<n;i++) 
		{ 
			//认为i左边的序列有序，将data[i]往左边的那一组序列插入 
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
		gap=gap/3+1;//knuth提出gap取(gap/3+1)时最好 
	}	
}
void QuickSort(vector<int> &data,int left,int right,int &cnt)//快速排序 
{
	if(left>=right) return;
	int i=left,j=right;
	int base=data[left];//取最左边的数为基准数
	//通过三个while循环来调整这个区间
	//使得基准数左边的比它小，右边的比它大 
	while(i<j)
	{
		while(data[j]>=base && i<j) j--;
		//从右往左找到下一个比基准数小的位置 
		while(data[i]<=base && i<j) i++;
		//从左往右找到下一个比基准数大的位置 
		if(i<j) 
		{
			swap(data[i],data[j]);
			cnt++;
		}
	}
	
	swap(data[left],data[i]);
	cnt++;
	//因为基准数一直在data[left]处 
	//所以这个交换为了让基准数归位，第i位小于基准数，第i+1也就是第j位大于基准数 
	
	//以基准数的位置为标准左右分别递归 
	QuickSort(data,left,i-1,cnt);//递归基准数左边
	QuickSort(data,i+1,right,cnt);//递归基准数右边
}

void Siftdown(vector<int> &array,int size,int pos,int &cnt)//堆化
{
	int left_child=pos*2+1,right_child=pos*2+2;
	while(right_child<size)//当结点有孩子的时候一直做 
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
	//左孩子还可能在长度内，判断是否需要调整 
	{
		swap(array[pos],array[left_child]);
		cnt++;
	}
	return;
}
void HeapSort(vector<int> &data,int &cnt)
{
	int n=data.size();
	for(int i=n-1;i>=0;i--) Siftdown(data,n,i,cnt);//初始堆 
	while(n>0)//重建最大堆 
	{
		swap(data[n-1],data[0]);
		n--;
		Siftdown(data,n,0,cnt);
	}
}

void Merge(vector<int> &data,vector<int> &output,int first,int mid,int last,int &cnt) 
{
	int left=first,right=mid+1;
	int tail=first;//记录output末尾的位置 
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
	//如果左序列未到头，而右序列已经结束
	while(right<=last) output[tail++]=data[right++];
	//如果右序列未到头，而左序列已经结束
}

//通过递归将待排序数列不断二分，进行排序
void Msort(vector<int> &data,vector<int> &output,int s,int t,int &cnt)//归并排序 
{
	vector<int> temp(data.size());
	if(s==t) output[s]=data[s];
	else 
	{
		int m=(s+t)/2;
		Msort(data,temp,s,m,cnt);//排左边的 
		Msort(data,temp,m+1,t,cnt);//排右边的 
		Merge(temp,output,s,m,t,cnt);//混合 
	}
}
void MergeSort(vector<int> &data,int &cnt)//基数排序 
{
	int n=data.size();
	vector<int> output(n);
	Msort(data,output,0,n-1,cnt);
	data=output;
}

int MaxBit(vector<int> &data)//求出数据中最大的位数
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
	for(i=1;i<=maxx;i++)//根据最大位数决定排序次数 
	{
		for(j=0;j<10;j++) count[j]=0;//每次分配前清空计数器 
		for(j=0;j<n;j++)//统计这一位上数字0~9的个数
		{
			k=(data[j]/radix)%10;
			count[k]++;
		}
		for(j=1;j<10;j++) count[j]=count[j-1]+count[j];//将temp中的位置依次分配
		for(j=n-1;j>=0;j--)//将所有记录依次收集到temp中
		{
			k=(data[j]/radix)%10;
			temp[count[k]-1]=data[j];
			cnt++;
			count[k]--;
		}
		data=temp;//将临时数组的内容复制到data中
		radix*=10;
	}
}
int main()
{
	vector<string> SortIndex=
	{"","冒泡排序","选择排序","直接插入排序","希尔排序","快速排序","堆排序 ","归并排序","基数排序"};
    cout<<"**            排序算法比较            **"<<endl;
    cout<<"========================================"<<endl;
    cout<<"**            1---冒泡排序            **"<<endl;
    cout<<"**            2---选择排序            **"<<endl;
    cout<<"**            3---直接插入排序        **"<<endl;
    cout<<"**            4---希尔排序            **"<<endl;
    cout<<"**            5---快速排序            **"<<endl;
    cout<<"**            6---堆排序              **"<<endl;
    cout<<"**            7---归并排序            **"<<endl;
    cout<<"**            8---基数排序            **"<<endl;
    cout<<"**            9---退出程序            **"<<endl;
    cout<<"========================================"<<endl;
	cout<<endl<<endl<<"请输入要产生的随机数的个数"<<endl;
	int n,choice=0;
	bool is_continue=true;
	cin>>n;
	while(is_continue)
	{
		vector<int> data(n);
		srand((unsigned)time(NULL));
		data=*new vector<int>();
		for(int i=0;i<n;i++) data.push_back(rand());
		cout<<endl<<"请选择排序算法：";
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
			cout<<"没有这个选项，请重新输入"<<endl;
			break;
			 
		}
		if(choice>=1 && choice<=8)
		{
			clock_t end=clock();
			cout<<SortIndex[choice]<<"所用时间:\t"<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
			cout<<SortIndex[choice]<<"交换次数:\t"<<cnt<<endl;
		}
	}
	system("pause"); 
	return 0;
}
