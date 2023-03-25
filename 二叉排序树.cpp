#include"二叉排序树.h"

//插入数据
Status BSTree::InsertData(const ElemType& data)
{
	return BST::InsertData(tree, data);
}
//插入数据
Status BST::InsertData(BSTNode*& t, const ElemType& data)
{
	if (!t)    //该节点为空节点
	{
		t = new BSTNode;
		assert(t != nullptr);
		t->data = data;
		t->lChild = t->rChild = nullptr;
		return TRUE;
	}
	else if (data < t->data)   //插入到左子树
	{
		return InsertData(t->lChild, data);
	}
	else if (data > t->data)   //插入到右子树
	{
		return InsertData(t->rChild, data);
	}

	return FALSE;
}

//求最大值
Status BSTree::Max(ElemType& max)
{
	if (tree)
	{
		BSTNode* p = tree;
		while (p->rChild)
			p = p->rChild;
		
		max = p->data;
		return TRUE;

	}//if
}

//求最大值
Status BSTree::Min(ElemType& min)
{
	if (tree)
	{
		BSTNode* p = tree;
		while (p->lChild)
			p = p->lChild;

		min = p->data;
		return TRUE;

	}//if
}

//按顺序打印数据
void BSTree::Sort_Print()
{
	BST::Sort_Print(tree);
	cout << endl;
}
//按顺序打印数据
void BST::Sort_Print(BSTNode*& t)
{
	if (t)
	{
		Sort_Print(t->lChild);
		cout << t->data << " ";
		Sort_Print(t->rChild);

	}//if
}

//非递归后续遍历
void BSTree::post_traverse()
{
	stack<stacknode> s;
	BSTNode* t = tree;
	BSTNode* p;
	stacknode snode;
	snode.ptr = t;
	snode.flag = 0;
	s.push(snode);
	while (!s.empty())
	{
		while (t && t->lChild)
		{
			snode.ptr = t->lChild;
			snode.flag = 0;
			s.push(snode);
			t = t->lChild;
		}
		
		snode = s.top();
		s.pop();
		p = snode.ptr;
		if (snode.flag == 0 && p->rChild)
		{
			snode.flag = 1;
			s.push(snode);
			t = p->rChild;
			snode.flag = 0;
			snode.ptr = t;
			s.push(snode);
		}
		else
			cout << p->data << " ";
		/*if (snode.flag == 1)
		{
			cout << p->data << " ";
		}
		else
		{
			if (p->rChild)
			{
				snode.flag = 1;
				s.push(snode);
				t = p->rChild;
				snode.flag = 0;
				snode.ptr = t;
				s.push(snode);
			}
			else
				cout << p->data << " ";
		}*/
	}//while
	cout << endl;
}

//查找数据
Status BSTree::Search(const ElemType& data, BSTNode*& p)
{
	return BST::Search(tree, data, p);
}
//查找数据
Status BST::Search(BSTNode*& t, const ElemType& data, BSTNode*& p)
{
	if (!t)
	{
		p = nullptr;
		return FALSE;
	}

	if (t->data == data)
	{
		p = t;
		return TRUE;
	}
	else if (data < t->data)
	{
		return Search(t->lChild, data, p);
	}
	else
	{
		return Search(t->rChild, data, p);
	}
}

//删除数据
Status BSTree::RemoveData(const ElemType& data)
{
	return BST::RemoveData(tree, data);
}
//删除数据
Status BST::RemoveData(BSTNode*& t, const ElemType& data)
{
	if (!t) return FALSE;  //空树

	if (data < t->data)    //在左子树删除
		return RemoveData(t->lChild, data);
	else if (data > t->data)    //在右子树删除
		return RemoveData(t->rChild, data);
	else      //当前节点就是要删除的
	{
		BSTNode* p;
		if (t->lChild && t->rChild)   //左右子树都不为空
		{
			p = t->rChild;
			while (p->lChild)    //找右子树的最小值 
				p = p->lChild;

			t->data = p->data;
			return RemoveData(t->rChild, p->data);
		}
		else       //左右子树至少一个为空
		{
			p = t;
			if (t->lChild)   //t的左子树非空
				t = t->lChild;
			else    //t的左子树为空
				t = t->rChild;
			
			delete p;
			p = nullptr;
			return TRUE;
		}
	}//else
}

//删除节点，释放资源
void BST::DeleteNode(BSTNode*& tree)
{
	if (tree)   //二叉树非空，删除节点
	{
		DeleteNode(tree->lChild);
		DeleteNode(tree->rChild);
		delete tree;
		tree = nullptr;
	}
}
BSTree::~BSTree()
{
	BST::DeleteNode(tree);
}