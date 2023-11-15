#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<graphics.h>
#include<string.h>
#include<string>
#include<math.h>
#include <random>
#include<time.h>
#include<vector>
#include<assert.h>
using namespace std;

struct MyPoint
{
	int x;
	int y;
};
//void Loadcontact(contact* pcon)
//{
//	Peoinfo tmp = { 0 };
//	FILE* pfread = fopen("contact.txt", "r");
//	if (pfread == NULL)
//	{
//		printf("load::%s\n", strerror(errno));
//		return;
//	}
//	while ((fscanf(pfread, "%s         	%s              	%s    	%d  	%s                             ",
//		tmp.name,
//		tmp.tele,
//		tmp.sex,
//		&tmp.age,
//		tmp.address)) == 5)
//	{
//		pcon->data[pcon->size] = tmp;
//		pcon->size++;
//		check_capacity(pcon);
//	}
//	printf("上次数据加载成功\n");
//	fclose(pfread);
//	pfread = NULL;
//}


//void Save_contact(contact* pcon)
//{
//	FILE* pfwrite = fopen("contact.txt", "w");
//	if (pfwrite == NULL)
//	{
//		printf("save ::%s\n", strerror(errno));
//		return;
//	}
//	for (int i = 0; i < pcon->size; i++)
//	{
//		fprintf(pfwrite, "%-10s\t%-15s\t%-5s\t%-3d\t%-30s\n",
//			pcon->data[i].name,
//			pcon->data[i].tele,
//			pcon->data[i].sex,
//			pcon->data[i].age,
//			pcon->data[i].address);
//	}
//	printf("保存成功\n");
//	fclose(pfwrite);
//	pfwrite = NULL;
//}

		
void PrintVector(const vector<int>& v)
{
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void PrintVectorContrast(const vector<int>& v1, const vector<int>& v2)
{
	vector<int>::const_iterator it2 = v2.begin();
	for (vector<int>::const_iterator it = v1.begin(); it != v1.end(); it++, it2++)
	{
		if (*it != *it2)
			cout << *it << "->" << *it2 << endl;
		else
			cout << "error!" << endl;
	}
	cout << endl;
}


void DelVector(vector<int>& v1, vector<int>& v2)
{
	size_t num = 0;
	size_t size = min(v1.size(), v2.size());
	for (int i = 0; i <size; i++)
	{
		if (v1[i] == v2[i])
		{
			v1.erase(v1.begin() + i);
			v2.erase(v2.begin() + i);
			i--;
			size--;
			num++;
		}
	}
	cout << "总共删除了" << num << endl;
}

void drawlink(const MyPoint* myPoint1,const vector<int>& target, const vector<int>& source)
{
	vector<int>::const_iterator it2 = source.begin();
	for (vector<int>::const_iterator it = target.begin(); it != target.end(); it++, it2++)
	{
		setlinecolor(BLACK);//黑线
		setlinestyle(PS_SOLID, 1);//实线,1宽
		cout << *it << "->" << *it2 << endl;
		//myPoint1[*it]->myPoint1[*it2];
		line(myPoint1[*it].x, myPoint1[*it].y, myPoint1[*it2].x, myPoint1[*it2].y);
	}
}

int main()
{
	FILE* pfwrite = fopen("node_distribution.txt", "w");
	if (pfwrite == NULL)
	{
		printf("save ::%s\n", strerror(errno));
		return 0;
	}
	//mt19937 gen((unsigned int)time(nullptr)); // 定义随机数生成器对象gen，使用time(nullptr)作为随机数生成器的种子
	//normal_distribution<double> dis(0.0, 1.0); // 定义随机数分布器对象dis，期望为0.0，标准差为1.0的正态分布
	//使用dis(gen)

	std::default_random_engine random(time(NULL));
	std::uniform_int_distribution<int> dis(0, 199);
	
	initgraph(2000, 900, SHOWCONSOLE);
	cout << "my name is luolan" << endl;
	//绘制背景颜色
	setbkcolor(RGB(128,128,128));
	cleardevice();//刷新graph界面
	//设置线的属性

	//fillcircle,line 两个函数要做的事
	// 
	setlinecolor(BLACK);//黑线
	setlinestyle(PS_SOLID, 1);//实线,1宽
	vector<int> target;
	vector<int> source;
	for (int i = 0; i < 200; i++)
	{
		int randomNum = rand() % 10 + 1;
		for (int it = 0; it < randomNum; it++)
		{
			target.push_back(i);
			std::uniform_int_distribution<int> dis1((i - 10) > 0 ? (i - 10) : 0, (10 + i) < 200 ? (10 + i) : 199);
			//int randomSource = i + rand() % 10;
			/*while (i == randomSource)
				randomSource = i + rand() % 10;*/

			source.push_back(dis1(random));
		}
	}
	MyPoint myPoint1[200] = { 0 };
	for (int i = 0; i < 200; i++)
	{
		
		myPoint1[i].x = (i + dis(random)) * 5;
		myPoint1[i].y = (i + dis(random)) * 2;
		putpixel(myPoint1[i].x, myPoint1[i].y, BLACK);
	}
	//drawlink(myPoint1, target, source);
	PrintVector(target);
	PrintVector(source);
	//PrintVectorContrast(target, source);
	DelVector(target, source);
	PrintVectorContrast(target, source);
	//drawlink(myPoint1, target, source);


	//fprintf(pfwrite, "node_distribution-> good : bad = %d : %d\n", average, 200 - average);
	//双缓冲绘图，防止闪屏
	//BeginBatchDraw();
	//while (1)
	//{


	//	FlushBatchDraw();

	//}

	//EndBatchDraw();
	fclose(pfwrite);
	system("pause");
	return 0;
}