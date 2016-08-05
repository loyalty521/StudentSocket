#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0
#define DATAFILE "DATAFILE.WL"//数据保存文件名

typedef struct student {     //定义链表数据结构
    int sno;                 //学号
    char name[9];            //姓名
    int chinese;             //语文
    int math;                //数学
    int english;             //英语
    int clanguage;           //C语言
    int sport;               //体育
    int score;               //总成绩
    struct student *next;
}STD;

void create_item_student (STD * head);  //向指定的链表添加学生,并返回链表头
void put_student (STD * head);          //输出学号及成绩(欲输出链表头)
bool is_sno(STD *head,int sno);         //判断指定学号是否存在
bool is_socre(int socre);               //判断成绩合法性
void del_item_student(STD *head);       //通过学生的学号删除学生的信息
void change_student(STD *head);         //通过学号修改学生信息。
STD *read_data();                       //从文件中读取数据到链表
void save_data(STD *head);              //保存链表内的数据到文件
void order(STD *head);                  //排序
void order_sno(STD *head);              //按学号排序
void order_score(STD *head);            //按成绩排序


int main(int argc, const char *argv[])
{
    STD *head;
    int cmd;
    head = (STD *)malloc(sizeof(STD));
    head->sno = 0;
    head->next = NULL;
    while(cmd != 8){
        printf("①添加学生\n②显示成绩列表\n③删除学生\n④排序\n⑤保存数据\n⑥读取数据\n⑦修改\n⑧退出系统\n\n");
        printf("等待输入命令:");
        scanf("%d",&cmd);
        switch(cmd){
        case 1:
            create_item_student(head);
            break;
        case 2:
            put_student(head);
            break;
        case 3:
            del_item_student(head);
            break;
        case 4:
            order(head);
            break;
        case 5:
            save_data(head);
            break;
        case 6:
            head = read_data();
            break;
        case 7:
            change_student(head);
            break;
        case 8:
            exit(0);
            break;
        }
    }
    return 0;
}
void order_sno(STD *head)
{

}
void order(STD *head)
{
    int cmd;
    printf("请输入排序方式，1按学号排序，2按成绩排序:");
    scanf("%d",&cmd);
    if(cmd !=1 && cmd !=2)
        printf("输入错误\n");
    else
    {
        if(cmd == 1) {
            order_sno(head);
        }
        else{
            order_score(head);
        }
    }
}

void save_data(STD *head)
{
    STD *data;
    FILE *p = fopen(DATAFILE,"wb");
    data = head->next;
    while(data != NULL)
    {
        fwrite(data,sizeof(STD),1,p);
        data = data->next;
    }
    printf("文件保存完成\n");
    fclose(p);
}

STD *read_data()
{
    STD *head,*p;
    FILE *file = fopen(DATAFILE,"rb");
    head = (STD *)malloc(sizeof(STD));
    p=head;
    while(!feof(file))
    {
        STD *newhead = (STD *)malloc(sizeof(STD));
        memset(newhead,0,sizeof(newhead));
        fread(newhead,sizeof(STD),1,file);
        if(feof(file))
        {
            p->next = NULL;
            break;
        }
        p->next = newhead;
        p=newhead;
        p->next = NULL;
    }
    fclose(file);
    return head;
}

void change_student(STD *head)//通过学号修改学生信息。
{
    STD *p;
    int sno;
    p=head;
    int str[5];
    char name[20];
    printf("请输入要修改学生的学号：");
    scanf("%d",&sno);
    while(p != NULL){
        if(p->sno == sno)
            break;
        p=p->next;
    }
    if(p ==NULL){
        printf("没有找到相应的学号修改失败\n");
        return;
    }
    p->sno = sno;
    printf("请输入学生姓名:");
    scanf("%s",name);
    printf("请输入学生成绩(语文,数学,英语,C语言,体育,以逗号分隔):");
    scanf("%d,%d,%d,%d,%d",&str[0],&str[1],&str[2],&str[3],&str[4]);
    if( is_socre(str[0])!=0 && is_socre(str[1])!=0 && is_socre(str[2])!=0 && is_socre(str[3])!=0 && is_socre(str[4])!=0 )
    {
        p->score = str[0]+str[1]+str[2]+str[3]+str[4];
        p->chinese = str[0];
        p->math = str[1];
        p->english = str[2];
        p->clanguage = str[3];
        p->sport = str[4];
        strcpy(p->name,name);
        printf("修改学号为 %d 的学生信息，修改成功！",sno);
    }
    else
        printf("输入的成绩不合法，修改失败\n");
}
//通过学生的学号删除学生的信息
void del_item_student(STD *head)
{
    STD *p,*q;
    int sno;
    printf("请输入要删除学生的学号：");
    scanf("%d",&sno);
    p=head;
    while(p != NULL){
        if(p->sno == sno)
            break;
        q = p;
        p=p->next;
    }
    if(p->next ==NULL){
        printf("没有找到相应的学号删除失败\n");
        return;
    }
    q->next = p->next;
    free(p);
    printf("删除学生信息成功\n");

}
//判断指定学号是否存在
bool is_sno(STD *head,int sno)
{
    STD *p;
    p=head;
    while(p!=NULL)
    {
        if(p->sno == sno)
        {
            return false;
        }
        p = p->next;
    }
    return true;
}
//判断成绩合法性
bool is_socre(int socre)
{
    if(socre>0 && socre<150)
        return true;
    else
        return false;
}

//向指定的链表添加学生,并返回链表头
void create_item_student(STD *head)
{
    STD *p1,*p2;
    p1=head;
    while(p1->next != NULL){
        p1 = p1->next;
    }
    p2 = (STD *)malloc(sizeof(STD));
    p2->next = NULL;
    printf("请输入学号，如果输入负数或0终止读取数据:");
    scanf("%d",&p2->sno);
    while(p2->sno >0)
    {
        if(is_sno(head,p2->sno) != 0)
        {
            printf("请输入学生姓名:");
            scanf("%s",p2->name);
            printf("请输入学生成绩(语文,数学,英语,C语言,体育,以逗号分隔):");
            scanf("%d,%d,%d,%d,%d",&p2->chinese,&p2->math,&p2->english,&p2->clanguage,&p2->sport);
            if( is_socre(p2->chinese)!=0 && is_socre(p2->math)!=0 && is_socre(p2->english)!=0 && is_socre(p2->clanguage)!=0 && is_socre(p2->sport) != 0){
                p2->score = p2->chinese + p2->math + p2->english + p2->clanguage + p2->sport;
                p1->next = p2;
                p1 = p2;
                p2 = (STD *)malloc(sizeof(STD));
                p2->next=NULL;
            }
            else
                printf("输入的成绩不合法，请重新录入学生信息\n");
        }
        else
            printf("输入的学号已存在,请重新输入！\n");
        printf("请输入学号，如果输入负数或0终止读取数据:");
        scanf("%d",&p2->sno);
    }
}

//输出学号及成绩(欲输出链表头)
void put_student (STD * head)
{
    STD *pstudent = head->next;

    printf (" --------------\n");
    printf ("|某班学生成绩表|\n");
    printf (" --------------\n");
    printf (" ----    ----    ----    ----    ----    -----    ----    ------    --------\n");
    printf ("|学号|  |姓名|  |语文|  |数学|  |英语|  |C语言|  |体育|  |总成绩|  |平均成绩|\n");
    printf (" ----    ----    ----    ----    ----    -----    ----    ------    --------\n");//8,8,8,8,9,8,10,12
    while(pstudent!=NULL){ 
        printf("%-8d%-8s%-8d%-8d%-8d%-9d%-8d%-10d%-12d\n",pstudent->sno,pstudent->name ,pstudent->chinese,pstudent->math,
                    pstudent->english,pstudent->clanguage,pstudent->sport,pstudent->score, pstudent->score / 5);
            pstudent=pstudent->next;
    }
}


