#pragma once
#include <string>
#include <iostream>
#include <fstream>

/* 生成浮点计算CPP文件 */
void generateFloatCpp(std::string stringInstruction);

/* 生成实数计算CPP文件 */
void generateIrramCpp(std::string stringInstruction);

/* 编译Cpp文件 */
void compileCpp(std::string filePath);

/* 执行 */
void execCommnd(std::string commnd, std::string argv);