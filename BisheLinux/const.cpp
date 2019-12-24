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
std::string floatExeName = FLOAT_CPP_PATH + FLOAT_FILE_NAME + NAME_DELIMITER + EXE_SUFFIX;
std::string irramExeName = IRRAM_CPP_PATH + IRRAM_FILE_NAME + NAME_DELIMITER + EXE_SUFFIX;

// 浮点计算程序 & irram 计算程序 cpp名称
std::string floatCppName = FLOAT_CPP_PATH + FLOAT_FILE_NAME + NAME_DELIMITER + CPP_SUFFIX;
std::string irramCppName = IRRAM_CPP_PATH + IRRAM_FILE_NAME + NAME_DELIMITER + CPP_SUFFIX;
