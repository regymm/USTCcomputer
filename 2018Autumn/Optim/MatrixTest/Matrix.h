//#define _CRT_SECURE_NO_WARNINGS
#ifndef MY_MATRIX_H
#define MY_MATRIX_H
#include <math.h>
#include <stdio.h>
//#include <Windows.h>
#include <iostream>
#include "mkl.h"
using namespace std;

#define EPS 1e-6
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int Status;
typedef double ElemType;

/*矩阵类的定义*/
class matrix 
{
public:
	/*矩阵基本元素*/
	int Col;	//列数
	int Row;	//行数
	long int Numel;
	ElemType *Elem;
public:
	/*矩阵基本函数*/
	matrix(void);													//默认构造函数
	matrix(int Rows, int Cols, double val);				//按行列构造矩阵,默认为0
	matrix(int Cols, double val);								//按列构造对角阵，默认为单位阵
	matrix(int Rows,int Cols, ElemType *Array);					//使用一维数组构造矩阵
	matrix(int Rows,int Cols, ElemType **Array);					//按二维数组构造矩阵
	matrix(const matrix& matrix);

	void show();													//打印矩阵
	ElemType GetElem(int L, int R);									//查看矩阵元
	void SetElem(int L, int R, ElemType val);									//修改矩阵元

	matrix GetCols(int Col_index);										//获取指定单列
	matrix GetCols(int start, int end, int step);							//获取指定列,step默认为1
	matrix GetRows(int Row_index);										//获取指定行
	matrix GetRows(int start, int end, int step);						//获取指定行,step默认为1
	matrix slice(int start_row, int end_row, int start_col, int end_col, int row_step, int col_step);//切片操作
	matrix transpose();									//矩阵转置
	ElemType& operator()(int L, int R);
	matrix& operator()(matrix Row_index, matrix Col_index);
	matrix& operator=(const matrix& matrix);            //矩阵的赋值操作符重载
	matrix& operator+=(matrix& matrix2);          //矩阵的加法操作符重载
	matrix& operator+=(ElemType val);                //矩阵与数的加法操作符重载
	matrix& operator-=(matrix& matrix2);          //矩阵的减法操作符重载
	matrix& operator-=(ElemType val);                //矩阵与数的减法操作符重载
	matrix& operator*=(matrix& matrix2);          //矩阵的乘法操作符重载
	matrix& operator*=(ElemType val);                //矩阵与数的乘法操作符重载
	
public:
	/*矩阵基本运算*/
	friend matrix operator+(matrix &matrix1, matrix &matrix2);
	friend matrix operator-(matrix &matrix1, matrix &matrix2);
	friend matrix operator*(matrix &matrix1, matrix &matrix2);			
	friend matrix operator+(double val, matrix& matrix1);      //矩阵与数加法－操作符重载（2）
	friend matrix operator-(matrix& matrix1, double val);      //矩阵与数减法－操作符重载（1）
	friend matrix operator-(double val, matrix& matrix1);      //矩阵与数减法－操作符重载（2）
	friend matrix operator-(matrix& M);									   //M的负矩阵
	friend matrix operator*(matrix& matrix1, double val);      //矩阵与数乘法－操作符重载（1）
	friend matrix operator*(double val, matrix& matrix1);      //矩阵与数乘法－操作符重载（2)
	friend std::ostream& operator<<(std::ostream &os,matrix &matrix);	//输出
public:
	/*矩阵功能函数*/
	Status reshape(int Rows, int Cols);								//矩阵变形,为-1则自动计算
	~matrix();														//析构函数
};



/*默认构造矩阵*/
matrix::matrix() {
	Row = 0;
	Col = 0;
	Numel = 0;
	Elem = NULL;
}
/*构造0矩阵*/
matrix::matrix(int Rows, int Cols, double val = 0) {
	Col = Cols;
	Row = Rows;
	Numel = Col * Row;
	Elem = (ElemType *)mkl_malloc(Col*Row * sizeof(ElemType), 64);
	for (int i = 0; i < Numel; i++)
		Elem[i] = val;
}
/*构造单位阵*/
matrix::matrix(int Cols, double val = 1) {
	Col = Row = Cols;
	Numel = Col * Row;
	Elem = (ElemType *)mkl_malloc(Col*Row * sizeof(ElemType), 64);
	for (int i = 0; i < Numel; i++)
		Elem[i] = 0;				//先初始化到0
	for (int i = 0; i < Col; i++)
		Elem[i*Col + i] = val;		//指定元初始化到val
}
/*使用已知数组构造矩阵*/
matrix::matrix(int Rows,int Cols, ElemType *Array) {
	Col = Cols;
	Row = Rows;
	Numel = Col * Row;
	Elem = (ElemType *)mkl_malloc(Col*Row * sizeof(ElemType), 64);
	for (int i = 0; i < Numel; i++)
		Elem[i] = Array[i];
}
/*使用已知数组构造矩阵*/
matrix::matrix(int Rows,int Cols, ElemType **Array) {
	Col = Cols;
	Row = Rows;
	Numel = Col * Row;
	Elem = (ElemType *)mkl_malloc(Col*Row * sizeof(ElemType), 64);
	for (int i = 0; i < Col; i++) {
		for (int j = 0; j < Row; j++) {
			Elem[i*Row + j] = Array[i][j];
		}
	}
}
/*使用已知矩阵构造矩阵*/
matrix::matrix(const matrix &M) {
	Col = M.Col;
	Row = M.Row;
	Numel = M.Numel;
	Elem = (ElemType *)mkl_malloc(Col*Row * sizeof(ElemType), 64);
	for (int i = 0; i < Numel; i++)
		Elem[i] = M.Elem[i];
}
/*析构*/
matrix::~matrix(void) {
	mkl_free(Elem);		//释放内存
}

/*打印矩阵*/
void matrix::show() {
	for (int i = 0; i < Numel; i++) {
		if (i%Col == 0)
			cout << "\n";
		cout << Elem[i] << " ";
	}
}

/*获取指定列*/
matrix matrix::GetCols(int Col_index) {
	if (Col_index > Col) {
		printf("索引大于数组维度,M:%d*%d,Col_index:%d\n", Row, Col, Col_index);
		matrix M;
		return M;
	}
	else {
		matrix M(Row, 1);
		for (int i = 0; i < Row; i++)
			M.Elem[i] = Elem[i*Row + Col_index];
		return M;
	}
}
/*获取指定列,使用了双循环,待改进*/
matrix matrix::GetCols(int start, int end, int step = 1) {
	/*从start到end(不包括end)，步长为step*/
	if (start <0 || end > Col) {
		printf("索引大于数组维度,M:%d*%d,start:%d,end:%d\n", Row, Col, start, end);
		matrix M;
		return M;
	}
	int num = (end - start - 1) / step + 1;
	matrix M(Row, num);
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < num; j++)
			M.Elem[i*Row + j] = Elem[i*Row + start + j * step];
	return M;

}
/*获取指定行*/
matrix matrix::GetRows(int Row_index) {
	if (Row_index > Row) {
		printf("索引大于数组维度,M:%d*%d,Row_index:%d\n", Row, Col, Row_index);
		matrix M;
		return M;
	}
	else {
		matrix M(1, Col);
		for (int i = 0; i < Col; i++)
			M.Elem[i] = Elem[Row_index*Row + i];
		return M;
	}
}
/*获取指定行,用到了双循环,待改进*/
matrix matrix::GetRows(int start, int end, int step = 1) {
	if (start < 0 || end > Row) {
		printf("索引大于数组维度,M:%d*%d,start:%d,end:%d\n", Row, Col, start, end);
		matrix M;
		return M;
	}
	int num = (end - start - 1) / step + 1;
	matrix M(num, Col);
	for (int i = 0; i < num; i++)
		for (int j = 0; j < Col; j++)
			M.Elem[i*Col + j] = Elem[(start + i * step)*Col + j];
	return M;
}

/*切片操作,只支持均匀步长索引,均从start到end(不包括end),步长为1采用Lapack库操作*/
matrix matrix::slice(int start_row, int end_row, int start_col, int end_col, int row_step = 1, int col_step = 1) {
	if (start_row < 0 || start_col < 0 || end_row > Row || end_col > Col || row_step <= 0 || col_step <= 0) {
		printf("索引失败,超过矩阵维度或索引不符合要求,M:%d*%d\n", Row, Col);
		matrix M;
		return M;
	}
	/*
	else if (row_step == 1 && col_step == 1) {
		int num_row = end_row - start_row;
		int num_col = end_col - start_col;
		matrix M(num_row, num_col);
		//int *row_index = (int *)malloc(num_row * sizeof(int));
		//int *col_index = (int *)malloc(num_col * sizeof(int));
		int *index_in = (int *)malloc(num_row*num_col * sizeof(int));
		int *index_out = (int *)malloc(num_row*num_col * sizeof(int));
		int k = 0;
		for (int i = 0; i < num_row; i++) {
			for (int j = 0; j < num_col; j++, k++) {
				index_in[k] = start_col + j + (start_row + i)*Col;
				index_out[k] = k;
			}
		}
			
		/*for (int i = 0; i < num_row; i++)
			row_index[i] = start_row + i;
		for (int i = 0; i < num_col; i++)
			col_index[i] = start_col + i;	 
		pdlacpy("A", &num_row, &num_col, Elem, &start_row, &start_col, index_in, M.Elem, 0, 0, index_out);
		return M;
	}*/
	else {
		int num_row = (end_row - start_row - 1) / row_step + 1;
		int num_col = (end_col - start_col - 1) / col_step + 1;
		matrix M(num_row, num_col);
		for (int i = 0; i < num_row; i++)
			for (int j = 0; j < num_col; j++)
				M.Elem[i*num_col + j] = Elem[(start_row + i * row_step)*Col + j * col_step + start_col];
		return M;
	}	
}

/*查看,修改矩阵数据*/
ElemType& matrix::operator()(int L, int R) {
	return Elem[L*Row + R];
}
/*矩阵索引,使用了双循环,待改进,支持任意步长索引,但最好都是整数(在内部已强行转化成int型)*/
matrix& matrix::operator()(matrix Row_index, matrix Col_index) {
	int Row1 = Row_index.Row;
	int Col1 = Row_index.Col;
	int Row2 = Col_index.Row;
	int Col2 = Col_index.Col;
	if ((Row1 == 1 && Row2 == 1) || (Row1 == 1 && Col2 == 1) || (Col1 == 1 && Row2 == 1) || (Col1 == 1 && Col2 == 1)) {
		int New_Row = max(Row1, Col1);
		int New_Col = max(Row2, Col2);
		matrix New(New_Row, New_Col);
		for (int i = 0; i < New.Row; i++)
			for (int j = 0; j < New.Col; j++)
				*(New.Elem + i * New_Row + j) = *(Elem + int(*(Row_index.Elem + i))*Row + int(*(Col_index.Elem + j)));
		return New;
	}
	else {
		printf("索引错误\n");
		matrix M;
		return M;
	}
}

ElemType matrix::GetElem(int L, int R) {
	return Elem[(L - 1)*Row + R - 1];
}

void matrix::SetElem(int L, int R, ElemType val) {
	Elem[(L - 1)*Row + R - 1] = val;
}


/*赋值运算符重载*/
matrix& matrix::operator=(const matrix &M) {
	if (this == &M)
		return *this;
	Col = M.Col;
	Row = M.Row;
	Numel = M.Numel;
	Elem = (ElemType *)mkl_malloc(Col*Row * sizeof(ElemType), 64);
	for (int i = 0; i < Numel; i++)
		Elem[i] = M.Elem[i];
	return *this;
}
matrix& matrix::operator+=(matrix &M) {
	if (Col == M.Col&&Row == M.Row) {
		for (int i = 0; i < Numel; i++)
			Elem[i] += M.Elem[i];
		return *this;
	}
	else {
		cout << "矩阵维度不同,不可相加\n";
		return *this;
	}
}
matrix& matrix::operator-=(matrix &M) {
	if (Col == M.Col&&Row == M.Row) {
		for (int i = 0; i < Numel; i++)
			Elem[i] -= M.Elem[i];
		return *this;
	}
	else {
		cout << "矩阵维度不同,不可相减\n";
		return *this;
	}
}

/*数加与数减*/
matrix& matrix::operator+=(ElemType val) {
	for (int i = 0; i < Numel; i++)
		Elem[i] += val;
	return *this;
}
matrix& matrix::operator-=(ElemType val) {
	for (int i = 0; i < Numel; i++)
		Elem[i] -= val;
	return *this;
}

/*矩阵数乘与矩阵乘*/
matrix& matrix::operator*=(matrix&M) {
	/*暂时采用普通矩阵乘法,之后会想办法优化该算法,比如使用并行计算*/
	/*这个函数是 A = A*B  */
	ElemType temp = 0;
	ElemType *NewElem = (ElemType *)mkl_malloc(Col*Row * sizeof(ElemType), 64);
	for (int i = 0; i < Col*M.Row; i++)
		NewElem[i] = 0;
	if (Col == M.Row) {
		//CPU并行计算
		int max_threads = mkl_get_max_threads();
		mkl_set_num_threads(max_threads);
		cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, Row, M.Col, Col, 1, Elem, Col, M.Elem, M.Col, 0, NewElem, M.Col);
		Elem = NewElem;
		return *this;
	}
	else {
		printf("矩阵维度不一致,无法相乘,A:%d*%d矩阵,B:%d*%d矩阵\n", Row, Col, M.Col, M.Row);
		return *this;
	}
}
matrix& matrix::operator*=(ElemType val) {
	for (int i = 0; i < Numel; i++)
		Elem[i] *= val;
	return *this;
}


/*矩阵与矩阵乘法*/
matrix operator*(matrix& M1, matrix& M2)
{
	ElemType temp = 0;
	matrix Temp(M1.Row, M2.Col);
	if (M1.Col == M2.Row) {
		//CPU并行计算
		//int max_threads = mkl_get_max_threads();
		//mkl_set_num_threads(max_threads);
		//mkl_set_num_threads(8);
		mkl_set_num_threads(1);
		cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M1.Row, M2.Col, M1.Col, 1, M1.Elem, M1.Col, M2.Elem, M2.Col, 0, Temp.Elem, M2.Col);
		return Temp; 
	}
	else {
		printf("矩阵维度不一致,无法相乘,A:%d*%d矩阵,B:%d*%d矩阵\n", M1.Row, M1.Col, M2.Row, M2.Col);
		return M1;
	}
}

/*矩阵与数乘法*/
matrix operator*(double val, matrix& M) {
	for (int i = 0; i < M.Numel; i++)
		M.Elem[i] *= val;
	return M;
}
matrix operator*(matrix& M, double val) {
	for (int i = 0; i < M.Numel; i++)
		M.Elem[i] *= val;
	return M;
}


/*矩阵与数加法*/
matrix operator+(matrix& M, double val) {
	for (int i = 0; i < M.Numel; i++)
		M.Elem[i] += val;
	return M;
}
matrix operator+(double val, matrix& M) {
	for (int i = 0; i < M.Numel; i++)
		M.Elem[i] += val;
	return M;
}

/*矩阵与矩阵加法*/
matrix operator+(matrix& M1, matrix& M2) {
	matrix M3(M1);
	if (M1.Col == M2.Col&&M1.Row == M2.Row) {
		for (int i = 0; i < M1.Numel; i++)
			M3.Elem[i] += M2.Elem[i];
		return M3;
	}
	else {
		printf("矩阵维度不一致,无法相加,A:%d*%d矩阵,B:%d*%d矩阵\n", M1.Row, M1.Col, M2.Row, M2.Col);
		return M1;
	}
}


/*矩阵与数减法*/
matrix operator-(matrix& M, double val) {
	for (int i = 0; i < M.Numel; i++)
		M.Elem[i] -= val;
	return M;
}
matrix operator-(double val, matrix& M) {
	for (int i = 0; i < M.Numel; i++)
		M.Elem[i] = val - M.Elem[i];
	return M;
}
matrix operator-(matrix& M) {
	for (int i = 0; i < M.Numel; i++)
		M.Elem[i] = -M.Elem[i];
	return M;
}


/*矩阵与矩阵减法*/
matrix operator-(matrix& M1, matrix& M2) {
	matrix M3(M1);
	if (M1.Col == M2.Col&&M1.Row == M2.Row) {
		for (int i = 0; i < M1.Numel; i++)
			M3.Elem[i] -= M2.Elem[i];
		return M3;
	}
	else {
		printf("矩阵维度不一致,无法相减,A:%d*%d矩阵,B:%d*%d矩阵\n", M1.Row, M1.Col, M2.Row, M2.Col);
		return M1;
	}
}

/*矩阵输出*/
std::ostream& operator<<(std::ostream &os,matrix& M) {
	for (int i = 0; i < M.Numel; i++) {
		if (i%M.Col == 0)
			cout << "\n";
		os << M.Elem[i] << " ";
	}
	return os;
}


/*reshape函数*/
Status matrix::reshape(int Rows, int Cols){
	if (Rows == -1 && Numel%Cols == 0) {
		Col = Cols;
		Row = Numel / Col;
		return OK;

	}
	else if (Cols == -1 && Numel%Rows == 0) {
		Row = Rows;
		Col = Numel / Row;
		return OK;
	}
	else if (Rows*Cols == Numel) {
		Row = Rows;
		Col = Cols;
		return OK;
	}
	else {
		cout << "矩阵Reshape维度错误:" << Row << "*" << Col << "\n";
		return ERROR;
	}
}


/*矩阵转置函数*/
matrix matrix::transpose() {
	/*采用MKL BLAs库中的转置操作*/
	for (int i = 0; i < Numel; i++)
		cout << Elem[i] << " ";
	cout << "\n";
	mkl_dimatcopy('r', 't', Row, Col, 1, Elem, Row, Col);
	for (int i = 0; i < Numel; i++)
		cout << Elem[i] << " ";
	int temp = Col;
	Col = Row;
	Row = temp;
	return *this;
}
#endif
