﻿#include <string>
#include <iostream>
#include <fstream>
#include "const.h"
#include "generateIrram.h"

void generateFloatCpp(std::string stringInstruction) {
	// TODO 生成浮点cpp
	std::ofstream ofile;               //定义输出文件
	std::cout << "float程序cpp名称： " + floatCppName << std::endl;
	ofile.open(floatCppName);     //作为输出文件打开
	ofile << "#include <iostream>                   " << std::endl;
	ofile << "#include <stdlib.h>                   " << std::endl;
	ofile << "#include <fstream>                    " << std::endl;
	ofile << "int main(int argc,char *argv[]) {     " << std::endl;
	ofile << "float res,x,y;                        " << std::endl;
	ofile << "if(argc == 2){                        " << std::endl;
	ofile << "x=atof(argv[1]);                      " << std::endl;
	ofile << "}                                     " << std::endl;
	ofile << "else if (argc == 3) {                 " << std::endl;
	ofile << "x=atof(argv[1]);                      " << std::endl;
	ofile << "y=atof(argv[2]);                      " << std::endl;
	ofile << "}                                     " << std::endl;
	ofile << "res=" + stringInstruction + ";"         << std::endl;
	//ofile << "std::ofstream ofile;                  " << std::endl;
	//ofile << "ofile.open(\"floatOut.txt\");   " << std::endl;
	//ofile << "ofile << res << \"\\n\";           " << std::endl;
	ofile << "std::cout << res;           " << std::endl;
	//ofile << "ofile.close();                        " << std::endl;
	ofile << "}                                     " << std::endl;
	ofile.close();
	/*
	std::cout << " 请输入参数" << std::endl;
	std::string argv;
	std::getline(std::cin, argv);
	std::string command = floatExeName + argv;
	system(command.data());*/
}

void generateIrramCpp(std::string stringInstruction) {
	// TODO 生成irram cpp
	std::ofstream ofile;               //定义输出文件
	std::cout << "irram 计算程序名称：" + irramCppName << std::endl;
	ofile.open(irramCppName);     //作为输出文件打开
	ofile << "#include \"iRRAM/lib.h\"                                                            " << std::endl;
	ofile << "#include \"iRRAM/core.h\"                       " << std::endl;
	ofile << "#include <string>                                                                 " << std::endl;
	ofile << "#include <fstream>                                                                 " << std::endl;
	ofile << "using namespace iRRAM;                                                            " << std::endl;
	ofile << "typedef char** CHARSTART;                                                            " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "int iRRAM_compute(const int &argc, const CHARSTART &argv) {                                        " << std::endl;
	ofile << "REAL res,x,y;                                                                     " << std::endl;
	ofile << "if (argc == 2){                                                                   " << std::endl;
	ofile << "	x = argv[1];                                                                    " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "else if (argc == 3){                                                              " << std::endl;
	ofile << "	x = argv[1];                                                                    " << std::endl;
	ofile << "	y = argv[2];                                                                    " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "res = " << stringInstruction << ";" << std::endl;
	//ofile << "                                                                                  " << std::endl;
	//ofile << "int deci_places;                                                                  " << std::endl;
	//ofile << "cout << \"please input deci_places: \" ;                                                      " << std::endl;
	//ofile << "cin >> deci_places;                                                               " << std::endl;
	//ofile << "std::string result = swrite(res,deci_places+8);                                        " << std::endl;
	//ofile << "std::ofstream ofile;                                                           " << std::endl;
	//ofile << "ofile.open(\"irramOut.txt\");                                                           " << std::endl;
	//ofile << "ofile << result << \"\\n\";                                                            " << std::endl;
	ofile << "cout << res;                                                            " << std::endl;
	//ofile << "ofile.close();                                                            " << std::endl;
	ofile << "return 0;                                                                         " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "template int iRRAM::iRRAM_exec <int,int,CHARSTART> (int (*) (const int &, const CHARSTART &),const int &, const CHARSTART &);   " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "int main(int argc,char **argv) {                                                  " << std::endl;
	ofile << "iRRAM_initialize(argc,argv);                                                      " << std::endl;
	ofile << "int a = iRRAM_exec(iRRAM_compute,argc,argv);                                              " << std::endl;
	ofile << "return 0;                                                                         " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile.close();
	//system("g++ d:\\testReal.cpp -c -o d:\\testReal.o -I d:\\project\\irramlib\\include\\");
	//system("g++ -o d:\\testReal.exe d:\\testReal.o d:\\project\\irramlib\\lib\\libiRRAM.a d:\\project\\irramlib\\lib\\libmpfr.a d:\\project\\irramlib\\lib\\libgmp.a");
	
	/*std::cout << " 请输入参数" << std::endl;
	std::string argv;
	std::getline(std::cin, argv);
	std::string command = irramExeName + argv;
	system(command.data());*/
}

void compileCpp(std::string filePath) {
	int end = filePath.find_last_of(".");
	std::string fileName = filePath.substr(0, end);
	/*// TODO 编译cpp文件
	std::string compileCommnd;
	std::string exeCommnd;
	//int begin = filePath.find_last_of("/\\");
	int end = filePath.find_last_of(".");
	
	std::string fileName = filePath.substr(0, end);
	std::string irramLibPath = "/root/iRRAM-master/installed/include";
	compileCommnd += "g++ " + filePath + " -c" + " -o "
		+ fileName + ".o" + " -I " + irramLibPath;;
	std::cout << compileCommnd << std::endl;
	execCommnd(compileCommnd);
	exeCommnd += "g++ -o " + fileName +" "
		+ fileName + ".o";
	std::cout << exeCommnd << std::endl;
	execCommnd(exeCommnd);
	//system("g++ d:\\testFloat.cpp -c -o d:\\testFloat.o -I d:\\project\\irramlib\\include\\");
	//system("g++ -o d:\\testFloat.exe d:\\testFloat.o");
	// TODO
	//std::string path = filePath.substr(0, begin);
	/*
	g++ -std=c++11 -g -O2 -I/root/iRRAM-master/installed/include
	-Xlinker -rpath
	-Xlinker /root/iRRAM-master/installed/lib  thread_test.cc
	-L/root/iRRAM-master/installed/lib -liRRAM -lmpfr -lgmp -lm -lpthread
	-o thread_test
	*/
	std::string testCommnd;
	testCommnd += "g++ -std=c++11 -g -O2 -I/root/iRRAM-master/installed/include -Xlinker -rpath -Xlinker /root/iRRAM-master/installed/lib  "
		+ fileName + ".CPP" + " -L/root/iRRAM-master/installed/lib -liRRAM -lmpfr -lgmp -lm -lpthread -o " + fileName;
	std::cout << testCommnd << std::endl;
	execCommnd(testCommnd);
}

std::string execCommnd(std::string commnd, std::string argv) {
	//system((commnd+" "+ argv).data());
	std::string result = exec((commnd + " " + argv).data());
	std::cout << result << std::endl;
	return result;
}

void execCommnd(std::string commnd)
{
	system(commnd.data());
}