#pragma once
#include "Matrix.h"


matrix linspace(double start, double end, int num);				//从start到end(不包括end),产生等距num个点
matrix linspace(double start, double end, long int num);				//从start到end(不包括end),产生等距num个点


matrix linspace(double start, double end, int num) {
	double step = (end - start) / num;
	if (num <= 0) {
		printf("列表长度小于0,Num:%d\n", num);
		matrix M;
		return M;
	}
	else {
		matrix M(1, num, start);
		M.show();
		double step = (end - start) / num;
		for (int i = 0; i < num; i++)
			M.Elem[i] += i * step;
		return M;
	}
}
matrix linspace(double start, double end,long int num) {
	double step = (end - start) / num;
	if (num <= 0) {
		printf("列表长度小于0,Num:%d\n", num);
		matrix M;
		return M;
	}
	else {
		matrix M(1, num, start);
		double step = (end - start) / num;
		for (int i = 0; i < num; i++)
			M.Elem[i] += i * step;
		return M;
	}
}



