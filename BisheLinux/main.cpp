
/*
#include "generateIrram.h"
#include "const.h"
#include "program3.h"

int main()
{
	std::string s = "y = x*x";
	//
	generateFloatCpp(s);
	compileCpp(floatCppName);
	std::string floatExec = "./" + FLOAT_FILE_NAME;
	std::string argv = "1.23456789";
	execCommnd(floatExec, argv);
	generateIrramCpp(s);
	compileCpp(irramCppName);
	std::string irramExec = "./" + IRRAM_FILE_NAME;
	execCommnd(irramExec, argv);
    printf("hello from BisheLinux!\n");
	//
	Result *result = new Result();
	calcError(*result);
    return 0;
}*/


/*
#include "generateIrram.h"
#include "const.h"
#include "program3.h"
#include "iRRAM/lib.h"
#include "iRRAM/core.h"

using namespace iRRAM;
extern "C" void iRRAM_initialize(int argc, char** argv);
template <class ARGUMENT, class RESULT>
RESULT iRRAM_exec(RESULT f(ARGUMENT), ARGUMENT);

int main(int argc, char **argv)
{
	iRRAM_initialize(argc, argv);
	std::string s = "y = x*x";
	Result *result = new Result();
	iRRAM_exec(calcError,*result );
	//calcError(*result);
	//system("pause");
	return 0;
}
*/
#include "generateIrram.h"
#include "const.h"
#include "program3.h"
#include "iRRAM/lib.h"

using namespace iRRAM;

int iRRAM_calc(const int &arg)
{
	//Result *result = new Result();
	//calcError(*result);
	std::cout << "请输入维度：";
	std::cin >> dimension;
	Result *result = new Result();
	result->dimension = dimension;
	result->mid = new MiddleValue[2 * dimension];
	// init 
	getInstrutionVariableNumber("123");
	initDataStruct(dimension);
	//执行循环，计算误差
	cycle(dimension, *result);
	// 将结果写入文件
	writeFile(resultList);
	return 0;
};

template int iRRAM::iRRAM_exec <int, int>(int(*) (const int &), const int &);

int main(int argc, char **argv) {
	iRRAM_initialize(argc, argv);
	int erg = iRRAM_exec(iRRAM_calc, 0);
	return 0;
}
