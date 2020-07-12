#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#include<stdio.h>
#include<stdlib.h>
#define DebugOn 0 //0 - 关闭；1 - 开启；

typedef int Status;
typedef float SElemType;

typedef struct 
{
    SElemType *base;    //在构造前和销毁后，base值为NULL
    SElemType *top;     //栈顶指针
    int stacksize;      //当前已分配顶存储空间，以元素为单位
}SqStack;//顺序栈

//-------基本操作算法声明------
//构造一个空栈S
Status InitStack(SqStack *S);
//销毁栈S
Status DestroyStack(SqStack *S);
//把S重置为空栈
Status ClearStack(SqStack *S);
//若S为空栈，返回True，否则返回False
Status isStackEmpty(SqStack S);
//返回S的元素个数
int StackLength(SqStack S);
//若栈不空，用e返回S的栈顶元素，并返回True；否则返回False
SElemType GetTop(SqStack S);
//插入元素e为新的栈顶元素
Status Push(SqStack *S, SElemType e);
//若栈不空，删除S的栈顶元素，用e返回其值，并返回True；否则返回False
Status Pop(SqStack *S, SElemType *e);
//从栈底到栈顶遍历并用printf输出元素内容
Status StackTraverse(SqStack S);
//输出SqStack内部结构
void OutputSqStack(SqStack S);

//-------基本操作算法描述------
Status InitStack(SqStack *S){
    //构造一个空栈S
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);   //存储分配失败
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    if(DebugOn==1) printf("InitStack Success.\n");
    OutputSqStack(*S);
    return TRUE;
}//InitStack

Status isStackEmpty(SqStack S){
    //若S为空栈，返回True，否则返回False
    if(S.base!=S.top) return FALSE;
    else {
        if(DebugOn==1) printf("Stack is Empty.\n");
        OutputSqStack(S);
        return TRUE;
    }
}//isStackEmpty

SElemType GetTop(SqStack S){
    //若栈不空，用e返回S的栈顶元素，并返回True；否则返回False
    if(isStackEmpty(S)==TRUE) return 0;
    return *(S.top-1);
}//GetTop

Status Push(SqStack *S, SElemType e){
    //插入元素e为新的栈顶元素
    if(S->top - S->base >= S->stacksize){
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!S->base) exit(OVERFLOW);
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    if(DebugOn==1) printf("Push : %c\n",e);
    OutputSqStack(*S);
    return OK;
}//Push

Status Pop(SqStack *S, SElemType *e){
    //若栈不空，删除S的栈顶元素，用e返回其值，并返回True；否则返回False
    if(isStackEmpty(*S)==TRUE) return ERROR;
    *e = * --S->top;
    if(DebugOn==1) printf("Pop : %c\n",*e);
    OutputSqStack(*S);
    return OK;
}//Pop

void OutputSqStack(SqStack S){
    //输出SqStack内部结构
    if(DebugOn==1)
        printf("----<SqStack>----\n[base] %d\n[top] %d\n[stacksize] %d\n------<END>------\n",(int)S.base,(int)S.top,(int)S.stacksize);
}