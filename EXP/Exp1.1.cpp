#include<iostream>
using namespace std;

#define MAXSIZE 1000

typedef struct {
    int *elem;   // 指向顺序表的数组
    int length;  // 顺序表的长度
} Seqlist;

// 初始化顺序表
void InitList(Seqlist &L) {
    L.elem = new int[MAXSIZE];  // 分配内存
    if (!L.elem) exit(0);       // 如果分配失败，退出
    L.length = 0;               // 初始化长度为0
    cout << "顺序表初始化完毕" << endl;
}

// 创建顺序表
void Creat(Seqlist &L, int n) {
    for(int i = 0; i < n; i++) {
        cin >> L.elem[i];  // 输入每个元素
        L.length++;        // 增加顺序表的长度
    }
}

// 插入元素到顺序表
bool Insert(Seqlist &L, int i, int e) {
    if (i < 1 || i > L.length + 1 || L.length >= MAXSIZE) {
        cout << "插入位置不合法或顺序表已满" << endl;
        return false;
    }
    for (int j = L.length - 1; j >= i - 1; j--) {
        L.elem[j + 1] = L.elem[j];  // 将元素向后移动
    }
    L.elem[i - 1] = e;  // 插入元素
    L.length++;         // 增加顺序表长度
    return true;
}

// 删除顺序表中的元素
bool Delete(Seqlist &L, int i) {
    if (i < 1 || i > L.length) {
        cout << "删除位置不合法" << endl;
        return false;
    }
    for (int j = i - 1; j < L.length - 1; j++) {
        L.elem[j] = L.elem[j + 1];  // 将元素向前移动
    }
    L.length--;  // 减少顺序表的长度
    return true;
}

// 输出顺序表的内容
void Print(const Seqlist &L) {
    for (int i = 0; i < L.length; i++) {
        cout << L.elem[i] << " ";  // 输出每个元素
    }
    cout << endl;
}

// 获取指定位置的元素
bool GetList(const Seqlist &L, int i) {
    if (i < 1 || i > L.length) {
        cout << "位置不合法" << endl;
        return false;
    }
    cout << "位置 " << i << " 上的元素为：" << L.elem[i - 1] << endl;
    return true;
}

// 查找元素在顺序表中的位置
int SearchList(const Seqlist &L, int e) {
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i + 1;  // 返回元素的索引+1（位置）
        }
    }
    return -1;  // 没找到
}

// 获取顺序表的长度
int lengthList(const Seqlist &L) {
    return L.length;
}

int main() {
    Seqlist L;
    int n, e, x, k, i;
    InitList(L);
    
    cout << "确定顺序表元素个数为：";
    scanf("%d", &n);
    cout << "请输入这" << n << "个元素：";
    Creat(L, n);
    cout << endl;

    cout << "       **请选择您想进行的操作**     " << endl;
    cout << "  ----------------------------------" << endl;
    cout << "  |     1.给顺序表插入值           |" << endl;
    cout << "  |     2.给顺序表删除值           |" << endl;
    cout << "  |     3.取顺序表位置上一个值     |" << endl;
    cout << "  |     4.在顺序表中查找一个值     |" << endl;
    cout << "  |     5.求线性表长度             |" << endl;
    cout << "  |     6.退出操作                 |" << endl;
    cout << "  ----------------------------------" << endl;

    while (1) {
        cout << "-------------------------------------------" << endl;
        cout << "您选择的操作是：";
        cin >> x;
        switch (x) {
        case 1:  // 插入元素
            {
                cout << "请输入要插入的位置：";
                cin >> i;
                cout << "请输入要插入的元素：";
                cin >> e;
                if (Insert(L, i, e)) {
                    cout << "插入之后的数组：";
                    Print(L);
                }
                break;
            }
        case 2:  // 删除元素
            {
                cout << "请输入要删除的位置：";
                cin >> i;
                if (Delete(L, i)) {
                    cout << "删除之后的数组：";
                    Print(L);
                }
                break;
            }
        case 3:  // 获取指定位置的元素
            {
                cout << "请输入要取值的位置：";
                cin >> k;
                if (GetList(L, k))
                    cout << "取值成功！" << endl;
                break;
            }
        case 4:  // 查找元素位置
            {
                int e;
                cout << "请输入要查找的值：";
                cin >> e;
                k = SearchList(L, e);
                if (k > 0)
                    cout << "查找成功！" << endl << "所在位置为：" << k << endl;
                else
                    cout << "查找失败！" << endl;
                break;
            }
        case 5:  // 求顺序表长度
            {
                cout << "线性表长度为：" << lengthList(L) << endl;
                break;
            }
        case 6:  // 退出程序
            {
                cout << "操作结束！！" << endl;
                return 0;
            }
        default:  // 错误输入
            {
                cout << "请输入正确的序号！！" << endl;
                break;
            }
        }
    }
}
