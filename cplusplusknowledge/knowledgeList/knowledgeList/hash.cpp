#include"hash.h"

int my_hash(HT* hashTable, keyType key)
{
	return(key % hashTable->TableSize);
}


HT* init_hash(int hashSize)
{
	if (hashSize <= 0)
	{
		hashSize = DEFAULT_HASH_SIZE;
	}
	HT* hashTable = (HT*)malloc(sizeof(HT));
	if (!hashTable)
		return NULL;
	hashTable->TableSize = hashSize;
	hashTable->list = (list*)malloc(hashTable->TableSize * sizeof(list));
	if (!hashTable->list)
	{
		free(hashTable->list);//可能开辟了一些空间，有一些没有开辟，也会导致失败
		return NULL;
	}
	for (int i = 0; i < hashTable->TableSize; i++)
	{
		// *(hashTable->list + i)->next为哨兵位，里面不存储有效数据
		*(hashTable->list + i) = (list)malloc(sizeof(ListNode));
		if (!(*(hashTable->list + i)))
		{
			//free(*(hashTable->list + i));没有创建成功你free了也没有用
			free(hashTable->list);
			free(hashTable);
			return NULL;
		}
		else
		{
			memset(*(hashTable->list + i), 0, sizeof(ListNode));
		}
	}
	return hashTable;
}


element find_hash(keyType key, HT* hashTable)
{
	int tableKey = my_hash(hashTable, key);
	list sentinelPosition = *(hashTable->list + tableKey);
	list find = (sentinelPosition->next);
	while (find != NULL && find->key != key)
	{
		find = find->next;
	}
	return find;
}


void insert_hash(HT* hashTable, keyType insertKey, dataType value)
{
	if (find_hash(insertKey, hashTable) == NULL)
	{
		int tableKey = my_hash(hashTable, insertKey);
		list sentinelPosition = *(hashTable->list + tableKey);
		ListNode* newLNode = (ListNode*)malloc(sizeof(ListNode));
		if (!newLNode)
			return;
		newLNode->data = value;
		newLNode->key = insertKey;
		newLNode->next = sentinelPosition->next;
		sentinelPosition->next = newLNode;
	}
}

void delete_hash(HT* hashTable, keyType insertKey)
{
	//element deleteElement = find_hash(insertKey, hashTable);
	//if (!deleteElement)
	//	return;
	assert(insertKey >= 0);
	int tableKey = my_hash(hashTable, insertKey);
	list sentinelPosition = *(hashTable->list + tableKey);
	list findPrev = sentinelPosition;
	list find = (findPrev->next);
	while (find != NULL && find->key != insertKey)
	{
		findPrev = findPrev->next;
		find = findPrev->next;
	}
	if (!find)
		return;
	list findNext = find->next;
	findPrev->next = findNext;
	free(find);
}