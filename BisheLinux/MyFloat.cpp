#include "MyFloat.h"
#include <iostream>
#include <sstream>
#include "Converter.h"


MyFloat::MyFloat()
{
}

/*
*	取下一个浮点数
*/
MyFloat* MyFloat::up()
{
	// 正
	if (this->bSign) {
		int man = (this->matntissa & 0x7fffff0000000000)>> (64 - mantissaSize);
		// 尾数全是1
		if (this->mantissa.all())
		{
			// 尾数首位置1
			//将bitset的每一位全部置为０
			this->mantissa.reset();
			//将尾数第一位置为1
			this->mantissa.set(0);
			// 指数+1
			expUp(true);
			//this->cExponent++;
		}
		else {
			// 尾数+1
			mantissaUp(true);
		}
	}
	// 负
	else {
		bitset<8> exp_min("00000001");
		//if (this->mantissa.count() == 1 && this->mantissa.test(22))
		if (this->mantissa.count() == 0)
		{
			// 尾数重置1
			this->mantissa.reset().flip();
			// 指数减1
			expUp(false);
		}
		else if (this->mantissa.count() == 1
			&& this->mantissa.test(0)
			&& this->cExponent == exp_min)
		{
			// 符号变为正
			this->bSign = true;
			// 尾数+1
			//mantissaUp(true);
		}
		else {
			// 尾数-1
			mantissaUp(false);
		}
	}
	return this;
}

void MyFloat::mantissaUp(bool sign)
{
	bitset<23> a = this->mantissa;
	bitset<23> b("00000000000000000000001");
	// +1
	if (sign) {
		bitset<23> s(a.to_ullong() + 1);
		this->mantissa = s;
	}
	// -1
	else {
		bitset<23> s(a.to_ullong() - 1);
		this->mantissa = s;
	}
}

void MyFloat::expUp(bool sign)
{
	bitset<8> a = this->cExponent;
	bitset<8> b("00000001");
	if (sign) // +1
	{
		bitset<8> s(a.to_ulong() + 1);
		this->cExponent = s;
	}
	else //-1
	{
		bitset<8> s(a.to_ulong() - 1);
		this->cExponent = s;
	}
}

bool MyFloat::equals(const MyFloat &other)
{
	return (this->bSign == other.bSign)
		&& (this->cExponent == other.cExponent)
		&& (this->mantissa == other.mantissa);
}

bool MyFloat::isFloatMax()
{
	return this->equals(FLOAT_MAX);
}


MyFloat::MyFloat(bool sign, bitset<8>& ex, bitset<23>& mantissa)
{
	this->bSign = sign;
	this->cExponent = ex;
	this->mantissa = mantissa;
}

std::string MyFloat::to_decimal()
{
	iRRAM::REAL real = GetFloat32(this->to_string());
	std::string res = iRRAM::swrite(real, 50);
	return res;
}

std::string MyFloat::to_string()
{
	std::string result;
	if (this->bSign)
	{
		result += "0";
	}
	else
	{
		result += "1";
	}
	result += this->cExponent.to_string();
	result += this->mantissa.to_string();
	return result;
}

std::string MyFloat::to_middle_value()
{
	iRRAM::REAL middle_value = GetFloat33(this->to_string());
	std::string middle_string = iRRAM::swrite(middle_value, 50);
	return middle_string;
}

bool MyFloat::getSign()
{
	return this->bSign;
}
