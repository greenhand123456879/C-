#pragma once

#include<iostream>
#include<string>

using namespace std;

typedef int ListNodeDataType;

typedef struct ListNode
{
	ListNodeDataType data;
	struct ListNode* next;
}LNode;

//增删查改

//增删 尾

void PrintList(LNode* list);

void InitList(ListNodeDataType x, LNode** list);

LNode* newnode(ListNodeDataType x);

void listpushback(ListNodeDataType x, LNode** list);

void listpopback(LNode** list);

void listpushfront(ListNodeDataType x, LNode** list);

void listpopfront(LNode** list);

LNode* listfind(ListNodeDataType x, LNode* list);


void  listmodify(ListNodeDataType xModify, int pos, LNode* list);