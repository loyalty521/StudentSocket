#include <stdio.h>//标准输入输出
#include <malloc.h>//内存分配
#include <stdlib.h>
#include <string.h>
/*####说明####
简单学生管理系统      蔚蓝之链编写   QQ:2454238510  本人是C语言初学者,求喜欢C语言的骚年们共同交流技术
本人是C语言初学者,初学C语言没几个月,程序写的"很笨",不喜勿喷^_^  
vc++6.0编译无error,无warning
已实现功能:添加学生,列出学生信息列表,删除学生,退出,学号重复检查,排序功能,
多科成绩录入(求平均成绩,及总平均成绩),保存记录,读取记录,修改功能;
待实现功能:查询......
2014.12.1创建文件,开始编写,增加添加学生函数,增加列出学生函数,增加删除学生函数,退出    版本1.0
2014.12.2修改内容:增加学号重复检查函数,修复显示内容时程序终止,输出列表函数优化,添加学生函数优化  1.1
2014.12.3~2014.12.4修改内容:增加排序函数,删除函数内部优化,main函数内部改动,添加学生函数优化   1.2
2014.12.5~2014.12.7修改内容:增加多科目录入,添加函数优化,新增总成绩与平均成绩显示,排序函数优化,输出函数改动 1.3,更新到此告一段落,继续学习去(^_^)
2014.12.9~2014.12.13修改内容:新增保存函数,读取函数,主程序修改,新增链表清除函数1.4
2014.12.14修改内容:新增修改函数,新增宏定义MAX_SCORE and MAX_SNO,方便程序的修改,修改程序中所有warning,一些bug修正1.5
*/
//常量定义区+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define bool int //由于C语言中不存在bool型,所以这里把它定义成int型
#define true 1   //同上
#define false 0  //↑
#define LEN sizeof(struct student)   //动态内存分配空间大小
#define DATAFILE "DATAFILE.WL"//数据保存文件名
#define MAX_SCORE 150  //最高分数上限值
#define MAX_SNO 200     //最多录入学生上限值,即能输入的最大学号数
//END常量定义============================================================================================================

//声明函数=================================================================================================================
struct student * del_item_student (struct student * head,int sno,int * del_message);//删除指定学号节点(链表头,欲删除学号,处理结果(1为删除成功,0为删除失败)),返回删除后的链表头
struct student * create_item_student (struct student * head);//向指定的链表添加学生,并返回链表头
void put_student (struct student * head);//输出学号及成绩(欲输出链表头)
bool is_sno(struct student * head, int sno );//判断指定学号是否存在,如存在返回true,不存在返回false(链表头,欲判断学号)
struct student * order(struct student * head, enum ordertype type, int fs );//排序函数;(链表头,排序方式(asc或desc),排序类型(1为按学号,2为按总成绩))
bool save_data(struct student * head);//保存链表数据函数(欲保存链表头)
struct student * read_data(void);//读取数据到链表,并返回链表头
void clear(struct student * head);//清除函数,清除指定链表所有数据,释放内存空间
void amend_student(struct student * head, int sno);//修改函数,修改指定学号学生成绩信息(链表头,要修改成绩的学生学号)

struct student {     //定义链表数据结构
	int sno;           //学号
	char name[9];     //姓名
	int chinese;      //语文
	int math;          //数学
	int english;       //英语
	int clanguage;      //C语言
	int tiyu;           //体育
	int score;           //总成绩
	struct student *next;
};

enum ordertype{//定义排序枚举类型
asc,desc
};

//性感的分割线$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$主程序$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
int main ( void )
{
	struct student * head,* temp_h;//链表头,临时链表
	bool exit = false;
	short int value;//接受输入信息1,2,3,4       1表示添加信息,2显示信息,3删除信息,4排序,5退出
	int sno, del_message = 0;//学号,删除函数处理结果(1为删除成功,0为删除失败)
	int pxfs,pxlx;//排序方式,排序类型(方式asc\desc);(类型 1学号,2成绩)
	char is_quit;//表示是否退出,y或Y表示退出,否则不退出
	char is_save;//表示是否保存数据,y或Y表示保存,否则不保存
	char is_read;//表示是否读取数据,y或Y表示读取,否则不读取
	bool ssave;//表示是否保存成功,true表示成功,false表示保存失败
	int amend_sno; //表示要修改的学号
	head = (struct student *) malloc(LEN);//创建初始链表
//	head->sno =0;//链表赋初值
	head->next = NULL;
	do
	{
	printf("蔚蓝学生管理系统v1.5(C语言版)QQ:2454238510\n\n");
	printf("①添加学生\n②显示成绩列表\n③删除学生\n④排序\n⑤保存数据\n⑥读取数据\n⑦修改\n⑧退出系统\n\n");
	printf("等待命令输入:");
	fflush(stdin);//清空键盘缓冲区
	scanf("%d",&value);
	if(value  == 1)//添加
	{
		head = create_item_student(head);//添加信息
		printf("录入信息结束!\n");
		system("pause");
	}else if (value == 2)//显示
	{
		put_student(head);      //显示信息
		system("pause");
	}else if(value == 3)//删除
	{
		printf("请输入要删除的学生学号:");
		fflush(stdin);//清空键盘缓冲区
		scanf("%d",&sno);
		head = del_item_student(head,sno, &del_message);		//删除
		if(del_message == 1)
		{
			printf("删除成功!!!\n");
		}
		else{
			printf("删除失败!!!\n");
		}
		system ("pause");
	}else if(value == 4)//排序
	{
r:		printf ("请请输入排序方式(1升序,2降序):");
		fflush(stdin);
		scanf("%d",&pxfs);
		printf ("请输入排序类型(1按学号,2按成绩):");
		fflush(stdin);
		scanf("%d",&pxlx);
		if (pxfs >2 || pxfs <0 || pxlx > 2 || pxlx <0 )
		{
			printf ("排序方式或排序类型输入不符合规定!!!请重新输入!!!\n");
            system ("pause");
			goto r;
		}
		if(pxfs==1)
		{
		head = order(head, asc,pxlx);
		}
		else {
			head= order(head, desc, pxlx);
		}
		printf ("排序完成!!!\n");
	    system("pause");
	}else if(value == 5)//保存数据
	{
		is_save = 'N';
		printf("您是否要保存当前修改过的学生数据,以前的数据将被覆盖!\n(Y\\N):");
		fflush(stdin);
		scanf ("%c", &is_save);
		if (is_save == 'Y' || is_save == 'y')
		{
			ssave = save_data(head);
			if(ssave == true)
			{
				printf ("当前数据已成功保存到磁盘!\n");
				system("pause");
			}else{
			printf("保存失败或没有数据!\n");
			system("pause");
			}
		}
		else
		{
			printf ("您取消了保存数据操作!\n");
			system ("pause");

		}
	}else if(value == 6)//读取数据
	{
	    is_read = 'N';
		printf("您是否要读取磁盘数据,执行此操作将覆盖当前数据,是否继续?\n(Y\\N):");
		fflush(stdin);
		scanf("%c", &is_read);
		if(is_read == 'Y' || is_read =='y')
		{
			temp_h = read_data();
			if(temp_h == NULL)
			{
			printf ("数据读取失败!\n");
			system("pause");	
			}else{
			clear(head);//清空当前链表,释放空间
			head = temp_h;//读取新链表
			printf ("数据读取成功!\n");
			system("pause");
			}

		}
		else
	{
		printf("您取消了数据读取操作!\n");
		system ("pause");
	}
	}
	else if(value == 7)
	{
		amend_sno = 0;
		printf("请输入要修改的学生学号:");
		fflush(stdin);
		scanf ("%d",&amend_sno);
		if(amend_sno > 0 && amend_sno <= MAX_SNO)
		{
			amend_student(head, amend_sno);

		}
		else{
		printf ("学号输入不合法,学号为1-%d之间的数包括(1,%d)!!!\n",MAX_SNO,MAX_SNO);
			system("pause");
			continue;
		}
	}
	else if(value == 8)//退出
	{
		printf("您确定要退出蔚蓝学生成绩管理系统吗?(Y\\N):");
		fflush(stdin);
		scanf("%c",&is_quit);
		if(is_quit == 'Y' || is_quit == 'y')
		{
		exit = true;
		printf ("感谢使用蔚蓝学生成绩管理系统,再见!\n");
		system("pause");
		}
		
	}
	else{
		printf("请输入1-7之间的数!!!\n");
		system("pause");
	}
	
	system("cls");
	}while(exit == false);
	return 0;
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$主程序END$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//函数定义
#if(1)
struct student * del_item_student (struct student * head, int sno,int *message)//删除指定学号节点(链表头,欲删除学号,处理结果(1为删除成功,0为删除失败)),返回删除后的链表头
{
	struct student * p,* p1;
	p = head;
	do
	{

		
		if(p->sno==sno)
		{
			
			if(p == head)//如果第一个为要删除的值
			{
				head = head->next;//修改链表头
				//printf("已成功修改头指针sno=%d\n",head->sno);
			}
			else
			{
			
			p1->next = p->next;//将链表节点指向要删除的链表节点的下一节点
			free(p);//释放已删除的链表节点内存
			}
			*message = 1;
			break;
		}

	    p1 = p;//保存当前链表节点
		p = p->next;
		if(p->next==NULL && p->math >= 0 && p->math <= MAX_SNO)
		{
			*message = 0;
		}
	}while(p->next && p->math >= 0 && p->math <= MAX_SNO);

	return head;
	
}
#endif

struct student * create_item_student (struct student * head)       //向指定的链表添加学生,并返回链表头
{
	struct student *p1;
	int i=1;//i表示学生数
	int tempsno;//临时学号
	int scorearr[5],n;//分数数组,循环值
	char tempname[9];//临时姓名
    
	printf("提示:当学号为0时则终止添加,并返回主界面,姓名长度不能超过4个字\n\n");//输出提示信息

	p1 = head;
    while (p1->next != NULL)//寻找链表尾,找到后将p1指向链表尾以接受学生信息的添加
	{
		p1 = p1->next;
		i++;
	}


	do {
		p1->sno = 0;
sno:	printf("请输入学生%d学号与姓名[格式:学号,姓名]:",i);
		fflush(stdin);//清空键盘缓冲区
		if(scanf("%d,%s",&tempsno,&tempname) == 2)
		{
			;
		}
		else 
		{
			printf ("输入格式错误!请重新输入T_T\n");
			system("pause");
			goto sno;
		}
		if(tempsno != 0)
		{
			if (is_sno(head,tempsno) == false)//判断学号是否存在
			{
				p1->sno = tempsno;
			}
			else {
				printf ("学号[%d]已存在!!!\n",tempsno);
				goto sno;
			}
		}
		else{
			continue;
		}
		printf("---------------------------------------------\n");
		printf("请输入学生%d成绩(语文,数学,英语,C语言,体育,以逗号分隔):",i);
		for(n=0;n<=4;n++)//成绩数组赋初值
		{
			scorearr[n]=0;
		}
		fflush(stdin);//清空键盘缓冲区
		scanf("%d,%d,%d,%d,%d",&scorearr[0],&scorearr[1],&scorearr[2],&scorearr[3],&scorearr[4]);

		printf("*********************************************\n");
        //检测输入合法性
		if(p1->sno == 0)
		{
			;
		}
		else if(p1->sno < 1 || p1->sno > MAX_SNO)//判断学号是否合法,(1~200)
		{
			printf("学号输入不合法,学号为1-%d之间的数包括(1,%d)!!!\n",MAX_SNO,MAX_SNO);
			system("pause");
			continue;
		}
		else//判断成绩合法性
		{
			for(n=0;n<=4;n++)//检测成绩录入合法性
			{
				if (scorearr[n]<0 || scorearr[n]>MAX_SCORE)
				{
					printf("成绩输入不合法或成绩数值输入错误,各科成绩应为0-%d之间的数包括(0,%d)!!!\n",MAX_SCORE,MAX_SCORE);
					system("pause");
					continue;
				}
			}
			p1->sno = tempsno;
			p1->chinese = scorearr[0];
			p1->math = scorearr[1];
			p1->english = scorearr[2];
			p1->clanguage = scorearr[3];
			p1->tiyu = scorearr[4];
			strcpy(p1->name ,tempname);
			//求总成绩
			p1->score=scorearr[0]+scorearr[1]+scorearr[2]+scorearr[3]+scorearr[4];
			
		}


		if(p1->sno != 0)
		{
			p1->next = (struct student *) malloc(LEN);//create一个新节点给p1->next
			p1 = p1->next;//将新节点地址给p1
			p1->next = NULL;//↑
			

		}else{
		p1->sno = 0;
		}
		i++;
	}while (p1->sno != 0);//判断学号是否为0;为0退出添加




	return head;
}

#if(1)
void put_student (struct student * head)//输出学号及成绩(欲输出链表头)
{
	struct student *pstudent = head;
	struct student zcj;//总成绩
	int student_num = 0;//学生人数

	zcj.chinese = 0;
	zcj.clanguage  = 0;
	zcj.english = 0;
	zcj.math = 0;
	zcj.tiyu = 0;

	system("cls");
	printf (" --------------\n");
	printf ("|某班学生成绩表|\n");
	printf (" --------------\n");
	printf (" ----    ----    ----    ----    ----    -----    ----    ------    --------\n");
	printf ("|学号|  |姓名|  |语文|  |数学|  |英语|  |C语言|  |体育|  |总成绩|  |平均成绩|\n");
	printf (" ----    ----    ----    ----    ----    -----    ----    ------    --------\n");//8,8,8,8,9,8,10,12
	do{
		if(pstudent->sno != 0 && pstudent->math >= 0 && pstudent->math <= MAX_SNO)//输出成绩
		{
		printf("%-8d%-8s%-8d%-8d%-8d%-9d%-8d%-10d%-12d\n",pstudent->sno,pstudent->name ,pstudent->chinese,pstudent->math,
	      pstudent->english,pstudent->clanguage,pstudent->tiyu,pstudent->score, pstudent->score / 5);
		zcj.chinese = zcj.chinese + pstudent->chinese ;//计算各科总成绩
		zcj.clanguage = zcj.clanguage + pstudent->clanguage ;
		zcj.english = zcj.english + pstudent->english ;
		zcj.math = zcj.math + pstudent->math ;
		zcj.tiyu = zcj.tiyu + pstudent->tiyu ;
		student_num++;//记录总学生人数,表示链表不为空:
		pstudent=pstudent->next;
		}
	}while(pstudent->next && pstudent->math >= 0 && pstudent->math <= MAX_SNO);
    if (student_num >= 1)//判断链表是否为空
	{
		printf ("\n\n[总平均成绩]:(语文:%d,数学:%d,英语:%d,C语言:%d,体育:%d)\n",zcj.chinese/student_num, zcj.math / student_num,
			zcj.english / student_num, zcj.clanguage / student_num , zcj.tiyu / student_num);//输出总平均成绩
	}else
	{
		printf ("没有可以输出列表!\n\n");
	}
	
}
#endif

bool is_sno(struct student * head,int sno)//判断学号是否存在(头指针,学号),如学号存在返回true,不存在返回false
{
	struct student * p;
	p=head;
	do {
		if(p->sno == sno)
		{
			return true;
		}

		if (p->next != NULL)
		{
			p = p->next;
		}
	}while(p->next!=NULL);
	return false;
}
//排序函数    排序使用冒泡算法
struct student * order(struct student * head, enum ordertype type, int fs )//排序函数;(链表头,排序方式(asc或desc),排序类型(1为按学号,2为按总成绩))
{
	struct student *p,*rp,*ptemp,*rph;//要排序的链表,要返回的链表,临时排序链表,要返回的链表头
	int max,min;
	int pro_mess;//删除函数处理结果1,0
    if (head->sno == 0)
	{
		return head;
	}

	p = head;
	max = 0, min = 0;
	rp = (struct student *) malloc(LEN);//create一个新节点给rp
	rph = rp;
	do{
		ptemp = p;
		if(fs == 1)//按学号
		{
			max = ptemp->sno;//赋初值
			min = ptemp->sno;
		}
		else {   //按成绩
		max = ptemp->sno;
			min = ptemp->score;
			max = ptemp->score;
		}
		rp->sno = ptemp->sno ;
		rp->score =ptemp->score ;
		rp->tiyu = ptemp->tiyu ;
		rp->english = ptemp->english ;
		rp->chinese = ptemp->chinese ;
		rp->math = ptemp->math ;
		rp->clanguage = ptemp->clanguage ;
		strcpy(rp->name , ptemp->name) ;
		
		do{
		if(type == desc)//降序
		{
			if(fs == 1)//按学号
			{
				if(ptemp->sno > max)
				{
					max = ptemp->sno;
					rp->sno = ptemp->sno ;
					rp->score =ptemp->score ;
					rp->tiyu = ptemp->tiyu ;
					rp->english = ptemp->english ;
					rp->chinese = ptemp->chinese ;
					rp->math = ptemp->math ;
					rp->clanguage = ptemp->clanguage ;
					strcpy(rp->name , ptemp->name) ;
				}

			}
			else if (fs == 2)//按成绩
			{
				if(ptemp->score > max)
				{
					max = ptemp->score;
					rp->sno = ptemp->sno ;
					rp->score = ptemp->score ;
					rp->tiyu = ptemp->tiyu ;
					rp->english = ptemp->english ;
					rp->chinese = ptemp->chinese ;
					rp->math = ptemp->math ;
					rp->clanguage = ptemp->clanguage ;
					strcpy(rp->name , ptemp->name) ;
				}
			}
		}
		if(type == asc)//升序
		{
			if(fs == 1)//按学号
			{
				if(ptemp->sno < min)
				{
					min = ptemp->sno;
					rp->sno = ptemp->sno ;
					rp->score = ptemp->score ;
					rp->tiyu = ptemp->tiyu ;
					rp->english = ptemp->english ;
					rp->chinese = ptemp->chinese ;
					rp->math = ptemp->math ;
					rp->clanguage = ptemp->clanguage ;
					strcpy(rp->name , ptemp->name) ;
				}

			}
			else if (fs == 2)//按成绩
			{
				if(ptemp->score < min)
				{
					min = ptemp->score;
					rp->sno = ptemp->sno ;
					rp->score = ptemp->score ;
					rp->tiyu = ptemp->tiyu ;
					rp->english = ptemp->english ;
					rp->chinese = ptemp->chinese ;
					rp->math = ptemp->math ;
					rp->clanguage = ptemp->clanguage ;
					strcpy(rp->name , ptemp->name) ;
				}
			}
		}
        ptemp= ptemp->next ;

		}while(ptemp->next != NULL);
    p=del_item_student(p,rp->sno, &pro_mess);
	rp->next  = (struct student *) malloc(LEN);//create一个新节点给rp->next
	rp = rp->next ;
	if(p->next == NULL)
	{//添加链表尾信息        链表尾为一个指向NULL的空结构,以表示链表结束
		rp->score = 0;
		rp->sno = 0;
		rp->next = NULL;
	}
	}while(p->next != NULL);
return rph;//返回排序后链表头
}
//排序函数END;------------------------------------------------------------------------------
bool save_data(struct student * head)//保存链表数据函数(欲保存链表头),成功返回true,失败返回false
{
	FILE * fp;
	struct student * p;
	p = head;
	if (head->sno == 0)//如果链表为空
	{
		return false;//返回false
	}
	fp = fopen(DATAFILE, "wb+");//打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
	rewind(fp);//指向文件头
	do{
		if (p->sno != 0)
		{
		fwrite(p,LEN,1,fp);//保存结构体
		p = p->next;//
		}

	}while(p->sno != 0);
	fclose(fp);//关闭文件
	return true;
}
//savedata_END------
struct student * read_data(void)//读取数据到链表,并返回链表头,失败返回 NULL
{
	FILE * fp;
	struct student *head, *p;
	head = (struct student *) malloc(LEN);//创建初始链表

	p = head;
	fp = fopen(DATAFILE, "r");//以只读方式打开文件
	if(fp == NULL)//判断文件是否打开失败
	{
		fclose(fp);
		return NULL;
	}
    while(1)
    {
	 
	    
	if(feof(fp) == 0)
	{
		fread(p,LEN,1,fp) ;
		if (p->math >= 0 && p->math <=MAX_SNO)
		{
			p->next  = (struct student *)malloc(LEN);
		      p = p->next ;
			p->sno = 0;
			p->next = NULL;
		}	
	}
	else 
	{
	
	break;
	}
	}
	fclose(fp);
	return head;
}
//read_data.END-------------------
void clear(struct student * head)//清除函数,清除指定链表所有数据,释放内存空间
{
	struct student * p;
	while(1)
	{
		if(head->sno == 0)
		{
			free(head);//释放空间
			break;
		}
		else{
			p=head;
		head = head->next ;
		free(p);
		}
	}

}
//clear.END------------------------------------------------------------

void amend_student(struct student * head, int sno)//成绩修改函数,修改指定学号学生成绩信息(链表头,要修改成绩的学生学号)
{
	struct student *p;//链表
	int arr[6],retvalue,i;//临时成绩数组[语,数,英,C语言,体育],scanf返回值,i循环用
	char name[9]={'n'};
	p = head;
	if (is_sno(head,sno) == false)//判断要修改的学生是否存在
	{
		printf("您要修改的学号[%d]不存在!(?_?)\n",sno);
		system("pause");
		return;
	}
	while (1)
	{
		if(p->sno == sno)
		{
flag:		printf("当前要修的学生学号为[%d],姓名:%s,成绩:\n[语文:%d],[数学:%d],[英语:%d],[C语言:%d],[体育:%d],[总成绩:%d]\n\n",
				sno,p->name,p->chinese,p->math,p->english,p->clanguage,p->tiyu,p->score);
			printf("提示:各科成绩用逗号隔开,输入-1即表示不修改该科目成绩或学号,姓名不修改输入n!↖(^ω^)↗\n");
			printf("请输入新的学号与姓名[格式:学号,姓名]:");
			fflush(stdin);
			if(scanf("%d,%s",&arr[0],name) == 2)
			{
				printf ("请输入新的成绩[语,数,英,C语言,体育]:");
				retvalue = scanf("%d,%d,%d,%d,%d",&arr[1],&arr[2],&arr[3],&arr[4],&arr[5]);	
			}
			else
			{
				printf("学号\姓名格式输入错误,请重新输入T_T!\n");
				system("pause");
				goto flag;
			}
			if (retvalue == 5)
			{
				for(i=0;i<5;i++)//检测输入值是否合法
				{
					if(arr[i+1] <= MAX_SCORE && arr[i] >= -1 && arr[0] >=-1 && arr[0] <= MAX_SNO && arr[0] != 0)
					{
						;
					}else {
					printf ("您输入的值有误,各科目值不应该大于%d,学号不应该大于%d,学号不能为0,输入-1即表示不修改对应科目成绩\学号,姓名输入n即表示不修改,请重新输入!→_→\n",MAX_SCORE,MAX_SNO);
					system("pause");
					goto flag;
					}
				}
                //判断对应科目是否需要修改
				if (arr[0] != -1)
				{
					if (is_sno(head, arr[0]) == false)
					{
						if (arr[0] >= 0 && arr[0] <= MAX_SNO)
						{
							p->sno = arr[0];
						}
						else
						{
							printf("学号应该是大于0且小于%d的数!",MAX_SNO);
							system("pause");
							goto flag;
						}
						
					}
					else 
					{
						printf("你要修改成的学号已存在!未能修改成功!,请重新输入! T_T\n");
						goto flag;
					}
				}

				if(arr[1] != -1)
				{
					p->chinese = arr[1];
				}

				if(arr[2] != -1)
				{
					p->math = arr[2];
				}

				if(arr[3] != -1)
				{
					p->english = arr[3];
				}

				if(arr[4] != -1)
				{
					p->clanguage = arr[4];
				}

				if(arr[5] != -1)
				{
					p->tiyu = arr[5];
				}

				if(name[0] != 'n' && name[0] !='N')
				{
					strcpy(p->name,name);
				}
				p->score = p->chinese + p->math + p->english + p->clanguage + p->tiyu;//计算修改过的总成绩
				printf ("修改完毕!^_^\n");
				system ("pause");

				return;
			}
			else{
				printf ("你输入的的值有误,请以指定格式重新输入!→_→\n");
				system("pause");
				goto flag;
			}

		}
		p = p->next;
	if (p->math >= 0 && p->math <= MAX_SCORE)
	{
		;
	}
	else
	{
		printf("修改失败!\n");
		system("pause");
		
	}

	}
	
}
