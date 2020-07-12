#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

//-------基本操作算法声明------
//初始化顺序表
Status InitList_Sq(SqList *L);
//在顺序表第i个位置之前插入新元素e
Status ListInsert_Sq(SqList *L, int i, ElemType e);
//删除第i个元素并用e返回其值
Status ListDelete_Sq(SqList *L, int i, ElemType *e);
//输出顺序表内容
Status PrintList_Sq(SqList *L);
//从用户输入获取顺序表元素
Status GetElemFromEnter_Sq(SqList *L);
//冒泡排序
Status BubbleSort_Sq(SqList *L);

//-------基本操作算法描述------
Status InitList_Sq(SqList *L){
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList *L, int i, ElemType e){
    if(i<1 || i>L->length+1) return ERROR;  //i值不合法
    if(L->length>=L->listsize){ //当前存储空间已满，增加分配
        ElemType *newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType *q = &(L->elem[i-1]);
    for(ElemType *p=&(L->elem[L->length-1]); p>=q;--p) *(p+1) = *p; //插入位置及之后的元素右移
    *q = e; //插入e
    ++L->length;
    return OK;
}

Status ListDelete_Sq(SqList *L, int i, ElemType *e){
    if((i<1) || (i>L->length))  return ERROR;
    ElemType *p = &(L->elem[i-1]);
    *e = *p;
    ElemType *q = L->elem + L->length - 1;
    for(++p; p<= q; ++p)    *(p-1) = *p;
    --L->length;
    return OK;
}

Status PrintList_Sq(SqList *L){
    if(L->length<1) return ERROR;
    for(int i=0;i<L->length;i++)    printf("%d, ",L->elem[i]);
    printf("\n");
    return OK;
}

Status GetElemFromEnter_Sq(SqList *L){
    ElemType temp;
    int enter=0;    //enter用来记录用户要输入的元素个数
    do
    {
        if(enter<1)
        {
            printf("How many number you need to enter(0 means end of enter):");
            scanf("%d",&enter);
            if(enter<1) break;  //输入为0或负数时结束输入
        }
        else
        {
            scanf("%d",&temp);
            ListInsert_Sq(L, L->length+1, temp);
            enter--;
        }
    }while(enter>=0);   //剩余次数为0后还会询问一次是否继续输入
    return OK;
}

Status BubbleSort_Sq(SqList *L){
    if(L->length<1) return ERROR;
    ElemType temp;
    for(int i=0;i<L->length;i++)
    {
        for(int j=i+1;j<L->length;j++)
        {
            if(L->elem[j]<L->elem[i])
            {
                temp = L->elem[i];
                L->elem[i] = L->elem[j];
                L->elem[j] = temp;
            }
        }
    }
    return OK;
}
