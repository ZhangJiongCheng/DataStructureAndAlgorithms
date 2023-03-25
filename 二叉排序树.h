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

struct stacknode   //辅助非递归后序遍历
{
	BSTNode* ptr;
	bool flag;     //0:从左子树来； 1:从有子树来
};

class BSTree
{
public:
	BSTree() :tree(nullptr) {}

	//插入数据
	Status InsertData(const ElemType& data);

	//求最大值
	Status Max(ElemType& max);

	//求最大值
	Status Min(ElemType& min);

	//按顺序打印数据
	void Sort_Print(); 

	//非递归后续遍历
	void post_traverse();

	//查找数据
	Status Search(const ElemType& data, BSTNode*& p);

	//删除数据
	Status RemoveData(const ElemType& data);

	~BSTree();

private:
	BSTNode* tree;
};

namespace BST
{
	//插入数据
	Status InsertData(BSTNode*& t, const ElemType& data);

	//按顺序打印数据
	void Sort_Print(BSTNode*& t);

	//查找数据
	Status Search(BSTNode*& t, const ElemType& data, BSTNode*& p);

	//删除数据
	Status RemoveData(BSTNode*& t, const ElemType& data);

	//删除节点，释放资源
	void DeleteNode(BSTNode*& tree);
}