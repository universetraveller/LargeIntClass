
#include <deque>
#include <string>
#include <iterator>
#include <vector>
#include <iostream>

using std::deque;
using std::string;
//����Ŀ׷���ܶ���Ч��
//�Ľ�������10000����/65536����
//���ָĽ���Ҫ�ı�ײ����ݽṹ����dequeӦ�����λ��
//�Ľ�����ʹ��ָ��
//�������⣺
//(fixed)������λ����Ϊ0,��������bug���ӷ���������size()
//(fixed)�����"-0"��"000"֮�����ֵ,�ô���Դ���С�ڵıȽ����Ӱ��
// Divide2_Algorithm()���ڸ�λ������ṹ���ִ��󣬲�׼������
//3.8���£�����0����λ0����0���ṩ����PopZero()�޸�,�ô����ڶ��û������β����뺯���壬�û����ڵ���ǰʹ��
//��������϶࣬û����ɺ���
//��ι�����ĵط�����inline

/*
Data Structure��
	bool�������λ��
	deque�����λ������Ϊ����棬��˫�˵�dequeЧ�ʸ��ߣ�

Interfaces��
���캯����
	LargeInteger(string input);  ���ַ������죬Ĭ�ϻ����ַ��Ϸ���
	LargeInteger(string input, bool Check_value);  bool��Ӧ�Ƿ����ַ��淶
	LargeInteger(const deque<int>&, bool,bool reverse=false);  ��deque��ʼ����bool��Ӧ���š�deque�Ƿ�Ϊ����
	LargeInteger();  ���ɳ�ʼ��Ϊ0�Ķ���

�����������
	bool operator==(const LargeInteger& input) const;
	bool operator!=(const LargeInteger& input) const��
	LargeInteger operator+(const LargeInteger&) const;
	LargeInteger operator-(const LargeInteger&) const;
	LargeInteger operator-() const;
	LargeInteger operator=(int);  ����������LargeInteger
	LargeInteger operator=(string);  ���ַ�������LargeInteger
	LargeInteger operator/(const LargeInteger&)const;
	LargeInteger operator%(const LargeInteger&)const;
	LargeInteger operator*(const LargeInteger&)const;
	bool operator>(const LargeInteger&)const;
	��+= -= *= < >= <= ++ --

��Ա������
	LargeInteger absolute() const;  ���ض���ľ���ֵ
	void TakeAbsolute();  ʹ����ȡ����ֵ
	LargeInteger UnsignedAdd(const LargeInteger& b)const;  �޷��żӷ�
	void PrintLargeInt()const;  ��cout�����������δ��׼������
	string ToString()const;  �����ַ����ʹ�������δ��׼������
	LargeInteger Multiple_AddRow(const LargeInteger&)const;  �˷�����һ��ʵ�֣�Ч�ʽϵ�
	LargeInteger UnsignedDivision(const LargeInteger&)const;  �޷��ų���
	void Right_Digit_Operation(int carry_number=0);  �ҷ�λ����,����int��ֵ
	void Left_Digit_Operation(int carry_number=1);  ��λ���㣬����int��ֵ
	void Divide2_Algorithm();  ��Ը����ܵĳ��Զ���Ҫ��λ������2���������
	void Divide2_Digit();  ��λ����2
	void Divide2_Bit();  ��λ����2�������Ϸ��Ĵ���
	LargeInteger AddAssignment(const LargeInteger&);  �Ż���+=
	bool IsZero()const;  ���ض����Ƿ�Ϊ0
	void PopZero();  ȥ������0��Ҳ��ʹ�����׼��
	void TenFold();  �൱��*=10

����������
	void FillValidChar();
	bool CheckSignChar();
	bool CheckChar();
	���ڼ�������ַ��Ƿ���Ϲ淶
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
		*this = *this + input;/*ʹ����i=i+j�������׸�ʽ��Ч�ʱȽϵͣ�������ֱ�Ӹ���deque ���׷��Ч����Ҫдһ���µļӷ�*/
		return *this;		//������Ϊʹ�û��ǿ��Լ򻯴���ģ����+=�õý��پͲ��Ż���
	}
	LargeInteger operator-=(const LargeInteger& input) {
		*this = *this - input;//��+=һ��Ч�ʱȽϵ�
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
				return false;//����λ���Ƿ�ȫΪ0
			}
		}
		return true;
	};
	void PopZero() {
		if (this->IsZero()) {
			this->large_number_.erase(large_number_.begin(),large_number_.end());
			this->large_number_.push_back(0);//��ȥ1�����ϵ�0
			this->is_minus_ = false;//ʹ0Ϊ��0
		}
		else {
			for (int i = this->large_number_.size() - 1; i > -1; i--) {
				if (this->large_number_[i] != 0) {
					break;//��0�����
				}
				else {
					this->large_number_.pop_back();//ɾ����λ0
				}
			}
		}
	};
	void TenFold(int times = 1) {
		this->PopZero();
		if (!this->IsZero()) {
			for (; times > 0; times--) {
				this->large_number_.push_front(0);  //������ĩβ��0��ʮ�������൱�ڳ�10
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
	deque<int> large_number_;//һ��ʼ�����򴢴����ݣ�����iteratorû��begin-1�Ĳ������޸�Ϊ����
	bool is_minus_;  //����λ
};
/*
�˷���˵����
	������ʵ���Ѷȣ�ѡ����ʽ�����ԭ��ʵ�ֳ˷�����ʹ��FFT�Ⱦ�������ʧ���㷨��
	��ʽ���㿼������ʵ�֣����󵥸����˻�����ͼ�����ʱ��λ��ͣ����ַ���������������m*n+2m�����߸��Ӷȶ���O(n^2);
	�ٶȲ��ԣ�
	����10000��-202202*-404404�˷�����һ��
	��������غ�����ʱ1.826s
	ͨ�������������ӵĳ˷���ʱ4.801s
	�ôβ���Ч������3��
	�˷��ͼӷ�Ч�ʱȽϣ�
	0+=1234ִ��10000�μ�1234*10000
	�ӷ���ʱ146ms���˷���ʱ6ms
*/
/*
�˷���˵����
	��������ָ������ţ�ٵ�����ʵ�֣��������漰��BigDecimal��ʵ��
	����û�й���С���࣬����Ŀ��ʵ�ֳ˷�
*/
/*
������˵����
	��������3��ʵ����ʽ��
	1.n+1��������
		����nλ��ʱ������n+1λȥ��
	2.������λ
		����������ʱ��λ
		�ڳ������м���1һ��
	3.���ַ�
		�ӿ��ܵ����λ����һ�뿪ʼ�ԣ�ÿ��ȡһ��
		���ַ�����Ҫ��ʵ�ֳ���2�ĺ���
		Ҳ�������ڷ���1��2�м򻯼���

		����2�ĺ�����������ʵ�֣���λ���������λ���㷨
		ʵ�ֺ���Է��ַ����λ���㷨Ч�ʸ���
		�ڲ����Ǿ�����ʧ������£������㷨Ҳ�������ڳ���

	���ѡ����ַ�ʵ�ֳ�������ȱ�����漰������̫�࣬ѭ����ʱ�������ڼ�λ����Ч�ʺܸߣ�
	���������ʵ�ֽ�λ���������ﲻ��һһʵ����

	������ʵ����ȼӼ��˵ı���������������㷨��˼��
	���Զ�����ͬ��
*/
