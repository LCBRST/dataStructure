#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
#define OK 0
#define ERROR 1
typedef int Status;
typedef char SElemType;
typedef struct
{
    SElemType *base;		//栈底指针
    SElemType *top;		//栈顶指针
    int stacksize;			//栈可用的最大容量
} SqStack;

Status InitStack(SqStack &S){
    S.base = (SElemType *)malloc(SIZE * sizeof(SElemType)); // 分配内存，SIZE是预定义的栈最大容量
    if (S.base == NULL) {
        return ERROR; // 内存分配失败
    }
    S.top = S.base; // 栈顶指针初始化为栈底指针，空栈时top与base重合
    S.stacksize = SIZE; // 设置栈的最大容量
    return OK;
}
Status GetTop(const SqStack S, SElemType &e) {
    if (S.top == S.base) { // 判断是否为空栈
        return ERROR;
    }
    e = *(S.top - 1); // 获取栈顶元素，注意top指向下一个空闲位置
    return OK;
}

Status Push(SqStack &S,SElemType e){
    if(S.top-S.base==S.stacksize){//判断是否为空栈
        return ERROR;
    }
    * (S.top++)=e;//将新元素压入栈顶
    return OK;
}

Status Pop(SqStack &S,SElemType e){
    if(S.base==S.top){
        return ERROR;
    }
    e=*(--S.top);
    return OK;
}

int main(){
    SqStack S;
    SElemType e;

    // 正确检查初始化状态
    if (InitStack(S) == OK) {
        Push(S, 'A');
        Push(S, 'B');
        // 正确检查获取栈顶元素状态
        if (GetTop(S, e) == OK) {
            printf("栈顶元素: %c\n", e); // 应输出 'B'
        }
        // 正确检查出栈元素状态
        if (Pop(S, e) == OK) {
            printf("出栈元素: %c\n", e); // 应输出 'B'
        }
        if (GetTop(S, e) == OK) {
            printf("栈顶元素: %c\n", e); // 应输出 'A'
        }
    }
    return 0;
}