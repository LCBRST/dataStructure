#include <stdio.h>
#include <stdlib.h>

typedef char SElemType;

typedef struct StackNode {
    SElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;

void InitStack(LinkStack &S) {
    S = NULL;
}

bool GetTop(LinkStack S, SElemType &e) {
    if (S == NULL) {
        return false;
    }
    e = S->data;
    return true;
}

void Push(LinkStack &S, SElemType e) {
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = e;
    node->next = S;
    S = node;
}

bool Pop(LinkStack &S, SElemType &e) {
    if (S == NULL) {
        return false;
    }
    StackNode *temp = S;
    e = S->data;
    S = S->next;
    free(temp);
    return true;
}

int main() {
    LinkStack S;
    SElemType e;

    InitStack(S);
    
    Push(S, 'A');
    Push(S, 'B');
    Push(S, 'C');

    if (GetTop(S, e)) {
        printf("栈顶元素: %c\n", e);
    }

    while (Pop(S, e)) {
        printf("出栈元素: %c\n", e);
    }

    return 0;
}
