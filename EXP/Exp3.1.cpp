#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip> // 用于设置浮点数输出精度
using namespace std;

#define MAXSIZE 100  // 表达式字符串最大值
#define N 10         // 表达式项的最大长度

char expression[MAXSIZE]; // 存储表达式字符串
char str[MAXSIZE][N];     // 存储表达式操作数、运算符
int expstart = 0, expend = 0; // 表达式开始、结束位置

typedef char ElemType;
typedef struct BiTNode {
    ElemType data[N];       // 结点的数据域，存储表达式的操作数、运算符
    BiTNode* lchild, *rchild;
} BiTNode;

void Init();
bool Judge(char (*str)[N], int expstart, int expend);
int GetOprt(char (*str)[N], int expstart, int expend);
BiTNode* CreateBT(char (*str)[N], int expstart, int expend);
void PreOrderBT(BiTNode* BT);
void InOrderBT(BiTNode* BT);
void PostOrderBT(BiTNode* BT);
double StrToDigital(char str[]);
double CalculateValue(BiTNode* BT);
void DestroyTree(BiTNode* BT);

void Init() {
    cout << "请输入表达式: ";
    cin >> expression;
    int len = strlen(expression);
    expend = 0;  // 确保 expend 从 0 开始

    int j = 0;
    for (int i = 0; i < len; i++) {
        if ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.') {
            str[expend][j++] = expression[i];
        } else {
            if (j != 0) {
                str[expend][j] = '\0';
                expend++;
                j = 0;
            }
            str[expend][0] = expression[i];
            str[expend][1] = '\0';
            expend++;
        }
    }
    if (j != 0) {
        str[expend][j] = '\0';
        expend++;
    }
    expend--;
}

bool Judge(char (*str)[N], int expstart, int expend) {
    if (str[expstart][0] == '(' && str[expend][0] == ')') {
        int count = 0;
        for (int i = expstart; i <= expend; i++) {
            if (str[i][0] == '(') count++;
            if (str[i][0] == ')') count--;
            if (count == 0 && i < expend) return false;
        }
        return true;
    }
    return false;
}

int GetOprt(char (*str)[N], int expstart, int expend) {
    int minPriority = 100, pos = -1, count = 0;
    for (int i = expstart; i <= expend; i++) {
        if (str[i][0] == '(') count++;
        else if (str[i][0] == ')') count--;

        if (count == 0) {
            int priority = 100;
            if (str[i][0] == '+' || str[i][0] == '-') priority = 1;
            else if (str[i][0] == '*' || str[i][0] == '/') priority = 2;

            if (priority <= minPriority) {
                minPriority = priority;
                pos = i;
            }
        }
    }
    return pos;
}

BiTNode* CreateBT(char (*str)[N], int expstart, int expend) {
    // 基本情况：当expstart == expend时，返回叶子节点
    if (expstart == expend) {
        BiTNode* node = new BiTNode();
        strcpy(node->data, str[expstart]);
        node->lchild = node->rchild = nullptr;
        return node;
    }

    // 找到操作符位置
    int opPos = GetOprt(str, expstart, expend);
    
    // 检查 opPos 是否为 -1
    if (opPos == -1) {
        // 如果没有找到操作符，说明表达式是单个操作数
        BiTNode* node = new BiTNode();
        strcpy(node->data, str[expstart]);
        node->lchild = node->rchild = nullptr;
        return node;
    }

    // 否则，创建新的操作符节点
    BiTNode* node = new BiTNode();
    strcpy(node->data, str[opPos]);

    // 递归创建左右子树
    node->lchild = CreateBT(str, expstart, opPos - 1);
    node->rchild = CreateBT(str, opPos + 1, expend);

    return node;
}


void PreOrderBT(BiTNode* BT) {
    if (BT) {
        cout << BT->data << " ";
        PreOrderBT(BT->lchild);
        PreOrderBT(BT->rchild);
    }
}

void InOrderBT(BiTNode* BT) {
    if (BT) {
        InOrderBT(BT->lchild);
        cout << BT->data << " ";
        InOrderBT(BT->rchild);
    }
}

void PostOrderBT(BiTNode* BT) {
    if (BT) {
        PostOrderBT(BT->lchild);
        PostOrderBT(BT->rchild);
        cout << BT->data << " ";
    }
}

double StrToDigital(char str[]) {
    return atof(str); // 将字符串转换为浮点型
}

double CalculateValue(BiTNode* BT) {
    if (!BT->lchild && !BT->rchild) {
        return StrToDigital(BT->data);
    }

    double leftVal = CalculateValue(BT->lchild);
    double rightVal = CalculateValue(BT->rchild);

    if (strcmp(BT->data, "+") == 0) return leftVal + rightVal;
    if (strcmp(BT->data, "-") == 0) return leftVal - rightVal;
    if (strcmp(BT->data, "*") == 0) return leftVal * rightVal;
    if (strcmp(BT->data, "/") == 0) return leftVal / rightVal;

    return 0;
}

void DestroyTree(BiTNode* BT) {
    if (BT) {
        DestroyTree(BT->lchild);
        DestroyTree(BT->rchild);
        delete BT;
    }
}

int main() {
    BiTNode* BT = NULL;
    double result;
    char c;

    do {
        Init();
        bool removable = Judge(str, expstart, expend);
        if (removable) {
            BT = CreateBT(str, expstart + 1, expend - 1);
        } else {
            BT = CreateBT(str, expstart, expend);
        }

        cout << "\n先序遍历得到前缀表示: ";
        PreOrderBT(BT);
        cout << "\n中序遍历得到中缀表示: ";
        InOrderBT(BT);
        cout << "\n后序遍历得到后缀表示: ";
        PostOrderBT(BT);
        cout << "\n\n表达式运算结果: ";
        result = CalculateValue(BT);
        cout << expression << " = " << fixed << setprecision(2) << result << endl;

        DestroyTree(BT);  // 释放树的内存
        BT = nullptr;     // 避免重复释放内存

        cout << "\n需要继续求值吗(y|Y or n|N)? ";
        cin >> c;
        cin.ignore(); // 清除输入缓存中的回车符
    } while (c == 'y' || c == 'Y');

    return 0;
}
