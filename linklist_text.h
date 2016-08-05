#ifndef __LIST_TEXT_DEF_H
#define __LIST_TEXT_DEF_H

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
void  __fflush();                       //清空读写缓冲区


#endif

