#include "LargeDecimal.h"


LargeDecimal::LargeDecimal(std::string input) { 
	static std::stringstream is;
	static int cache_number;
	static const int LENGTH = 4;
	static const int BEGIN = 0;
	unsigned int top_number_bit = input.size() / 4; //可能溢出，但减少代码量
	if (input[0] == '-') {
		is_minus_ = true;
		input.erase(BEGIN,1);
	}
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '.') {
			is_decimal_ = true;
			dot_pos_ = input.size() - i - 1;
			input.erase(i,1);
			break;
		}
	}
	is<<input.substr(BEGIN, top_number_bit);
	is >> cache_number;
	is.str("");
	is.clear();
	large_number_.push_front(cache_number);
	cache_number = BEGIN;
	input.erase(BEGIN, top_number_bit);
	for (; input.size() > BEGIN;) {
		is << input.substr(BEGIN, LENGTH);
		is >> cache_number;
		is.str("");
		is.clear();
		large_number_.push_front(cache_number);
		cache_number = BEGIN;
		input.erase(BEGIN, LENGTH);
	}
}
std::string LargeDecimal::ToString()const {
	std::ostringstream os;
	if (is_minus_) {
		os << "-";
	}
	for (int i = this->large_number_.size() - 1; i >= 0; i--) {
		os << this->large_number_[i];
	}
	return os.str();
}
