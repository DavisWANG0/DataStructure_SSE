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
//注意txt文件要是ANSI编码（在简体中文Windows操作系统中，ANSI 编码代表GBK编码），不然读出来是乱码！！
//如果读出来是乱码，编码格式可能是UTF等格式，用记事本的话，可以“另存为”，“确认”按键的左边有编码格式，选取ANSI。
//还有可能每一个数据之间没有用空格隔开，用TAB隔开会出现问题 
ifstream inf(INPUT_PATH);
ofstream outf(OUTPUT_PATH);

class course
{
public:
    string code;//课程编号 
    string name;//课程名称 
    string hours_string;//string类型的学时数 
	string Semester_string;//string类型的指定开学学期 
    int hours;//int类型的学时数 
    int Semester;//int类型的指定开学学期
    vector<string> preCourse;//先修课程编码 
    friend ifstream& operator>>(ifstream& input,course& c)//重载输入 
	{
        string strline=""; 
        string temp="";//初始化 
        getline(inf,strline);
        int choice=1;//choice决定存哪个变量 
        for(int i=0;i<strline.length();i++)
        {
        	if(strline[i]!=' ')//通过空格判断读取的是什么 
        	{
        		if(choice<=4)
				//前四个分别是课程编号，课程名称，学时数，指定开课学期 
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
				else//其它的是先修课程
				{
					temp+=strline[i];
				}
			}
			else if(choice<=4) choice++;//如果是前四个变量的话直接更新choice 
			else if(choice>=5)
			//如果是读取的是先修课程的话，更新choice的同时，记录并清空temp 
			{
				c.preCourse.push_back(temp);
				temp="";
				choice++;
			}
		}
		if(temp!="") c.preCourse.push_back(temp);
		//最后一位没有空格，无法通过空格判断，如果是先修课程的话需要记录 
		//转化char数组再转化为int 
		c.hours=atoi(c.hours_string.c_str());
		c.Semester=atoi(c.Semester_string.c_str()); 
        return input;
        
    }
};
int maxCourseNum[17];//用户要求的每学期选课的门数 
vector<course> courses;//存课程的不定长数组 
vector<course> topoSorting[17];//记录每个学期选的哪些课程
vector<int> succeed_course[10007];//记录每一个先修课程的所有后继课程 
int indegree[10007];//入度 
int hours[17];//记录每学期的学时 
int compulsoryCourseNum[17];//记录的是:每一个学期 指定开课学期的课程的数目 
bool visted[10007];//记录课程有没有上过 
int semAfterCompulsoryCourse[10007];
//记录每门课至少应该在第几学期才能学，如果先修课在第n学期，那么后继课程必须至少在(n+1)学期后学习 
int totalHours=0;//总学时
int curTotalHours=0;//当前已选学时 
int tureDay[11]={0,1,3,5,2,4};
//优先安排周1，周3，周5，然后周2，周4。连续的课要隔着排课 
int tureTime[5]={0,1,3,6,8};
//连上的大课，第一节课是1、2两节小课，第二节是3、4、5三节小课...
//所以枚举的四节大课开始的小课时间分别为1,3,6,8 
int classTime[6][5]={{0,0,0,0,0},
                	 {0,2,3,2,3},
                	 {0,2,3,2,3},
                	 {0,2,3,2,3},
                	 {0,2,3,2,3},
                	 {0,2,3,2,3}};
                	 //五个横行  一个星期有五天
					 //四个纵列 一天有四节可以连上的大课
bool emptyClass[6][5];//记录大课有没有被安排 
int table[15][15];//最终的课表 


void output()//输出 
{
    for(int i=1;i<=8;i++) 
	{
        memset(&table[0][0],0,sizeof(table));
        memset(emptyClass,1,sizeof(emptyClass));
		outf<<endl<<"第"<<i<<"学期"<<endl;
        for(int j=0;j<topoSorting[i].size();j++) 
		{
			/*
			此处为了实现以下目的： 
			如一门课程有3节课，则优先安排3节课连续上
			如3节课连续无法按排，再优先安排两节课连续上
			如果一门课程需要安排上两天，为教学效果较好，最好不安排在相邻的两天，比如优先安排相隔2天上课
			*/ 
			while(topoSorting[i][j].hours>=3) 
			{
				bool f_find=0;
	            for(int Day=1;Day<=5;Day++) 
	                for(int Time=2;Time<=4;Time+=2) 
					{
						//[tureDay[d]][Time]意思是第tureDay[d]天的第t节课，这节课可以连上classTime[tureDay[d]][Time]节小课 
	                    if(emptyClass[tureDay[Day]][Time] && topoSorting[i][j].hours>=3) 
	                   	//如果[tureDay[d]][Time]这节大课的时间没有被安排 并且 且 这节课的剩余学时数>=3 
						{
							f_find=1;//找到了尚未安排的大课 
	                        emptyClass[tureDay[Day]][Time]=0;//安排这节课 
	                        topoSorting[i][j].hours-=3;//这节课的剩余学时数减3 
	                        for(int k=0;k<classTime[tureDay[Day]][Time];k++) table[tureDay[Day]][tureTime[Time]+k]=j+1;//把这节课录入课表 
	                        //j+1是因为只有要用0来判断，如果标号从1开始就不会出错 
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
	                    //如果[tureDay[d]][Time]这节大课的时间没有被安排 并且 这节课的剩余学时数>=2 
						{
							f_find=1;//找到了尚未安排的大课
	                        emptyClass[tureDay[Day]][Time]=0;//安排这节课
	                        topoSorting[i][j].hours-=2;//这节课的剩余学时数减2
	                        for(int k=0;k<classTime[tureDay[Day]][Time];k++) table[tureDay[Day]][tureTime[Time]+k]=j+1;//把这节课录入课表
	                        break;
	                    }
					}
				if(f_find==0) break;
			}
        }
        //最后再安排单节课上的情况
        for(int j=0;j<topoSorting[i].size();j++)
            while(topoSorting[i][j].hours>=1)
            //当选的几门的学时还没有上完的时候（剩余学时大于零）
            { 
                for(int time=0;time<=49;time++)
				//枚举这一周所有可以上课的时间，一节课一节课地枚举(即一个学时一个学时地枚举) 
                    if(table[(time/10)+1][time%10+1]==0 && topoSorting[i][j].hours>=1)
					//如果这周第[(k/10)+1]天的第[k%10+1]节课，还没有安排课 
					{
                        table[(time/10)+1][time%10+1]=j+1;//那么直接把课安排在此处 
                        topoSorting[i][j].hours--;//这节课的剩余学时减一 
                    }
            }
                    
        for(int p=1;p<=10;p++)
		{
            for(int j=1;j<=5;j++)
                if(table[j][p]==0) outf<<setw(5)<<setiosflags(ios::left)<<"无  ";
                else outf<<setw(5)<<setiosflags(ios::left)<<topoSorting[i][table[j][p]-1].name<<"  ";
            outf<<endl;
        }
        outf<<endl;
    }
    cout<<endl<<"课表保存！"<<endl;
    inf.close();
    outf.close();
    exit(0);
}

int DFS(int currentSemester,int count)
//带拓扑排序的深搜，形参currentSemester为当前学期；
//形参count为当前已选课程数目 
{
	//————以下四个为搜索的终止条件————
    if(count==courses.size()) output();
	//如果所有课排完了，就输出 
    if(currentSemester==9) return 0;
	//总共四学年八学期，超过了就说明排错了 
    if(curTotalHours+(8-currentSemester+1)*50<totalHours) return 0;
    //如果当前总学时加上未来几个学期满课的学时数还是小于所要求的总学时数，说明排错了 
    if(hours[currentSemester]>50) return 0;
	//如果课报满的话，一周一共5天*10节课， 所以一学期超过50学时就说明排错了 
	//————————————————————
	 
	//以下为搜索的枚举过程 
    for(int i=0;i<courses.size();i++)
    if(topoSorting[currentSemester].size()<maxCourseNum[currentSemester])
	//如果还没有选满操作者意愿所选择的课程数目那么继续选课 
        if(courses[i].Semester==0 || courses[i].Semester==currentSemester)
		//如果这节课没有指定开课学期，或者现在就是指定的开课学期就继续 
	        if(indegree[i]==0 && !visted[i] && currentSemester>=semAfterCompulsoryCourse[i])                                
	        //如果这节课入度为0(先修课已经上完了) 并且 之前没有选过 并且 在必须要学的先修课的学期之后 
			{
	            int tempLeast[1007];
	            //————以下五步为标记与修改操作，如果选了这门课会发生哪些变化————
	            for(int j=0;j<succeed_course[i].size();j++)
				{
					indegree[succeed_course[i][j]]--;//选了课程i之后，课程i的后继课程入度减一 
					//succeed_course[i][j]意思是先修课程i的后面的第j个后继课程 
					tempLeast[succeed_course[i][j]]=semAfterCompulsoryCourse[succeed_course[i][j]];
					//记录原来的二维不定长变量，方便还原 
					semAfterCompulsoryCourse[succeed_course[i][j]]=currentSemester+1;
					//先修课程i的后面的第j个后继课程，这个课程必须在(currentSemester+1)学期或以后才能选 
				} 
	            visted[i]=true;//标记这门课已经选过 
				curTotalHours+=courses[i].hours;//当前课时数加上所选课程的课时 
				hours[currentSemester]+=courses[i].hours;//当前学期的课时数加上所选课程的课时 
	            if(courses[i].Semester==currentSemester) compulsoryCourseNum[currentSemester]--;
	            //如果是当前学期所选课指定的开课学期， 那么选了这节课之后，指定这一学期的必修课数量减一 
	            topoSorting[currentSemester].push_back(courses[i]);
	            //这节课被记录在排序课表之中 
	            //——————————————————————————————————— 
	            
				DFS(currentSemester,count+1);//继续深搜 
				
	            //————以下五步是回溯，还原未选这门课之前的状态——————————
				//由于是还原以上步骤，就是上述操作的反操作，不再赘述 
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
				//———————————————————————————————————
	        }
    if(compulsoryCourseNum[currentSemester]==0) DFS(currentSemester+1,count);//如果这学期没有强制这学期学习的课了，那么直接学下学期的课 
    return 0;
}

int main()
{
	string temp;
    cout<<"使用默认文件地址吗?(Y/N)";
    cin>>temp;
    if(temp=="N") 
	{
        cout<<"输入input.txt文件的地址: " ;
        cin>>INPUT_PATH;
        inf.open(INPUT_PATH);
        if(!inf) 
		{
            cerr<<"\n地址错误，打不开文件！"<<endl;
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
		//指定学期必修课程 所在的学期位置加一 
    }
    cout<<"输入你想要每个学期(共8个学期)选修的课程数！注意：课程数总和为"<<totalCourseNum<<endl;
    int tempsum=0;
    for(int i=1;i<=8;i++) 
	{
		cin>>maxCourseNum[i];
		tempsum+=maxCourseNum[i];
	}
	if(tempsum!=totalCourseNum) 
	{
		cout<<"与课程总数不相等！"<<endl; 
		system("pause");
		return 0;
	}
    for(int i=0;i<courses.size();i++) 
	{
        indegree[i]=courses[i].preCourse.size();
		//入度定义为这门课先修课的门数 
        for(int j=0;j<courses.size();j++)
            for(int k=0;k<courses[j].preCourse.size();k++)
                if(courses[j].preCourse[k]==courses[i].code)
				//如果课程i是课程j的先修课程
				{
                    succeed_course[i].push_back(j);
					//课程i的后继课程加入课程j 
                    break;
                }
    }
    DFS(1,0);//深搜，搜出结果直接输出
	//如果搜不出结果，说明这种课表无法编排无解 
    cerr<<"\n当前课表无法编排！"<<endl;
    system("pause");
    return 0;
}
