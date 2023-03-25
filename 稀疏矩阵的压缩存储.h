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

	SparseMatrix(const SparseMatrix& sm);   //�������캯��

	SparseMatrix operator=(const SparseMatrix& sm);   //������ֵ����

	void CreateSMatrix();   //��������

	void PrintSMatrix();    //��ӡ����

	SparseMatrix CopySMatrix();   //���ƾ��󣬷��ؾ����Ƶõ��ľ���

	SparseMatrix AddSMatrix(const SparseMatrix& sm2);  //������ӣ�������Ӻ�ľ���

	SparseMatrix SubSMatrix(const SparseMatrix& sm2);  //������������������ľ���

	SparseMatrix MultSMatrix(const SparseMatrix& sm2);  //������ˣ�������˺�ľ���

	SparseMatrix TransposeMatrix();  //����ת�ã�����ת�ú�ľ���

	~SparseMatrix() = default;

private:
	vector<tuple<int, int, ElemType>> data;    //��ž����������tuple��ʾ����Ԫ�ص���Ԫ��
	int mu;   //���������
	int nu;    //���������
	int tu;   //����ķ���Ԫ����
};