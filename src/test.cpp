#include <iostream>
#include <string>
#include "LargeInteger.h"
#include <deque>

using std::string;

void Tests();

int main() {
	Tests();
	return 0;
}



void Tests() {
	//Interfaces：
	//	构造函数：
	
	//	LargeInteger(string input);  用字符串构造，默认会检查字符合法性
	LargeInteger CS1("-2022");
	CS1.PrintLargeInt_cout();
	std::cout << "\n";

		//	LargeInteger(string input, bool Check_value);  bool对应是否检查字符规范
	LargeInteger CS2("2-022",false);
	CS2.PrintLargeInt_cout();
	std::cout << "\n";

	//	LargeInteger(const deque<int>&, bool, bool reverse = false);  用deque初始化，bool对应符号、deque是否为反向
	std::deque<int> cs3;
	cs3.push_back(1);
	cs3.push_back(2);
	LargeInteger CS3(cs3, true);
	CS3.PrintLargeInt_cout();
	std::cout << "\n";

	//	LargeInteger();  生成初始化为0的对象
	LargeInteger CS4;
	CS4.PrintLargeInt_cout();
	std::cout << "\n";

	//	重载运算符：
	LargeInteger a("98765432112345678998765432101234567890987654321123456789987654321123456789987654321");
	LargeInteger b("2147483647", true);
	LargeInteger c("-65536", false);
	LargeInteger d("310", false);
	LargeInteger e("-310", false);
	LargeInteger f("310");
	//	bool operator==(const LargeInteger & input) const;
	std::cout << (a == b) << " " << (d == f) << "\n";
	//	bool operator!=(const LargeInteger & input) const；
	std::cout << (d != f) << "\n";
	//LargeInteger operator+(const LargeInteger&) const;
	(b + c).PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator-(const LargeInteger&) const;
	(d - c).PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator-() const;
	(-e).PrintLargeInt_cout();
	//LargeInteger operator=(int);  用整数构造LargeInteger
	LargeInteger CS5;
	CS5 = 15;
	CS5.PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator=(string);  用字符串构造LargeInteger
	CS5 = "16";
	CS5.PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator/(const LargeInteger&)const;
	(b / d).PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator%(const LargeInteger&)const;
	(b % d).PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator*(const LargeInteger&)const;
	(c * d).PrintLargeInt_cout();
	std::cout << "\n";

	//bool operator>(const LargeInteger&)const;
	std::cout << (b > d) << "\n";
	//及 += -= *= < >= <= ++ --

	//	成员函数：
	//	LargeInteger absolute() const;  返回对象的绝对值
	c.absolute().PrintLargeInt_cout();
	std::cout << "\n";

	//	void TakeAbsolute();  使对象取绝对值
	CS1.TakeAbsolute();
	CS1.PrintLargeInt_cout();
	//	LargeInteger UnsignedAdd(const LargeInteger & b)const;  无符号加法
	(b.UnsignedAdd(c)).PrintLargeInt_cout();
	std::cout << "\n";

	//	void PrintLargeInt()const;  用cout输出大整数，未标准化对象
	//	string ToString()const;  返回字符串型大整数，未标准化对象
	string str = a.ToString();
	std::cout << str << "\n";
	//	LargeInteger Multiple_AddRow(const LargeInteger&)const;  乘法的另一种实现，效率较低
	(c.Multiple_AddRow(d)).PrintLargeInt_cout();
	std::cout << "\n";

	//	LargeInteger UnsignedDivision(const LargeInteger&)const;  无符号除法
	(b / d).PrintLargeInt_cout();
	std::cout << "\n";

	//	void Right_Digit_Operation(int carry_number = 0);  右方位运算
	d.Right_Digit_Operation();
	d.PrintLargeInt_cout();
	std::cout << "\n";

	//	void Left_Digit_Operation(int carry_number = 1);  左方位运算
	//	void Divide2_Algorithm();  相对高性能的除以二，要求位数大于2，否则错误
	a.Divide2_Algorithm();
	a.PrintLargeInt_cout();
	std::cout << "\n";

	//	void Divide2_Digit();  按位除以2
	b.Divide2_Digit();
	b.PrintLargeInt_cout();
	std::cout << "\n";

	//	void Divide2_Bit();  个位除以2，补充上方的错误
	
	//	LargeInteger AddAssignment(const LargeInteger&);  优化的 +=
	b.AddAssignment(d);
	b.PrintLargeInt_cout();
	std::cout << "\n";

	//	bool IsZero()const;  返回对象是否为0
	LargeInteger CSZero("000");
	LargeInteger CSOne("0015");
	std::cout << CSZero.IsZero() << "\n";
	//	void PopZero();  去除多余0，也会使对象标准化
	CSZero.PopZero();
	CSOne.PopZero();
	CSZero.PrintLargeInt_cout();
	std::cout << " ";
	CSOne.PrintLargeInt_cout();
	std::cout << "\n";

	//	void TenFold();  相当于 *= 10
	f.TenFold();
	f.PrintLargeInt_cout();
}

int TestInCoding() {
	std::deque<int> setDeque;
	setDeque.push_back(1);
	setDeque.push_back(2);
	LargeInteger f(setDeque, true);
	LargeInteger a("98765432112345678998765432101234567890987654321123456789987654321123456789987654321");
	LargeInteger b("2147483647", true);
	LargeInteger c("10", false);
	LargeInteger d("5", false);
	LargeInteger e("2", false);
	LargeInteger g;
	(a).PrintLargeInt_cout();
	/*a.PrintLargeInt_cout();
	b.PrintLargeInt_cout();
	c.PrintLargeInt_cout();
	f.PrintLargeInt_cout();*/
	//c += b;
	//(a*=c).PrintLargeInt_cout();
	//std::cout << (b > a) << ' ' << (a > c) << " " << (e > a)<<" "<<(d>e);
	//std::cout << (true && 2);
	//a.PopZero();
	//a.Divide2_Algorithm();
	//g = -1305;
	//g.PrintLargeInt_cout();
	//c.TenFold();
	//d.TenFold(3);
	//c.PrintLargeInt_cout();
	//d.PrintLargeInt_cout();
	//(a*c).PrintLargeInt_cout();
	//std::cout <<' ' << (c == d) << ' ' << (c == e) << ' ' << (c != d) << ' ' << (c != e) << ' '<<(b==c)<<' '<<(b!=c) << std::endl;
	/*int a0 = -3, b0 = 4;
	a0 = a0 ^ b0;
	b0 = a0 ^ b0;
	a0 = a0 ^ b0;
	std::cout <<" " << a0 << b0;*/
	//a.Right_Digit_Operation(0);
	return 0;
}