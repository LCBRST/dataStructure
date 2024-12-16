#include <iostream>
using namespace std;

// 定义元素类型
typedef struct ElemType {
    int key;
} ElemType;

// 二叉排序树节点定义
typedef struct BSTNode {
    ElemType data;  // 节点数据
    BSTNode *lchild, *rchild;  // 左右子节点指针
} BSTNode, *BSTree;

// 创建二叉排序树
void CreateBST(BSTree &T) {
    T = nullptr;
    int key;
    while (true) {
        cin >> key;
        if (key == 111) break;  // 输入结束标志
        BSTNode *newNode = new BSTNode;
        newNode->data.key = key;
        newNode->lchild = newNode->rchild = nullptr;
        if (T == nullptr) {
            T = newNode;
        } else {
            BSTNode *parent = nullptr, *current = T;
            while (current != nullptr) {
                parent = current;
                if (key < current->data.key) {
                    current = current->lchild;
                } else {
                    current = current->rchild;
                }
            }
            if (key < parent->data.key) {
                parent->lchild = newNode;
            } else {
                parent->rchild = newNode;
            }
        }
    }
}

// 中序遍历二叉排序树
void InOrderTraverse(BSTree T) {
    if (T != nullptr) {
        InOrderTraverse(T->lchild);
        cout << T->data.key << " ";
        InOrderTraverse(T->rchild);
    }
}

// 查找二叉排序树中的关键字
BSTree SearchBST(BSTree T, int key) {
    while (T != nullptr && T->data.key != key) {
        if (key < T->data.key) {
            T = T->lchild;
        } else {
            T = T->rchild;
        }
    }
    return T;  // 如果找到返回节点，否则返回nullptr
}

// 删除二叉排序树中的节点
void DeleteNode(BSTree &T, int key) {
    if (T == nullptr) return;  // 空树不需要删除

    if (key < T->data.key) {
        DeleteNode(T->lchild, key);  // 在左子树递归删除
    } else if (key > T->data.key) {
        DeleteNode(T->rchild, key);  // 在右子树递归删除
    } else {
        // 找到需要删除的节点
        if (T->lchild == nullptr) {
            BSTree temp = T;
            T = T->rchild;  // 右子树替代当前节点
            delete temp;
        } else if (T->rchild == nullptr) {
            BSTree temp = T;
            T = T->lchild;  // 左子树替代当前节点
            delete temp;
        } else {
            // 当前节点有两个子树，找到右子树中的最小节点
            BSTree temp = T->rchild;
            while (temp->lchild != nullptr) {
                temp = temp->lchild;
            }
            T->data.key = temp->data.key;  // 用右子树的最小值替代当前节点
            DeleteNode(T->rchild, temp->data.key);  // 删除右子树中的最小节点
        }
    }
}

// 删除二叉排序树中的关键字
void DeleteBST(BSTree &T, int key) {
    DeleteNode(T, key);
}

// 主函数
int main() {
    BSTree T;
    cout << "请输入若干记录关键字，用空格区分，以111结束输入，如：12 45 67 89 111" << endl;
    CreateBST(T);

    cout << "当前二叉排序树中序遍历结果为：" << endl;
    InOrderTraverse(T);
    cout << endl;

    int key;  // 待查找或待删除内容

    // 查找关键字
    cout << "请输入待查找关键字：";
    cin >> key;
    BSTree result = SearchBST(T, key);
    if (result) {
        cout << "找到关键字 " << key << endl;
    } else {
        cout << "未找到 " << key << endl;
    }

    // 删除关键字
    cout << "请输入待删除的关键字：";
    cin >> key;
    DeleteBST(T, key);

    cout << "当前有序二叉树中序遍历结果为：" << endl;
    InOrderTraverse(T);
    cout << endl;

    return 0;
}
