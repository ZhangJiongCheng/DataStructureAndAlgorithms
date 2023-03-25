#include"二叉平衡树.h"

//插入数据
void AVLTree::Insert(const DataType& data)
{
	AVLNode* p = root;
	AVLNode* parent = nullptr;
	stack<AVLNode*> mystack;
	while (p)
	{
		if (data == p->data)
			return;

		parent = p;
		mystack.push(parent);
		if (data < p->data)
			p = p->lChild;
		else
			p = p->rChild;
	}//while
	BTree::buyNode(data, p);    //开辟节点
	if (!parent)    //p为根节点
	{
		root = p;
		return;
	}
	if (data < parent->data)
		parent->lChild = p;
	else
		parent->rChild = p;

	while (!mystack.empty())
	{
		parent = mystack.top();
		mystack.pop();
		if (parent->lChild == p)
			parent->bf++;
		else
			parent->bf--;

		if (parent->bf == 0)   //平衡
			break;
		else if (parent->bf == -1 || parent->bf == 1)  //不确定是否平衡，回溯
			p = parent;
		else   //不平衡，旋转调整
		{
			int flag = (parent->bf < 0) ? -1 : 1;
			if (p->bf == flag)   //p和parent的bf同号，单旋转
			{
				if (flag == 1)     // 形态:/
					BTree::RotateR(parent);   //右旋转
				else                 /*   形态:\    */
					BTree::RotateL(parent);        //左旋转
			}//if 
			else    //异号，双旋转
			{
				if (flag == 1)     // 形态:<
					BTree::RotateLR(parent);  //先左后右旋转
				else             // 形态:>
					BTree::RotateRL(parent); //先右后左旋转
			}//else
			break;     //调整完跳出循环
		}//else
	}//while

	if (mystack.empty())     //修改的节点是根节点
		root = parent;
	else        //修改的节点不是根节点
	{
		AVLNode* q = mystack.top();
		if (q->data > parent->data)  //parent是q的左子树
			q->lChild = parent;
		else      //parent是q的右子树
			q->rChild = parent;
	}
}

//删除数据
void AVLTree::Remove(const DataType& data)
{
	AVLNode* ppr = nullptr; //parent节点的父节点
	AVLNode* p = root;
	AVLNode* parent = nullptr;
	stack<AVLNode*> mystack;
	while (p)  //非空树，循环结束后p要么为空，要么指向要删除的节点
	{ 
		if (p->data == data)  //p就是要删除的节点
			break;

		parent = p;
		mystack.push(parent);   //后面进行出栈并处理bf
		if (data < p->data)
			p = p->lChild;
		else
			p = p->rChild;
	}//while
	if (!p)   //说明是空树或者树上没有要删除的数据
		return;

	//能走到这里说明树非空且p指向要删除的节点
	AVLNode* q;
	if (p->lChild && p->rChild)
	{
		//用p的直接后继替代p，然后删除p的直接后继
		parent = p;
		mystack.push(parent);
		q = p->rChild; 
		while (q->lChild)
		{
			parent = q;
			mystack.push(parent);
			q = q->lChild;
		}
		p->data = q->data;
		p = q;
	}
	if (p->lChild)
		q = p->lChild;
	else
		q = p->rChild;
	 
	int f = 0;   //-1:q是parent的左， 1:q是parent的右
	if (!parent)  //要删除的就是根且根最多只有单子树
		root = q;       
	else    //要删除的p不是根
	{
		if (parent->lChild == p)
		{
			parent->lChild = q;
			f = -1;    
		}
		else
		{
			parent->rChild = q;
			f = 1;
		}

		//删除一个节点，路径上的所有节点都可能失衡
		while (!mystack.empty())
		{
			parent = mystack.top();
			mystack.pop();
			if (f == -1) //删除的是parent的左子树，如果用parent->lChild==q来判断，则当p为parent的右子树且q为空时会出错
				parent->bf--;
			else
				parent->bf++;

			if (!mystack.empty())
			{
				ppr = mystack.top();
				f = (ppr->lChild == parent) ? -1 : 1;
			}
			else
				f = 0;

			if (parent->bf == 1 || parent->bf == -1)  //原来parent的bf为0，现在整棵树仍然平衡
				break;
			else if (parent->bf == 0)  //原来parent的bf为1或-1，目前无法确定是否平衡，得回溯
				q = parent;
			else   //现在parent的bf为2或-2，不平衡
			{
				int flag = 0;
				//让q指向parent较高的子树
				if (parent->bf > 0)   //左高右低
				{
					q = parent->lChild;
					flag = 1;
				}
				else
				{
					q = parent->rChild;
					flag = -1;
				}
				if (q->bf == 0)   //单旋转
				{
					if (flag == 1)  //左高右低，右旋转
					{
						BTree::RotateR(parent);
						parent->bf = -1;
						parent->rChild->bf = 1;
					}
					else
					{
						BTree::RotateL(parent);
						parent->bf = 1; 
						parent->lChild->bf = -1;
					}
					if (f == -1)
						ppr->lChild = parent;
					else if (f == 1)
						ppr->rChild = parent;
					break;      //由于q->bf == 0，所以旋转后以parent为根的子树高度不变，必须break;不能回溯
				}//if(q->bf == 0)
				else if(q->bf == flag)
				{
					if (flag == -1)
						BTree::RotateL(parent);
					else
						BTree::RotateR(parent);
				}
				else
				{
					if (flag == -1)
						BTree::RotateRL(parent);
					else
						BTree::RotateLR(parent);
				}
				if (f == -1)
					ppr->lChild = parent;
				else if (f == 1)
					ppr->rChild = parent;
			}//else  parent->bf == 2或-2
		}//while
		if (mystack.empty())  //调节的就是根节点
			root = parent;
	}//else

	delete p;
}

AVLTree::~AVLTree()
{
	BTree::clear(root);
}

void BTree::clear(AVLNode*& tree)
{
	if (tree)
	{
		clear(tree->lChild);
		clear(tree->rChild);
		delete tree;
		tree = nullptr;
	}
}

void  BTree::buyNode(const DataType& data, AVLNode*& p)
{
	p = new AVLNode;
	assert(p != nullptr);
	p->data = data;
	p->bf = 0;
	p->rChild = p->lChild = nullptr;
}

//右旋转
void BTree::RotateR(AVLNode*& p)    //p->bf=2
{
	AVLNode* subR = p;
	p = subR->lChild;
	subR->lChild = p->rChild;
	p->rChild = subR;
	p->bf = subR->bf = 0;
}

//左旋转
void BTree::RotateL(AVLNode*& p)  //p->bf=2
{
	AVLNode* subL = p;
	p = subL->rChild;
	subL->rChild = p->lChild;
	p->lChild = subL;
	p->bf = subL->bf = 0;
}

//先右后左旋转
void BTree::RotateRL(AVLNode*& p)
{
	AVLNode* subL = p;
	AVLNode* subR = subL->rChild;
	p = subR->lChild;

	subR->lChild = p->rChild;
	p->rChild = subR;
	if (p->bf <= 0)
		subR->bf = 0;
	else
		subR->bf = -1;

	subL->rChild = p->lChild;
	p->lChild = subL;
	if (p->bf >= 0)
		subL->bf = 0;
	else
		subL->bf = 1;

	p->bf = 0;
}

//先左后右旋转
void BTree::RotateLR(AVLNode*& p)
{
	AVLNode* subR = p;
	AVLNode* subL = subR->lChild;
	p = subL->rChild;

	subL->rChild = p->lChild;
	p->lChild = subL;
	if (p->bf >= 0)
		subL->bf = 0;
	else
		subL->bf = 1;

	subR->lChild = p->rChild;
	p->rChild = subR;
	if (p->bf <= 0)
		subR->bf = 0;
	else
		subR->bf = -1;

	p->bf = 0;
}