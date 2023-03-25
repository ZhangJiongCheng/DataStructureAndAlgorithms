#include<iostream>
#include<fstream>
#include<cassert>
#include"稀疏矩阵的压缩存储.h"
using namespace std;

SparseMatrix::SparseMatrix(const SparseMatrix& sm)
{
	mu = sm.mu;
	nu = sm.nu;
	tu = sm.tu;
	data.resize(tu);
	data = sm.data;

	//tuple<int, int, ElemType> tem;
	//for (int i = 0; i < tu; ++i)
	//{
	//	get<0>(tem) = get<0>(sm.data[i]);
	//	get<1>(tem) = get<1>(sm.data[i]);
	//	get<2>(tem) = get<2>(sm.data[i]);
	//	data.push_back(tem);    //将矩阵元素放到容器里
	//}
	//data.resize(tu);   //分配空间，以免与data的空间重叠
	//memmove(&data, &sm.data, sizeof(tuple<int, int, ElemType>) * tu);
}

SparseMatrix SparseMatrix::operator=(const SparseMatrix& sm)
{
	mu = sm.mu;
	nu = sm.nu;
	tu = sm.tu;
	data.resize(tu);
	data = sm.data;   //两个相同的vector可以直接赋值

	//tuple<int, int, ElemType> tem;
	//for (int i = 0; i < tu; ++i)
	//{
	//	get<0>(tem) = get<0>(sm.data[i]);
	//	get<1>(tem) = get<1>(sm.data[i]);
	//	get<2>(tem) = get<2>(sm.data[i]);
	//	data.push_back(tem);    //将矩阵元素放到容器里
	//}
	
	//data.resize(tu);   //分配空间，以免与data的空间重叠
	//memmove(&data, &sm.data, sizeof(tuple<int, int, ElemType>) * tu);    //明明能成功复制，却无法输出
	return *this;
}

void SparseMatrix::CreateSMatrix()   //创建矩阵
{
	//矩阵在文件里，打开文件
	ifstream fp1(R"zfc(C:\Users\Lenovo\OneDrive\桌面\数据结构程序\稀疏矩阵的压缩存储\sm1.txt)zfc", ios::in);
	//ifstream fp1("sm1.txt", ios::in);
	if (!fp1)
		cout << "error 1" << endl;

	fp1 >> mu >> nu;    //读入行数和列数

	tuple<int, int, ElemType> tem;
	ElemType v; //从矩阵里一个一个将值读到v
	tu = 0;   //一开始非零元个数为0
	for (int row = 0; row < mu; ++row)  //行
	{
		for (int col = 0; col < nu; ++col)  //列
		{
			fp1 >> v;
			if (v != 0)
			{
				get<0>(tem) = row;    
				get<1>(tem) = col;
				get<2>(tem) = v;
				data.push_back(tem);    //将矩阵元素放到容器里
				++tu;
			}
		}
	}//for

	fp1.close();  //记得关闭文件
}

void SparseMatrix::PrintSMatrix()    //打印矩阵
{
	cout << "row = " << mu << "   col = " << nu << endl;
	for (const auto& elem : data)
	{
		cout << elem << endl;
	}
}

SparseMatrix SparseMatrix::CopySMatrix()   //复制矩阵，返回经复制得到的矩阵
{
	return *this;
}

SparseMatrix SparseMatrix::AddSMatrix(const SparseMatrix& sm2)  //矩阵相加，返回相加后的矩阵
{
	return *this;
}
SparseMatrix SparseMatrix::SubSMatrix(const SparseMatrix& sm2)  //矩阵相减，返回相减后的矩阵
{
	return *this;
}
SparseMatrix SparseMatrix::MultSMatrix(const SparseMatrix& sm2)  //矩阵相乘，返回相乘后的矩阵
{
	return *this;
}

SparseMatrix SparseMatrix::TransposeMatrix()  //矩阵转置，返回转置后的矩阵
{
	SparseMatrix tem;
	tem.mu = nu;
	tem.nu = mu;
	tem.tu = tu;
	tem.data.resize(tu);
	
	int* num = new int[nu];
	memset(num, 0, sizeof(int) * nu);   //初始化num

	int i;
	for (i = 0; i < tu; ++i)  ++num[get<1>(data[i])];    //统计转置后的矩阵每一行的元素个数
	
	int* cpot = new int[nu];
	cpot[0] = 0;   //转置后的矩阵第0行的首元素在data中的下标位置为0
	for (i = 1; i < nu; ++i)  cpot[i] = cpot[i - 1] + num[i - 1];  //计算转置后的矩阵每一行的首元素在data中的下标位置

	int col;
	int p;
	for (i = 0; i < tu; ++i)   //将原矩阵的每一个元素放到转置后的矩阵的恰当位置
	{
		col = get<1>(data[i]);   //获得第i个元素在转置后的矩阵的哪一行
		p = cpot[col];      ////获得第i个元素在转置后的矩阵的data中的下标位置
		//转置后的矩阵元素与原矩阵的行列位置互换
		get<0>(tem.data[p]) = get<1>(data[i]);
		get<1>(tem.data[p]) = get<0>(data[i]);
		get<2>(tem.data[p]) = get<2>(data[i]);

		++cpot[col];
	}

	delete[] num;
	delete[] cpot;
	return tem;
}

ostream& operator<<(ostream& os, const tuple<int, int, ElemType>& t)
{
	cout << "(" << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << ")";
	return os;
}
