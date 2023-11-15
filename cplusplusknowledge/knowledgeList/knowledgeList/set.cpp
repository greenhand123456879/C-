//#include<iostream>
//#include<set>
//
//using namespace std;
//
//class Person
//{
//public:
//	Person(string aname, int aage) :name(aname), age(aage){}
//	string name;
//	int age;
//};
//
//class PersonCompare
//{
//public:
//	bool operator()(const Person& p1, const Person& p2) const 
//	{
//		return p1.age > p2.age;
//	}
//};
//
//
//class MyCompare
//{
//public:
//	bool operator() (const int s1, const int s2) const
//	{
//		return s1 > s2;
//	}
//};
//
//void printmultiset(const multiset<int>& ms)
//{
//	for (multiset<int>::const_iterator it = ms.begin(); it != ms.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}
//
//void printset(const set<int>& s)
//{
//	for (set<int>::const_iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}
//
//
//
//void test05()
//{
//	Person p1("11111", 19);
//	Person p2("11112", 132);
//	Person p3("11113", 20);
//	Person p4("11114", 11);
//	Person p5("11115", 30);
//
//	set<Person, PersonCompare> sp;
//
//	sp.insert(p1);
//	sp.insert(p2);
//	sp.insert(p3);
//	sp.insert(p4);
//	sp.insert(p5);
//
//	for (set<Person, PersonCompare>::iterator it = sp.begin(); it != sp.end(); it++)
//	{
//		cout << (*it).age << " " << (*it).name << endl;
//	}
//}
//void test04()
//{
//	set<int, MyCompare> s;
//	s.insert(10);
//	s.insert(340);
//	s.insert(0);
//	s.insert(1010);
//	s.insert(10);
//	s.insert(10156);
//	for (set<int, MyCompare>::iterator it = s.begin(); it != s.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}
//void test03()
//{
//	pair<string, int> par = make_pair("sdfds", 10);
//	cout << par.first << " " << par.second << " " << endl;
//}
//
//void test02()
//{
//	multiset<int> ms;
//	//pair<set<int>::iterator, bool> par = s.insert(10);
//	//if (par.second)
//	ms.insert(1000);
//	ms.insert(100);
//	ms.insert(10);
//	//if (par.second)
//	//	cout << "成功！" << endl;
//	ms.insert(10);
//	printmultiset(ms);
//}
//
//void test01()
//{
//	set<int> s;
//	pair<set<int>::iterator, bool> par = s.insert(10);
//	if (par.second)
//		cout << "成功！" << endl;
//	s.insert(1000);
//	s.insert(100);
//	par = s.insert(10);
//	if (par.second)
//		cout << "成功！" << endl;
//
//	printset(s);
//	if (s.find(10) != s.end())
//		cout << *(s.find(10));
//	cout << s.count(10);
//}
//int main()
//{
//	test05();
//	return 0;
//}