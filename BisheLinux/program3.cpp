#include "program3.h"
/*获取指令的元数，即对应的维度值*/

int getInstrutionVariableNumber(std::string inputInstruction) {
	int n = 1;
	// TODO 分析指令有几个变量
	dimension = n;
	// 定义长度为n的数组，存储每个维度当前遍历的浮点值
	arrNLoop = new MyFloat[dimension];
	return n;
}

void initDataStruct(int n) {
	// 将数组的值初始化为浮点数最小值
	init(arrNLoop);
}

/* 将数组的值初始化为浮点数最小值 */
void init(MyFloatPtr arrNLoop)
{
	for (int i = 0; i < dimension; i++) {
		arrNLoop[i] = *FLOAT_MIN;
	}
}

void init(MyFloatPtr arrNLoop, int index) {
	// 下标index 之前的数组初始化为浮点数最小值
	for (int i = 0; i <= index; i++) {
		arrNLoop[i] = *FLOAT_MIN;
	}
	int newIndex = index+1;
	while (newIndex < dimension) {
		if (newIndex == dimension - 1 && arrNLoop[newIndex].isFloatMax()) {
			// 循环结束
			loopOver = true;
		}
		else if(arrNLoop[newIndex].isFloatMax()){
			arrNLoop[newIndex] = *FLOAT_MIN;
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
	MyFloat *begin = FLOAT_MIN;
	for (; !begin->isFloatMax(); begin = begin->up())
	{
		// 计算左中间点
		struct MiddleValue leftMiddleVal;
		leftMiddleVal.value = *begin;
		leftMiddleVal.direct = false;
		// 计算右中间点
		struct MiddleValue rightMiddleVal;
		rightMiddleVal.value = *begin->up();
		rightMiddleVal.direct = false;

		if (dimension == 1)
		{
			result.mid[2 * (dimension - 1)] = leftMiddleVal;
			result.mid[2 * (dimension - 1) + 1] = rightMiddleVal;
			// 计算误差
			calcError(result);

			// TODO 如何合并不同维度的误差
			if (result.error == preResult->error)	// 误差一致，合并
			{
				// 左值更新，右值不变
				result.mid[2 * (dimension - 1)] = preResult->mid[2 * (dimension - 1)];
				// 删除集合中的preResult
				resultList.pop_back();
			}
			// (合并后的result)加入结果集
			resultList.push_back(result);
			// 赋值新的preResult
			preResult = &result;
		}
		else
		{
			int curDim = dimension - localDim;
			result.mid[2 * curDim] = leftMiddleVal;
			result.mid[2 * curDim + 1] = rightMiddleVal;
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

/* 结果写入文件 */
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
	std::cout << "float计算程序文件名: " + floatCppName << std::endl;
	std::cout << "irram计算程序文件名: " + irramCppName << std::endl;
	if (fileExist(floatCppName) && fileExist(irramCppName)) {
		// TODO 调用float程序算出浮点结果
		// TODO 调用real程序算出实数结果
		// TODO 计算误差
		iRRAM::REAL error = "1";
		result.error = error;
	}
	else {
		// TODO 生成计算程序，再计算误差
		std::string instruction;
		generateFloatCpp(instruction);
		generateIrramCpp(instruction);
		compileCpp(floatCppName);
		compileCpp(irramCppName);
		calcError(result);
	}
}