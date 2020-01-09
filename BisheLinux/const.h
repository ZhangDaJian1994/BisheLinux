#ifndef CONST_H
#define CONST_H
#include <vector>
extern int MANTISSA_SIZE;
extern int EXP_MIN;
extern int EXP_MAX;
extern std::string FLOAT_CPP_PATH;
extern std::string IRRAM_CPP_PATH;
extern std::string FLOAT_FILE_NAME;
extern std::string IRRAM_FILE_NAME;
extern std::string CPP_SUFFIX;
extern std::string O_SUFFIX;
extern std::string EXE_SUFFIX;
extern std::string NAME_DELIMITER;
extern std::string PATH_DELIMITER;
extern std::string IRRAM_LIB_PATH;

// 浮点计算程序 & irram 计算程序 exe名称
extern std::string floatExeName;
extern std::string irramExeName;

// 浮点计算程序 & irram 计算程序 cpp名称
extern std::string floatCppName;
extern std::string irramCppName;

extern std::string exec(const char* cmd);

extern std::vector<std::string> funcs;

extern void replaceAll(std::string& str, const std::string& from, const std::string& to);

extern bool isLetter(char&);
#endif // !CONST_H


