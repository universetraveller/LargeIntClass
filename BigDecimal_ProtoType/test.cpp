#include "LargeDecimal.h"
#include <string>
#include <iostream>

int main() {
	LargeDecimal a("-111123554");
	std::cout << a.ToString();
	return 0;
}