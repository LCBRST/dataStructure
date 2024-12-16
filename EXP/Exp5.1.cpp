#include <iostream>
using namespace std;

// 查找表的数据存储结构定义
typedef struct {
    int key;  // 关键字域
} SSTableElemType;  // 修改为SSTableElemType，避免与BSTNode中的ElemType冲突

typedef struct {
    SSTableElemType *R;  // 查找表的数组
    int length;   // 查找表的当前长度
} SSTable;

// 二叉排序树的存储结构定义
typedef struct BSTElemType {  // 修改为BSTElemType
    int key;
} BSTElemType;

typedef struct BSTNode {
    BSTElemType data;  // 节点数据
    BSTNode *lchild, *rchild;  // 左右子树指针
} BSTNode, *BSTree;

// 函数声明
void InitList_SSTable(SSTable &ST);
void Insert_SSTable(SSTable &ST);
int Search_Seq(SSTable ST, int key);
int Search_Seq2(SSTable ST, int key);
int Search_Bin(SSTable ST, int key);
void InsertSort(SSTable &ST);
void heapify(SSTable &ST, int n, int i);
void heapSort(SSTable &ST);
void show(SSTable ST);
void Show_End(int result, int key);

// 初始化查找表
void InitList_SSTable(SSTable &ST) {
    ST.R = nullptr;
    ST.length = 0;
}

// 在查找表中添加元素
void Insert_SSTable(SSTable &ST) {
    int n;
    cout << "输入查找表的元素个数: ";
    cin >> n;
    ST.R = new SSTableElemType[n];
    ST.length = n;

    cout << "输入查找表的元素: ";
    for (int i = 0; i < n; i++) {
        cin >> ST.R[i].key;
    }
}

// 顺序查找
int Search_Seq(SSTable ST, int key) {
    for (int i = 0; i < ST.length; i++) {
        if (ST.R[i].key == key)
            return i;
    }
    return -1;  // 找不到返回-1
}

// 设置监视哨的顺序查找
int Search_Seq2(SSTable ST, int key) {
    ST.R[ST.length].key = key;  // 设置监视哨
    int i = 0;
    while (ST.R[i].key != key) {
        i++;
    }
    return (i == ST.length) ? -1 : i;
}

// 折半查找
int Search_Bin(SSTable ST, int key) {
    int low = 0, high = ST.length - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (ST.R[mid].key == key)
            return mid;
        else if (ST.R[mid].key < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;  // 查找失败
}

// 插入排序
void InsertSort(SSTable &ST) {
    for (int i = 1; i < ST.length; i++) {
        SSTableElemType temp = ST.R[i];
        int j = i - 1;
        while (j >= 0 && ST.R[j].key > temp.key) {
            ST.R[j + 1] = ST.R[j];
            j--;
        }
        ST.R[j + 1] = temp;
    }
}

// 堆排序相关函数
void heapify(SSTable &ST, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && ST.R[left].key > ST.R[largest].key)
        largest = left;
    if (right < n && ST.R[right].key > ST.R[largest].key)
        largest = right;

    if (largest != i) {
        swap(ST.R[i], ST.R[largest]);
        heapify(ST, n, largest);
    }
}

void heapSort(SSTable &ST) {
    int n = ST.length;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(ST, n, i);
    }

    for (int i = n - 1; i >= 1; i--) {
        swap(ST.R[0], ST.R[i]);
        heapify(ST, i, 0);
    }
}

// 显示查找表
void show(SSTable ST) {
    for (int i = 0; i < ST.length; i++) {
        cout << ST.R[i].key << " ";
    }
    cout << endl;
}

// 显示查找结果
void Show_End(int result, int key) {
    if (result == -1) {
        cout << "关键字 " << key << " 未找到!" << endl;
    } else {
        cout << "关键字 " << key << " 在位置 " << result << endl;
    }
}

// 主函数
int main() {
    SSTable ST;
    int key1, key2;  // 待查关键字
    int result;

    InitList_SSTable(ST);  // 初始化查找表
    Insert_SSTable(ST);    // 在查找表中添加元素

    cout << "输入待查关键字key1、key2:" << endl;
    cin >> key1 >> key2;

    // 顺序查找
    cout << endl << "顺序查找 待查关键字 key1=" << key1 << "  key2=" << key2 << endl;
    result = Search_Seq(ST, key1);
    Show_End(result, key1);
    result = Search_Seq(ST, key2);
    Show_End(result, key2);

    // 设置监视哨的顺序查找
    cout << endl << "设置监视哨的顺序查找 待查关键字 key1=" << key1 << "  key2=" << key2 << endl;
    result = Search_Seq2(ST, key1);
    Show_End(result, key1);
    result = Search_Seq2(ST, key2);
    Show_End(result, key2);

    // 折半查找
    cout << endl << "折半查找 待查关键字 key1=" << key1 << "  key2=" << key2 << endl;

    // 对查找表进行排序
    cout << "第一步先对查找表进行排序" << endl;
    cout << endl << "初始查找表的数据状态:";
    show(ST);
    
    // 排序方式选择
    // InsertSort(ST);  // 插入排序
    heapSort(ST);  // 堆排序

    cout << endl << "排序后查找表的数据状态:" << endl;
    show(ST);

    cout << endl << "第二步对有序表进行折半查找" << endl;

    result = Search_Bin(ST, key1);
    Show_End(result, key1);
    result = Search_Bin(ST, key2);
    Show_End(result, key2);

    return 0;
}
