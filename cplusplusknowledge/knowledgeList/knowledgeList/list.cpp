//#include<iostream>
//#include<list>
//
//using namespace std;
//
//void printlist(const list<int> list1)
//{
//	for (list<int>::const_iterator it = list1.begin(); it != list1.end(); it++)
//	{
//		cout << *it << endl;
//	}
//}
//
//void test1()//���캯��
//{
//	list<int> l1;
//	l1.push_back(1);
//	l1.push_back(2);
//	l1.push_back(3);
//	printlist(l1);
//	list<int>l2(l1.begin(), l1.end());
//	printlist(l2);
//	list<int>l3(l2);
//	printlist(l2);
//
//}
//
//void test2()//��ֵ�뽻��
//{
//	list<int> l1;
//	l1.push_back(1);
//	l1.push_back(2);
//	l1.push_back(3);
//	l1.push_back(2);
//	l1.push_back(1);
//	list<int> l2;
//	l2 = l1;
//	printlist(l2);
//}
//
//void test3()
//{
//	string path = R"(C:\luolan\my_D\Allprogarm\chess)";
//	//int * ptr = new int[10];
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	ptr[i] = i;
//	//	cout << "arr" << "[" << i << "] = " << i << endl;
//	//}
//	
//	//int* large = new (std::nothrow) int[1000000001];
//	//if (large == nullptr)
//	//{
//	//	large[1000000000] = 0;
//	//	delete[] large;
//	//}
//	//else
//	//	cout << "!!!!!!�ڴ����ʧ�ܣ�" << endl;
//	
//}
//
//void test4()
//{
//	list<int> l1;
//	l1.push_back(1);
//	l1.push_back(2);
//	l1.push_back(3);
//	printlist(l1);
//	if (!l1.empty())
//		cout << "��Ϊ��!" << "��СΪ��" << l1.size() << endl;
//	else
//		cout << "Ϊ��" << endl;
//	l1.resize(1);
//	printlist(l1);
//}
//
//void test5()
//{
//	list<int> list1;
//	list1.push_back(10);
//	list1.push_back(20);
//	list1.push_back(30);
//	list1.push_back(40);
//	list1.push_back(40);
//	list1.push_back(30);
//	list1.push_back(20);
//	list1.push_back(10);
//	printlist(list1);
//	list1.reverse();
//	printlist(list1);
//	list1.sort();
//	printlist(list1);
//	
//}
//
//
//
//class Person
//{
//public:
//	int age;
//	string name;
//	double height;
//	Person(int mage, string mname, double mheight):age(mage), name(mname), height(mheight){}
//	
//private:
//
//};
//
//void printlistPerson(const list<Person> listPerson)
//{
//	for (list<Person>::const_iterator it = listPerson.begin(); it != listPerson.end(); it++)
//	{
//		cout << "������" << (*it).name << " ���䣺" << (*it).age << " ��ߣ�" << (*it).height << endl;
//	}
//}
//
//bool comparePerson(const Person& p1, const Person& p2)
//{
//	if (p1.age < p2.age)
//		return true;
//	else if (p1.age > p2.age)
//		return false;
//	else if (p1.age == p2.age)
//		return p1.height > p2.height;
//}
//
//
//void SortPerson(list<Person> &listPerson)
//{
//	//����������������������ͬ���������  ���н���
//	cout << "����" << endl;
//	listPerson.sort(comparePerson);
//}
//
//
//int main()
//{
//	list<Person> listPerson;
//	Person p1(21, "1", 163.5);
//	Person p2(11, "2", 164.5);
//	Person p3(31, "3", 155.6);
//	Person p4(41, "4", 169.1);
//	Person p5(1, "5", 173.3);
//	Person p6(12, "6", 153.4);
//	Person p7(51, "7", 183);
//	Person p8(31, "8", 183);
//	listPerson.push_back(p1);
//	listPerson.push_back(p2);
//	listPerson.push_back(p3);
//	listPerson.push_back(p4);
//	listPerson.push_back(p5);
//	listPerson.push_back(p6);
//	listPerson.push_back(p7);
//	listPerson.push_back(p8);
//	printlistPerson(listPerson);
//	SortPerson(listPerson);
//	printlistPerson(listPerson);
//
//	//test5();
//	return 0;
//}  