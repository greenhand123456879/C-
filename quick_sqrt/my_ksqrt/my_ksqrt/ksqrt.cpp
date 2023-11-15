#include "ksqrt.h"
//���������ֵ���Ǻܾ�ȷ
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


//ţ�ٵ�����
float commonsqrt(float number) {
	float y0, yn;
	int count = 0;
	y0 = number / 2.0;
	//ţ�ٵ�����f(x) = (1 / x^2) - a
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


//https://www.cnblogs.com/luo-greenhand/p/17831818.html���
float ksqrt(float number) {
	float y;
	y = number;
	int i = *(int*)&y;//��yת��int ��������
	int a = 0x5F3759DF - (i >> 1);//�ʼ�ĳ�����0x5F400000��������Ըĳ�0x5f3759df���𰸸��쾫ȷ, ����������������С��,
	y = *(float*)&a;//��a��ظ�����
	//ţ�ٵ�����f(x) = (1 / x^2) - a
	y = 1.5 * y - (number * 0.5) * y * y * y;//��λ��Ч
	y = 1.5 * y - (number * 0.5) * y * y * y;//��λ��Ч
	return y;
}
