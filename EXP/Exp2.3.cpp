#include <stdio.h>
#include <stdlib.h>

#define MAXQSIZE 100  // 队列的最大长度
typedef int QElemType; // 队列元素类型可以根据需求修改

// 定义顺序队列结构体
typedef struct {
    QElemType *base; // 队列数组首地址
    int front;       // 队头游标
    int rear;        // 队尾游标
} SqQueue;

// 初始化队列
int InitQueue(SqQueue *Q) {
    Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q->base) return 0; // 分配失败
    Q->front = Q->rear = 0; // 队头和队尾都指向0，表示空队列
    return 1; // 初始化成功
}

// 入队操作
int EnQueue(SqQueue *Q, QElemType e) {
    if ((Q->rear + 1) % MAXQSIZE == Q->front) {
        return 0; // 队列已满，插入失败
    }
    Q->base[Q->rear] = e;        // 在队尾插入新元素
    Q->rear = (Q->rear + 1) % MAXQSIZE; // 队尾后移，循环队列
    return 1; // 插入成功
}

// 出队操作
int DeQueue(SqQueue *Q, QElemType *e) {
    if (Q->front == Q->rear) {
        return 0; // 队列为空，无法出队
    }
    *e = Q->base[Q->front];         // 获取队头元素
    Q->front = (Q->front + 1) % MAXQSIZE; // 队头后移，循环队列
    return 1; // 出队成功
}

// 取队头元素
int GetHead(SqQueue Q, QElemType *e) {
    if (Q.front == Q.rear) {
        return 0; // 队列为空，无队头元素
    }
    *e = Q.base[Q.front]; // 取出队头元素
    return 1; // 获取成功
}

// 合并两个队列 Q2 到 Q1
int MergeQueue(SqQueue *Q1, SqQueue *Q2) {
    int length1 = (Q1->rear - Q1->front + MAXQSIZE) % MAXQSIZE; // 计算Q1的长度
    int length2 = (Q2->rear - Q2->front + MAXQSIZE) % MAXQSIZE; // 计算Q2的长度

    if (length1 + length2 >= MAXQSIZE) {
        return 0; // 合并后的队列超出最大长度，无法合并
    }

    // 将Q2中的元素逐个插入到Q1中
    while (Q2->front != Q2->rear) {
        QElemType e;
        DeQueue(Q2, &e);      // 从Q2中出队
        EnQueue(Q1, e);       // 插入到Q1中
    }
    return 1; // 合并成功
}

int main() {
    SqQueue Q1, Q2;
    QElemType e;

    // 初始化队列Q1和Q2
    if (!InitQueue(&Q1) || !InitQueue(&Q2)) {
        printf("队列初始化失败\n");
        return -1;
    }

    // 向Q1入队
    for (int i = 1; i <= 5; i++) {
        EnQueue(&Q1, i);
    }

    // 向Q2入队
    for (int i = 6; i <= 8; i++) {
        EnQueue(&Q2, i);
    }

    // 合并Q2到Q1
    if (MergeQueue(&Q1, &Q2)) {
        printf("队列合并成功\n");
    } else {
        printf("队列合并失败\n");
    }

    // 输出合并后的Q1队列元素
    printf("合并后的Q1队列元素：\n");
    while (Q1.front != Q1.rear) {
        DeQueue(&Q1, &e);
        printf("%d ", e);
    }

    printf("\n");
    return 0;
}
