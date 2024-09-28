#include <iostream>

struct ListNode {
    int data;        // 节点数据
    ListNode* next;  // 指向下一个节点的指针
    ListNode(int x) : data(x), next(nullptr) {}
};

ListNode* mergeLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);  // 哨兵节点
    ListNode* tail = &dummy;

    while (l1 && l2) {
        if (l1->data < l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else if (l1->data > l2->data) {
            tail->next = l2;
            l2 = l2->next;
        } else {
            // 数据相同，避免重复
            tail->next = l1;
            l1 = l1->next;
            l2 = l2->next;
        }
        tail = tail->next;  // 移动尾指针
    }

    // 链接剩余的节点
    tail->next = (l1 != nullptr) ? l1 : l2;

    return dummy.next;  // 返回合并后的链表头
}

// 辅助函数：打印链表
void printList(ListNode* head) {
    while (head) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    // 示例：创建两个有序链表
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(3);
    l1->next->next = new ListNode(5);

    ListNode* l2 = new ListNode(2);
    l2->next = new ListNode(4);
    l2->next->next = new ListNode(6);
    
    ListNode* mergedList = mergeLists(l1, l2);
    
    printList(mergedList);  // 输出合并后的链表

    // 释放内存（建议实际应用中添加内存释放的逻辑）
    
    return 0;
}
