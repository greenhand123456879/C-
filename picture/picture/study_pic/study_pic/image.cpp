#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<assert.h>

void ToGray(IMAGE* desImage, IMAGE* srcImage)
{
	//1.����Ŀ��ͼƬ��С
	desImage->Resize(srcImage->getwidth(), srcImage->getheight());
	//2. ��ȡ������,����������һ���������Ķ�ά���飬���Ǵ洢�ķ�ʽ��һά����Ĵ洢����
	DWORD* dPtr = GetImageBuffer(desImage);
	DWORD* sPtr = GetImageBuffer(srcImage);
	//3. copy����
	//for (int i = 0; i < srcImage->getheight() * srcImage->getwidth(); i++)
	//{
	//	*(dPtr + i) = *(sPtr + i);
	//}
	//4.ת�ɻҶ�ͼ _---->����argb(0,255,0,0) ���һ���Ҷ�ֵ argb(0,85,85,85)���ǰ�(r+g+b) / 3
	unsigned char r = 0;//UCHAR
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 0;
	DWORD averageRGB = 0;
	for (int i = 0; i < srcImage->getheight() * srcImage->getwidth(); i++)
	{
		r = *(sPtr + i);
		g = *(sPtr + i) >> 8;
		b = *(sPtr + i) >> 16;
		//a = *(sPtr + i) >> 24;
		averageRGB = (r + g + b) / 3;
		//*(dPtr + i) = (averageRGB | (averageRGB << 8)) | averageRGB << 16;
		*(dPtr + i) = RGB(averageRGB, averageRGB, averageRGB);
	}
	//x. ����
	//putimage(srcImage->getwidth(), 0, desImage);
}

void DarwTeacherImage(int x, int y, IMAGE* ima)
{
	DWORD* pImg = GetImageBuffer(ima);//ͼƬ������
	DWORD* pWin = GetImageBuffer();	//���ڻ�����
	int win_w = getwidth();
	int win_h = getheight();
	int ima_w = ima->getwidth();
	int ima_h = ima->getheight();
	printf("win_w = %d,win_h = %d,ima_w = %d,ima_h = %d", win_w, win_h, ima_w, ima_h);
	for (int iy = 0; iy < ima_w; iy++)
	{
		for (int ix = 0; ix < ima_h; ix++)
		{
			int ima_i = ix * ima_w + iy;
			int win_i = (ix + y) * win_w + (iy + x);
			UCHAR alpha = pImg[ima_i] >> 24;
			//printf("%d ", alpha);
			if (alpha > 200 && win_i >= 0 && win_i < win_w * win_h)
				pWin[win_i] = pImg[ima_i];
		}
		//printf("\n");
	}
	//printf("\n");
}

void DarwTeacherImage_s(int x, int y, IMAGE* ima)
{
	//assert(x >= 0 && y >= 0 && x <= getwidth() && y <= getheight() && ima != NULL);
	DWORD* pImg = GetImageBuffer(ima);//ͼƬ������
	DWORD* pWin = GetImageBuffer();	//���ڻ�����
	int win_w = getwidth();
	int win_h = getheight();
	int ima_w = ima->getwidth();
	int ima_h = ima->getheight();
	if (x < 0)
		ima_w = ima->getwidth() + x;
	else if (x + ima->getwidth() > win_w)
		ima_w = win_w - x;
	if (y < 0)
		ima_h = ima->getheight() + y;
	else if (y + ima->getheight() > win_h)
		ima_h = win_h - y;
	if (x >= 0 and y >= 0)
		pWin += y * getwidth() + x;
	else if (x >= 0 and y < 0)
	{
		pWin += x;
		pImg += abs(y) * ima->getwidth();
	}
	else if (x < 0 and y >= 0)
	{
		pWin += y * getwidth();
		pImg += abs(x);

	}
	else if (x < 0 and y < 0)
	{
		pImg += abs(y) * ima->getwidth() + abs(x);
	}
	printf("win_w = %d,win_h = %d,ima_w = %d,ima_h = %d", win_w, win_h, ima_w, ima_h);
	
	for (int iy = 0; iy < ima_h; iy++)
	{
		for (int ix = 0; ix < ima_w; ix++)
		{
			UCHAR alpha = pImg[ix] >> 24;
			//printf("%d ", alpha);
			if (alpha > 200)
				pWin[ix] = pImg[ix];
		}
		pImg += ima->getwidth();
		pWin += getwidth();
		//printf("\n");
	}
	//printf("\n");
}

void DarwMyImage_s(int x, int y, IMAGE* image)
{
	//assert(x >= 0 && y >= 0 && x <= getwidth() && y <= getheight() && image != NULL);
	assert(image);
	DWORD* Iptr = GetImageBuffer(image);//ͼƬ������
	DWORD* Wptr = GetImageBuffer();	//���ڻ�����
	int real_h;
	int real_w;

	//1.localization
	if (x >= 0 && y >= 0)
		Wptr += x + y * getwidth();
	else if (y <= 0 && x >= 0)
	{
		Wptr += x;
		Iptr += abs(y) * image->getwidth();
	}
	else if (x <= 0 && y >= 0)
	{
		Wptr += y * getwidth();
		Iptr += abs(x);
	}
	else if (x <= 0 && y <= 0)
	{
		Iptr += abs(x) + abs(y) * image->getwidth();
	}

	//2.real size of picture
	if (y > 0)
		real_h = y + image->getheight() > getheight() ? getheight() - y : image->getheight();
	else
		real_h = image->getheight() + y;
	if (x > 0)
		real_w = x + image->getwidth() > getwidth() ? getwidth() - x : image->getwidth();
	else
		real_w = image->getwidth() + x;

	//3.���Ŵ�ӡͼƬ�ڴ���
	for (int ix = 0; ix < real_h; ix++)
	{
		for (int iy = 0; iy < real_w; iy++)
		{
				UCHAR a = *(Iptr + iy) >> 24;
				//printf("%x ", a);//���Դ���
				if (a > 100)//filter, alpha͸����, 0��ʾ��ȫ͸��
				{
					*(Wptr + iy) = *(Iptr + iy);//ָ�벢û���߶�Ŷ,��ֻ����iy������,wptr,iptr֮��Ŀռ�,��Ҳ��ָ�����;,hhhhhh
				}
		}
		//����
		Wptr += getwidth();
		Iptr += image->getwidth();
		//printf("\n");
	}
}

void DarwMyImage(int x, int y, IMAGE* image)
{
	DWORD* Iptr = GetImageBuffer(image);//ͼƬ������
	DWORD* Wptr = GetImageBuffer();	//���ڻ�����

	//�ڴ��ڻ�ȡͼƬ��ʵ���ϴ�����һ��һά���飬�������ǲ�����ʱ���������һ����ά���飬������Ҫת��
	// --------------
	//    0 1 2 3
	// 
	//0   0 1 2 3
	//1   4 5 6 7
	//2   8 9 10 11
	// --------------
	//����9��������(2, 1),9 = width * 2 + 1, ��������Ϊ(i, j), i��������,j��������
	//ͨʽ: һά��������� = i * width + j
	for (int ix = 0; ix < image->getheight(); ix++)
	{
		for (int iy = 0; iy < image->getwidth(); iy++)
		{
			if ((ix + y) * getwidth() + (iy + x) < (840 + 840 + 120) * 840 && (ix + y) * getwidth() + (iy + x) >=0 )//��ֹ����Խ��
			{

				UCHAR a = *(Iptr + ix * image->getwidth() + iy) >> 24;
				printf("%x ", a);//���Դ���
				if (a > 100)//filter, alpha͸����, 0��ʾ��ȫ͸��
					*(Wptr + (ix + y) * getwidth() + (iy + x)) = *(Iptr + ix * image->getwidth() + iy);
			}
		}
		printf("\n");
	}

	//image->getheight();
	//image->getwidth();
	//ʵ���������
	//putimage(0, 300, image);
}

void test01()
{
	//��������ͼƬ����
	IMAGE pic_1;
	//�������ǵ�ͼƬ
	loadimage(&pic_1, _T("C:/Users/luolan/my_D/VS19/ALLprogarm/picture/3.jpg"), 2560 / 3, 1440 / 3);
	//DarwTeacherImage(0, 0, &pic_1);
	DarwMyImage_s(-600, -300, &pic_1);
	//putimage(0, 0, &pic_1);
	//ת�ɻҶ�ͼ
	IMAGE gray;
	//ToGray(&gray, &pic_1);
	//putimage(860, 0, &gray);
	//putimage(850, 0, &pic_1);
	system("pause");
}
void test02()
{
	//��������ͼƬ����
	IMAGE pic_1;
	//�������ǵ�ͼƬ
	loadimage(&pic_1, _T("C:/Users/luolan/my_D/VS19/ALLprogarm/picture/2.jpg"), 2560 / 3, 1440 / 3);
	COLORREF color = getpixel(0, 0);
	UCHAR r = color;
	UCHAR g = color >> 8;
	UCHAR b = color >> 16;
	UCHAR a = color >> 24;
	printf("%x %x %x %x;", r, g, b, a);
}

int main()
{
	//��������
	int width = 840 + 840 + 120;
	int height = 840;
	initgraph(width, height, EW_SHOWCONSOLE);
	//����һ�´��ڱ�����ɫ  
	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	//��ʾ
	test01();
	//ȡһ�����ص�
	//test02();
	//system("puase");
	return 0;
}