#include<iostream>

using namespace std;
//
////1. ��װ��mean �Ҳ�������˿�����ȥʹ�ã����ǿ���ͨ��setter and getter �� access
////2. ����mean ����Ҫ��ʵ�ֹ������û��������룬ʵ�ֹ��ܿ��Ը��ӣ����ǲ������ܸ��ӣ�������ͨ����������ʵ�֣�������ʵ�ʾ�����һ�����麯����ֻ���壬��������ֻ��������̳е�ʱ�����Ҫ�������庯��ʵ��
////3. ��̬: mean �����ø���ָ��ȥ����������ͬ�������ĺ�����������Ҫ�����ú�����Ϊvirtual�麯��
class AbstractMovie
{
	virtual void script() = 0;
};

class Movie :private AbstractMovie
{
private:
	string rating;
	void script()
	{
		cout << "character, story, music." << endl;
	}
public:
	string title;
	string director;
	Movie()
	{
		rating = "NR";
		title = "no title"; 
		director = "no director";
	}
	Movie(string atitle, string adirector, string arating)
	{
		title = atitle;
		director = adirector;
		rating = arating;
	}
	//~Movie();
	void SetRating(string arating)
	{
		if ("G" == arating || "PG" == arating || "PG -13" == arating || "R" == arating || "NR" == arating)
			rating = arating;
		else
			rating = "NR";

	}
	string GetRating()
	{
		return rating;
	}
	void SetTitle(string atitle)
	{
		title = atitle;
	}
	string GetTitle()
	{
		return title;
	}
	void SetDirector(string adirector)
	{
		director = adirector;
	}
	string GetDirector()
	{
		return director;
	}
};
//
class MovieEmployee : public Movie
{
public:
	MovieEmployee(string atitle, string adirector, string arating, string amyDialogue)
		:Movie(atitle, adirector, arating),myDialogue(amyDialogue)
	{
		//myDialogue = amyDialogue;
	}
	//~MovieEmployee();
	void GetMyTitle()
	{
		//cout << GetTitle();
		//cout << script();
	}
private:
	string myDialogue;
};
//
//class Teacher : MovieEmployee
//{
//public:
//	Teacher(string atitle, string adirector, string arating, string amyDialogue, string amysubject)
//		:MovieEmployee(atitle, adirector, arating, amyDialogue)
//	{
//		mysubject = amysubject;
//	}
//	//~MovieEmployee();
//	void PreLesson()
//	{
//
//	}
//private:
//	string mysubject;
//};
//
//int main()
//{
//	MovieEmployee employee1("niubu", "luolan", "NR", ".......");
//	Teacher teacher1("niubu", "luolan", "NR", ".......", "english");
//	teacher1.PreLesson();
//	return 0;
//}