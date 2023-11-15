#include<iostream>

using namespace std;
//
////1. 封装：mean 我不想给别人看到或去使用，但是可以通过setter and getter 来 access
////2. 抽象：mean 我需要把实现功能与用户操作分离，实现功能可以复杂，但是操作不能复杂，，可以通过抽象类来实现，抽象类实际就是用一个纯虚函数，只定义，不声明，只有在子类继承的时候才需要给出具体函数实现
////3. 多态: mean 我们用父类指针去调用子类相同函数名的函数，父类需要声明该函数名为virtual虚函数
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