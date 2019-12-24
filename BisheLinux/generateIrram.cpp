#include <string>
#include <iostream>
#include <fstream>
#include "const.h"

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
	ofile << "std::ofstream ofile;                  " << std::endl;
	ofile << "ofile.open(\"d:\\\\floatOut.txt\");   " << std::endl;
	ofile << "ofile << res << \"\\n\";           " << std::endl;
	ofile << "ofile.close();                        " << std::endl;
	ofile << "}                                     " << std::endl;
	ofile.close();
	std::cout << " 请输入参数" << std::endl;
	std::string argv;
	std::getline(std::cin, argv);
	std::string command = floatExeName + argv;
	system(command.data());
}

void generateIrramCpp(std::string stringInstruction) {
	// TODO 生成irram cpp
	std::ofstream ofile;               //定义输出文件
	std::cout << "irram 计算程序名称：" + irramCppName << std::endl;
	ofile.open(irramCppName);     //作为输出文件打开
	ofile << "#include \"iRRAM/lib.h\"                                                            " << std::endl;
	ofile << "#include \"iRRAM/core.h\"                       " << std::endl;
	ofile << "#include <string>                                                                 " << std::endl;
	ofile << "#include<fstream>                                                                 " << std::endl;
	ofile << "using namespace iRRAM;                                                            " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "int iRRAM_compute(int argc, char **argv) {                                        " << std::endl;
	ofile << "REAL res,x,y;                                                                     " << std::endl;
	ofile << "if (argc == 2){                                                                   " << std::endl;
	ofile << "	x = argv[1];                                                                    " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "else if (argc == 3){                                                              " << std::endl;
	ofile << "	x = argv[1];                                                                    " << std::endl;
	ofile << "	y = argv[2];                                                                    " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "res = " << stringInstruction << ";" << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "int deci_places;                                                                  " << std::endl;
	ofile << "cout << \"please input deci_places: \" ;                                                      " << std::endl;
	ofile << "cin >> deci_places;                                                               " << std::endl;
	ofile << "string result = swrite(res,deci_places+8);                                        " << std::endl;
	ofile << "std::ofstream ofile;                                                           " << std::endl;
	ofile << "ofile.open(\"d:\\\\realOut.txt\");                                                           " << std::endl;
	ofile << "ofile << result << \"\\n\";                                                            " << std::endl;
	ofile << "ofile.close();                                                            " << std::endl;
	ofile << "return 0;                                                                         " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "template int iRRAM_exec <int,char **,int> (int (*) (int,char **),int, char **);   " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "int main(int argc,char **argv) {                                                  " << std::endl;
	ofile << "iRRAM_initialize(argc,argv);                                                      " << std::endl;
	ofile << "iRRAM_exec(iRRAM_compute,argc,argv);                                              " << std::endl;
	ofile << "return 0;                                                                         " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile.close();
	//system("g++ d:\\testReal.cpp -c -o d:\\testReal.o -I d:\\project\\irramlib\\include\\");
	//system("g++ -o d:\\testReal.exe d:\\testReal.o d:\\project\\irramlib\\lib\\libiRRAM.a d:\\project\\irramlib\\lib\\libmpfr.a d:\\project\\irramlib\\lib\\libgmp.a");
	std::cout << " 请输入参数" << std::endl;
	std::string argv;
	std::getline(std::cin, argv);
	std::string command = irramExeName + argv;
	system(command.data());
}

void compileCpp(std::string filePath) {
	// TODO 编译cpp文件
	std::string compileCommnd;
	std::string execCommnd;
	int begin = filePath.find_last_of("/\\");
	int end = filePath.find_last_of(".cpp");
	std::string path = filePath.substr(0, begin);
	std::string fileName = filePath.substr(begin, end);
	std::string irramLibPath = "d:\\project\\irramlib\\include\\";
	compileCommnd += "g++ " + filePath + " -c" + " -o " 
		+ path +"\\"+ fileName + ".o" + " -I " + irramLibPath;
	execCommnd += "g++ -o " + path + "\\" + fileName + ".exe "
		+ path + "\\" + fileName + ".o";
	//system("g++ d:\\testFloat.cpp -c -o d:\\testFloat.o -I d:\\project\\irramlib\\include\\");
	//system("g++ -o d:\\testFloat.exe d:\\testFloat.o");
	// TODO
}

void execCommnd(std::string commnd, std::string argv) {
	system((commnd+" "+ argv).data());
}