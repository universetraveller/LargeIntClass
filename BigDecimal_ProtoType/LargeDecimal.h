#pragma once
#include <deque>
#include <string>
#include <sstream>

class LargeDecimal {
public:
	LargeDecimal() {
		dot_pos_ = 0;
		large_number_.push_back(0);
		is_minus_ = false;
		is_decimal_ = false;
	}
	LargeDecimal(std::string);
	std::string ToString()const;  //ûдС�����ֵ�ʵ��
private:
	int dot_pos_;  //�������
	bool is_decimal_;  //С��������������ʾ
	bool is_minus_;
	std::deque<int> large_number_;  //���캯���ĽṹĬ�����λ��Ϊunsigned int�����ֵ
	static const int BASE_DECIMAL_ = 10000; //Ӧ��ʹ��46340���ƣ�����Ҫ�����λ��¼��̫�鷳
};
