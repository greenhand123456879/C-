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

//��ɾ���
void pushbacklist(TwNode** list, TwNodedataType x);
void popbacklist(TwNode** list);
void pushfrontlist(TwNode** list, TwNodedataType x);
void popfrontlist(TwNode** list);
//��ӡ����
void PrintList(TwNode* list);
//�����ڵ�
TwNode* NewNode(TwNodedataType x);
//��ʼ��
void InitList(TwNode** list, TwNodedataType x);
