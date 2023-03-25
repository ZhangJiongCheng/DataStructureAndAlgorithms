#pragma once

#include<iostream>
#include<cassert>
#include<stack>
using namespace std;

typedef int DataType;

struct AVLNode     //二叉平衡树的节点
{
	DataType data;
	int bf;    //平衡因子
	AVLNode* lChild;
	AVLNode* rChild;
};

class AVLTree
{
public:
	AVLTree(): root(nullptr) {}

	//插入数据
	void Insert(const DataType& data);

	//删除数据
	void Remove(const DataType& data);

	~AVLTree();

private:
	AVLNode* root;
};

namespace BTree
{
	void buyNode(const DataType& data, AVLNode*& p);   //开辟节点
	void clear(AVLNode*& tree);    //删除二叉平衡树的节点，释放空间
	
	//右旋转
	void RotateR(AVLNode*& p);
	//左旋转
	void RotateL(AVLNode*& p);
	//先右后左旋转
	void RotateRL(AVLNode*& p);
	//先左后右旋转
	void RotateLR(AVLNode*& p);
}