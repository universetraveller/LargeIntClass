
#include <deque>
#include <string>
#include <iterator>
#include <vector>
#include <iostream>

using std::deque;
using std::string;
//该项目追求功能而非效率
//改进可以用10000进制/65536进制
//这种改进需要改变底层数据结构，即deque应储存多位数
//改进可以使用指针
//存在问题：
//(fixed)数的首位可以为0,可能引起bug，加法重载依靠size()
//(fixed)会出现"-0"和"000"之类的数值,该处会对大于小于的比较造成影响
// Divide2_Algorithm()用于个位数会因结构出现错误，不准备修正
//3.8更新：正负0及首位0，多0已提供函数PopZero()修复,该处出于对用户的信任不插入函数体，用户可在调用前使用
//代码冗余较多，没抽象成函数
//多次构造类的地方可以inline

/*
Data Structure：
	bool储存符号位；
	deque储存各位数，因为反向存，可双端的deque效率更高；

Interfaces：
构造函数：
	LargeInteger(string input);  用字符串构造，默认会检查字符合法性
	LargeInteger(string input, bool Check_value);  bool对应是否检查字符规范
	LargeInteger(const deque<int>&, bool,bool reverse=false);  用deque初始化，bool对应符号、deque是否为反向
	LargeInteger();  生成初始化为0的对象

重载运算符：
	bool operator==(const LargeInteger& input) const;
	bool operator!=(const LargeInteger& input) const；
	LargeInteger operator+(const LargeInteger&) const;
	LargeInteger operator-(const LargeInteger&) const;
	LargeInteger operator-() const;
	LargeInteger operator=(int);  用整数构造LargeInteger
	LargeInteger operator=(string);  用字符串构造LargeInteger
	LargeInteger operator/(const LargeInteger&)const;
	LargeInteger operator%(const LargeInteger&)const;
	LargeInteger operator*(const LargeInteger&)const;
	bool operator>(const LargeInteger&)const;
	及+= -= *= < >= <= ++ --

成员函数：
	LargeInteger absolute() const;  返回对象的绝对值
	void TakeAbsolute();  使对象取绝对值
	LargeInteger UnsignedAdd(const LargeInteger& b)const;  无符号加法
	void PrintLargeInt()const;  用cout输出大整数，未标准化对象
	string ToString()const;  返回字符串型大整数，未标准化对象
	LargeInteger Multiple_AddRow(const LargeInteger&)const;  乘法的另一种实现，效率较低
	LargeInteger UnsignedDivision(const LargeInteger&)const;  无符号除法
	void Right_Digit_Operation(int carry_number=0);  右方位运算,加入int数值
	void Left_Digit_Operation(int carry_number=1);  左方位运算，加入int数值
	void Divide2_Algorithm();  相对高性能的除以二，要求位数大于2，否则错误
	void Divide2_Digit();  按位除以2
	void Divide2_Bit();  个位除以2，补充上方的错误
	LargeInteger AddAssignment(const LargeInteger&);  优化的+=
	bool IsZero()const;  返回对象是否为0
	void PopZero();  去除多余0，也会使对象标准化
	void TenFold();  相当于*=10

其他函数：
	void FillValidChar();
	bool CheckSignChar();
	bool CheckChar();
	用于检查输入字符是否符合规范
*/


class LargeInteger {
public:
	LargeInteger(string input);
	LargeInteger(string input, bool Check_value);
	LargeInteger(const deque<int>&, bool,bool reverse=false);
	LargeInteger();
	void PrintLargeInt_cout() const{
		string LargeInt="";
		if (is_minus_) {
			LargeInt += "-";
		}
		for (int i = large_number_.size()-1; i >-1; i--) {
			LargeInt += (char)(large_number_[i]+48);
		}
		std::cout << LargeInt;
	}
	string ToString()const {
		string LargeInt = "";
		if (is_minus_) {
			LargeInt += "-";
		}
		for (int i = large_number_.size() - 1; i > -1; i--) {
			LargeInt += (char)(large_number_[i] + 48);
		}
		return LargeInt;
	}
	bool operator==(const LargeInteger& input) const;
	bool operator!=(const LargeInteger& input) const {
		if (*this == input) {
			return false;
		}
		return true;
	}
	LargeInteger operator+(const LargeInteger&) const;
	LargeInteger operator-(const LargeInteger&) const;
	LargeInteger operator-() const;
	LargeInteger operator=(int);
	LargeInteger operator=(string);
	LargeInteger absolute() const;
	void TakeAbsolute();
	LargeInteger UnsignedAdd(const LargeInteger& b)const;
	LargeInteger operator+=(const LargeInteger& input) {
		*this = *this + input;/*使用了i=i+j这种老套格式，效率比较低，但不能直接复制deque 如果追求效率需要写一个新的加法*/
		return *this;		//单单作为使用还是可以简化代码的，这个+=用得较少就不优化了
	}
	LargeInteger operator-=(const LargeInteger& input) {
		*this = *this - input;//和+=一样效率比较低
		return *this;
	}
	LargeInteger operator*(const LargeInteger&) const;
	LargeInteger operator*=(const LargeInteger& input) {
		*this = (*this) * input;
		return *this;
	}
	bool operator>(const LargeInteger&)const;
	bool operator>=(const LargeInteger& input)const {
		return (*this) > input || (*this) == input;
	}
	bool operator<(const LargeInteger& input)const {
		return !(*this >= input);
	}
	bool operator<=(const LargeInteger& input)const {
		return !(*this > input);
	}
	bool IsZero()const {
		for (int i = 0; i < this->large_number_.size(); i++) {
			if (this->large_number_[i] != 0) {
				return false;//检查各位数是否全为0
			}
		}
		return true;
	};
	void PopZero() {
		if (this->IsZero()) {
			this->large_number_.erase(large_number_.begin(),large_number_.end());
			this->large_number_.push_back(0);//消去1个以上的0
			this->is_minus_ = false;//使0为正0
		}
		else {
			for (int i = this->large_number_.size() - 1; i > -1; i--) {
				if (this->large_number_[i] != 0) {
					break;//非0则结束
				}
				else {
					this->large_number_.pop_back();//删掉首位0
				}
			}
		}
	};
	void TenFold(int times = 1) {
		this->PopZero();
		if (!this->IsZero()) {
			for (; times > 0; times--) {
				this->large_number_.push_front(0);  //数的最末尾加0，十进制下相当于乘10
			}
		}
	}
	LargeInteger Multiple_AddRow(const LargeInteger&)const;
	LargeInteger UnsignedDivision(const LargeInteger&)const;
	LargeInteger operator/(const LargeInteger&)const;
	LargeInteger operator%(const LargeInteger&)const;
	void Right_Digit_Operation(int carry_number=0);
	void Left_Digit_Operation(int carry_number=1);
	void Divide2_Algorithm();
	void Divide2_Digit();
	void Divide2_Bit();
	LargeInteger AddAssignment(const LargeInteger&);
	LargeInteger operator++() {
		static const LargeInteger BASE_INCREMENT("1");
		this->AddAssignment(BASE_INCREMENT);
		return *this;
	}
	LargeInteger operator--() {
		static const LargeInteger BASE_DECREMENT("-1");
		this->AddAssignment(BASE_DECREMENT);
		return *this;
	}
private:
	deque<int> large_number_;//一开始是正向储存数据，但是iterator没有begin-1的操作，修改为反向
	bool is_minus_;  //符号位
};
/*
乘法的说明：
	受限于实现难度，选择按竖式计算的原理实现乘法；不使用FFT等精度有损失的算法。
	竖式计算考虑两种实现，先求单个数乘积再求和及乘数时按位求和，两种方法迭代次数都是m*n+2m，两者复杂度都是O(n^2);
	速度测试：
	进行10000次-202202*-404404乘法测试一次
	运算符重载函数用时1.826s
	通过创建对象的相加的乘法用时4.801s
	该次测试效率相差近3倍
	乘法和加法效率比较：
	0+=1234执行10000次及1234*10000
	加法耗时146ms，乘法耗时6ms
*/
/*
乘方的说明：
	可以利用指数或者牛顿迭代法实现，但这里涉及了BigDecimal的实现
	限于没有构建小数类，该项目不实现乘方
*/
/*
除法的说明：
	除法考虑3种实现形式：
	1.n+1子列运算
		除以n位数时保持用n+1位去除
	2.持续进位
		当除数不够时进位
		在除法的中间与1一致
	3.二分法
		从可能的最大位数的一半开始试，每次取一半
		这种方法需要先实现除以2的函数
		也可以用在方法1和2中简化计算

		除以2的函数考虑两种实现：按位除及分离个位的算法
		实现后测试发现分离个位的算法效率更高
		在不考虑精度损失的情况下，这种算法也可以用于除法

	最后选择二分法实现除法，其缺点是涉及对象定义太多，循环耗时，但对于简单位除法效率很高，
	其可以用来实现进位除法，这里不就一一实现了

	除法的实现相比加减乘的暴力运算更能体现算法的思想
	除以二函数同理
*/
