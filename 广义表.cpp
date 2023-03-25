//#include<iostream>
#include"广义表.h"
//using namespace std;

GList::GList()
{

	list = new GLNode;
	assert(list != nullptr);
	list->hp = list->tp = nullptr;
	list->tag = LIST;   //头结点的标志一定为LIST

}

//创建广义表
//无论广义表长什么样，都将其看成两部分，一部分是表头，另一部分是表尾
void GList::CreateGList(string& s)
{
	strlist = s;   //保存广义表的字符串形式
	help::CreateGList(list, s);
}

void help::CreateGList(GLNode*& list, string& s)
{
	//先将s最外层的括号脱去
	string hsub;    //广义表的表头
	int n = s.length();
	string sub = s.substr(1, n - 2);   //s脱去最外层的括号

	GLNode* p = list;
	GLNode* q;
	bool flag = true;  //flag==true，说明p为头结点，得让头结点的hp连接下一个节点
	while (sub.length() != 0)
	{
		q = new GLNode;
		assert(q != nullptr);
		q->hp = q->tp = nullptr;
		q->tag = ATOM;
		if (flag)
		{
			p->hp = q;
			flag = false;
		}
		else
			p->tp = q;

		if (separate(sub, hsub))
		{
			if (hsub[0] == '(')
			{
				q->tag = LIST;
				CreateGList(q, hsub);
			}
			else
			{
				q->tag = ATOM;
				q->atom = atoi(hsub.c_str());
			}
			p = q;
		}
	}
}

bool help::separate(string& sub, string& hsub)
{
	if (sub.length() == 0)
		return true;

	//将sub的表头分离到hsub,sub本身的内容为分离表头之后剩余的部分
	int i = 0;
	char ch = sub[0];
	int k = 0;   //k>0,表示有（，k<0,表示有),分离处的逗号应该不在括号内
	int n = sub.length();

	while (i < n && !(ch == ',' && k == 0))   //(ch == ',' && k == 0)表示该逗号是分隔点，加上！表示不是分割点
	{
		if (ch == '(')
			++k;
		else if (ch == ')')
			--k;

		++i;
		ch = sub[i];
	}

	if (i < n)
	{
		hsub = sub.substr(0, i);
		sub = sub.substr(i + 1, n - i - 1);
	}
	else if (k != 0)
		return false;
	else
	{
		hsub = sub;
		sub = "";
	}
	return true;
}

void GList::print()
{
	help::print(list->hp);
}

void help::print(GLNode* p)
{
	cout << "(";
	while (p)
	{
		if (p->tag == ATOM && p->tp)
		{
			cout << p->atom << ",";
		}
		else if (p->tag == ATOM)
		{
			cout << p->atom;
		}
		else if (p->tag == LIST && p->tp)
		{
			print(p->hp);
			cout << ",";
		}
		else
		{
			print(p->hp);
		}
		p = p->tp;
			
	}//while
	cout << ")";
}

bool GList::empty()
{
	if (list->hp)
		return false;
	return true;
}

int GList::length()
{
	GLNode* p = list->hp;
	int len = 0;
	while (p)
	{
		++len;
		p = p->tp;
	}
	return len;
}

int GList::depth()
{
	return help::depth(list);
}

int help::depth(GLNode*& p)
{
	if (!p->hp) return 1;

	GLNode* q = p->hp;
	int maxdepth = 0;

	int dep;
	while (q)
	{
		if (q->tag == LIST)
		{
			dep = depth(q);
			if (dep > maxdepth)
				maxdepth = dep;
		}
		q = q->tp;
	}
	return maxdepth+1;
}

void GList::getHead(string& s)   //获取表头
{
	if (!list->hp)
		s = "";
	else //表不为空
	{
		int n = strlist.length();
		string sub = strlist.substr(1, n - 2);
		help::separate(sub, s);
	}
}

void GList::getTail(string& s)  //获取表尾
{
	if (!list->hp)
		s = "";
	else
	{
		int n = strlist.length();
		string sub = strlist.substr(1, n - 2);
		help::separate(sub, s);
		s = sub;
	}
}

GList::~GList()
{
	help::DeleteGList(list);
}

void help::DeleteGList(GLNode*& p)
{

	if (p)
	{
		if (p->tag == LIST)    //因为hp和atom用了联合体，所以即使节点是原子节点，hp也不为nullptr,会导致错误，
			//因此，得满足p->tag == LIST && p->hp这个条件才能删除hp,后又发现p->hp无论如何一定不为空
		{

			DeleteGList(p->hp);
		}
		DeleteGList(p->tp);
		delete p;
	}

}