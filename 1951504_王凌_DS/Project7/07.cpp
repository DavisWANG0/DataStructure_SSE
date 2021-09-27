#include<iostream>
using namespace std;
template <class T>
class MinHeap{
private:
    T *heap;
    int MaxSize,CurrentSize;//CurrentSize是当前堆的大小
	//MaxSize是算上所有元素后最大的大小，在本题中，因为规定了一共n块木头，所以MaxSize最大为n 
public:
    MinHeap(const int n);
    T top();//返回小根堆首最小元素 
    void push(int num);//在堆尾压入值为num的元素并进行调整 
    void pop();//在堆中弹出堆首最小值，并进行将队尾元素移到堆首，再进行调整 
};
template <class T>
MinHeap<T>::MinHeap(const int n)
{
    if(n<0)return;
    MaxSize=n;
    CurrentSize=0;
    heap=new T[MaxSize+1];
}
template <class T>
void MinHeap<T>::push(int num)
{
    heap[++CurrentSize]=num;
    for(int i=CurrentSize,j=i>>1;j;i=j,j=i>>1)
		if(heap[j]>heap[i]) swap(heap[j],heap[i]);
			else break; 
}
template <class T>
T MinHeap<T>::top()
{
	return heap[1];
}
template <class T>
void MinHeap<T>::pop()
{
    heap[1]=heap[CurrentSize--];//堆头最小值被队尾最后一个值覆盖
	for(int i=1,j=i<<1;j<=CurrentSize;i=j,j=i<<1)//i是相对于子节点j的父节点 
	{
		if(j+1<=CurrentSize&&heap[j+1]<heap[j]) j++;
			//在两个兄弟节点之间选取更小的那个
		if(heap[i]<heap[j]) break;
			else swap(heap[i],heap[j]);
	}
}
int main()
{
    int n,ans=0;
    cin>>n;
    MinHeap<int> min_que(n);
    for (int i=0;i<n;i++)
    {
    	int num;
        cin>>num;
        min_que.push(num);
    }
    for (int i=0;i<n-1;i++)
    {
    	int a,b;
        a=min_que.top();
        min_que.pop();
        b=min_que.top();
        min_que.pop();
        min_que.push(a+b);
        ans+=a+b;
    }
    cout<<ans;
    system("pause"); 
    return 0; 
}
