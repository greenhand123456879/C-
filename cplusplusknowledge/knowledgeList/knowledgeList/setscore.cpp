//#include<iostream>
//#include<string>
//#include<deque>
//#include<vector>
//#include<algorithm>
//#include<ctime>
//using namespace std;
//
//class Person
//{
//public:
//	Person(string aname, double ascore)
//	{
//		name = aname;
//		score = ascore;
//	}
//	string name;
//	double score;
//};
//
//void PrintPerson(const vector<Person> &v)
//{
//	for (vector<Person>::const_iterator i = v.begin(); i < v.end(); i++)
//	{
//		cout << "选手：" << (*i).name << " 分数：" << (*i).score << endl;
//	}
//}
//
//void CreatePerson(vector<Person>& v)
//{
//	string abcd = "ABCD";
//	
//	for (int j = 0; j < 4; j++)
//	{
//		string temp = "选手";
//		temp += abcd[j];
//		Person p(temp, 0);
//		
//		v.push_back(p);
//	}
//}
//
//void SetScore(vector<Person>& v)
//{
//	for (vector<Person>::iterator it = v.begin(); it < v.end(); it++)
//	{
//		deque<int> d;
//
//		for (int i = 0; i < 10; i++)
//		{
//			d.push_back(rand() % 41 + 60);
//		}
//		sort(d.begin(), d.end());
//		d.pop_front();
//		d.pop_back();
//		int sum = 0;
//		for (deque<int>::const_iterator itt = d.begin(); itt < d.end(); itt++)
//		{
//			sum += *itt;
//		}
//		double averageScore = sum / 8.0;
//
//		(*it).score = averageScore;
//	}
//
//
//
//
//}
//
//int main()
//{
//	int a[10] = { 0 };
//	srand((unsigned int)time(NULL));
//	vector<Person> v;
//	CreatePerson(v);
//	PrintPerson(v);
//	
//	SetScore(v);
//	PrintPerson(v);
//	return 0;
//}