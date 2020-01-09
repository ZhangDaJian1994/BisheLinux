#include <iomanip>
#include "program3.h"
#include "Converter.h"

// 优先队列的定义
std::priority_queue<Result, std::vector<Result>, CompareError> pq;

// 默认精度50
int percision = 100;

/*获取指令的元数，即对应的维度值*/
int getInstrutionVariableNumber(std::string inputInstruction) {
	std::vector<std::string>::iterator iter;
	for (iter = funcs.begin(); iter != funcs.end(); iter++)
	{
		replaceAll(inputInstruction, (*iter), "");
	}
	int count = 0;
	for (int i = 0; i < inputInstruction.length(); i++)
	{
		char curChar = inputInstruction[i];
		if (isLetter(curChar) && iVarSet.find(curChar) == iVarSet.end())
		{
			iVarSet.insert(curChar);
			count++;
		}
	}
	iVarSet.clear();
	std::cout << "自变量有-" << count << "-个" << std::endl;
	return count;
}

void initDataStruct(int n, std::string instr) {
	
	dimension = n;
	instruction = instr;
	//cycleModel = model;
	//num = Num;
	//// 定义长度为n的数组，存储每个维度当前遍历的浮点值
	//arrNLoop = new MyFloat[dimension];
	//// 将数组的值初始化为浮点数最小值
	//init(arrNLoop);

}

/* 将数组的值初始化为浮点数最小值 */
void init(MyFloatPtr &arrNLoop)
{
	for (int i = 0; i < dimension; i++) {
		arrNLoop[i] = FLOAT_MIN;
	}
	preResult = new Result();
}

void init(MyFloatPtr arrNLoop, int index) {
	// 下标index 之前的数组初始化为浮点数最小值
	for (int i = 0; i <= index; i++) {
		arrNLoop[i] = FLOAT_MIN;
	}
	int newIndex = index+1;
	while (newIndex < dimension) {
		if (newIndex == dimension - 1 && arrNLoop[newIndex].isFloatMax()) {
			// 循环结束
			//loopOver = true;
		}
		else if(arrNLoop[newIndex].isFloatMax()){
			arrNLoop[newIndex] = FLOAT_MIN;
		}
		else {
			arrNLoop[newIndex] = *arrNLoop[newIndex].up();
			break;
		}
		newIndex++;
	}
}
/* 递归动态生成N重循环 */
void cycle(int localDim, Result& result)
{
	MyFloatPtr begin = FLOAT_MIN_PTR;
	MyFloatPtr end = FLOAT_MAX_PTR;
	/*switch (cycleModel)
	{
	case 1:
		begin = FLOAT_MIN_PTR;
		break;
	case 2: 
		begin = FLOAT_POS_MIN_PTR;
		break;
	case 3:
		begin = FLOAT_NEG_MAX_PTR;
		break;
	case 4:
		begin = FLOAT_NEG_SMALL_PTR;
		break;
	case 5:
		begin = FLOAT_NEG_ONE_PTR;
		end = FLOAT_POS_ONE_PTR;
		break;
	case 6:
		begin = FLOAT_NEG_ZERO_ONE_PTR;
		end = FLOAT_POS_ZERO_ONE_PTR;
		break;
	default:
		break;
	}*/
	std::cout << begin->to_string() << std::endl;
	MyFloat last = *begin;
	for (; !begin->equals(*end); )
	{
		struct MiddleValue leftMiddleVal;
		struct MiddleValue rightMiddleVal;
		// 计算左中间点
		if ((*begin).equals(FLOAT_MIN))
		{
			leftMiddleVal.value = *begin;
			leftMiddleVal.direct = false;
			rightMiddleVal.value = *begin;
			rightMiddleVal.direct = true;
			begin = begin->up();
		}
		else
		{
			//正
			if (begin->getSign())
			{
				//std::cout << "last: " << last.to_string() << std::endl;
				leftMiddleVal.value = last;
				leftMiddleVal.direct = true;
				iRRAM::REAL leftMid_real = GetFloat33(leftMiddleVal.value.to_string());
				std::string leftMid = iRRAM::swrite(leftMid_real, 50);
				//std::cout << "leftMid---> " + leftMid << std::endl;
				rightMiddleVal.value = *begin;
				rightMiddleVal.direct = true;
				iRRAM::REAL rightMid_real = GetFloat33(rightMiddleVal.value.to_string());
				std::string rightMid = iRRAM::swrite(rightMid_real, 50);
				//std::cout << "rightMid---> " + rightMid << std::endl;
				begin = begin->up();
			}
			// 负
			else
			{
				leftMiddleVal.value = *begin;
				leftMiddleVal.direct = true;
				//std::cout << "leftFloat---> " + begin->to_string() << std::endl;
				//iRRAM::REAL leftMid_real = GetFloat33(leftMiddleVal.value.to_string());
				//std::string leftMid = iRRAM::swrite(leftMid_real, 50);
				//std::cout << "leftMid---> " + leftMid << std::endl;
				rightMiddleVal.value = *(begin->up());
				rightMiddleVal.direct = true;
				/*std::cout << "rightFloat---> " + end->to_string() << std::endl; 
				iRRAM::REAL rightMid_real = GetFloat33(rightMiddleVal.value.to_string());
				std::string rightMid = iRRAM::swrite(rightMid_real, 50);
				std::cout << "rightMid---> " + rightMid << std::endl;*/
			}
			
		}
		if (localDim == 1)
		{
			result.mid[2 * (dimension - 1)] = leftMiddleVal;
			result.mid[2 * (dimension - 1) + 1] = rightMiddleVal;
			// 计算误差
			calcError(result);

			// TODO 如何合并不同维度的误差
			/*
			if (result.error == preResult->error)	// 误差一致，合并
			{
				// 左值更新，右值不变
				result.mid[2 * (dimension - 1)] = preResult->mid[2 * (dimension - 1)];
				// 删除集合中的preResult
				resultList.pop_back();
			}*/
			// (合并后的result)加入结果集
			Result *newResult = new Result();
			*newResult = result;
			//resultList.push_back(*newResult);
			// 区间-误差 写入文件
			writeToFile(result);
			// 区间-方程 写入文件
			std::string equat = errorToEquation(result);
			writeToFile(result, equat);
			// add to priority_queue
			addToPriorityQueue(pq, *newResult);
			// 赋值新的preResult
			preResult = newResult;
			last = *begin;
		}
		else
		{
			int curDim = dimension - localDim;
			result.mid[2 * curDim] = leftMiddleVal;
			result.mid[2 * curDim + 1] = rightMiddleVal;
			// 维度变化时，重置preResult
			preResult = new Result();
			// 递归
			cycle(localDim - 1, result);
		}
	}
}
/*
// TODO 考虑通过递归实现动态N重循环
void calc(std::string inputInstruction) {
	//int n = getInstrutionVariableNumber(inputInstruction);
	//initDataStruct(n);  
	// 如果循环数组最后一位已经为浮点数最大值，则退出递归
	if (arrNLoop[dimension-1].isFloatMax()) {
		return;
	}
	for (int currentDim = 0; currentDim < dimension; ) {
		// 遍历n维
		MyFloat begin = arrNLoop[currentDim];
		for (; !begin.isFloatMax(); begin = *begin.up()) 
		{
			Result result;
			result.mid = new MiddleValue[2 * dimension];
			int index = 0;
			// 将每一个维度的中间点值写入Result
			while (index < dimension)
			{
				struct MiddleValue leftMiddleVal;
				leftMiddleVal.value = arrNLoop[index];
				leftMiddleVal.direct = false;
				// 右中间点为【下一浮点数，左】
				struct MiddleValue rightMiddleVal;
				rightMiddleVal.value = *arrNLoop[index].up();
				rightMiddleVal.direct = false;
				int left = index, right = left + 1;
				result.mid[left] = leftMiddleVal;
				result.mid[right] = rightMiddleVal;
				index++;
			}
			// 调用程序算出误差
			if (fileExist("xx") && fileExist("xx")) {
				// TODO 调用float程序算出浮点结果
				// TODO 调用real程序算出实数结果
				// TODO 计算误差
				REAL error = "1";
				result.error = error;
			}
			else {
				// 生成计算程序，再计算误差
			}
			// 加入集合
			resultList.push_back(result);
		}

		// 优化-区间合并
		//intervalMerge(resList_float);

		// TODO 结果写入文件
		writeFile(resultList);
		//重新初始化循环数组
		if (arrNLoop[currentDim + 1].isFloatMax()) {
			//arrNLoop[currentDim + 1] = *FLOAT_MIN;
			init(arrNLoop, currentDim + 1);
			if (loopOver) break;
		}
		else {
			arrNLoop[currentDim] = *FLOAT_MIN;
			arrNLoop[currentDim+1] = *arrNLoop[currentDim + 1].up();
		}
		//init(arrNLoop, currentDim + 1, arrNLoop[currentDim + 1].up());
		// 递归
		//return calc(inputInstruction);
}
	}*/
bool isFloatMax(MyFloat f) {
	return f.isFloatMax();
}

bool fileExist(std::string filePath) {
	struct stat buffer;
	return (stat(filePath.c_str(), &buffer)) == 0;
}
// 合并区间，如果误差值大小一致，则可以合并
void intervalMerge(std::list<Result>& resultList) {
	int size = resultList.size();
	//REAL* errorList = resultList.error;
	for (int i = 0; i < size-1; i++) {
		// 误差一致，可以合并
		// TODO 怎么合并
	}
}


/* 结果列表写入文件 */
void writeFile(std::list<Result>& resultList)
{
	FILE* fp = fopen("result.txt", "w");
	if (fp) {
		std::list<Result>::iterator iter = resultList.begin();
		for (; iter != resultList.end(); iter++) {
			// 输出N维坐标区间
			fprintf(fp, "{");
			for (int i = 0; i < dimension; i++) {
				fprintf(fp, "[%s,", (*iter).mid[2 * i].value);
				fprintf(fp, "%s],", (*iter).mid[2 * i+1].value);
			}
			fprintf(fp, "}");
			// 区间和误差之间用 ： 分割
			fprintf(fp, ":");
			// 输出误差
			//fprintf(fp, "%s\n", iRRAM::swrite((*iter).error).c_str());
		}
	}
	else {
		std::cout << "result.txt 打开失败！ 程序异常退出！！！" << std::endl;
		exit(1);
	}
	fclose(fp);
}

/* 计算误差 */
void calcError(Result& result)
{
	//std::cout << "float计算程序文件名: " + floatCppName << std::endl;
	//std::cout << "irram计算程序文件名: " + irramCppName << std::endl;
	if (fileExist(FLOAT_FILE_NAME) && fileExist(IRRAM_FILE_NAME)) {
		// TODO 调用float程序算出浮点结果
		std::string floatExec = "./" + FLOAT_FILE_NAME;
		//std::string argv = "1.23456789";
		std::string argv = result.mid[0].value.to_decimal();

		//std::string argv = iRRAM::swrite(result.mid[0].value.to_decimal(), 50);
		std::cout << "argv: " << argv << std::endl;
		std::string floatRes = execCommnd(floatExec, argv);
		// TODO 调用real程序算出实数结果
		std::string irramExec = "./" + IRRAM_FILE_NAME;
		std::string irramRes = execCommnd(irramExec, argv);
		std::cout << "irramRes:" << irramRes << std::endl;
		// TODO 计算误差 
		iRRAM::REAL err = iRRAM::REAL(irramRes) - iRRAM::REAL(floatRes);
		result.error = err;
		iRRAM::cout <<  "error:" << iRRAM::setRwidth(100) << err << "\n";
	}
	else {
		// TODO 生成计算程序，再计算误差
		//std::string instruction = "y=x/3";
		generateFloatCpp(instruction);
		generateIrramCpp(instruction);
		compileCpp(floatCppName);
		compileCpp(irramCppName);
		calcError(result);
	}
}

/* 结果写入文件 */
void writeToFile(Result &result)
{
	FILE* fp = fopen("result.txt", "a+");
	if (fp != NULL) {
		// 输出N维坐标区间
		fprintf(fp, "{");
		for (int i = 0; i < dimension; i++) {
			fprintf(fp, "[%s,", result.mid[2 * i].value.to_middle_value().c_str());
			fprintf(fp, "%s", result.mid[2 * i + 1].value.to_middle_value().c_str());
			if (i == dimension - 1)	fprintf(fp, "]");
			else fprintf(fp, "],");
		}
		fprintf(fp, "}");
		// 区间和误差之间用 ： 分割
		fprintf(fp, ":");
		// 输出误差
		fprintf(fp, "%s\r\n", iRRAM::swrite(result.error, 100).c_str());
		fclose(fp);
	}
	else {
		std::cout << "result.txt 打开失败！ 程序异常退出！！！" << std::endl;
		exit(1);
	}
}

void writeToFile(Result &result, std::string& equation)
{
	FILE* fp = fopen("equation.txt", "a+");
	if (fp != NULL) {
		fprintf(fp, "{");
		for (int i = 0; i < dimension; i++) {
			fprintf(fp, "[%s,", result.mid[2 * i].value.to_middle_value().c_str());
			fprintf(fp, "%s", result.mid[2 * i + 1].value.to_middle_value().c_str());
			if (i == dimension - 1)	fprintf(fp, "]");
			else fprintf(fp, "],");
		}
		fprintf(fp, "}");
		// 区间和误差之间用 ： 分割
		fprintf(fp, ":");
		fprintf(fp, "%s\r\n", equation.c_str());
		fclose(fp);
	}
	else {
		std::cout << "equation.txt 打开失败！ 程序异常退出！！！" << std::endl;
		exit(1);
	}
}

void writePqToFile(Result& result)
{
	FILE* fp = fopen("pq.txt", "a+");
	if (fp != NULL) {
		// 输出N维坐标区间
		fprintf(fp, "{");
		for (int i = 0; i < dimension; i++) {
			fprintf(fp, "[%s,", result.mid[2 * i].value.to_middle_value().c_str());
			fprintf(fp, "%s", result.mid[2 * i + 1].value.to_middle_value().c_str());
			if (i == dimension - 1)	fprintf(fp, "]");
			else fprintf(fp, "],");
		}
		fprintf(fp, "}");
		// 区间和误差之间用 ： 分割
		fprintf(fp, ":");
		// 输出误差
		fprintf(fp, "%s\r\n", iRRAM::swrite(result.error, 100).c_str());
		fclose(fp);
	}
	else {
		std::cout << "result.txt 打开失败！ 程序异常退出！！！" << std::endl;
		exit(1);
	}

}

void errorListToEquation(std::list<Result>& resultList)
{
	std::list<Result>::iterator iter;
	for (iter = resultList.begin() ; iter != resultList.end(); iter++)
	{
		std::string temp;
		temp += instruction + "-" + equaltionConvert((*iter).mid[1].value);
		//equationList.push_back(temp);
		//writeToFile(temp);
	}
}

std::string errorToEquation(Result &result)
{
	std::string temp;
	temp += instruction + "-(" + equaltionConvert(result.mid[1].value) + ")";
	//equationList.push_back(temp);
	return temp;
	//writeToFile(temp);
}

std::string equaltionConvert(MyFloat &x)
{
	std::string result;
	int len = instruction.length();
	for (int i = 0; i < len; i++)
	{
		// 是变量
		if ('a' <= instruction[i] && instruction[i] <= 'z' || 'A' <= instruction[i] && instruction[i] <= 'Z')
		{
			result += x.to_decimal();
		}
		else
		{
			result += instruction[i];
		}
	}
	//std::cout << result << std::endl;
	return result;
}

void addToPriorityQueue(std::priority_queue<Result, std::vector<Result>, CompareError>&pq, Result& result)
{
	if (priority_queue_size < num)
	{
		pq.push(result);
		std::cout << "priority_queue size: " << pq.size() << std::endl;
		priority_queue_size++;
	}
	else
	{
		if (iRRAM::abs(result.error) > iRRAM::abs(pq.top().error))
		{
			pq.pop();
			pq.push(result);
		}
	}
}
