#include"TWList.h"


//增删查改
void pushfrontlist(TwNode** list, TwNodedataType x)
{
	assert(*list);
	if ((*list)->next == *list)
	{
		InitList(list, x);
		return;
	}
		
	TwNode* newnode = NewNode(x);
	newnode->next = (*list)->next;
	newnode->prev = *list;
	((*list)->next)->prev = newnode;
	(*list)->next = newnode;
	
}
void popfrontlist(TwNode** list)
{
	if ((*list)->next == *list)
		return;
	TwNode* next = ((*list)->next)->next;
	free((*list)->next);
	next->prev = *list;
	(*list)->next = next;
}



void pushbacklist(TwNode** list, TwNodedataType x)
{
	assert(*list);
	if ((*list)->next == *list)
	{
		InitList(list, x);
		return;
	}
	TwNode* newnode = NewNode(x);
	newnode->next = *list;
	newnode->prev = (*list)->prev;
	((*list)->prev)->next = newnode;
	(*list)->prev = newnode;
}
void popbacklist(TwNode** list)
{
	if ((*list)->next == *list)
		return;
	TwNode* popPrev = ((*list)->prev)->prev;
	free((*list)->prev);
	popPrev->next = *list;
	(*list)->prev= popPrev;
}
//打印测试
void PrintList(TwNode* list)
{
	if (!list)
		return;
	TwNode* cur = list->next;
	while (cur != list)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("\n");
}
//创建节点
TwNode* NewNode(TwNodedataType x)
{
	TwNode* newnode = (TwNode*)malloc(sizeof(TwNode));
	newnode->data = x;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}
//初始化
void InitList(TwNode** list, TwNodedataType x)
{
	TwNode* newnode = NewNode(x);
	(*list)->next = newnode;
	newnode->next = *list;
	(*list)->prev = newnode;
	newnode->prev = *list;
}
