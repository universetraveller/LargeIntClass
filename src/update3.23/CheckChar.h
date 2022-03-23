#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/*FillValidChar�����ڼ�������Ƿ�Ϸ���vector���*/
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

/*���ڼ�����ַ��Ƿ�Ϸ�����vector��CheckChar��ͬ*/
inline bool CheckSignChar(const std::string::iterator& first_iterator) {
	static std::vector<char> valid_sign;
	FillVaildChar(valid_sign);
	valid_sign.push_back('-');  //���Ӽ�鸺��
	for (int i = 0; i < valid_sign.size(); i++) {
		if (*first_iterator == valid_sign[i]) {
			return true;
		}
	}
	return false;
}

/*������ַ�������ַ��Ϸ��ԣ�����ԭ���Ǽ�⵽�Ϸ��ַ����˳������򷵻�false*/
inline bool CheckChar(std::string& input_string) {
	const std::string::iterator string_begin = input_string.begin();
	const std::string::iterator string_end = input_string.end();
	std::string::iterator counter = string_begin;  //������
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