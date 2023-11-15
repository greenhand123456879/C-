//#include<iostream>
//#include<deque>
//using namespace std;
//
//void PrintDeque(const deque<int> &d)
//{
//	for (deque<int>::const_iterator i = d.begin(); i < d.end(); i++)
//	{
//		cout << *i << " ";
//	}
//}
//
//int main()
//{
//	deque<int> deqt;
//	for (int i = 0; i < 10; i++)
//	{
//		deqt.push_back(i);
//	}
//	PrintDeque(deqt);
//	deque<int> deqt1(deqt);
//	cout << "size:" << deqt.size();
//	cout << "empty:" << deqt.empty();
//	deqt.resize(15);
//	PrintDeque(deqt);
//	deqt.resize(20, 1);
//	PrintDeque(deqt);
//	deqt.push_back(1);
//	deqt.pop_back();
//	deqt.push_front(2);
//	deqt.pop_front();
//	return 0;
//}