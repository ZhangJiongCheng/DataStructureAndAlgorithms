#include<iostream>
#include"线索化二叉树.h"
using namespace std;

//创建二叉树
Status BinTree::CreateBinTree()     
{
	help::CreateBinTree(root, Null);
	return OK;
}
//创建二叉树的实现
Status help::CreateBinTree(BinTreeNode*& root, ElemType& Null)
{
	char ch;
	cin >> ch;    //输入二叉树的节点值

	if (ch == Null) root = nullptr;    //空节点
	else
	{
		if (!(root = new BinTreeNode())) exit(ERROR);    //分配节点失败，退出

		//节点分配成功
		root->data = ch;
		root->lTag = Link;     //左标志默认为节点
		root->rTag = Link;    //右标志默认为节点
		CreateBinTree(root->lChild, Null);     //创建左子树
		CreateBinTree(root->rChild, Null);     //创建右子树
	}

	return OK;
}

//中序线索化二叉树
Status BinTree::InOrderThread()
{
	help::InOrderThread(root, head);
	return OK;
}
//中序线索化二叉树的实现
Status help::InOrderThread(BinTreeNode*& root, BinTreeNode*& head)
{
	if (!(head = new BinTreeNode())) exit(ERROR);  //开辟头结点
	head->lTag = Link;
	head->rTag = Thread;
	head->rChild = head;

	if (!root)    //空树
		head->lChild = head;
	else       //树非空
	{
		head->lChild = root;
		BinTreeNode* pre = head;   //pre辅助线索化
		InThreading(root, pre);
		//处理最后一个元素节点
		pre->rChild = head;
		pre->rTag = Thread;
		head->rChild = pre;
	}
	
	return OK;
}

void help::InThreading(BinTreeNode*& root, BinTreeNode*& pre)
{
	if (root)    //再次确定树非空
	{
		InThreading(root->lChild, pre);    //左子树线索化
		if (!root->lChild)         //前驱
		{
			root->lChild = pre;
			root->lTag = Thread;
		}
		if (!pre->rChild)  //后继
		{
			pre->rChild = root;
			pre->rTag = Thread;
		}
		pre = root;
		InThreading(root->rChild, pre);    //右子树线索化
	}
}

//中序线索遍历二叉树
Status BinTree::InOrderTraverse()
{
	help::InOrderTraverse(root, head);
	return OK;
}
//中序线索遍历二叉树的实现
Status help::InOrderTraverse(BinTreeNode*& root, BinTreeNode*& head)
{
	if (root && root != head)   //非空树
	{
		BinTreeNode* p = first(root);     //获取第一个输出节点
		BinTreeNode* pLast = last(root);     //获取最后一个输出节点 
		while (p != pLast)       //p不是最后一个输出节点
		{
			visit(p->data);
			p = next(p);       //获取下一个输出节点
		}
		visit(p->data);     //输出最后一个节点的数据
	}
	return OK;
}

//一些辅助函数
Status help::visit(ElemType& elem)  //打印数据
{
	cout << elem << " ";
	return OK;
}

BinTreeNode* help::first(BinTreeNode* root)   //获取第一个输出节点
{
	if (!root)      //安全起见，确保节点非空
		return nullptr;
	while (root->lTag == Link)  
		root  = root->lChild;
	return root; 
}

BinTreeNode* help::last(BinTreeNode* root)   //获取最后一个输出节点
{
	if (!root)          //安全起见，确保节点非空
		return nullptr;
	while (root->rTag == Link)
		root = root->rChild;
	return root;
}

BinTreeNode* help::prior(BinTreeNode* cur)  //获取上一个输出节点，即前驱
{
	if (!cur)
		return nullptr;
	if (cur->lTag == Thread)     //左指针指向的是前驱
		return cur->lChild;
	return last(cur->lChild);   //如果左指针指向左孩子，左孩子的最后一个输出节点即为前驱
}

BinTreeNode* help::next(BinTreeNode* cur)  //获取下一个输出节点，即后继
{
	if (!cur)   //当前节点为空
		return nullptr;
	if (cur->rTag == Thread)     //右指针保存的是后继
		return cur->rChild;
	return first(cur->rChild);   //如果右指针指向右孩子，右孩子的第一个输出节点即为后继
}

BinTree::~BinTree()
{
	if (root)    //二叉树非空
		help::deleteBinTree(root);   //删除二叉树，收回内存
	if (head)
		delete head;     //删除头结点
}

void help::deleteBinTree(BinTreeNode* root)
{
	if (!root) return;     //空树，直接返回
	BinTreeNode* p = first(root);       //获取第一个输出节点
	BinTreeNode* pLast = last(root);   //获取最后一个输出节点
	BinTreeNode* pNext = nullptr;       //pNext指向p的下一个输出节点
	//按输出顺序一个一个地删除
	while (p != pLast)
	{
		pNext = next(p);     //获取p的下一个输出节点
		delete p;
		p = pNext;
	}
	delete p;    //删除最后一个输出节点
}
 