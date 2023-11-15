#include <iostream>
#include <string>

/*string 的本质是一个类，里面维护了一个char* 的指针，还有封装了很多成员函数，find，copy，delete，replace，insert函数...*/
/*拼接函数：+= 或者 
//append(const char*)
//append(const string&)
//append(const char*, int n)
//append(const string&, int pos, int n)
*/
/*[] 取字符*/
int main() {
	std::string s1;
	s1 = "dfdfdf";
	std::string s2(s1);
	std::string s3("woshishabi");
	std::cout << "s1: " << s1 << std::endl;
	std::cout << "s2: " << s2 << std::endl;
	std::cout<< "s3: " << s3 << std::endl;
	std::string s4;
	s4 = s3;
	std::cout << "s4: " << s4 << std::endl;

	s4 = 'a';
	std::cout << "s4: " << s4 << std::endl;
	return 0;
}