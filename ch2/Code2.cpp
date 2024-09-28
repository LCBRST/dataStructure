#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
typedef int DataType,Status;
typedef struct xhnode{
 DataType data;
 struct xhnode * next;
}xhListNode,*xhLinkList;

//初始化 ,加一个尾指针 
Status InitList_L(xhLinkList & xhL,xhLinkList & REAR)
{
  xhL =new xhListNode;
  xhL->next = xhL;
  REAR=xhL;
 return OK;
} //OK

//尾插法建立循环链表 
Status CreateList(xhLinkList & REAR,int n)
{
 REAR = (xhLinkList)malloc(sizeof(xhListNode));
 xhnode * p;
 REAR->next = REAR;
 int i;
 DataType ele;
 for(i = 0;i < n;i++)
 {
  scanf("%d",&ele);
  p = (xhListNode*)malloc(sizeof(xhListNode));  
  p->data = ele; 
  p->next=NULL;
  p->next =REAR->next;
  REAR->next =p;
  REAR=p;
 }
 return OK;
} 


//按照值查找 
xhListNode * GetList_Elem(xhLinkList REAR,DataType find_ele)
{
 xhListNode * node = REAR->next;
 while(node!=REAR && node->data != find_ele)
 {
  node = node->next;
 }
 return node;
}

//按照位置查找 
xhListNode * GetList_Pos(xhLinkList REAR,int pos)
{
 if(pos == 0)
 {
  return REAR;
 }
 if(pos < 1)
 {
  return NULL;
 }
 xhListNode * p= REAR->next;
 int j = 0;
 while(p!=REAR && j < pos)
 {
  
  p=p->next;
  j++;
 }
 if(p == NULL)
 {
  printf("插入位置超出范围！");
  return NULL; 
 }
 return p;
}

//插入 
Status InserElem(xhLinkList & REAR,int pos,DataType inser_ele)
{
 xhListNode * p;
 xhListNode * new_node = (xhListNode*)malloc(sizeof(xhListNode));
 new_node->data = inser_ele;
 p = GetList_Pos(REAR,pos-1);
 new_node->next = p->next;
 p->next = new_node;
 return OK;
}

//删除
Status DeleteElem(xhLinkList & REAR,int pos,DataType * del_ele)
{
 xhListNode * p;
 xhListNode *del_node;
 p = GetList_Pos(REAR,pos-1);
 del_node =p->next;
 p->next = del_node->next;
 *del_ele = del_node->data; 
 free(del_node);
 return OK;
} 

//输出
void PrintList(xhLinkList REAR)
{
 xhListNode * p = REAR->next->next;
 printf("表中元素为:\n"); 
 while(p!= REAR->next)
 {
  printf("%d ",p->data);
  p = p->next;
 } 
 printf("\n");
}

//两个循环链表的合并
xhListNode *connect(xhLinkList & LA,xhLinkList & LB)
{
 xhListNode * p= LA->next;
 LA->next= LB->next->next;
 free(LB->next);
 LB->next=p;
 return LB;

} 

int main()
{
 xhLinkList L;
 DataType inser_ele;
 xhListNode * find_node;
 DataType del_ele;
 int pos,z;
 printf("初始化循环链表,输入数据的个数："); 
 scanf("%d",&z);
 printf("请输入数据：");
 CreateList(L,z);
 PrintList(L);
 printf("请输入要插入的位置:");
 scanf("%d",&pos);
 printf("请输入要插入的元素:");
 scanf("%d",&inser_ele);
 InserElem(L,pos,inser_ele); 
 PrintList(L);
 printf("请输入要删除元素的位置：");
 scanf("%d",&pos);
 DeleteElem(L,pos,&del_ele); 
 printf("所删除的元素为：%d\n",del_ele);
 PrintList(L);
 printf("请输入要查找的元素的位置：");
 scanf("%d",&pos);
 find_node = GetList_Pos(L,pos);
 printf("所查找的元素为:%d\n",find_node->data); 

 printf("循环链表的合并：\n");
 xhLinkList LA; 
 xhLinkList LB; 
 xhLinkList LC; 
 int m,n;
 printf("初始化链表LA,输入数据的个数："); 
 scanf("%d",&m);
 printf("请输入数据：");
 CreateList(LA,m);
 printf("初始化链表LB,输入数据的个数："); 
  scanf("%d",&n);
 printf("请输入数据：");
 CreateList(LB,n);
 LC=connect(LA,LB);
 PrintList(LC);
 return 0;
}
