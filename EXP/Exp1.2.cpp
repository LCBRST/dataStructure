#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status; // Status 是函数返回值类型，其值是函数结果状态代码
typedef int dataType; // dataType 表示链表中的数据类型

// 结构体定义单链表的结点
typedef struct LNode {
    dataType data; // 结点的数据域，存储实际数据
    struct LNode *next; // 结点的指针域，指向下一个结点
} LNode, *LinkList; // LinkList 为指向结构体 LNode 的指针类型

// 初始化链表，创建空链表
Status InitList_L(LinkList &L) {
    L = new LNode; // 生成新结点作为头结点
    L->next = NULL; // 头结点的指针域置为空，表明链表为空
    return OK;
}

// 使用后插法创建单链表
void CreateList_R(LinkList &L, int n) {
    LinkList r = L; // r 为表尾指针，初始指向头结点
    for (int i = 0; i < n; i++) {
        LinkList p = new LNode; // 创建新结点
        cin >> p->data; // 输入新结点的数据域值
        p->next = NULL; // 新结点的指针域置为空
        r->next = p; // 将新结点插入到链表末尾
        r = p; // 更新 r 指向链表末尾新插入的结点
    }
}

// 按序号 i 获取单链表中的元素
Status GetElem_L(LinkList L, int i, int &e) {
    LinkList p = L->next; // 指向第一个实际存储数据的结点
    int j = 1; // 计数器，记录当前结点位置
    while (p && j < i) { // 遍历寻找第 i 个结点
        p = p->next; // 向后移动指针
        j++; // 计数器加 1
    }
    if (!p || j > i) return ERROR; // 如果第 i 个结点不存在，返回 ERROR
    e = p->data; // 将第 i 个结点的数据域赋给 e
    return OK;
}

// 按值查找单链表，返回值为 e 的逻辑位置
int LocateElem_L(LinkList L, dataType e) {
    LinkList p = L->next; // 从第一个实际存储数据的结点开始查找
    int pos = 1; // 计数器记录元素的逻辑位置，初始为1
    while (p && p->data != e) { // 遍历链表，寻找值为 e 的结点
        p = p->next; // 向后移动指针
        pos++; // 计数器加1，表示当前结点的位置
    }
    if (p == NULL) return 0; // 如果没有找到值为 e 的结点，返回 0 表示查找失败
    return pos; // 返回值为 e 的结点的逻辑位置
}

// 向单链表的第 i 个位置插入元素 e
Status ListInsert_L(LinkList &L, int i, dataType e) {
    LinkList p = L; // p 指向头结点
    int j = 0; // 计数器，记录当前结点位置
    while (p && j < i - 1) { // 遍历寻找第 i-1 个结点
        p = p->next; // 向后移动指针
        j++; // 计数器加 1
    }
    if (!p || j > i - 1) return ERROR; // 若 i-1 个结点不存在，返回 ERROR
    LinkList s = new LNode; // 生成新结点 s
    s->data = e; // 将数据域赋值为 e
    s->next = p->next; // 将新结点插入到第 i 位置
    p->next = s; // 将第 i-1 个结点指向新结点
    return OK;
}

// 删除单链表第 i 个位置的元素
Status ListDelete_L(LinkList &L, int i) {
    LinkList p = L; // p 指向头结点
    int j = 0; // 计数器，记录当前结点位置
    while (p->next && j < i - 1) { // 遍历寻找第 i-1 个结点
        p = p->next; // 向后移动指针
        j++; // 计数器加 1
    }
    if (!(p->next) || j > i - 1) return ERROR; // 若第 i 个结点不存在，返回 ERROR
    LinkList q = p->next; // q 指向第 i 个结点
    p->next = q->next; // 删除第 i 个结点
    delete q; // 释放第 i 个结点的内存
    return OK;
}

// 输出单链表中所有元素
void PrintList(LinkList L) {
    LinkList p = L->next; // 指向第一个实际存储数据的结点
    while (p) { // 遍历链表
        cout << p->data << " "; // 输出当前结点的数据域值
        p = p->next; // 移动到下一个结点
    }
    cout << endl; // 输出换行符
}

// 返回单链表的长度
int LengthList(LinkList L) {
    LinkList p = L->next; // 指向第一个实际存储数据的结点
    int length = 0; // 计数器，初始为 0
    while (p) { // 遍历链表
        length++; // 计数器加 1
        p = p->next; // 移动到下一个结点
    }
    cout << "当前链表的长度为: " << length << endl; // 输出链表长度
    return length; // 返回链表长度
}

// 清空单链表，删除所有结点
void EmptyList(LinkList &L) {
    LinkList p = L->next; // 指向第一个实际存储数据的结点
    while (p) { // 遍历链表
        LinkList q = p; // 保存当前结点
        p = p->next; // 移动到下一个结点
        delete q; // 释放当前结点的内存
    }
    L->next = NULL; // 头结点的指针域置为空，表示链表已空
    cout << "链表已清空！" << endl; // 提示链表已清空
}

int main() {
    int a, length, choose;
    double t;
    int e;
    LinkList L; // 定义链表指针 L
    cout << "1. 建立\n";
    cout << "2. 输入\n";
    cout << "3. 取值\n";
    cout << "4. 查找\n";
    cout << "5. 插入\n";
    cout << "6. 删除\n";
    cout << "7. 输出\n";
    cout << "8. 表长\n";
    cout << "9. 清空\n";
    cout << "0. 退出\n\n";

    choose = -1; // 初始选择值为 -1，避免程序立即退出
    while (choose != 0) { // 循环操作，直到用户选择退出
        cout << "\n请选择:";
        cin >> choose; // 获取用户选择的操作
        switch (choose) {
        case 1: // 建立一个单链表
            if (InitList_L(L))
                cout << "成功建立链表!\n\n";
            break;
        case 2: // 使用后插法创建单链表
            cout << "输入单链表的元素个数:";
            cin >> length;
            if (length > 0) {
                CreateList_R(L, length);
                cout << "单链表数据输入成功\n\n";
            } else cout << "元素个数输入有误，单链表数据输入失败\n\n";
            break;
        case 3: // 单链表的按序号取值
            cout << "请输入一个位置用来取值:";
            cin >> a;
            if (GetElem_L(L, a, e)) {
                cout << "查找成功\n";
                cout << "第" << a << "个元素值是:" << e << endl;
            } else
                cout << "查找失败\n\n";
            break;
        case 4: // 单链表的按值查找
            cout << "请输入所要查找元素值:";
            cin >> t;
            if (LocateElem_L(L, t) != NULL) {
                cout << "查找成功\n";
                cout << "该值对应的储存位置为：" << LocateElem_L(L, t) << endl;
            } else
                cout << "查找失败! " << t << " 没有找到\n\n";
            break;
        case 5: // 单链表的插入
            cout << "请输入插入的位置：";
            cin >> a;
            cout << "请输入插入元素值的信息:";
            cin >> e;
            if (ListInsert_L(L, a, e))
                cout << "插入成功.\n\n";
            else
                cout << "插入失败!\n\n";
            break;
        case 6: // 单链表的删除
            cout << "请输入所要删除的元素的位置:";
            cin >> a;
            if (ListDelete_L(L, a))
                cout << "删除成功!\n\n";
            else
                cout << "删除失败!\n\n";
            break;
        case 7: // 单链表的输出
            PrintList(L);
            break;
        case 8: // 单链表的表长
            LengthList(L);
            break;
        case 9: // 清空单链表
            EmptyList(L);
            break;
        }
    }
    return 0;
}
