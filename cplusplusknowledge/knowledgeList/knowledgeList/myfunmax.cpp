#include"myfunmax.h"

//递归
//整体思想: 把大任务不断细分成小任务，而最后有一个出口来结束细分的任务
//1. 先写出细分任务
//2. 写出结束条件
//3. 特殊边界问题需要另外处理
//4. 递归函数至少有两个return
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
			if (*(arr + i) - *(arr + i + 1) > 0)//比较出较大者
				*(arrSub + j) = *(arr + i);//生成下一个比较数组
			else
				*(arrSub + j) = *(arr + i + 1);
		}
	}
	int max = MyFunMax(arrSub, arrSubSize);
	delete[] arrSub;
	return max;
}