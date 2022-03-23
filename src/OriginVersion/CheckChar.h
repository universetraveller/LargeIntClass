#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/*FillValidChar给用于检测输入是否合法的vector填充*/
inline void FillVaildChar(std::vector<char>& input_vector) {
	input_vector.push_back('1');
	input_vector.push_back('2');
	input_vector.push_back('3');
	input_vector.push_back('4');
	input_vector.push_back('5');
	input_vector.push_back('6');
	input_vector.push_back('7');
	input_vector.push_back('8');
	input_vector.push_back('9');
	input_vector.push_back('0');
}

/*用于检测首字符是否合法，其vector与CheckChar不同*/
inline bool CheckSignChar(const std::string::iterator& first_iterator) {
	static std::vector<char> valid_sign;
	FillVaildChar(valid_sign);
	valid_sign.push_back('-');  //增加检查负号
	for (int i = 0; i < valid_sign.size(); i++) {
		if (*first_iterator == valid_sign[i]) {
			return true;
		}
	}
	return false;
}

/*检测首字符以外的字符合法性，基本原理是检测到合法字符便退出，否则返回false*/
inline bool CheckChar(std::string& input_string) {
	const std::string::iterator string_begin = input_string.begin();
	const std::string::iterator string_end = input_string.end();
	std::string::iterator counter = string_begin;  //计数器
	static std::vector<char> valid_char;
	bool check_value = false;
	FillVaildChar(valid_char);
	if (CheckSignChar(counter)) {
		counter++;
		for (; counter < string_end; counter++) {
			check_value = false;
			for (int i = 0; i < valid_char.size(); i++) {
				if (*counter == valid_char[i]) {
					check_value = true;
					break;
				}
			}
			if (!check_value) {
				std::cerr << "Invalid number"<<std::endl;
				return false;
			}
		}
		return true;
	}
	else{
		std::cerr << "Invalid number"<<std::endl;
		return false;
	}
}
