#include "ksqrt.h"
//计算出来的值不是很精确
//log(number) =  M / 2^23 + E -127
//log(number) = 1 / 2^23 * NUMBER -127
float MyLog(float number) {

	int i = *(int*)&number;
	return i / pow(2, 23) - 127;
}

template <typename T>
T MyAbs(T number) {
	if (number < 0)	return -number;
	else return number;
}


//牛顿迭代法
float commonsqrt(float number) {
	float y0, yn;
	int count = 0;
	y0 = number / 2.0;
	//牛顿迭代，f(x) = (1 / x^2) - a
	while (true) {
		yn = 1.5 * y0 - (number * 0.5) * y0 * y0 * y0;
		count++;
		if (MyAbs(y0 - yn) < 1e-6) {
			std::cout << "count:" << count << std::endl;
			break;
		}
		y0 = yn;
	}
	return yn;
}


//https://www.cnblogs.com/luo-greenhand/p/17831818.html解读
float ksqrt(float number) {
	float y;
	y = number;
	int i = *(int*)&y;//将y转成int 类型运算
	int a = 0x5F3759DF - (i >> 1);//最开始的常数是0x5F400000，这里可以改成0x5f3759df，答案更快精确, 右移奇数，会少了小数,
	y = *(float*)&a;//把a变回浮点数
	//牛顿迭代，f(x) = (1 / x^2) - a
	y = 1.5 * y - (number * 0.5) * y * y * y;//两位有效
	y = 1.5 * y - (number * 0.5) * y * y * y;//五位有效
	return y;
}
