#include <iostream>
#include <string>

/*string �ı�����һ���࣬����ά����һ��char* ��ָ�룬���з�װ�˺ܶ��Ա������find��copy��delete��replace��insert����...*/
/*ƴ�Ӻ�����+= ���� 
//append(const char*)
//append(const string&)
//append(const char*, int n)
//append(const string&, int pos, int n)
*/
/*[] ȡ�ַ�*/
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