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
			is_minus_ = true;  //���÷���
			input_counter++;
		}
		else{
			is_minus_ = false;
		}
		for (; input_counter < input_end; input_counter++) {
			push_integer = (*input_counter) - 48;  //����ASCII���Ӧ����
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
			large_number_ = input;  //����ʱʹ��deque�Դ��ĸ�ֵ
		}
		else {
			for (int i = 0; i < input.size(); i++) {
				large_number_.push_front(input[i]);
			}
		}
		//ԭ����large_number_ = input;�ײ��Ϊ�������ֱ�Ӹ�ֵ��
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
		return false;  //����
	}
	if (this->large_number_.size() != input.large_number_.size()) {
		return false;  //λ��
	}
	bool Check_Deque = std::equal(this->large_number_.begin(), this->large_number_.end(), input.large_number_.begin());
	if (!Check_Deque) {
		return false;  //ÿλ���
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
		//ʵ�ּ����󷵻ؼ���ֵ
		if (this->is_minus_) {
			return right_value - (*this).absolute();
		}
		else{
			return (*this) - right_value.absolute();
		}
	}
	if (this->large_number_.size() > right_value.large_number_.size()) {
		left_is_longer = true;//bool�ɴ���mark�Ĺ���
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
				cache_number = ZERO;  //����������0��
			}
			cache_number += *main_value;
			cache_number += overflow_number;
			if (cache_number >= 10) {
				cache_number -= 10;
				overflow_number = 1;  //��λ����
			}
			else{
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);  //���λ��λ����
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
	//�򻯵�+=����
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
		//ʵ�ּ����󷵻ؼ���ֵ
		if (this->is_minus_) {
			return right_value - (*this).absolute();
		}
		else {
			return (*this) - right_value.absolute();
		}
	}
	if (this->large_number_.size() > right_value.large_number_.size()) {
		left_is_longer = true;//bool�ɴ���mark�Ĺ���
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
		left_is_longer = true;//bool�ɴ���mark�Ĺ���
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
	bool operation_check=true;  //����Ƿ������һ��ѭ��
	const std::deque<int>::const_iterator left_begin = this->large_number_.begin(),
		left_end = this->large_number_.end(),
		right_begin = right_value.large_number_.begin(),
		right_end = right_value.large_number_.end();
	std::deque<int>::const_iterator left_count=left_begin, right_count=right_begin;

	if (this->is_minus_ != right_value.is_minus_) {
		return LargeInteger(std::move(this->UnsignedAdd(right_value).large_number_), this->is_minus_);
	}
	additional_sign = this->is_minus_ && right_value.is_minus_;  //��Ҫ�����ķ��źϲ�
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
		operation_check = (left_count < left_end) || (right_count < right_end);  //�������յ�����ֹ
	}
	cache_sign = (additional_sign && (!borrow_number)) || ((!additional_sign) && borrow_number);
	if (borrow_number == 1) {
		int borrow_number_mod = 0;  //С�����������ɶ����λ����Ҫȡģ
		for (int i = 0; i < cache_result.size(); i++) {
			if (cache_result[i]==0&&borrow_number_mod==0) {
				continue;  //�������
			}
			else {
				cache_result[i] = 10 - borrow_number_mod - cache_result[i];  //��λ�ֱ�ȡģ�����ұ߿�ʼ��ģ��Ϊ10��9����λԭ��
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
	int mark_left, mark_right;//��Ϊ�±�
	int sub_mark_left=0, sub_mark_right=0;//��ΪC++�������±�С��0�����ӵı�ʾ��,���������ڴ�
	int timer_left = 0, timer_right = 0;//Ϊ�˳�ʼ��sub_mark����ļƲ���������֮�٣���������ʾ�˱�д��ˮƽ�Ĳ���
	int cache_number = 0;
	if (this->is_minus_ == right_value.is_minus_) {
		cache_sign = false;//���˷��ķ���ԭ��
	}
	else{
		cache_sign = true;
	}
	/*
	ע������ʵ���в��ֽ��ͱ�ע�ͣ�����Ϊ����ԭ����ʵ�ַ������Ż�����Ч��û����������ע�͵�
	*/
	for (;/* sub_mark_left < this->large_number_.size() || */ sub_mark_right< right_value.large_number_.size()/*������sub_mark_rightӦ��д��ǰ��õ�*/;) {
		mark_left = sub_mark_left;//���ַ������ɱ���Ķ����ֵ
		mark_right = sub_mark_right;
		cache_number = 0;
		while (sub_mark_left>-1&&sub_mark_right<right_value.large_number_.size() ){
			cache_number += (this->large_number_[mark_left])*(right_value.large_number_[mark_right]);//����ʽÿһ�����㣬����cache_number
			if (mark_left != 0) {
				mark_left--;
			}
			sub_mark_left--;
			mark_right++;
			sub_mark_right++;
		}
		cache_number += overflow_number;
		if (cache_number>= 10) {
			overflow_number = cache_number / 10;//��λ����
			cache_number %= 10;
		}
		else{
			overflow_number = 0;
		}
		cache_result.push_back(cache_number);
		/*if (timer_left == this->large_number_.size() - 1 && timer_right == right_value.large_number_.size() - 1) {
			break;//�ص������䣬��������ѭ��,��Ϊ����±����Ǳ�sizeС
		}*/
		if (timer_left < this->large_number_.size()-1) {
			timer_left++;
		}
		else if(timer_right<right_value.large_number_.size()/* - 1*/) {
			timer_right++;//������������ֵ����size����
		}
		sub_mark_left = timer_left;
		sub_mark_right = timer_right;
	}
	if (overflow_number != 0) {
		cache_result.push_back(overflow_number);//��߽�λ����
	}

	return LargeInteger(std::move(cache_result),cache_sign);
}
bool LargeInteger::operator>(const LargeInteger& right_value)const {
	if (this->IsZero() && right_value.IsZero()) {
		return false;
	}
	if (this->is_minus_ != right_value.is_minus_) {
		//������Ҫ�޸�0��λ������0ͬʱ���ֵ�bug���������ִ�����
		if (this->is_minus_) {
			return false;
		}
		else{
			return true;
		}
	}
	else {
		//������Ҫ�޸����0ͬʱ���ּ�0��λ�����⣬��ΪΪ�˼���������Ҫ�ȱȽ�λ��
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
	//�˷�����һ��ʵ��
	std::deque<int> cache_result;
	bool cache_sign;
	int overflow_number = 0;
	int cache_number = 0;
	cache_result.push_back(0);
	if (this->is_minus_ == right_value.is_minus_) {
		cache_sign = false;//���˷��ķ���ԭ��
	}
	else {
		cache_sign = true;
	}
	LargeInteger cache_Int(cache_result, false,true);
	cache_result.erase(cache_result.begin(), cache_result.end());//ÿ�δ����������cache
	for (int i = 0; i < right_value.large_number_.size(); i++) {
		for (int j = 0; j < this->large_number_.size(); j++) {
			cache_number = (right_value.large_number_[i]) * (this->large_number_[j]);
			cache_number += overflow_number;
			if (cache_number >= 10) {
				overflow_number = cache_number / 10;//��λ����
				cache_number %= 10;
			}
			else{
				overflow_number = 0;
			}
			cache_result.push_back(cache_number);
		}
		for (int k = i; k > 0; k--) {
			cache_result.push_front(0);//��λ����
		}
		if (overflow_number != 0) {
			cache_result.push_back(overflow_number);//���λ����
		}
		cache_Int += LargeInteger(cache_result, false, true);//����Ч�ʱȽϵͣ���Ϊ�������¶������ֱ�Ӽ�������Ӧ�û��һ��
															//������UnsignedAdd�Ż�����cache_result�����飬���贴������
		cache_result.erase(cache_result.begin(), cache_result.end());
		overflow_number = 0;//����ڶ���ǰ��λ����
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
	//����3������������Ƿ�ɳ���ԭ����4����
	int first_number_left, first_number_right;  //���ĵ�һ����
	int left_size, right_size, d_size;  //������������
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
		mark.Divide2_Algorithm();  //�״ζ���
		while ((mark + BASE_MULTIPLY) * right_value <= (*this) || (mark - BASE_MULTIPLY) * right_value >= (*this)) {
			if (mark * right_value > (*this)) {
				max_mark = mark;
			}
			else {
				min_mark = mark;
			}
			mark = min_mark;
			mark.AddAssignment(max_mark);
			mark.Divide2_Algorithm();  //���ַ�
		}
		if (mark * right_value > (*this)) {
			mark += (-BASE_MULTIPLY);
		}
	}
	else {
		//size��ͬʱ����bug��������������д
		min_mark = 0;
		max_mark = 9;
		mark = 4;
		while ((max_mark-min_mark)>BASE_MULTIPLY) {
			if (mark * right_value == (*this)) {
				return mark;  //��ֵ������������һЩ����
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
	//Ч��Ϊʹԭ��������λ��Ĭ�Ͻ�λ0
	//LargeInt.R_D_O(2); ����Ϊ��ԭ���������һλ2
	this->PopZero();//ʹ����Ϊ��׼��
	if (!(this->IsZero())) {
		this->large_number_.push_front(carry_number);
	}
	else{
		this->large_number_.push_front(carry_number);
		this->large_number_.pop_back();
	}
}
void LargeInteger::Left_Digit_Operation(int carry_number) {
	//�ҽ�λ�ĶԳ���ʽ
	this->PopZero();
	if (carry_number!=0) {
		this->large_number_.push_back(carry_number);
	}
}
void LargeInteger::Divide2_Algorithm() {
	//NUMBER=OTHER_NUMBER*10+LAST_NUMBER;
	//��λ��ִ��ʱ����bug����Ϊpop������dequeΪ��
	//���޸ģ���ֹ�������������ú�������2λ���������ĳ��Զ�����
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
			throw "error number";  //�쳣����
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
		cache_result.push_front(cache_number / 2);  //��λ�ĳ���
		overflow_number = cache_number % 2;  //�������Ľ�λ
		cache_number = 10 * overflow_number;  //��λ
	}
	this->large_number_ = cache_result;
	this->PopZero();
}
void LargeInteger::Divide2_Bit() {
	//����D2_A�������ṩ�˸�λ���ĳ�������
	if(this->large_number_.size()==1){(this->large_number_[0]) /= 2;}
	else{
		this->Divide2_Algorithm();
	}
}
LargeInteger LargeInteger::operator%(const LargeInteger& right_value)const {
	return (*this) - (*this / right_value) * right_value;//ԭʼ���壬Ч�ʽϵͣ����Ƚ�����
}
LargeInteger LargeInteger::operator/(const LargeInteger& right_value)const {
	LargeInteger cache_result = (this->absolute()).UnsignedDivision(right_value.absolute());//��һ�о���������UnsignedDivision��
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