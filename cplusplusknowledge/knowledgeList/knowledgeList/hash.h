#pragma once
#define DEFAULT_HASH_SIZE 16

#include<stdio.h>
#include<iostream>
#include<assert.h>
typedef int keyType;
typedef int dataType;

typedef struct ListNode
{
	struct ListNode* next;
	keyType key;
	dataType data;
}ListNode;

typedef ListNode* list;
typedef ListNode* element;

typedef struct HashTable
{
	int TableSize;
	list* list;
}HT;

//增删查改，初始化

int my_hash(HT* hashTable, keyType key);

HT* init_hash(int hashSize);
void insert_hash(HT* hashTable, keyType insertKey, dataType value);//不允许有相同的值插入
void delete_hash(HT* hashTable, keyType insertKey);
element find_hash(keyType key, HT* hashTable);//返回NULL就说明没有重复的元素