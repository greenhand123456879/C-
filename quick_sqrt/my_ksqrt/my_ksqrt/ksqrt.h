#pragma once
#include <iostream>
#include <math.h>
//²âÊÔ´úÂë
/*int main() {
	std::cout << "common:" << commonsqrt(2) << std::endl;

	std::cout << "ksqrt:" << ksqrt(2) << std::endl;
	//for (float i = 1.0f; i < 16.0; i++)
	//{
	//	printf("%lf:%lf\n",i ,MyLog(i));
	//}

	std::cout << "Mylog:" << MyLog(4) << std::endl;
	return 0;
}
*/


template <typename T>
T MyAbs(T number);

float MyLog(float number);

float commonsqrt(float number);

float ksqrt(float number);