#pragma once

#include<iostream>
#include<cassert>
#include<stack>
using namespace std;

typedef int DataType;

struct AVLNode     //����ƽ�����Ľڵ�
{
	DataType data;
	int bf;    //ƽ������
	AVLNode* lChild;
	AVLNode* rChild;
};

class AVLTree
{
public:
	AVLTree(): root(nullptr) {}

	//��������
	void Insert(const DataType& data);

	//ɾ������
	void Remove(const DataType& data);

	~AVLTree();

private:
	AVLNode* root;
};

namespace BTree
{
	void buyNode(const DataType& data, AVLNode*& p);   //���ٽڵ�
	void clear(AVLNode*& tree);    //ɾ������ƽ�����Ľڵ㣬�ͷſռ�
	
	//����ת
	void RotateR(AVLNode*& p);
	//����ת
	void RotateL(AVLNode*& p);
	//���Һ�����ת
	void RotateRL(AVLNode*& p);
	//���������ת
	void RotateLR(AVLNode*& p);
}