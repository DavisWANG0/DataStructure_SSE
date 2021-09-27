#include<iostream>
using namespace std;
template <class T>
class MinHeap{
private:
    T *heap;
    int MaxSize,CurrentSize;//CurrentSize�ǵ�ǰ�ѵĴ�С
	//MaxSize����������Ԫ�غ����Ĵ�С���ڱ����У���Ϊ�涨��һ��n��ľͷ������MaxSize���Ϊn 
public:
    MinHeap(const int n);
    T top();//����С��������СԪ�� 
    void push(int num);//�ڶ�βѹ��ֵΪnum��Ԫ�ز����е��� 
    void pop();//�ڶ��е���������Сֵ�������н���βԪ���Ƶ����ף��ٽ��е��� 
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
    heap[1]=heap[CurrentSize--];//��ͷ��Сֵ����β���һ��ֵ����
	for(int i=1,j=i<<1;j<=CurrentSize;i=j,j=i<<1)//i��������ӽڵ�j�ĸ��ڵ� 
	{
		if(j+1<=CurrentSize&&heap[j+1]<heap[j]) j++;
			//�������ֵܽڵ�֮��ѡȡ��С���Ǹ�
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
