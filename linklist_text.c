#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student {     //定义链表数据结构
    int sno;           //学号
    char name[9];     //姓名
    int chinese;      //语文
    int math;          //数学
    int english;       //英语
    int clanguage;      //C语言
    int sport;           //体育
    int score;           //总成绩
    struct student *next;
}STD;

STD * create_item_student (STD * head);//向指定的链表添加学生,并返回链表头
void put_student (STD * head);//输出学号及成绩(欲输出链表头)

int main(int argc, const char *argv[])
{
    STD *head;
    head = (STD *)malloc(sizeof(STD));
    head->sno = 0;
    head->next = NULL;
    int cmd;
    while(cmd != 8){
        printf("①添加学生\n②显示成绩列表\n③删除学生\n④排序\n⑤保存数据\n⑥读取数据\n⑦修改\n⑧退出系统\n\n");
        printf("等待输入命令:");
        scanf("%d",&cmd);
        switch(cmd){
        case 1:
            head = create_item_student(head);
            break;
        case 2:
            put_student(head);
            exit(0);
            break;
        case 8:
            break;
        }
    }
    return 0;
}

STD *create_item_student(STD *head)
{
    STD *p1,*p2;
    int i=1;//i表示学生数
    int tempsno;//临时学号
    int scorearr[5],n;//分数数组,循环值
    char tempname[9];//临时姓名

    p1=head;
    while(p1->next != NULL){
        p1 = p1->next;
    }
    /*   // 在百度提问的主要是解决这个问题，为什么注释部分的代码不能执行呢。
    p2 = (STD *)malloc(sizeof(STD));
    p2->next = NULL;
    printf("请输入学号，如果输入负数或0终止读取数据:");
    scanf("%d",&p2->sno);
    while(p2->sno >0)
    {
        printf("请输入学生姓名:");
        scanf("%s",p2->name);
        printf("请输入学生成绩(语文,数学,英语,C语言,体育,以逗号分隔):");
        scanf("%d,%d,%d,%d,%d",&p2->chinese,&p2->math,&p2->english,&p2->clanguage,&p2->sport);
        p2->score = p2->chinese + p2->math + p2->english + p2->clanguage + p2->sport;
        p1->next = p2;
        p1 = p2;
        p2 = (STD *)malloc(sizeof(STD));
        printf("请输入学号，如果输入负数或0终止读取数据:");
        scanf("%d",&p2->sno);
    }
    */
    printf("请输入学号，如果输入负数或0终止读取数据:");
    scanf("%d",&tempsno);
    while(tempsno > 0){
        printf("请输入学生姓名:");
        scanf("%s",tempname);
        printf("请输入学生成绩(语文,数学,英语,C语言,体育,以逗号分隔):");
        scanf("%d,%d,%d,%d,%d",&scorearr[0],&scorearr[1],&scorearr[2],&scorearr[3],&scorearr[4]);
        p1->sno = tempsno;
        p1->chinese = scorearr[0];
        p1->math = scorearr[1];
        p1->english = scorearr[2];
        p1->clanguage = scorearr[3];
        p1->sport = scorearr[4];
        strcpy(p1->name ,tempname);
        //求总成绩
        p1->score=scorearr[0]+scorearr[1]+scorearr[2]+scorearr[3]+scorearr[4];

        printf("请输入学号，如果输入负数或0终止读取数据:");       
        scanf("%d",&tempsno);
            p1->next = (STD *) malloc(sizeof(STD));//create一个新节点给p1->next
            p1 = p1->next;//将新节点地址给p1
            p1->next = NULL;//↑
    }
    free(p1);
    return head;
}

void put_student (struct student * head)//输出学号及成绩(欲输出链表头)
{
    struct student *pstudent = head;
    struct student zcj;//总成绩
    int student_num = 0;//学生人数

    zcj.chinese = 0;
    zcj.clanguage  = 0;
    zcj.english = 0;
    zcj.math = 0;
    zcj.sport = 0;

    printf (" --------------\n");
    printf ("|某班学生成绩表|\n");
    printf (" --------------\n");
    printf (" ----    ----    ----    ----    ----    -----    ----    ------    --------\n");
    printf ("|学号|  |姓名|  |语文|  |数学|  |英语|  |C语言|  |体育|  |总成绩|  |平均成绩|\n");
    printf (" ----    ----    ----    ----    ----    -----    ----    ------    --------\n");//8,8,8,8,9,8,10,12
    do {
            printf("%-8d%-8s%-8d%-8d%-8d%-9d%-8d%-10d%-12d\n",pstudent->sno,pstudent->name ,pstudent->chinese,pstudent->math,
                    pstudent->english,pstudent->clanguage,pstudent->sport,pstudent->score, pstudent->score / 5);
            zcj.chinese = zcj.chinese + pstudent->chinese ;//计算各科总成绩
            zcj.clanguage = zcj.clanguage + pstudent->clanguage ;
            zcj.english = zcj.english + pstudent->english ;
            zcj.math = zcj.math + pstudent->math ;
            zcj.sport = zcj.sport + pstudent->sport ;
            student_num++;//记录总学生人数,表示链表不为空:
            pstudent=pstudent->next;
    }while(pstudent->next!=NULL && pstudent->math >= 0 && pstudent->math <= 150);
    printf (" --------------\n");
    if (student_num >= 1)//判断链表是否为空
    {
    printf (" --------------\n");
        printf ("\n\n[总平均成绩]:(语文:%d,数学:%d,英语:%d,C语言:%d,体育:%d)\n",zcj.chinese/student_num, zcj.math / student_num,
                zcj.english / student_num, zcj.clanguage / student_num , zcj.sport / student_num);//输出总平均成绩
    }else
    {
        printf ("没有可以输出列表!\n\n");
    }

}


