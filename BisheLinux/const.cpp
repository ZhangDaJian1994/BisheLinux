#include <string>
#include "const.h"
 int MANTISSA_SIZE = 23;
 int EXP_MIN = -126;
 int EXP_MAX = 127;
 std::string FLOAT_CPP_PATH = "d:\\";
 std::string IRRAM_CPP_PATH = "d:\\";
std::string FLOAT_FILE_NAME = "floatcalc";
std::string IRRAM_FILE_NAME = "irramcalc";
 std::string CPP_SUFFIX = "CPP";
 std::string O_SUFFIX = "o";
 std::string EXE_SUFFIX = "EXE";
 std::string NAME_DELIMITER = ".";
 std::string PATH_DELIMITER = "\\";
 std::string IRRAM_LIB_PATH = "d:\\project\\irramlib\\include\\";

// 浮点计算程序 & irram 计算程序 exe名称
std::string floatExeName = FLOAT_FILE_NAME + NAME_DELIMITER + EXE_SUFFIX;
std::string irramExeName = IRRAM_FILE_NAME + NAME_DELIMITER + EXE_SUFFIX;

// 浮点计算程序 & irram 计算程序 cpp名称
std::string floatCppName = FLOAT_FILE_NAME + NAME_DELIMITER + CPP_SUFFIX;
std::string irramCppName = IRRAM_FILE_NAME + NAME_DELIMITER + CPP_SUFFIX;

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}