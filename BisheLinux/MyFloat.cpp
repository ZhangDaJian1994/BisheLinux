#include "MyFloat.h"
#include <iostream>
#include <sstream>
#include "Converter.h"
#include "const.h"

unsigned char buffer[4] = { 0xff,0xff,0xff,0xff };
//MyFloat* FLOAT_MAX = new MyFloat(true, 127, buffer, MANTISSA_SIZE);
MyFloatPtr FLOAT_MAX = new MyFloat(true, 127, buffer, MANTISSA_SIZE);
MyFloatPtr FLOAT_MIN = new MyFloat(false, -126, buffer, MANTISSA_SIZE);

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
		if (countOne(this->ulMantissa) == MANTISSA_SIZE) {
			// 尾数首位置1
			setToOne(this->ulMantissa, 2);
			// 指数+1
			this->cExponent++;
		}
		else {
			// 尾数+1
			mantissaUp(true);
		}
	}
	// 负
	else {
		if (countOne(this->ulMantissa)==1 && (this->ulMantissa[0] >> 7) & 1 == 1) {
			// 尾数重置1
			setToOne(this->ulMantissa,1);
			// 指数减1
			this->cExponent--;
		}
		 else if (countOne(this->ulMantissa)  == 1
			&& (this->ulMantissa[2] >> 1) & 1 == 1
			&& this->cExponent == 1) {
			// 符号变为正
			this->bSign = true;
			// 尾数+1
			mantissaUp(true);
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
	// +1
	if (sign) {

	}
	// -1
	else {

	}
}

bool MyFloat::equals(MyFloat *other)
{
	return (this->bSign == other->bSign) 
		&& (this->cExponent == other->cExponent)
		&& (this->ulMantissa == other->ulMantissa)
		&& (this->mantissaSize == other->mantissaSize);
}

bool MyFloat::isFloatMax()
{
	return this->equals(FLOAT_MAX);
}

MyFloat MyFloat::setToOne(unsigned char *mantissa, int type)
{
	if (type == 1) {
		unsigned char one[4] = { 0xff,0xff,0xff,0xff };
		this->ulMantissa = one;
	}
	else if (type == 2) {
		unsigned char one[4] = { 0x80,0x00,0x00 };
		this->ulMantissa = one;
	}
	return MyFloat();
}

int MyFloat::countOne(unsigned char *mantissa)
{
	int count = 0;
	int index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 7; j >= 0; j--) {
			index++;
			if (index == MANTISSA_SIZE) {
				break;
			}
			if ((mantissa[i] >> j) & 1 == 1) {
				count++;
			}
		}
	}
	return count;
}


MyFloat::MyFloat(bool sign, char ex, unsigned char* mantissa, int size)
{
	this->bSign = sign;
	this->cExponent = ex;
	this->ulMantissa = mantissa;
	this->mantissaSize = size;
}

std::string MyFloat::to_decimal()
{
	float result = GetFloat32(this->to_string());
	std::ostringstream ss;
	ss << result;
	std::string s(ss.str());
	std::cout << s << std::endl;
	return s;
}

std::string MyFloat::to_string()
{
	char result[32];
	int index = 0;
	if (this->bSign) {
		result[index++] = '0';
	}
	else {
		result[index++] = '1';
	}
	std::cout << this->cExponent << std::endl;
	char ex = this->cExponent + 127;
	int temp;
	for (int i = 7; i >= 0; i--) {
		temp = (ex >> i) & 1;
		result[index++] = temp+'0';
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 7; j >= 0; j--) {
			if (index == 32) {
				break;
			}
			char temp = this->ulMantissa[i] >> j;
			result[index++] = (temp & 1) + '0';
		}
	}
	std::string s(&result[0], &result[32]);
	return s;
}


