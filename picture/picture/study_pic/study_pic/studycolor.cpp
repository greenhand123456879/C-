#include<stdio.h>
#include<easyx.h>

bool CheckDaXiaoDuan()
{
	union u
	{
		int a = 1;
		char c;

	}u1;
	return u1.c;
}

//int main()
//{
//	int width = 640;
//	int height = 840;
//	initgraph(width, height, EX_SHOWCONSOLE);//kuan,gao
//	
//	int size = 400;
//	//for (int i = 0; i < 500; i++)
//	//{
//	//	if (i < 255)
//	//		putpixel(i, 50, RGB(0, 0, i));
//	//	else
//	//	 putpixel(i, 50, RGB(255, 255, 255));
//	//}
//
//	for (int i = width / 2 - size / 2; i < width / 2 + size / 2; i++)
//	{
//		//COLORREF color = RGB(rand() % 256, rand() % 256, rand() % 256);
//		COLORREF color = RGB(0, 0, i);
//		int randColor = ((63 << 8) | (125)) | (77 << 16);
//		for (int j = height / 2 - size / 2; j < height / 2 + size / 2; j++)
//		{
//			//putpixel(i, j, RGB(rand() % 256, rand() % 256, rand() % 256));
//			putpixel(i, j, randColor);
//		} 
//	}
//	//RED;
//	int red = 0x000000AA;
//
//	unsigned char r = red;
//	unsigned char g = red >> 8;
//	unsigned char b = red >> 16;
//	printf("r = %d, g = %d, b = %d", r, g, b);
//
//	//将三个数字转成一个颜色值
//	int randColor = ((63 << 8) | (125)) |(77 << 16);
//
//	printf(" x = %x", randColor);
//	getchar();
//
//	return 0;
//}