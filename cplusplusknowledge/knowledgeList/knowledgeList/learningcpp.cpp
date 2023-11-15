//#include<iostream>
//#include<string>
//#include<assert.h>
//#include"myfunmax.h"
//using namespace std;

//递归
//整体思想: 把大任务不断细分成小任务，而最后有一个出口来结束细分的任务
//1. 先写出细分任务
//2. 写出结束条件
//3. 特殊边界问题需要另外处理
//4. 递归函数至少有两个return

 
//int main()
//{
//	//string s1;
//	//s1 = "hello world!";
//	//cout << s1 << endl;
//	//cout << s1[1];
//	//cout << s1.find("h", 1);
//	//cout << s1.substr(6, 5);
//	//cout << " before:" << s1.append("123");
//	//cout << " APPEND:" << s1;
//	//cout << " ERASE:" << s1.erase() << endl;
//	//cout << s1;
//
//	//int a = 10;
//	//ceil(), floor(),round()
//	//fmax(), fmin()
//	//pow(), sprt()
//
//	//input 
//	/*int age;char b = 'a';
//	cout << "enter your age: ";
//	cin >> age;  
//	cout << "You are " << age << " years old" << endl;*/
//	//string name;
//	//cout << "enter your name: ";
//	//getline(cin, name);//input string, use getline function
//	//cout << "Hello " << name << endl;
//
//	//input game 
//	//string color, celebrity, nonu;
//	//cout << "enter the color: " << endl;
//	//getline(cin, color);
//	//cout << "enter the celebrity: " << endl;
//	//getline(cin, celebrity);
//	//cout << "enter the nonu: " << endl;
//	//getline(cin, nonu);
//	//cout << color << " is my favorite color!" << endl;
//	//cout << "I love " << celebrity << endl;
//	//cout << nonu << " is so bad!" << endl;
//	
//	//int arr[] = { 9,2,3,4,5,6,7,34,3,3,43,34,3,3,423,423,534,645,756,876,867,86,34,523,423,4,345,47,568,56,6743,523,423,54,765,856,643,53,46,456,45,234,5534,634,5};
//	//cout << MyFunMax(arr, sizeof(arr) / sizeof(arr[0]));
//
//	 
//
//	return 0;
//}