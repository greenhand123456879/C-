#include"myfunmax.h"

//�ݹ�
//����˼��: �Ѵ����񲻶�ϸ�ֳ�С���񣬶������һ������������ϸ�ֵ�����
//1. ��д��ϸ������
//2. д����������
//3. ����߽�������Ҫ���⴦��
//4. �ݹ麯������������return
int MyFunMax(int* arr, int arrSize)
{
	assert(arr);
	assert(arrSize);
	if (arrSize == 1)
	{
		return *arr;
	}
	int arrSubSize = arrSize / 2;
	if (arrSize % 2 != 0)
		arrSubSize++;
	int* arrSub = new int[arrSubSize];
	for (int i = 0, j = 0; i < arrSize; i += 2, j++)
	{
		if (i + 1 >= arrSize)
			arrSub[j] = *(arr + i);
		else
		{
			if (*(arr + i) - *(arr + i + 1) > 0)//�Ƚϳ��ϴ���
				*(arrSub + j) = *(arr + i);//������һ���Ƚ�����
			else
				*(arrSub + j) = *(arr + i + 1);
		}
	}
	int max = MyFunMax(arrSub, arrSubSize);
	delete[] arrSub;
	return max;
}