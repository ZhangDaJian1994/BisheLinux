
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
#include "program3.h"
#include "generateIrram.h"
#include "const.h"
#include "iRRAM/lib.h"
#include "Converter.h"
#include <float.h>

using namespace iRRAM;

int iRRAM_calc(const int &arg)
{
	std::cout << "请输入方程：";
	std::string ins = "x*x";
	std::cin >> ins;
	/*int cyc = 6;
	std::cout << "请输入循环模式: ";*/
	//std::cin >> cyc;
	/*std::cout << "请输入N：";
	int Num;
	std::cin >> Num;*/
	//extern int percision;
	// init 
	int dim = getInstrutionVariableNumber(ins);
	//dimension = dim;
	initDataStruct(dim, ins);
	// 
	Result* result = new Result();
	result->dimension = dim;
	result->mid = new MiddleValue[2 * dim];
	//执行循环，计算误差
	cycle(dim, *result);
	// 打印优先队列
	std::cout << "begin print priority_queue!----" << std::endl;
	extern std::priority_queue<Result, std::vector<Result>, CompareError> pq;
	while (!pq.empty())
	{
		Result r = pq.top();
		writePqToFile(r);
		iRRAM::REAL item = pq.top().error;
		iRRAM::cout << iRRAM::setRwidth(100) << item << "\n";
		/*std::string item_string = iRRAM::swrite(item, 50);
		std::cout << item_string << std::endl;*/
		pq.pop();
	}
	std::cout << "end print priority_queue!----" << std::endl;
	// 将结果写入文件
	//writeFile(*result);
	return 0;
};

template int iRRAM::iRRAM_exec <int, int>(int(*) (const int &), const int &);

int main(int argc, char **argv) {
	iRRAM_initialize(argc, argv);
	int erg = iRRAM_exec(iRRAM_calc, 0);
	return 0;
}
