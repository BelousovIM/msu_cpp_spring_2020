#include "functions.h"

BigInt::BigInt(const long long int& val)
	: size_(0)
	, sign_(val >= 0 ? 1 : -1)
{
	long long int val_ex = val * sign_;
	do {
		++size_;
		val_ex /= 10;
	} while (val_ex);
	data_ = new char[size_];
	val_ex = val * sign_;
	for (size_t i = 0; i < size_; ++i) {
		data_[i] = val_ex % 10;
		val_ex /= 10;
	}
}

BigInt::BigInt(const BigInt& copied)
	: sign_(copied.sign_)
	, size_(copied.size_)
{
	data_ = new char[copied.size_];
	for(size_t i = 0; i < size_; ++i)
	{
		data_[i] = copied.data_[i];
	}
}

BigInt::BigInt(char* data, char sign, size_t size)
	: data_(data)
	, sign_(sign)
	, size_(size)
{
}

BigInt::BigInt(BigInt&& B)
	: size_(B.size_)
	, sign_(B.sign_)
	, data_(B.data_)
{
	B.data_ = nullptr;
}

BigInt::~BigInt()
{
	size_ = 0;
	sign_ = 1;
	delete[] data_;
}

BigInt& BigInt::operator=(const BigInt& copied)
{
	if (this == &copied)
	{
		return *this;
	}
	char* ptr = new char[copied.size_];
	delete[] data_;
	data_ = ptr;
	size_ = copied.size_;
	sign_ = copied.sign_;
	for(size_t i = 0; i < size_; ++i)
	{
		data_[i] = copied.data_[i];
	}
	return *this;
}

BigInt& BigInt::operator=(BigInt&& B)
{
	if (this == &B)
	{
		return *this;
	}
	size_ = B.size_;
	sign_ = B.sign_;
	data_ = B.data_;
	B.data_ = nullptr;
	return *this;
}

bool operator==(const BigInt& left, const BigInt& right)
{
	if (&left == &right)
	{
		return true;
	}

	if (left.size_ != right.size_ or left.sign_ != right.sign_)
	{
		return false;
	}

	for(size_t i = 0; i<left.size_; ++i)
	{
		if (left.data_[i] != right.data_[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const BigInt& left, const BigInt& right)
{
	return !(left == right);
}

bool operator<=(const BigInt& left, const BigInt& right)
{
	if (left.sign_ != right.sign_)
	{
		return right.sign_ > 0 ? true : false;
	}
	if (left.size_ != right.size_)
	{
		if (left.size_ < right.size_)
		{
			return right.sign_ > 0 ? true : false;
		}
		else
		{
			return right.sign_ < 0 ? true : false;
		}
	}

	for (size_t i = right.size_ ; i > 0; --i)
	{
		if (left.data_[i-1] == right.data_[i-1])
		{
			continue;
		}
		else if(left.data_[i-1] < right.data_[i-1])
		{
			return right.sign_ > 0 ? true : false;
		}
		else
		{
			return right.sign_ < 0 ? true : false;
		}
			
	}
	return true;
}

bool operator<(const BigInt& left, const BigInt& right)
{
	return (left <= right) and (left != right);
}
bool operator>(const BigInt& left, const BigInt& right)
{
	return !(left <= right);
}
bool operator>=(const BigInt& left, const BigInt& right)
{
	return !(left < right);
}

BigInt BigIntAdd(const BigInt& left, const BigInt& right)
{
	size_t max = std::max(right.size_, left.size_);
	size_t min = std::min(right.size_, left.size_);
	size_t size;
	char* ptr = new char[max + 1];
	char ostatok = 0;
	for (size_t i = 0; i < min; ++i)
	{
		ostatok += left.data_[i] + right.data_[i];
		ptr[i] = ostatok % 10;
		ostatok /= 10;
	}
	char* tail = (left.size_ == max ? left.data_ : right.data_);
	for (size_t i = min; i < max; ++i)
	{
		ostatok += tail[i];
		ptr[i] = ostatok % 10;
		ostatok /= 10;
	}
	if (ostatok != 0)
	{
		ptr[max] = ostatok;
		size = max + 1;
		return BigInt(ptr, left.sign_, size);
	}
	size = max;
	return BigInt(ptr, left.sign_, size);
}

BigInt BigIntSub(const BigInt& left, const BigInt& right)
{
	size_t max = std::max(right.size_, left.size_);
	size_t min = std::min(right.size_, left.size_);
	size_t size;
	char* ptr = new char[max]; 
	char sign = left >= -right ? 1 : -1;
	char* left_ex = sign > 0 ? left.data_ : right.data_;
	char* right_ex = sign < 0 ? left.data_ : right.data_;
		
	int ostatok = 0;

	for (size_t i = 0; i < min; ++i) 
	{
		ptr[i] = (left_ex[i] - right_ex[i] - ostatok + 10) % 10;
		ostatok = (left_ex[i] - right_ex[i] - ostatok) < 0;
	}
	for (size_t i = min; i < max; ++i) 
	{
		ptr[i] = (left_ex[i] - ostatok + 10) % 10;
		ostatok = (left_ex[i] - ostatok) < 0;
	}
	for (size_t i = 0; i < max; ++i)
	{
		if (ptr[i] != 0)
		{
			size = i + 1;
		}
	}
	return BigInt(ptr, sign, size);
}
	
	
	
BigInt operator+(const BigInt& left, const BigInt& right)
{
	if (left.sign_ == right.sign_)
	{
		return BigIntAdd(left, right);
	}
	if (left.sign_ == 1)
	{
			return BigIntSub(left, right);
	}
	return BigIntSub(right, left);
}



BigInt operator-(const BigInt& left, const BigInt& right)
{
	return left + (-right);
}

BigInt BigInt::operator-() const
{
	
	if (*this == 0)
	{
		return *this;
	}
	BigInt answer(*this);
	answer.sign_ *= -1;
	return answer;
}

std::ostream& operator<<(std::ostream& out, const BigInt& val)
{
	if (val.sign_ < 0) {
		out << '-';
	}
	for (size_t i = val.size_ ; i > 0; --i)
	{
		out << char(val.data_[i-1] + '0');
	}
	return out;
}
