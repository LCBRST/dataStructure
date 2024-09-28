#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define OK 1
#define ERROR 0
typedef int Status;
typedef char DataType;
typedef struct node{
 DataType data;
 struct node * next;
}ListNode,*LinkList;

//21页无头结点头插法建立单链表 
LinkList CreateListF(void)
{  
  DataType ch;
  LinkList head;
  ListNode * s;
    head=NULL;
    printf("请输入链表各节点的数据（字符型）:\n");
    while((ch=getchar())!='\n'){
      s=(ListNode*)malloc(sizeof(ListNode));
      s->data=ch;
      s->next=head;
      head=s;
    }
    
    
 return head;
} 


int main()
{ LinkList  L;
  L=CreateListF();
   //printf("%c ",L->data);
   //printList(L);
return 0;
}

