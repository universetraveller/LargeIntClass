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
	std::string ToString()const;  //没写小数部分的实现
private:
	int dot_pos_;  //可能溢出
	bool is_decimal_;  //小数用两个整数表示
	bool is_minus_;
	std::deque<int> large_number_;  //构造函数的结构默认最大位数为unsigned int的最大值
	static const int BASE_DECIMAL_ = 10000; //应该使用46340进制，但需要引入进位记录，太麻烦
};
