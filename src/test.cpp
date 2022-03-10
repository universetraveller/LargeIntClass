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
	//Interfaces��
	//	���캯����
	
	//	LargeInteger(string input);  ���ַ������죬Ĭ�ϻ����ַ��Ϸ���
	LargeInteger CS1("-2022");
	CS1.PrintLargeInt_cout();
	std::cout << "\n";

		//	LargeInteger(string input, bool Check_value);  bool��Ӧ�Ƿ����ַ��淶
	LargeInteger CS2("2-022",false);
	CS2.PrintLargeInt_cout();
	std::cout << "\n";

	//	LargeInteger(const deque<int>&, bool, bool reverse = false);  ��deque��ʼ����bool��Ӧ���š�deque�Ƿ�Ϊ����
	std::deque<int> cs3;
	cs3.push_back(1);
	cs3.push_back(2);
	LargeInteger CS3(cs3, true);
	CS3.PrintLargeInt_cout();
	std::cout << "\n";

	//	LargeInteger();  ���ɳ�ʼ��Ϊ0�Ķ���
	LargeInteger CS4;
	CS4.PrintLargeInt_cout();
	std::cout << "\n";

	//	�����������
	LargeInteger a("98765432112345678998765432101234567890987654321123456789987654321123456789987654321");
	LargeInteger b("2147483647", true);
	LargeInteger c("-65536", false);
	LargeInteger d("310", false);
	LargeInteger e("-310", false);
	LargeInteger f("310");
	//	bool operator==(const LargeInteger & input) const;
	std::cout << (a == b) << " " << (d == f) << "\n";
	//	bool operator!=(const LargeInteger & input) const��
	std::cout << (d != f) << "\n";
	//LargeInteger operator+(const LargeInteger&) const;
	(b + c).PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator-(const LargeInteger&) const;
	(d - c).PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator-() const;
	(-e).PrintLargeInt_cout();
	//LargeInteger operator=(int);  ����������LargeInteger
	LargeInteger CS5;
	CS5 = 15;
	CS5.PrintLargeInt_cout();
	std::cout << "\n";

	//LargeInteger operator=(string);  ���ַ�������LargeInteger
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
	//�� += -= *= < >= <= ++ --

	//	��Ա������
	//	LargeInteger absolute() const;  ���ض���ľ���ֵ
	c.absolute().PrintLargeInt_cout();
	std::cout << "\n";

	//	void TakeAbsolute();  ʹ����ȡ����ֵ
	CS1.TakeAbsolute();
	CS1.PrintLargeInt_cout();
	//	LargeInteger UnsignedAdd(const LargeInteger & b)const;  �޷��żӷ�
	(b.UnsignedAdd(c)).PrintLargeInt_cout();
	std::cout << "\n";

	//	void PrintLargeInt()const;  ��cout�����������δ��׼������
	//	string ToString()const;  �����ַ����ʹ�������δ��׼������
	string str = a.ToString();
	std::cout << str << "\n";
	//	LargeInteger Multiple_AddRow(const LargeInteger&)const;  �˷�����һ��ʵ�֣�Ч�ʽϵ�
	(c.Multiple_AddRow(d)).PrintLargeInt_cout();
	std::cout << "\n";

	//	LargeInteger UnsignedDivision(const LargeInteger&)const;  �޷��ų���
	(b / d).PrintLargeInt_cout();
	std::cout << "\n";

	//	void Right_Digit_Operation(int carry_number = 0);  �ҷ�λ����
	d.Right_Digit_Operation();
	d.PrintLargeInt_cout();
	std::cout << "\n";

	//	void Left_Digit_Operation(int carry_number = 1);  ��λ����
	//	void Divide2_Algorithm();  ��Ը����ܵĳ��Զ���Ҫ��λ������2���������
	a.Divide2_Algorithm();
	a.PrintLargeInt_cout();
	std::cout << "\n";

	//	void Divide2_Digit();  ��λ����2
	b.Divide2_Digit();
	b.PrintLargeInt_cout();
	std::cout << "\n";

	//	void Divide2_Bit();  ��λ����2�������Ϸ��Ĵ���
	
	//	LargeInteger AddAssignment(const LargeInteger&);  �Ż��� +=
	b.AddAssignment(d);
	b.PrintLargeInt_cout();
	std::cout << "\n";

	//	bool IsZero()const;  ���ض����Ƿ�Ϊ0
	LargeInteger CSZero("000");
	LargeInteger CSOne("0015");
	std::cout << CSZero.IsZero() << "\n";
	//	void PopZero();  ȥ������0��Ҳ��ʹ�����׼��
	CSZero.PopZero();
	CSOne.PopZero();
	CSZero.PrintLargeInt_cout();
	std::cout << " ";
	CSOne.PrintLargeInt_cout();
	std::cout << "\n";

	//	void TenFold();  �൱�� *= 10
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