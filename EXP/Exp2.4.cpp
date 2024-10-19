#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW -1

// 定义队列元素类型
typedef char QElemType;

// 链式队列的链式存储结构
typedef struct QNode
{
    QElemType data;          // 数据域
    struct QNode *next;      // 指针域，指向下一个结点
} QNode, *QueuePtr;

// 链式队列结构体，包含队头和队尾指针
typedef struct
{
    QueuePtr front;          // 队头指针
    QueuePtr rear;           // 队尾指针
} LinkQueue;

// 初始化队列
void InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front)
    {
        exit(OVERFLOW);  // 分配内存失败
    }
    Q.front->next = NULL;  // 初始化时头结点的 next 指向 NULL
}

// 入队操作
void EnQueue(LinkQueue &Q, QElemType e)
{
    QueuePtr newNode = (QueuePtr)malloc(sizeof(QNode));
    if (!newNode)
    {
        exit(OVERFLOW);  // 分配内存失败
    }
    newNode->data = e;     // 设置数据域
    newNode->next = NULL;  // 新结点的 next 指向 NULL

    Q.rear->next = newNode;  // 将当前队尾的 next 指向新结点
    Q.rear = newNode;        // 更新队尾指针
}

// 出队操作
bool DeQueue(LinkQueue &Q, QElemType &e)
{
    if (Q.front == Q.rear)
    {
        return false;  // 队列为空，无法出队
    }

    QueuePtr temp = Q.front->next;  // 队头的下一个结点是要出队的结点
    e = temp->data;                 // 获取出队元素
    Q.front->next = temp->next;     // 更新队头指针

    if (Q.rear == temp)
    {
        Q.rear = Q.front;  // 若队列中只有一个元素，出队后更新队尾指针
    }

    free(temp);  // 释放出队结点的内存
    return true;
}

// 获取队头元素
bool GetHead(LinkQueue Q, QElemType &e)
{
    if (Q.front == Q.rear)
    {
        return false;  // 队列为空
    }

    e = Q.front->next->data;  // 队头元素存储在头结点的 next 指向的结点中
    return true;
}

// 主程序
int main()
{
    LinkQueue Q;               // 声明一个链式队列
    QElemType elem;            // 用于存储出队或队头的元素

    // 初始化队列
    InitQueue(Q);
    printf("队列已初始化。\n");

    // 入队
    EnQueue(Q, 'A');
    EnQueue(Q, 'B');
    EnQueue(Q, 'C');
    printf("已将A, B, C元素入队。\n");

    // 获取队头元素
    if (GetHead(Q, elem))
    {
        printf("队头元素为: %c\n", elem);
    }
    else
    {
        printf("队列为空，无法获取队头元素。\n");
    }

    // 出队
    if (DeQueue(Q, elem))
    {
        printf("出队元素为: %c\n", elem);
    }
    else
    {
        printf("队列为空，无法出队。\n");
    }

    // 再次获取队头元素
    if (GetHead(Q, elem))
    {
        printf("新的队头元素为: %c\n", elem);
    }
    else
    {
        printf("队列为空，无法获取队头元素。\n");
    }

    return 0;
}
