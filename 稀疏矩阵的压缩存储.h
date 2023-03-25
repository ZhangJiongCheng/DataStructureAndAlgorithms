#pragma once

#include<tuple>
#include<vector>
using namespace std;

typedef int ElemType;

ostream& operator<<(ostream& os, const tuple<int, int, ElemType>& t);

class SparseMatrix
{
public:
	//friend ostream& operator<<(ostream& os, const tuple<int, int, ElemType>& t);

	SparseMatrix():mu(0),nu(0),tu(0){}

	SparseMatrix(const SparseMatrix& sm);   //拷贝构造函数

	SparseMatrix operator=(const SparseMatrix& sm);   //拷贝赋值函数

	void CreateSMatrix();   //创建矩阵

	void PrintSMatrix();    //打印矩阵

	SparseMatrix CopySMatrix();   //复制矩阵，返回经复制得到的矩阵

	SparseMatrix AddSMatrix(const SparseMatrix& sm2);  //矩阵相加，返回相加后的矩阵

	SparseMatrix SubSMatrix(const SparseMatrix& sm2);  //矩阵相减，返回相减后的矩阵

	SparseMatrix MultSMatrix(const SparseMatrix& sm2);  //矩阵相乘，返回相乘后的矩阵

	SparseMatrix TransposeMatrix();  //矩阵转置，返回转置后的矩阵

	~SparseMatrix() = default;

private:
	vector<tuple<int, int, ElemType>> data;    //存放矩阵的容器，tuple表示矩阵元素的三元组
	int mu;   //矩阵的行数
	int nu;    //矩阵的列数
	int tu;   //矩阵的非零元个数
};