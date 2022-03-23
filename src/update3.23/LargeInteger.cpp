#include "LargeInteger.h"
#include <iostream>
#include "CheckChar.h"
#include <algorithm>
#include <iterator>

LargeInteger::LargeInteger(string input) {
	if (CheckChar(input)) {
		std::string::iterator input_begin = input.begin();
		std::string::iterator input_end = input.end();
		std::string::iterator input_counter = input_begin;
		int push_integer = 0;
		if (*input_begin == '-') {
			is_minus_ = true;  //设置符号
			input_counter++;
		}
		else{
			is_minus_ = false;
		}
		for (; input_counter < input_end; input_counter++) {
			push_integer = (*input_counter) - 48;  //根据ASCII码对应整数
			large_number_.push_front(push_integer);
		}
	}
	else{
		std::cerr << "Invalid number"<<std::endl;
	}
}
LargeInteger::LargeInteger(string input, bool Check_value) {
	if (Check_value == true) {
		if (CheckChar(input)) {
			std::string::iterator input_begin = input.begin();
			std::string::iterator input_end = input.end();
			std::string::iterator input_counter = input_begin;
			int push_integer = 0;
			if (*input_begin == '-') {
				is_minus_ = true;
				input_counter++;
			}
			else {
				is_minus_ = false;
			}
			for (; input_counter < input_end; input_counter++) {
				push_integer = (*input_counter) - 48;
				large_number_.push_front(push_integer);
			}
		}
		else {
			std::cerr << "Invalid number" << std::endl;
		}
	}
	else {
		std::string::iterator input_begin = input.begin();
		std::string::iterator input_end = input.end();
		std::string::iterator input_counter = input_begin;
		int push_integer = 0;
		if (*input_begin == '-') {
			is_minus_ = true;
			input_counter++;
		}
		else {
			is_minus_ = false;
		}
		for (; input_counter < input_end; input_counter++) {
			push_integer = (*input_counter) - 48;
			large_number_.push_front(push_integer);
		}
	}
}
LargeInteger::LargeInteger(const deque<int>& input, bool sign,bool reverse):is_minus_(sign) {
	if (!input.empty()) {
		if (reverse) {
			large_number_ = input;  //反向时使用deque自带的赋值
		}
		else {
			for (int i = 0; i < input.size(); i++) {
				large_number_.push_front(input[i]);
			}
		}
		//原来是large_number_ = input;底层改为反向后不能直接赋值了
	}
	else{
		large_number_.push_back(0);
	}
};
LargeInteger::LargeInteger(deque<int>&& input, bool sign):large_number_(input),is_minus_(sign) {

}
LargeInteger::LargeInteger() {
	is_minus_ = false;
	large_number_.push_back(0);
}
bool LargeInteger::operator==(const LargeInteger& input) const {
	if (is_minus_ != input.is_minus_) {
		return false;  //符号
	}
	if (this->large_number_.size() != input.large_number_.size()) {
		return false;  //位数
	}
	bool Check_Deque = std::equal(this->large_number_.begin(), this->large_number_.end(), input.large_number_.begin());
	if (!Check_Deque) {
		return false;  //每位检测
	}
	return true;
}
LargeInteger LargeInteger::operator+(const LargeInteger& right_value) const {
	std::deque<int> cache_result;
	bool cache_sign;
	int cache_number=0;
	int overflow_number=0;
	const int ZERO = 0;
	bool left_is_longer;
	const std::deque<int>::const_iterator left_begin = this->large_number_.begin(),
		left_end = this->large_number_.end(),
		right_begin = right_value.large_number_.begin(),
		right_end = right_value.large_number_.end();
	std::deque<int>::const_iterator main_value, sub_value;

	if (this->is_minus_ == right_value.is_minus_) {
		cache_sign = this->is_minus_;
	}
	else {
		//实现减法后返回减法值
		if (this->is_minus_) {
			return right_value - (*this).absolute();
		}
		else{
			return (*this) - right_value.absolute();
		}
	}
	if (this->large_number_.size() > right_value.large_number_.size()) {
		left_is_longer = true;//bool可代替mark的功能
		main_value = left_begin;
		sub_value = right_begin;
	}
	else{
		left_is_longer = false;
		main_value = right_begin;
		sub_value = left_begin;
	}
	if (left_is_longer) {
		for (; main_value < left_end; main_value++) {
			if (sub_value < right_end) {
				cache_number = *sub_value;
				sub_value++;
			}
			else{
				cache_number = ZERO;  //超过数长以0计
			}
			cache_number += *main_value;
			cache_number += overflow_number;
			if (cache_number >= 10) {
				cache_number -= 10;
				overflow_number = 1;  //进位处理
			}
			else{
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);  //最高位进位处理
		}
	}
	else{
		for (; main_value < right_end; main_value++) {
			if (sub_value < left_end) {
				cache_number = *sub_value;
				sub_value++;
			}
			else {
				cache_number = ZERO;
			}
			cache_number += *main_value;
			cache_number += overflow_number;
			if (cache_number >= 10) {
				cache_number -= 10;
				overflow_number = 1;
			}
			else {
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);
		}
	}
	return LargeInteger(std::move(cache_result),cache_sign);
}
LargeInteger LargeInteger::operator-() const{
	return LargeInteger(this->large_number_, !(this->is_minus_), true);
}
LargeInteger& LargeInteger::operator=(string input) {
	LargeInteger temp(input);
	*this = temp;
	return *this;
}
LargeInteger& LargeInteger::operator=(int input) {
	int cache_number = 0;
	this->large_number_.erase(this->large_number_.begin(),this->large_number_.end());
	if (input != 0) {
		if (input > 0) {
			this->is_minus_ = false;
		}
		else {
			this->is_minus_ = true;
			input *= -1;
		}
		for (; input > 0;) {
			cache_number = input % 10;
			this->large_number_.push_back(cache_number);
			input -= cache_number;
			input /= 10;
		}
	}
	else{
		this->large_number_.push_front(0);
	}
	return *this;
}
LargeInteger& LargeInteger::operator=(const LargeInteger& input) {
	this->is_minus_ = input.is_minus_;
	this->large_number_ = input.large_number_;
	return *this;
}
LargeInteger LargeInteger::absolute() const{
	return LargeInteger(this->large_number_, false, true);
}
void LargeInteger::TakeAbsolute() {
	is_minus_ = false;
}
LargeInteger LargeInteger::AddAssignment(const LargeInteger& right_value) {
	//Edit from the code of operator+
	//简化的+=运算
	std::deque<int> cache_result;
	bool cache_sign;
	int cache_number = 0;
	int overflow_number = 0;
	const int ZERO = 0;
	bool left_is_longer;
	const std::deque<int>::const_iterator left_begin = this->large_number_.begin(),
		left_end = this->large_number_.end(),
		right_begin = right_value.large_number_.begin(),
		right_end = right_value.large_number_.end();
	std::deque<int>::const_iterator main_value, sub_value;

	if (this->is_minus_ == right_value.is_minus_) {
		cache_sign = this->is_minus_;
	}
	else {
		//实现减法后返回减法值
		if (this->is_minus_) {
			return right_value - (*this).absolute();
		}
		else {
			return (*this) - right_value.absolute();
		}
	}
	if (this->large_number_.size() > right_value.large_number_.size()) {
		left_is_longer = true;//bool可代替mark的功能
		main_value = left_begin;
		sub_value = right_begin;
	}
	else {
		left_is_longer = false;
		main_value = right_begin;
		sub_value = left_begin;
	}
	if (left_is_longer) {
		for (; main_value < left_end; main_value++) {
			if (sub_value < right_end) {
				cache_number = *sub_value;
				sub_value++;
			}
			else {
				cache_number = ZERO;
			}
			cache_number += *main_value;
			cache_number += overflow_number;
			if (cache_number >= 10) {
				cache_number -= 10;
				overflow_number = 1;
			}
			else {
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);
		}
	}
	else {
		for (; main_value < right_end; main_value++) {
			if (sub_value < left_end) {
				cache_number = *sub_value;
				sub_value++;
			}
			else {
				cache_number = ZERO;
			}
			cache_number += *main_value;
			cache_number += overflow_number;
			if (cache_number >= 10) {
				cache_number -= 10;
				overflow_number = 1;
			}
			else {
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);
		}
	}
	this->large_number_ = std::move(cache_result);
	return *this;
}
LargeInteger LargeInteger::UnsignedAdd(const LargeInteger& b)const {
	std::deque<int> cache_result;
	int cache_number = 0;
	int overflow_number = 0;
	const int ZERO = 0;
	bool left_is_longer;
	const std::deque<int>::const_iterator left_begin = this->large_number_.begin(),
		left_end = this->large_number_.end(),
		right_begin = b.large_number_.begin(),
		right_end = b.large_number_.end();
	std::deque<int>::const_iterator main_value, sub_value;
	if (this->large_number_.size() > b.large_number_.size()) {
		left_is_longer = true;//bool可代替mark的功能
		main_value = left_begin;
		sub_value = right_begin;
	}
	else {
		left_is_longer = false;
		main_value = right_begin;
		sub_value = left_begin;
	}
	if (left_is_longer) {
		for (; main_value < left_end; main_value++) {
			if (sub_value < right_end) {
				cache_number = *sub_value;
				sub_value++;
			}
			else {
				cache_number = ZERO;
			}
			cache_number += *main_value;
			cache_number += overflow_number;
			if (cache_number >= 10) {
				cache_number -= 10;
				overflow_number = 1;
			}
			else {
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);
		}
	}
	else {
		for (; main_value < right_end; main_value++) {
			if (sub_value < left_end) {
				cache_number = *sub_value;
				sub_value++;
			}
			else {
				cache_number = ZERO;
			}
			cache_number += *main_value;
			cache_number += overflow_number;
			if (cache_number >= 10) {
				cache_number -= 10;
				overflow_number = 1;
			}
			else {
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);
		}
	}
	return LargeInteger(std::move(cache_result), false);
};
LargeInteger LargeInteger::operator-(const LargeInteger& right_value) const {
	std::deque<int> cache_result;
	bool cache_sign;
	int left_cache_number = 0;
	int rigth_cache_number = 0;
	int cache_number = 0;
	int borrow_number = 0;
	const int ZERO = 0;
	bool additional_sign;
	bool operation_check=true;  //检查是否进行下一次循环
	const std::deque<int>::const_iterator left_begin = this->large_number_.begin(),
		left_end = this->large_number_.end(),
		right_begin = right_value.large_number_.begin(),
		right_end = right_value.large_number_.end();
	std::deque<int>::const_iterator left_count=left_begin, right_count=right_begin;

	if (this->is_minus_ != right_value.is_minus_) {
		return LargeInteger(std::move(this->UnsignedAdd(right_value).large_number_), this->is_minus_);
	}
	additional_sign = this->is_minus_ && right_value.is_minus_;  //需要与最后的符号合并
	while (operation_check) {
		if (left_count < left_end) {
			left_cache_number = *left_count;
			left_count++;
		}
		else{
			left_cache_number = ZERO;
		}
		if (right_count < right_end) {
			rigth_cache_number = *right_count;
			right_count++;
		}
		else {
			rigth_cache_number = ZERO;
		}
		cache_number = left_cache_number - rigth_cache_number - borrow_number;
		if (cache_number < 0) {
			cache_number += 10;
			borrow_number = 1;
		}
		else{
			borrow_number = 0;
		}
		cache_result.push_back(cache_number);
		operation_check = (left_count < left_end) || (right_count < right_end);  //均到达终点则终止
	}
	cache_sign = (additional_sign && (!borrow_number)) || ((!additional_sign) && borrow_number);
	if (borrow_number == 1) {
		int borrow_number_mod = 0;  //小数减大数生成额外进位，需要取模
		for (int i = 0; i < cache_result.size(); i++) {
			if (cache_result[i]==0&&borrow_number_mod==0) {
				continue;  //特殊情况
			}
			else {
				cache_result[i] = 10 - borrow_number_mod - cache_result[i];  //各位分别取模，由右边开始，模数为10或9（借位原理）
				borrow_number_mod = 1;
			}
		}
		return LargeInteger(std::move(cache_result), cache_sign);
	}
	else {
		return LargeInteger(std::move(cache_result), cache_sign);
	}
}
LargeInteger LargeInteger::operator*(const LargeInteger& right_value) const {
	std::deque<int> cache_result;
	bool cache_sign;
	int overflow_number=0;
	int mark_left, mark_right;//作为下标
	int sub_mark_left=0, sub_mark_right=0;//因为C++不允许下标小于0而增加的标示符,可能增加内存
	int timer_left = 0, timer_right = 0;//为了初始化sub_mark引入的计步器，无奈之举，这三行显示了编写者水平的不足
	int cache_number = 0;
	if (this->is_minus_ == right_value.is_minus_) {
		cache_sign = false;//按乘法的符号原则
	}
	else{
		cache_sign = true;
	}
	/*
	注：以下实现中部分解释被注释，是因为那是原来的实现方法，优化后发现效果没有区别，于是注释掉
	*/
	for (;/* sub_mark_left < this->large_number_.size() || */ sub_mark_right< right_value.large_number_.size()/*按道理sub_mark_right应该写在前面好点*/;) {
		mark_left = sub_mark_left;//这种方法不可避免的多个赋值
		mark_right = sub_mark_right;
		cache_number = 0;
		while (sub_mark_left>-1&&sub_mark_right<right_value.large_number_.size() ){
			cache_number += (this->large_number_[mark_left])*(right_value.large_number_[mark_right]);//按竖式每一列运算，存入cache_number
			if (mark_left != 0) {
				mark_left--;
			}
			sub_mark_left--;
			mark_right++;
			sub_mark_right++;
		}
		cache_number += overflow_number;
		if (cache_number>= 10) {
			overflow_number = cache_number / 10;//进位处理
			cache_number %= 10;
		}
		else{
			overflow_number = 0;
		}
		cache_result.push_back(cache_number);
		/*if (timer_left == this->large_number_.size() - 1 && timer_right == right_value.large_number_.size() - 1) {
			break;//重点控制语句，跳出无限循环,因为最后下标总是比size小
		}*/
		if (timer_left < this->large_number_.size()-1) {
			timer_left++;
		}
		else if(timer_right<right_value.large_number_.size()/* - 1*/) {
			timer_right++;//最终总是以右值到达size结束
		}
		sub_mark_left = timer_left;
		sub_mark_right = timer_right;
	}
	if (overflow_number != 0) {
		cache_result.push_back(overflow_number);//最高进位处理
	}

	return LargeInteger(std::move(cache_result),cache_sign);
}
bool LargeInteger::operator>(const LargeInteger& right_value)const {
	if (this->IsZero() && right_value.IsZero()) {
		return false;
	}
	if (this->is_minus_ != right_value.is_minus_) {
		//这里需要修复0首位和正负0同时出现的bug，否则会出现错误结果
		if (this->is_minus_) {
			return false;
		}
		else{
			return true;
		}
	}
	else {
		//这里需要修复多个0同时出现及0首位的问题，因为为了减少运算需要先比较位数
		/*this->PopZero();
		right_value.PopZero();*/
		int left_size = this->large_number_.size();
		int right_size = right_value.large_number_.size();
		if (*this == right_value) {
			return false;
		}
		if (this->is_minus_) {
			if (left_size>right_size) {
				return false;
			}
			else if (left_size < right_size) {
				return true;
			}
			else {
				for (int i = left_size - 1, j = right_size - 1; i > -1; i--, j--) {
					if (this->large_number_[i] < right_value.large_number_[j]) {
						return true;
					}
					else if(this->large_number_[i]>right_value.large_number_[j]) {
						return false;
					}
				}
				return false;
			}
		}
		else{
			if (left_size > right_size) {
				return true;
			}
			else if (left_size < right_size) {
				return false;
			}
			else {
				for (int i = left_size - 1, j = right_size - 1; i > -1; i--, j--) {
					if (this->large_number_[i] > right_value.large_number_[j]) {
						return true;
					}
					else if (this->large_number_[i] < right_value.large_number_[j]) {
						return false;
					}
				}
				return false;
			}
		}
	}
}
LargeInteger LargeInteger::Multiple_AddRow(const LargeInteger& right_value)const {
	//乘法的另一种实现
	std::deque<int> cache_result;
	bool cache_sign;
	int overflow_number = 0;
	int cache_number = 0;
	cache_result.push_back(0);
	if (this->is_minus_ == right_value.is_minus_) {
		cache_sign = false;//按乘法的符号原则
	}
	else {
		cache_sign = true;
	}
	LargeInteger cache_Int(cache_result, false,true);
	cache_result.erase(cache_result.begin(), cache_result.end());//每次创建对象都清空cache
	for (int i = 0; i < right_value.large_number_.size(); i++) {
		for (int j = 0; j < this->large_number_.size(); j++) {
			cache_number = (right_value.large_number_[i]) * (this->large_number_[j]);
			cache_number += overflow_number;
			if (cache_number >= 10) {
				overflow_number = cache_number / 10;//进位控制
				cache_number %= 10;
			}
			else{
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		for (int k = i; k > 0; k--) {
			cache_result.push_front(0);//百位控制
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);//最高位控制
		}
		cache_Int += LargeInteger(cache_result, false, true);//该项效率比较低，因为创建了新对象，如果直接计算数组应该会快一点
															//考虑用UnsignedAdd优化，但cache_result是数组，仍需创建对象
		cache_result.erase(cache_result.begin(), cache_result.end());
		overflow_number = 0;//进入第二行前进位清零
	}
	cache_Int.is_minus_ = cache_sign;
	return cache_Int;
}
LargeInteger LargeInteger::UnsignedDivision(const LargeInteger& right_value)const {
	static const LargeInteger BASE_MULTIPLY("1");
	if (right_value.IsZero()) {
		std::cerr << "Invalid number";
		return LargeInteger("0");
	}
	if (right_value == BASE_MULTIPLY) {
		return *this;
	}
	/*if (right_value == -BASE_MULTIPLY) {
		return -(*this);
	}*/
	if (this->absolute() < right_value.absolute()) {
		return LargeInteger("0");
	}
	//上面3个条件语句检查是否可除（原来有4个）
	int first_number_left, first_number_right;  //数的第一个数
	int left_size, right_size, d_size;  //数长及数长差
	int ori_min_mark, ori_max_mark;
	left_size = this->large_number_.size();
	right_size = right_value.large_number_.size();
	d_size = left_size - right_size;
	LargeInteger min_mark, max_mark, mark;
	if (d_size > 0) {
		first_number_left = this->large_number_[left_size - 1];
		first_number_right = right_value.large_number_[right_size - 1];
		first_number_left *= 10;
		ori_min_mark = first_number_left / (first_number_right + 1);
		ori_max_mark = (first_number_left + 10) / first_number_right;
		ori_max_mark += 1;
		min_mark = ori_min_mark;
		max_mark = ori_max_mark;
		min_mark.TenFold(d_size-1);
		max_mark.TenFold(d_size - 1);
		mark = min_mark;
		mark.AddAssignment(max_mark);
		mark.Divide2_Algorithm();  //首次二分
		while ((mark + BASE_MULTIPLY) * right_value <= (*this) || (mark - BASE_MULTIPLY) * right_value >= (*this)) {
			if (mark * right_value > (*this)) {
				max_mark = mark;
			}
			else {
				min_mark = mark;
			}
			mark = min_mark;
			mark.AddAssignment(max_mark);
			mark.Divide2_Algorithm();  //二分法
		}
		if (mark * right_value > (*this)) {
			mark += (-BASE_MULTIPLY);
		}
	}
	else {
		//size相同时出现bug，针对这种情况编写
		min_mark = 0;
		max_mark = 9;
		mark = 4;
		while ((max_mark-min_mark)>BASE_MULTIPLY) {
			if (mark * right_value == (*this)) {
				return mark;  //数值补正，会增加一些运算
			}
			if (mark * right_value > (*this)) {
				max_mark = mark;
			}
			else{
				min_mark = mark;
			}
			mark = min_mark;
			mark.AddAssignment(max_mark);
			mark.Divide2_Bit();
		}
		return min_mark;
	}
	return mark;
}
void LargeInteger::Right_Digit_Operation(int carry_number) {
	//效果为使原来的数进位，默认进位0
	//LargeInt.R_D_O(2); 表现为在原数最后增加一位2
	this->PopZero();//使数变为标准型
	if (!(this->IsZero())) {
		this->large_number_.push_front(carry_number);
	}
	else{
		this->large_number_.push_front(carry_number);
		this->large_number_.pop_back();
	}
}
void LargeInteger::Left_Digit_Operation(int carry_number) {
	//右进位的对称形式
	this->PopZero();
	if (carry_number!=0) {
		this->large_number_.push_back(carry_number);
	}
}
void LargeInteger::Divide2_Algorithm() {
	//NUMBER=OTHER_NUMBER*10+LAST_NUMBER;
	//个位数执行时出现bug，因为pop结束后deque为空
	//不修改，防止增加运算量，该函数用于2位及以上数的除以二操作
	LargeInteger BASE_DIVIDE2("5");
	int Last_number = this->large_number_[0];
	Last_number /= 2;
	this->large_number_.pop_front();
	(*this) *= BASE_DIVIDE2;
	BASE_DIVIDE2.large_number_[0] = Last_number;
	this->AddAssignment(BASE_DIVIDE2);
}
void LargeInteger::Divide2_Algorithm_public() {
	try {
		if (this->large_number_.size() <= 1) {
			throw "error number";  //异常处理
		}
	}
	catch (const char* error_number) {
		std::cerr << error_number;
		this->Divide2_Bit();
		return;
	}
	LargeInteger BASE_DIVIDE2("5");
	int Last_number = this->large_number_[0];
	Last_number /= 2;
	this->large_number_.pop_front();
	(*this) *= BASE_DIVIDE2;
	BASE_DIVIDE2.large_number_[0] = Last_number;
	this->AddAssignment(BASE_DIVIDE2);
}
void LargeInteger::Divide2_Digit() {
	int cache_number=0;
	int overflow_number = 0;
	deque<int> cache_result;
	this->PopZero();
	for (int i = this->large_number_.size() - 1; i > -1; i--) {
		cache_number += this->large_number_[i];
		cache_result.push_front(cache_number / 2);  //高位的除法
		overflow_number = cache_number % 2;  //除不尽的借位
		cache_number = 10 * overflow_number;  //借位
	}
	this->large_number_ = cache_result;
	this->PopZero();
}
void LargeInteger::Divide2_Bit() {
	//争对D2_A的问题提供了个位数的除二运算
	if(this->large_number_.size()==1){(this->large_number_[0]) /= 2;}
	else{
		this->Divide2_Algorithm();
	}
}
LargeInteger LargeInteger::operator%(const LargeInteger& right_value)const {
	return (*this) - (*this / right_value) * right_value;//原始定义，效率较低，但比较少用
}
LargeInteger LargeInteger::operator/(const LargeInteger& right_value)const {
	LargeInteger cache_result = (this->absolute()).UnsignedDivision(right_value.absolute());//这一行决定了它比UnsignedDivision慢
	if (this->is_minus_ == right_value.is_minus_) {
		cache_result.is_minus_ = false;
	}
	else {
		cache_result.is_minus_ = true;
	}
	return cache_result;
}
std::ostream& operator<<(std::ostream& os, const LargeInteger& input) {
	os << input.ToString();
	return os;
}