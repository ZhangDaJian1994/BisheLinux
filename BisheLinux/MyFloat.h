#pragma once

#include <string>


/*自定义浮点类型*/
class MyFloat{
private:
	bool bSign; // 符号位 1位

	char cExponent;	// 指数为 从-126到127 8位

	unsigned char *ulMantissa; // 尾数

	int mantissaSize;// 尾数 23位

public:
	MyFloat();
	MyFloat(bool sign, char ex, unsigned char *mantissa, int size);
	// 取下一个浮点数
	MyFloat* up();
	// 尾数+1
	void mantissaUp(bool sign);
	// 判断两个浮点数是否相等
	bool equals(MyFloat *other);
	// 判断是否为浮点数最大值
	bool isFloatMax();
	// set
	MyFloat setToOne(unsigned char *mantissa, int type);
	// 计算尾数中1的个数
	int countOne(unsigned char *mantissa);
	// 转换为十进制
	std::string to_decimal();
	// 转换为字符串
    std::string to_string();
};

typedef MyFloat* MyFloatPtr;
extern MyFloatPtr FLOAT_MAX;
extern MyFloatPtr FLOAT_MIN;