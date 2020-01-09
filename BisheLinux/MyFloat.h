#pragma once

#include <string>
#include "iRRAM/lib.h"
using namespace std;

extern int expSize = 8;
extern int mantissaSize = 23;
/*自定义浮点类型*/
class MyFloat {
private:
	bool bSign; // 符号位 1位

	// 指数为 从-126到127 8位
	uint32_t cExponent;
	uint64_t matntissa;

	// 尾数

public:
	// 拷贝构造函数
	void operator=(const MyFloat& otherFloat)
	{
		bSign = otherFloat.bSign;
		cExponent = otherFloat.cExponent;
		mantissa = otherFloat.mantissa;
	}
	MyFloat();
	MyFloat(bool sign, uint32_t exp, uint64_t mantissa);
	// 取下一个浮点数
	MyFloat* up();
	// 尾数+1
	void mantissaUp(bool sign);
	// 指数+1
	void expUp(bool sign);
	// 判断两个浮点数是否相等
	bool equals(const MyFloat &other);
	// 判断是否为浮点数最大值
	bool isFloatMax();
	// 转换为十进制
	std::string to_decimal();
	//iRRAM::REAL to_decimal();
	// 转换为字符串
	std::string to_string();
	// 转换为中间点值
	std::string to_middle_value();

	bool getSign();
};

typedef MyFloat* MyFloatPtr;
extern MyFloatPtr FLOAT_MAX_PTR;
extern MyFloatPtr FLOAT_MIN_PTR;
extern MyFloatPtr FLOAT_POS_MIN_PTR;
extern MyFloatPtr FLOAT_NEG_MAX_PTR;
extern MyFloatPtr FLOAT_NEG_SMALL_PTR; // -100
extern MyFloatPtr FLOAT_NEG_ONE_PTR; //-1
extern MyFloatPtr FLOAT_POS_ONE_PTR;	//1
extern MyFloatPtr FLOAT_NEG_ZERO_ONE_PTR; //-0.1
extern MyFloatPtr FLOAT_POS_ZERO_ONE_PTR; //0.1
extern const MyFloat FLOAT_MAX;
extern const MyFloat FLOAT_MIN;
extern const MyFloat FLOAT_POS_MIN;
extern const MyFloat FLOAT_NEG_MAX;
extern const MyFloat FLOAT_NEG_SMALL; 
extern const MyFloat FLOAT_NEG_ONE;
extern const MyFloat FLOAT_POS_ONE;
extern const MyFloat FLOAT_NEG_ZERO_ONE;
extern const MyFloat FLOAT_POS_ZERO_ONE;