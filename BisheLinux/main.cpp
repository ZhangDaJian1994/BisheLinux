
#include "generateIrram.h"
#include "const.h"
#include "program3.h"

int main()
{
	std::string s = "y = x*x";
	/*
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
	*/
	Result *result = new Result();
	calcError(*result);
    return 0;
}