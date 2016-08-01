#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct student {     //定义链表数据结构
    int sno;           //学号
    char name[20];     //姓名
    int chinese;      //语文
    int math;          //数学
    int english;       //英语
    int clanguage;      //C语言
    int sport;           //体育
    int score;           //总成绩
    struct student *next;
}STD;

//创建线性表，此函数学号输入负数或0终止读取数据
STD *addList(STD *pHead){
    STD *p1,*p2,*tmp;
    p1=p2= (STD *)malloc(sizeof(STD));
    printf("请输入学号，如果输入负数或0终止读取数据:");
    scanf("%d",&p1->sno);
    while(p1->sno > 0 ){
        printf("请输入学生姓名:");
        scanf("%s",p1->name);
        printf("---------------------------------------------\n");
        printf("请输入学生成绩(语文,数学,英语,C语言,体育,以逗号分隔):");
        scanf("%d,%d,%d,%d,%d",&p1->chinese,&p1->math,&p1->english,&p1->clanguage,&p1->sport);
        p1->score = p1->chinese + p1->math + p1->english + p1->clanguage + p1->sport;
        
        if(pHead == NULL)//将新节点的指针成员赋值为空。若是空表，将新节点连接到表头；若是非空表，将新节点接到表尾;
            pHead = p1;
        else{
            tmp = pHead;
            while(tmp->next == NULL){
                tmp=tmp->next;
            }
            tmp = p2;
            p2->next = p1;
        }
        p2 = p1;

        p1 = (STD *)malloc(sizeof(STD));
        printf("请输入学号，如果输入负数或0终止读取数据:");
        scanf("%d",&p1->sno);
    }
    printf("addList函数执行，链表创建成功\n");
    free(p2);
    free(p1);
    return pHead;   //返回链表的头指针
}

void printList(STD *pHead)
{
    if(NULL == pHead)
    {
        printf("printList函数执行，链表为空\n");
    }
    else
    {
        printf (" --------------\n");
        printf ("|某班学生成绩表|\n");
        printf (" --------------\n");
        printf (" ----    ----    ----    ----    ----    -----    ----    ------    --------\n");
        printf ("|学号|  |姓名|  |语文|  |数学|  |英语|  |C语言|  |体育|  |总成绩|  |平均成绩|\n");
        printf (" ----    ----    ----    ----    ----    -----    ----    ------    --------\n");
        while(NULL != pHead->next){
            printf("%-8d%-8s%-8d%-8d%-8d%-9d%-8d%-10d%-12d\n",pHead->sno,pHead->name ,pHead->chinese,pHead->math,
                              pHead->english,pHead->clanguage,pHead->sport,pHead->score, pHead->score / 5);
            pHead = pHead->next;
        }
    }
}

STD *deleteItemList(STD *pHead){
    STD *p1,*p2;
    p2 = pHead;
    int num,i;
    printf("请输入要删除学生数据的编号输入负数或0返回上一层:");
    scanf("%d",&num);
    while(p2->next != NULL)
    {
        if(p2->sno == num)
        {
            p1 = p2->next;
            p2 = p1;
            free(p1);
            return pHead;
        }
        p2=p2->next;
    }
    printf("删除失败，没有查询到学号为 %d 的学生 \n",num);
    return pHead;
}


int main(int argc, const char *argv[])
{
    STD *pHead;
    pHead = NULL;
    pHead = addList(pHead);
    printList(pHead);
    pHead = deleteItemList(pHead);
    printList(pHead);
    return 0;
}
