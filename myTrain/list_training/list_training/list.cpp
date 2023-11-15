#include"list.h"

void PrintList(LNode* list)
{
	if (!list)
		return;
	LNode* start = list;
	while (start != NULL)
	{
		printf("%d\n", start->data);
		start = start->next;
	} 
}


void InitList(ListNodeDataType x, LNode** list)
{
	LNode* newnode = (LNode*)malloc(sizeof(LNode));
	newnode->data = x;
	newnode->next = NULL;
	(*list) = newnode;
	newnode = NULL;
}

LNode* newnode(ListNodeDataType x)
{
	LNode* newnode = (LNode*)malloc(sizeof(LNode));
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

void listpushback(ListNodeDataType x, LNode** list)
{
	if (!(*list))
	{
		InitList(x, list);
		return;
	}
	LNode* start = *list;
	LNode* newNode = newnode(x);
	while ((start)->next != NULL)
		start = (start)->next;//找最后一个元素
	(start)->next = newNode;
}

void listpopback(LNode** list)
{
	if (!(*list))
		return;
	if ((*list)->next == NULL)
	{
		free((*list));
		*list = NULL;
		return;
	}
	LNode* prev = *list;
	LNode* cur = prev->next;
	while (cur->next != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	free(cur);
	cur = NULL;
	prev->next = NULL;
}

void listpushfront(ListNodeDataType x, LNode** list)
{		
	LNode* newNode = newnode(x);
	newNode->next = *list;
	(*list) = newNode;
}

void listpopfront(LNode** list)
{
	if (!(*list))
		return;
	LNode* prev = *list;
	LNode* cur = prev->next;
	if (!cur)
	{
		free(prev);
		*list = NULL;
		return;
	}
	(*list) = cur;
	free(prev);
}

LNode* listfind(ListNodeDataType x, LNode* list)
{
	if (!list)
		return NULL;
	LNode* start = list;
	while (start != NULL)
	{
		if (x == start->data)
			return start;
		start = start->next;
	}
	return NULL;
}

void listmodify(ListNodeDataType xModify, int pos, LNode* list)
{
	if (!list)
		return;
	LNode* modifyNode = listfind(pos, list);
	if (!modifyNode)
		return;
	else
		modifyNode->data = xModify;
}