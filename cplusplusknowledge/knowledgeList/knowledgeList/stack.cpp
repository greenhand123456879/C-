//#include<iostream>
//#include<stack>
//#include<queue>
//using namespace std;
//
//void test()
//{
//	stack<int> s;
//	int i = 10;
//	while (i--)
//		s.push(i);
//	cout << s.size() << endl;
//	while (!s.empty())
//	{
//		cout << s.top() << endl;
//		s.pop();
//	}
//	cout << s.size();
//
//}
//class Person
//{
//public:
//	Person(string aname, int aage)
//	{
//		name = aname;
//		age = aage;
//	}
//	string name;
//	int age;
//};
//
//ostream& operator<<(ostream& out, const Person& p)
//{
//	cout << "Ãû×Ö£º" << p.name << " ÄêÁä£º" << p.age;
//	return out;
//}
//
//void test1()
//{
//	queue<Person> q;
//	Person p1("1", 1);
//	Person p2("2", 1);
//	Person p3("3", 1);
//	Person p4("4", 1);
//
//	q.push(p1);
//	q.push(p2);
//	q.push(p3);
//	q.push(p4);
//	cout << q.size() << endl;;
//	while (!q.empty())
//	{
//		cout << q.back() << endl;
//		cout << q.front() << endl;
//		q.pop();
//	}
//	cout << q.size();
//}
//
//
//int main()
//{
//	test1();
//	return 0;
//}