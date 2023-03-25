#pragma once

#define OK     1     
#define ERROR  -1
typedef int Status;    //状态码

typedef char ElemType;      //节点元素类型

typedef enum { Link, Thread } PointerTag;    //Link表示节点，Thread表示前驱或者后继
//二叉树节点
typedef struct BinTreeNode
{
	ElemType data;    //数据域
	BinTreeNode* lChild;     //左孩子指针
	BinTreeNode* rChild;    //右孩子指针
	PointerTag lTag;      //左标志
	PointerTag rTag;     //右标志
}BiThrNode, * BiThrLink;


//二叉树
struct BinTree
{
public:
	BinTree():root(nullptr),Null('*'),head(nullptr) {}     //构造函数初始化二叉树

	Status CreateBinTree();     //创建二叉树,内部调用BinTreeNode::CreateBinTree()完成创建

	Status InOrderThread();   //中序线索化二叉树，内部调用BinTreeNode::InOrderThread()完成创建

	Status InOrderTraverse();   //中序线索遍历二叉树,内部调用BinTreeNode::InOrderTraverse()完成创建

	~BinTree();          //析构函数delete掉二叉树

private:
	BinTreeNode* root;     //指向二叉树根节点的指针
	ElemType    Null;    //表示空节点
	BinTreeNode* head;    //头结点
};


namespace help
{
	Status CreateBinTree(BinTreeNode*& root, ElemType& Null);     //创建二叉树,为了通过类名调用，必须static

	Status InOrderThread(BinTreeNode*& root, BinTreeNode*& head);  //中序线索化二叉树，处理头结点和最后一个元素节点
	void InThreading(BinTreeNode*& root, BinTreeNode*& pre);   //中序线索化二叉树

	Status InOrderTraverse(BinTreeNode*& root, BinTreeNode*& head);   //中序遍历二叉树


	/*
	* 接下来的四个函数都有可能改变形参的指向，所以形参不能引用，否则结果会出错
	* 例如，BinTreeNode* first(BinTreeNode*& root);   //获取第一个输出节点;  错误，会改变类BinTree中的root成员，导致结果出错
	*/
	BinTreeNode* first(BinTreeNode* root);   //获取第一个输出节点;
	BinTreeNode* last(BinTreeNode* root);   //获取最后一个输出节点
	BinTreeNode* prior(BinTreeNode* cur);  //获取上一个输出节点，即前驱
	BinTreeNode* next(BinTreeNode* cur);  //获取下一个输出节点，即后继

	Status visit(ElemType& elem);

	void deleteBinTree(BinTreeNode* root);        //delete掉new出来的二叉树
}
