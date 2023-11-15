#pragma once
#include<iostream>
#include<string>
#include<cassert>
typedef int TwNodedataType;


typedef struct TwNode
{
	TwNodedataType data;
	struct TwNode* next;
	struct TwNode* prev;
}TwNode;

//增删查改
void pushbacklist(TwNode** list, TwNodedataType x);
void popbacklist(TwNode** list);
void pushfrontlist(TwNode** list, TwNodedataType x);
void popfrontlist(TwNode** list);
//打印测试
void PrintList(TwNode* list);
//创建节点
TwNode* NewNode(TwNodedataType x);
//初始化
void InitList(TwNode** list, TwNodedataType x);
