#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Student
{
    int no;
    char name[10];
    float score[3];  //three scores
    float average;  //average score
    struct Student *next;
}Student;
void Initial(Student *p)
{
    p=(Student*)malloc(sizeof(Student));//the head of the linklist
    p->next=NULL;
}
void Input(Student *p)
{
    Student *stu=(Student*)malloc(sizeof(Student));
    printf("学号："); scanf("%d",&stu->no);
    printf("姓名："); scanf("%s",stu->name);
    printf("成绩1："); scanf("%f",&stu->score[0]);
    printf("成绩2："); scanf("%f",&stu->score[1]);
    printf("成绩3："); scanf("%f",&stu->score[2]);
    stu->average=(stu->score[0]+stu->score[1]+stu->score[2])/3;
    stu->next=NULL;
    Student *ps=(Student*)malloc(sizeof(Student));
    ps=p;
    while(ps->next)
        ps=ps->next;
    ps->next=stu;
    //free(ps);
}
void Output(Student *p)
{
    Student *ps=(Student*)malloc(sizeof(Student));
    ps=p->next;
    printf("学号\t姓名\t成绩1\t成绩2\t成绩3\t平均分\n");
    while(ps!=NULL)
    {
        printf("%d\t",ps->no);
        printf("%s\t",ps->name);
        printf("%.1f\t",ps->score[0]);
        printf("%.1f\t",ps->score[1]);
        printf("%.1f\t",ps->score[2]);
        printf("%.1f\t\n",ps->average);
        ps=ps->next;  
    }
    free(ps);
}
void Find(Student *p)
{
    Student *ps=(Student*)malloc(sizeof(Student));
    ps=p->next;
    char name[10];
    printf("输入要查询的学生姓名:");
    scanf("%s",name);
    while(strcmp(ps->name,name)!=0) //相同时为0
        ps=ps->next;  

    printf("学号\t姓名\t成绩1\t成绩2\t成绩3\t平均分\n");
    printf("%d\t",ps->no);
    printf("%s\t",ps->name);
    printf("%.1f\t",ps->score[0]);
    printf("%.1f\t",ps->score[1]);
    printf("%.1f\t",ps->score[2]);
    printf("%.1f\t\n",ps->average);

}
void swap(Student *p1, Student *p2) //swap two nodes for sorting
{
    Student *temp=(Student*)malloc(sizeof(Student));
    temp->no=p1->no;
    strcpy(temp->name,p1->name);
    temp->score[0]=p1->score[0];
    temp->score[1]=p1->score[1];
    temp->score[2]=p1->score[2];
    temp->average=p1->average;

    p1->no=p2->no;
    strcpy(p1->name,p2->name);
    p1->score[0]=p2->score[0];
    p1->score[1]=p2->score[1];
    p1->score[2]=p2->score[2];
    p1->average=p2->average;

    p2->no=temp->no;
    strcpy(p2->name,temp->name);
    p2->score[0]=temp->score[0];
    p2->score[1]=temp->score[1];
    p2->score[2]=temp->score[2];
    p2->average=temp->average;
    free(temp);
}
void Sort(Student *p) //sort by average
{
    Student *p1=(Student*)malloc(sizeof(Student));
    Student *p2=(Student*)malloc(sizeof(Student));
    p1=p->next;
    while(p1)
    {
        float avg=p1->average;
        p2=p1->next;
        while(p2)
        {
            if( avg< (p2->average))
            {
                swap(p1,p2);
                avg=p2->average;
            }
            p2=p2->next;
        }
        p1=p1->next;
    }
}
void Insert(Student *p)
{
    printf("按平均分高低插入数据!\n"); 
    Student *stu=(Student*)malloc(sizeof(Student));//the data being inserted

    printf("学号："); scanf("%d",&stu->no);
    printf("姓名："); scanf("%s",stu->name);
    printf("成绩1："); scanf("%f",&stu->score[0]);
    printf("成绩2："); scanf("%f",&stu->score[1]);
    printf("成绩3："); scanf("%f",&stu->score[2]);
    stu->average=(stu->score[0]+stu->score[1]+stu->score[2])/3;
    stu->next=NULL;

    Student *p1=(Student*)malloc(sizeof(Student));//temp
    p1=p;
    while(p1->next && ((p1->next)->average) >(stu->average))
        p1=p1->next;
    //p1=p1->next;
    stu->next=p1->next;
    p1->next=stu;
}
void Menu(Student *p)
{
    int select;
    printf("您好，欢迎使用学生成绩管理系统！\n");
    printf("1:输入学生成绩数据\n2：输出全部学生信息\n3：按姓名查找学生记录\n4：按平均成绩进行排序\n5：按平均成绩高低插入数据\n6:退出\n");
    scanf("%d",&select);
    while(select<=6 && select>0)
    {
        switch(select)
        {
            case 1: Input(p);break;
            case 2: Output(p);break;
            case 3: Find(p);  break;
            case 4: Sort(p); break;
            case 5: Insert(p); break;
            case 6: printf("成功退出，欢迎再次使用！\n"); return ; break;
        }
        printf("1:输入学生成绩数据\n2：输出全部学生信息\n3：按姓名查找学生记录\n4：按平均成绩进行排序\n5：按平均成绩高低插入数据\n6:退出\n");
        scanf("%d",&select);
    }

}
int main()
{
    Student *head=(Student*)malloc(sizeof(Student));
    Menu(head);
}
