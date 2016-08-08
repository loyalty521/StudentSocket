#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linklist_text.h"

int main(int argc, const char *argv[])
{
    STD *head;
    int cmd,flag =0;
    head = (STD *)malloc(sizeof(STD));
    while(cmd != 8 )
    {
        flag = 0;
        while(flag != 1)
        {
            printf("①添加学生\n②显示成绩列表\n③删除学生\n④排序\n⑤保存数据\n⑥读取数据\n⑦修改\n⑧退出系统\n\n");
            printf("等待输入命令:");
            flag = scanf("%d",&cmd);
            __fflush();
            if(flag != 1)
                printf("输入命令错误！请重新输入\n");
        }
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
                break;
        }
    }
    free(head);
    return 0;
}
