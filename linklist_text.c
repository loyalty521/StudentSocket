#include "linklist_text.h"

void order_sno(STD *head)
{

}
void order(STD *head)
{
    int cmd;
    printf("请输入排序方式，1按学号排序，2按成绩排序:");
    if(scanf("%d",&cmd) != 1)
    {
        printf("输入错误\n");
        return;
    }
    if(cmd !=1 && cmd !=2)
    {
        printf("输入错误\n");
        return;
    }
    else
    {
        if(cmd == 1) {
            order_sno(head);
        }
        else{
//            order_score(head);
        }
    }
}

void  __fflush()//清空读写缓冲区
{
    int c;
    while((c=getchar())!='\n'&&c!=EOF);//在GCC下这句话等价于VC6.0下的fflush(stdin)函数
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
        memset(newhead,0,sizeof(STD));
        if(fread(newhead,sizeof(STD),1,file) != 0);
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
    int sno,flag=0;
    p=head;
    int str[5];
    char name[20];
    
    while(flag != 1)
    {
        printf("请输入要修改学生的学号：");
        flag = scanf("%d",&sno);
        __fflush();
        if(flag != 1)
            printf("输入学号错误，请重新输入学号!!!\n");
    }
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
    flag = scanf("%s",name);
    __fflush();

    flag = 0;
    while(flag != 5)
    {
        printf("请输入学生成绩(语文,数学,英语,C语言,体育,以逗号分隔):");
        flag = scanf("%d,%d,%d,%d,%d",&str[0],&str[1],&str[2],&str[3],&str[4]);
        __fflush();
        if(flag != 5)
        printf("输入成绩出错请重新输入成绩！！！\n");
    }
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
    STD *p,*q=NULL;
    int sno,flag=0;
    while(flag != 1 )
    {
        printf("请输入要删除学生的学号：");
        flag = scanf("%d",&sno);
        __fflush();
        if(flag != 1)
            printf("输入学号错误，请从新输入学号：");
    }
    p=head;
    while(p->next != NULL){
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
    int flag = 0;
    p1=head;
    while(p1->next != NULL){
        p1 = p1->next;
    }
    p2 = (STD *)malloc(sizeof(STD));
    p2->next = NULL;
    while(flag != 1)
    {
        printf("请输入学号，如果输入负数或0终止读取数据:");
        flag = scanf("%d",&p2->sno);
        __fflush();
        if(flag != 1)
            printf("输入学号错误，请重新输入学号!!!\n");
    }
    while(p2->sno >0)
    {
        if(is_sno(head,p2->sno) != 0)
        {
            printf("请输入学生姓名:");
            flag = scanf("%s",p2->name);
            flag = 0;
            while(flag != 5)
            {
                printf("请输入学生成绩(语文,数学,英语,C语言,体育,以逗号分隔):");
                flag = scanf("%d,%d,%d,%d,%d",&p2->chinese,&p2->math,&p2->english,&p2->clanguage,&p2->sport);
                __fflush();
                if(flag != 5)
                    printf("输入成绩出错请重新输入成绩！！！\n");
            }
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
        flag = 0;
        while(flag != 1)
        {
            printf("请输入学号，如果输入负数或0终止读取数据:");
            flag = scanf("%d",&p2->sno);
            __fflush();
            if(flag != 1)
                printf("输入学号错误，请重新输入学号!!!\n");
        }
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


