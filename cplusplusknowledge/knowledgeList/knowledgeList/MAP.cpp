//#include<iostream>
//#include<map>
//#include<vector>
//using namespace std;
//
//void printmap(const map<int, string>& map1)
//{
//	for (map<int, string>::const_iterator it = map1.begin(); it != map1.end(); it++)
//	{
//		cout << (*it).first << " " << it->second << endl;
//	}
//}
//
//class MyCompare
//{
//public:
//	bool operator() (const int& x, const int& y) const
//	{
//		return x > y;
//	}
//};
//
//void test02()
//{
//	map<int, string, MyCompare> m;
//	m.insert(make_pair(1, "ll"));
//	m.insert(make_pair(2, "zyr"));
//	m.insert(make_pair(3, "zzf"));
//	m.insert(make_pair(4, "lyz"));
//	for (map<int, string, MyCompare>::iterator i = m.begin(); i != m.end(); i++)
//	{
//		cout << "key = " << i->first << " value = " << i->second << endl;
//	}
//}
//
//void test01()
//{
//	map<int, string> map1;
//	map1.insert(pair<int, string>(1, "ll"));
//	map1.insert(pair<int, string>(2, "zyr"));
//	map1.insert(pair<int, string>(3, "zzf"));
//	map1.insert(pair<int, string>(4, "lyz"));
//
//	map<int, string> map2;
//	map2.insert(pair<int, string>(1, "ll1"));
//	map2.insert(make_pair(2, "zyr2"));
//	map1.swap(map2);
//	cout << "map1:" << map1.size() << endl;;
//	printmap(map1);
//
//	map1.erase(10);
//	//map1.erase(1);
//
//	printmap(map1);
//}
//
//
//
//class Employee
//{
//	friend ostream& operator<<(ostream& cout1, Employee& e);
//public:
//	Employee(char aname, int asalary, string adepartment) :name(aname), salary(asalary), department(adepartment){}
//	string department;
//	char name;
//	int salary;
//	friend ostream& operator<<(ostream& cout1 ,Employee& e)
//	{
//		cout << "name : " << e.name << " ";
//		cout << "salary : " << e.salary;
//		return cout1;
//	}
//	
//};
//
//void test03()
//{
//	const string departmentName[3] = { "策划", "美术", "研发" };
//	vector<Employee> ve;
//	for (int  i = 0; i < 10; i++)
//	{
//		int randNum = rand() % 3;
//		int randSalary = rand() % 6001 + 3000;
//		char s = 'A' + i;
//		Employee p((s), randSalary, departmentName[randNum]);
//		ve.push_back(p);
//	}
//	/*for (vector<Employee>::iterator i = ve.begin(); i != ve.end(); i++)
//	{
//		cout << "department : " << i->department << " name: " << i->name << " salary: " << i->salary << endl;
//	}*/
//
//	multimap<string,Employee> m;
//	for (vector<Employee>::iterator i = ve.begin(); i != ve.end(); i++)
//	{
//		m.insert({ i->department, *i });
//	}
//
//	multimap<string, Employee>::iterator pos = m.find(departmentName[0]);
//	int count = m.count(departmentName[0]);
//	for (int i = 0;i < count; pos++, i++)
//	{
//		cout << "key : " << pos->first << " value : " << pos->second << endl;
//		cout << "========" << endl;
//	}
//	pos = m.find(departmentName[1]);
//	count = m.count(departmentName[1]);
//	for (int i = 0; i < count; pos++, i++)
//	{
//		cout << "key : " << pos->first << " value : " << pos->second << endl;
//		cout << "========" << endl;
//
//	}
//	pos = m.find(departmentName[2]);
//	count = m.count(departmentName[2]);
//	for (int i = 0; i < count; pos++, i++)
//	{
//		cout << "key : " << pos->first << " value : " << pos->second << endl;
//	}
//}
//int main()
//{
//	//test03();
//
//	int* a = new int[100000000];
//	while (1);
//	return 0;
//}