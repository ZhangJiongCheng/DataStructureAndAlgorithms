#pragma once

#include<iostream>
#include<cassert>
#include<stack>
using namespace std;

#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;

struct BSTNode
{
	ElemType data;
	BSTNode* lChild;
	BSTNode* rChild;
};

struct stacknode   //�����ǵݹ�������
{
	BSTNode* ptr;
	bool flag;     //0:������������ 1:����������
};

class BSTree
{
public:
	BSTree() :tree(nullptr) {}

	//��������
	Status InsertData(const ElemType& data);

	//�����ֵ
	Status Max(ElemType& max);

	//�����ֵ
	Status Min(ElemType& min);

	//��˳���ӡ����
	void Sort_Print(); 

	//�ǵݹ��������
	void post_traverse();

	//��������
	Status Search(const ElemType& data, BSTNode*& p);

	//ɾ������
	Status RemoveData(const ElemType& data);

	~BSTree();

private:
	BSTNode* tree;
};

namespace BST
{
	//��������
	Status InsertData(BSTNode*& t, const ElemType& data);

	//��˳���ӡ����
	void Sort_Print(BSTNode*& t);

	//��������
	Status Search(BSTNode*& t, const ElemType& data, BSTNode*& p);

	//ɾ������
	Status RemoveData(BSTNode*& t, const ElemType& data);

	//ɾ���ڵ㣬�ͷ���Դ
	void DeleteNode(BSTNode*& tree);
}