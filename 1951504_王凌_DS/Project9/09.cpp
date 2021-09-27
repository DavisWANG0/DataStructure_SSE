#include<iostream>
#include<cstdio>
#include<cstring>
#include<fstream>
#include<cstring>
#include<vector>
#include<stdlib.h> 
#include<iomanip>
using namespace std;
string INPUT_PATH="C:\\Users\\Ling Wang\\Desktop\\input.txt",OUTPUT_PATH="C:\\Users\\Ling Wang\\Desktop\\output.txt";
//ע��txt�ļ�Ҫ��ANSI���루�ڼ�������Windows����ϵͳ�У�ANSI �������GBK���룩����Ȼ�����������룡��
//��������������룬�����ʽ������UTF�ȸ�ʽ���ü��±��Ļ������ԡ����Ϊ������ȷ�ϡ�����������б����ʽ��ѡȡANSI��
//���п���ÿһ������֮��û���ÿո��������TAB������������� 
ifstream inf(INPUT_PATH);
ofstream outf(OUTPUT_PATH);

class course
{
public:
    string code;//�γ̱�� 
    string name;//�γ����� 
    string hours_string;//string���͵�ѧʱ�� 
	string Semester_string;//string���͵�ָ����ѧѧ�� 
    int hours;//int���͵�ѧʱ�� 
    int Semester;//int���͵�ָ����ѧѧ��
    vector<string> preCourse;//���޿γ̱��� 
    friend ifstream& operator>>(ifstream& input,course& c)//�������� 
	{
        string strline=""; 
        string temp="";//��ʼ�� 
        getline(inf,strline);
        int choice=1;//choice�������ĸ����� 
        for(int i=0;i<strline.length();i++)
        {
        	if(strline[i]!=' ')//ͨ���ո��ж϶�ȡ����ʲô 
        	{
        		if(choice<=4)
				//ǰ�ĸ��ֱ��ǿγ̱�ţ��γ����ƣ�ѧʱ����ָ������ѧ�� 
        		{
		        	switch(choice)
		        	{
		        		case 1:
		        			c.code+=strline[i];
		        			break;
		        		case 2:
		        			c.name+=strline[i];
		        			break;
		        		case 3:
		        			c.hours_string+=strline[i];
		        			break;
		        		case 4:
		        			c.Semester_string+=strline[i];
		        			break;
		        		default:
		        			break;
					}
				}
				else//�����������޿γ�
				{
					temp+=strline[i];
				}
			}
			else if(choice<=4) choice++;//�����ǰ�ĸ������Ļ�ֱ�Ӹ���choice 
			else if(choice>=5)
			//����Ƕ�ȡ�������޿γ̵Ļ�������choice��ͬʱ����¼�����temp 
			{
				c.preCourse.push_back(temp);
				temp="";
				choice++;
			}
		}
		if(temp!="") c.preCourse.push_back(temp);
		//���һλû�пո��޷�ͨ���ո��жϣ���������޿γ̵Ļ���Ҫ��¼ 
		//ת��char������ת��Ϊint 
		c.hours=atoi(c.hours_string.c_str());
		c.Semester=atoi(c.Semester_string.c_str()); 
        return input;
        
    }
};
int maxCourseNum[17];//�û�Ҫ���ÿѧ��ѡ�ε����� 
vector<course> courses;//��γ̵Ĳ��������� 
vector<course> topoSorting[17];//��¼ÿ��ѧ��ѡ����Щ�γ�
vector<int> succeed_course[10007];//��¼ÿһ�����޿γ̵����к�̿γ� 
int indegree[10007];//��� 
int hours[17];//��¼ÿѧ�ڵ�ѧʱ 
int compulsoryCourseNum[17];//��¼����:ÿһ��ѧ�� ָ������ѧ�ڵĿγ̵���Ŀ 
bool visted[10007];//��¼�γ���û���Ϲ� 
int semAfterCompulsoryCourse[10007];
//��¼ÿ�ſ�����Ӧ���ڵڼ�ѧ�ڲ���ѧ��������޿��ڵ�nѧ�ڣ���ô��̿γ̱���������(n+1)ѧ�ں�ѧϰ 
int totalHours=0;//��ѧʱ
int curTotalHours=0;//��ǰ��ѡѧʱ 
int tureDay[11]={0,1,3,5,2,4};
//���Ȱ�����1����3����5��Ȼ����2����4�������Ŀ�Ҫ�����ſ� 
int tureTime[5]={0,1,3,6,8};
//���ϵĴ�Σ���һ�ڿ���1��2����С�Σ��ڶ�����3��4��5����С��...
//����ö�ٵ��Ľڴ�ο�ʼ��С��ʱ��ֱ�Ϊ1,3,6,8 
int classTime[6][5]={{0,0,0,0,0},
                	 {0,2,3,2,3},
                	 {0,2,3,2,3},
                	 {0,2,3,2,3},
                	 {0,2,3,2,3},
                	 {0,2,3,2,3}};
                	 //�������  һ������������
					 //�ĸ����� һ�����Ľڿ������ϵĴ��
bool emptyClass[6][5];//��¼�����û�б����� 
int table[15][15];//���յĿα� 


void output()//��� 
{
    for(int i=1;i<=8;i++) 
	{
        memset(&table[0][0],0,sizeof(table));
        memset(emptyClass,1,sizeof(emptyClass));
		outf<<endl<<"��"<<i<<"ѧ��"<<endl;
        for(int j=0;j<topoSorting[i].size();j++) 
		{
			/*
			�˴�Ϊ��ʵ������Ŀ�ģ� 
			��һ�ſγ���3�ڿΣ������Ȱ���3�ڿ�������
			��3�ڿ������޷����ţ������Ȱ������ڿ�������
			���һ�ſγ���Ҫ���������죬Ϊ��ѧЧ���Ϻã���ò����������ڵ����죬�������Ȱ������2���Ͽ�
			*/ 
			while(topoSorting[i][j].hours>=3) 
			{
				bool f_find=0;
	            for(int Day=1;Day<=5;Day++) 
	                for(int Time=2;Time<=4;Time+=2) 
					{
						//[tureDay[d]][Time]��˼�ǵ�tureDay[d]��ĵ�t�ڿΣ���ڿο�������classTime[tureDay[d]][Time]��С�� 
	                    if(emptyClass[tureDay[Day]][Time] && topoSorting[i][j].hours>=3) 
	                   	//���[tureDay[d]][Time]��ڴ�ε�ʱ��û�б����� ���� �� ��ڿε�ʣ��ѧʱ��>=3 
						{
							f_find=1;//�ҵ�����δ���ŵĴ�� 
	                        emptyClass[tureDay[Day]][Time]=0;//������ڿ� 
	                        topoSorting[i][j].hours-=3;//��ڿε�ʣ��ѧʱ����3 
	                        for(int k=0;k<classTime[tureDay[Day]][Time];k++) table[tureDay[Day]][tureTime[Time]+k]=j+1;//����ڿ�¼��α� 
	                        //j+1����Ϊֻ��Ҫ��0���жϣ������Ŵ�1��ʼ�Ͳ������ 
	                        break;
	                    }
                }
                if(f_find==0) break;
            }
            while(topoSorting[i][j].hours>=2) 
            {
            	bool f_find=0;
	            for(int Day=1;Day<=5;Day++) 
	                for(int Time=1;Time<=3;Time+=2)   
	        		{
	        			if(emptyClass[tureDay[Day]][Time] && topoSorting[i][j].hours>=2) 
	                    //���[tureDay[d]][Time]��ڴ�ε�ʱ��û�б����� ���� ��ڿε�ʣ��ѧʱ��>=2 
						{
							f_find=1;//�ҵ�����δ���ŵĴ��
	                        emptyClass[tureDay[Day]][Time]=0;//������ڿ�
	                        topoSorting[i][j].hours-=2;//��ڿε�ʣ��ѧʱ����2
	                        for(int k=0;k<classTime[tureDay[Day]][Time];k++) table[tureDay[Day]][tureTime[Time]+k]=j+1;//����ڿ�¼��α�
	                        break;
	                    }
					}
				if(f_find==0) break;
			}
        }
        //����ٰ��ŵ��ڿ��ϵ����
        for(int j=0;j<topoSorting[i].size();j++)
            while(topoSorting[i][j].hours>=1)
            //��ѡ�ļ��ŵ�ѧʱ��û�������ʱ��ʣ��ѧʱ�����㣩
            { 
                for(int time=0;time<=49;time++)
				//ö����һ�����п����Ͽε�ʱ�䣬һ�ڿ�һ�ڿε�ö��(��һ��ѧʱһ��ѧʱ��ö��) 
                    if(table[(time/10)+1][time%10+1]==0 && topoSorting[i][j].hours>=1)
					//������ܵ�[(k/10)+1]��ĵ�[k%10+1]�ڿΣ���û�а��ſ� 
					{
                        table[(time/10)+1][time%10+1]=j+1;//��ôֱ�Ӱѿΰ����ڴ˴� 
                        topoSorting[i][j].hours--;//��ڿε�ʣ��ѧʱ��һ 
                    }
            }
                    
        for(int p=1;p<=10;p++)
		{
            for(int j=1;j<=5;j++)
                if(table[j][p]==0) outf<<setw(5)<<setiosflags(ios::left)<<"��  ";
                else outf<<setw(5)<<setiosflags(ios::left)<<topoSorting[i][table[j][p]-1].name<<"  ";
            outf<<endl;
        }
        outf<<endl;
    }
    cout<<endl<<"�α��棡"<<endl;
    inf.close();
    outf.close();
    exit(0);
}

int DFS(int currentSemester,int count)
//��������������ѣ��β�currentSemesterΪ��ǰѧ�ڣ�
//�β�countΪ��ǰ��ѡ�γ���Ŀ 
{
	//�������������ĸ�Ϊ��������ֹ������������
    if(count==courses.size()) output();
	//������п������ˣ������ 
    if(currentSemester==9) return 0;
	//�ܹ���ѧ���ѧ�ڣ������˾�˵���Ŵ��� 
    if(curTotalHours+(8-currentSemester+1)*50<totalHours) return 0;
    //�����ǰ��ѧʱ����δ������ѧ�����ε�ѧʱ������С����Ҫ�����ѧʱ����˵���Ŵ��� 
    if(hours[currentSemester]>50) return 0;
	//����α����Ļ���һ��һ��5��*10�ڿΣ� ����һѧ�ڳ���50ѧʱ��˵���Ŵ��� 
	//����������������������������������������
	 
	//����Ϊ������ö�ٹ��� 
    for(int i=0;i<courses.size();i++)
    if(topoSorting[currentSemester].size()<maxCourseNum[currentSemester])
	//�����û��ѡ����������Ը��ѡ��Ŀγ���Ŀ��ô����ѡ�� 
        if(courses[i].Semester==0 || courses[i].Semester==currentSemester)
		//�����ڿ�û��ָ������ѧ�ڣ��������ھ���ָ���Ŀ���ѧ�ھͼ��� 
	        if(indegree[i]==0 && !visted[i] && currentSemester>=semAfterCompulsoryCourse[i])                                
	        //�����ڿ����Ϊ0(���޿��Ѿ�������) ���� ֮ǰû��ѡ�� ���� �ڱ���Ҫѧ�����޿ε�ѧ��֮�� 
			{
	            int tempLeast[1007];
	            //�������������岽Ϊ������޸Ĳ��������ѡ�����ſλᷢ����Щ�仯��������
	            for(int j=0;j<succeed_course[i].size();j++)
				{
					indegree[succeed_course[i][j]]--;//ѡ�˿γ�i֮�󣬿γ�i�ĺ�̿γ���ȼ�һ 
					//succeed_course[i][j]��˼�����޿γ�i�ĺ���ĵ�j����̿γ� 
					tempLeast[succeed_course[i][j]]=semAfterCompulsoryCourse[succeed_course[i][j]];
					//��¼ԭ���Ķ�ά���������������㻹ԭ 
					semAfterCompulsoryCourse[succeed_course[i][j]]=currentSemester+1;
					//���޿γ�i�ĺ���ĵ�j����̿γ̣�����γ̱�����(currentSemester+1)ѧ�ڻ��Ժ����ѡ 
				} 
	            visted[i]=true;//������ſ��Ѿ�ѡ�� 
				curTotalHours+=courses[i].hours;//��ǰ��ʱ��������ѡ�γ̵Ŀ�ʱ 
				hours[currentSemester]+=courses[i].hours;//��ǰѧ�ڵĿ�ʱ��������ѡ�γ̵Ŀ�ʱ 
	            if(courses[i].Semester==currentSemester) compulsoryCourseNum[currentSemester]--;
	            //����ǵ�ǰѧ����ѡ��ָ���Ŀ���ѧ�ڣ� ��ôѡ����ڿ�֮��ָ����һѧ�ڵı��޿�������һ 
	            topoSorting[currentSemester].push_back(courses[i]);
	            //��ڿα���¼������α�֮�� 
	            //���������������������������������������������������������������������� 
	            
				DFS(currentSemester,count+1);//�������� 
				
	            //�������������岽�ǻ��ݣ���ԭδѡ���ſ�֮ǰ��״̬��������������������
				//�����ǻ�ԭ���ϲ��裬�������������ķ�����������׸�� 
	            visted[i]=false;
				curTotalHours-=courses[i].hours;
				hours[currentSemester]-=courses[i].hours;
	            if(courses[i].Semester==currentSemester) compulsoryCourseNum[currentSemester]++; 
	            topoSorting[currentSemester].pop_back();
	            for(int j=0;j<succeed_course[i].size();j++) 
				{
					indegree[succeed_course[i][j]]++;
					semAfterCompulsoryCourse[succeed_course[i][j]]=tempLeast[succeed_course[i][j]];
				}
				//����������������������������������������������������������������������
	        }
    if(compulsoryCourseNum[currentSemester]==0) DFS(currentSemester+1,count);//�����ѧ��û��ǿ����ѧ��ѧϰ�Ŀ��ˣ���ôֱ��ѧ��ѧ�ڵĿ� 
    return 0;
}

int main()
{
	string temp;
    cout<<"ʹ��Ĭ���ļ���ַ��?(Y/N)";
    cin>>temp;
    if(temp=="N") 
	{
        cout<<"����input.txt�ļ��ĵ�ַ: " ;
        cin>>INPUT_PATH;
        inf.open(INPUT_PATH);
        if(!inf) 
		{
            cerr<<"\n��ַ���󣬴򲻿��ļ���"<<endl;
            return 0; 
        }
    } 
    int totalCourseNum=0; 
    while(!inf.eof()) 
	{
        course tempCourse;
        inf>>tempCourse;
        totalCourseNum++;
        courses.push_back(tempCourse);
        totalHours+=tempCourse.hours;
        compulsoryCourseNum[tempCourse.Semester]++;
		//ָ��ѧ�ڱ��޿γ� ���ڵ�ѧ��λ�ü�һ 
    }
    cout<<"��������Ҫÿ��ѧ��(��8��ѧ��)ѡ�޵Ŀγ�����ע�⣺�γ����ܺ�Ϊ"<<totalCourseNum<<endl;
    int tempsum=0;
    for(int i=1;i<=8;i++) 
	{
		cin>>maxCourseNum[i];
		tempsum+=maxCourseNum[i];
	}
	if(tempsum!=totalCourseNum) 
	{
		cout<<"��γ���������ȣ�"<<endl; 
		system("pause");
		return 0;
	}
    for(int i=0;i<courses.size();i++) 
	{
        indegree[i]=courses[i].preCourse.size();
		//��ȶ���Ϊ���ſ����޿ε����� 
        for(int j=0;j<courses.size();j++)
            for(int k=0;k<courses[j].preCourse.size();k++)
                if(courses[j].preCourse[k]==courses[i].code)
				//����γ�i�ǿγ�j�����޿γ�
				{
                    succeed_course[i].push_back(j);
					//�γ�i�ĺ�̿γ̼���γ�j 
                    break;
                }
    }
    DFS(1,0);//���ѣ��ѳ����ֱ�����
	//����Ѳ��������˵�����ֿα��޷������޽� 
    cerr<<"\n��ǰ�α��޷����ţ�"<<endl;
    system("pause");
    return 0;
}
