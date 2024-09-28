#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status; //Status 是函数返回值类型，其值是函数结果状态代码。
typedef int dataType;

typedef struct LNode {
    dataType data;    //结点的数据域
    struct LNode *next; //结点的指针域
} LNode, *LinkList; //LinkList为指向结构体LNode的指针类型


Status InitList_L(LinkList &L) {  // 初始化链表
    L = new LNode;
    L->next = NULL;  // 头结点指针域为空
    return OK;
}

void CreateList_R(LinkList &L, int n) {
    LinkList r = L;  // r为表尾指针
    for (int i = 0; i < n; i++) {
        LinkList p = new LNode;  // 创建新结点
        cin >> p->data;  // 输入数据域的值
        p->next = NULL;  // 设置指针域为空
        r->next = p;     // 将新结点插入表尾
        r = p;           // r 指向新的表尾
    }
}

Status GetElem_L(LinkList L, int i, int &e) {
    LinkList p = L->next;  // 指向第一个结点
    int j = 1;  // 计数器
    while (p && j < i) {  // 查找第i个结点
        p = p->next;
        j++;
    }
    if (!p || j > i) return ERROR;  // 若第i个元素不存在
    e = p->data;  // 取值
    return OK;
}

LinkList LocateElem_L(LinkList L, dataType e) {
    LinkList p = L->next;  // 指向第一个结点
    while (p && p->data != e) {
        p = p->next;  // 查找值为e的结点
    }
    return p;  // 返回找到的结点位置，若未找到返回NULL
}

Status ListInsert_L(LinkList &L, int i, dataType e) {
    LinkList p = L;  // p指向头结点
    int j = 0;  // 计数器
    while (p && j < i - 1) {  // 查找第i-1个结点
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) return ERROR;  // 第i-1个元素不存在
    LinkList s = new LNode;  // 生成新结点
    s->data = e;  // 将数据赋值给新结点
    s->next = p->next;  // 将新结点插入
    p->next = s;
    return OK;
}

Status ListDelete_L(LinkList &L, int i) {
    LinkList p = L;  // p指向头结点
    int j = 0;  // 计数器
    while (p->next && j < i - 1) {  // 查找第i-1个结点
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i - 1) return ERROR;  // 第i个元素不存在
    LinkList q = p->next;  // 指向第i个结点
    p->next = q->next;  // 删除第i个结点
    delete q;  // 释放内存
    return OK;
}

void PrintList(LinkList L) {
    LinkList p = L->next;  // 跳过头结点
    while (p) {
        cout << p->data << " ";  // 输出每个结点的数据
        p = p->next;
    }
    cout << endl;
}

int LengthList(LinkList L) {
    LinkList p = L->next;  // 跳过头结点
    int length = 0;
    while (p) {
        length++;  // 计数
        p = p->next;
    }
    cout << "当前链表的长度为: " << length << endl;
    return length;
}

void EmptyList(LinkList &L) {
    LinkList p = L->next;  // 指向第一个结点
    while (p) {
        LinkList q = p;  // 保存当前结点
        p = p->next;  // 移动到下一个结点
        delete q;  // 释放当前结点
    }
    L->next = NULL;  // 将头结点的指针域置为空
    cout << "链表已清空！" << endl;
}

int main() {
    int a, length, choose;
    double t;
    int e;
    LinkList L;
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

    choose = -1;
    while (choose != 0) {
        cout << "\n请选择:";
        cin >> choose;
        switch (choose) {
        case 1:  //建立一个单链表
            if (InitList_L(L))
                cout << "成功建立链表!\n\n";
            break;
        case 2:  //使用后插法创建单链表
            cout << "输入单链表的元素个数:";
            cin >> length;
            if (length > 0) {
                CreateList_R(L, length);
                cout << "单链表数据输入成功\n\n";
            } else cout << "元素个数输入有误，单链表数据输入失败\n\n";
            break;
        case 3:  //单链表的按序号取值
            cout << "请输入一个位置用来取值:";
            cin >> a;
            if (GetElem_L(L, a, e)) {
                cout << "查找成功\n";
                cout << "第" << a << "个元素值是:" << e << endl;
            } else
                cout << "查找失败\n\n";
            break;
        case 4:  //单链表的按值查找
            cout << "请输入所要查找元素值:";
            cin >> t;
            if (LocateElem_L(L, t) != NULL) {
                cout << "查找成功\n";
                cout << "该值对应的储存位置为：" << LocateElem_L(L, t) << endl;
            } else
                cout << "查找失败! " << t << " 没有找到\n\n";
            break;
        case 5:  //单链表的插入
            cout << "请输入插入的位置：";
            cin >> a;
            cout << "请输入插入元素值的信息:";
            cin >> e;
            if (ListInsert_L(L, a, e))
                cout << "插入成功.\n\n";
            else
                cout << "插入失败!\n\n";
            break;
        case 6:  //单链表的删除
            cout << "请输入所要删除的元素的位置:";
            cin >> a;
            if (ListDelete_L(L, a))
                cout << "删除成功!\n\n";
            else
                cout << "删除失败!\n\n";
            break;
        case 7:  //单链表的输出
            PrintList(L);
            break;
        case 8:  //单链表的表长
            LengthList(L);
            break;
        case 9:  //清空单链表
            EmptyList(L);
            break;
        }
    }
    return 0;
}
