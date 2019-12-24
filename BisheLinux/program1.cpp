#include <iostream>
#include <string>
#include "program1.h"

/*
	将原指令转为汇编指令，原指令的形式有机器码、汇编、字符串
	type ： 原指令的类型， 1 ： 机器码, 2 ： 汇编, 3：字符串
*/
std::string sourceInstructionToCompilation(std::string input, int type) {
	std::string result;
	switch (type)
	{
	case 1:
		// 机器码转汇编
		result = machineInstructionToCompilation(input);
		break;
	case 2:
		// 汇编转汇编
		result = input;
		break;
	case 3:
		// 字符串转汇编
		result = stringInstructionToCompilation(input);
		break;
	default:
		// 其他情况
		result = "";
		break;
	}
	return result;
}

/*
	机器指令转为汇编指令
*/
std::string machineInstructionToCompilation(std::string machineInstruction) {
	// TODO
	return machineInstruction;
}

/*
	字符指令转为汇编指令
*/
std::string stringInstructionToCompilation(std::string stringInstruction) {
	// TODO
	return stringInstruction;
}