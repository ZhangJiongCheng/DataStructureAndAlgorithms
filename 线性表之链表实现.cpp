#include<iostream>
#include<list>
#include<algorithm>
#include"线性表之链表实现.h"
using namespace std;

void menu()
{
	cout << "*********************************************" << endl;
	cout << "*   [1]  push_back        [2]  push_front   *" << endl;
	cout << "*   [3]  pop_back         [4]  pop_front    *" << endl;
	cout << "*   [5]  showList         [6]  insert_pos   *" << endl;
	cout << "*   [7]  insert_val       [8]  find         *" << endl;
	cout << "*   [9]  length           [10] clearList    *" << endl;
	cout << "*   [11] delete_val       [12] delete_pos   *" << endl;
	cout << "*   [13] reverse          [14] sort         *" << endl;
	cout << "*   [0] exit                                *" << endl;
	cout << "*********************************************" << endl;

}

void LinkList::push_back()
{
	ElemType item;
	cout << "请输入想插入的数据(0结束插入):";
	while (cin >> item, item != 0)
	{
		mylist.emplace_back(item);
	}
	cout << "添加数据成功！" << endl;
}

void LinkList::push_front()
{
	ElemType item;
	cout << "请输入想插入的数据(0结束插入):";
	while (cin >> item, item != 0)
	{
		mylist.emplace_front(item);
	}
	cout << "添加数据成功！" << endl;
}

void LinkList::pop_back()
{
	if (!mylist.empty())
	{
		mylist.pop_back();
		cout << "删除数据成功!" << endl;
	}
	else
	{
		cout << "表已空，无数据可删除!" << endl;
	}
}

void LinkList::pop_front()
{
	if (!mylist.empty())
	{
		mylist.pop_front();
		cout << "删除数据成功!" << endl;
	}
	else
	{
		cout << "表已空，无数据可删除!" << endl;
	}
}

void LinkList::showList()
{
	copy(mylist.cbegin(), mylist.cend(), ostream_iterator<ElemType>(cout, "->"));  //标准库算法，将元素输出到cout
	cout << "Nul." << endl;
}

void LinkList::insert_pos()
{
	int pos;
	ElemType item;
	cout << "请输入要插入的位置:";
	while (1)     //检查插入位置的合法性
	{
		cin >> pos;
		if (pos <= 0 || pos > mylist.size()+1)    //pos=size+1相当于尾插，pos=1相当于头插
			cout << "插入的位置非法，请重新输入:";
		else
			break;
	}
	cout << "请输入要插入的数据:";
	cin >> item;

	list<ElemType>::const_iterator it;
	int i;
	for (it = mylist.cbegin(), i = 1; i < pos; it++, i++);    //循环结束，it就指向要插入的位置
	mylist.emplace(it, item);
	cout << "插入数据成功！" << endl;
}

void LinkList::insert_val()
{
	//无论表是否已排序，都将item插入到第一个大于等于item的值之前
	ElemType item;
	cout << "请输入要插入的值:";
	cin >> item;
	
	//查找插入位置,将item插入到第一个大于等于item的值之前
	mylist.emplace(std::find_if(mylist.begin(), mylist.end(), [item](ElemType i) {return i >= item; }), item);
	cout << "插入数据成功！" << endl;
}

void LinkList::find()
{
	ElemType item;
	cout << "请输入要查找的值:";
	cin >> item;

	auto it = std::find(mylist.begin(), mylist.end(), item);
	int pos = 1;
	for (auto temp = mylist.cbegin(); temp != it; pos++, temp++);
	if (it != mylist.end())  //查找的值在表中存在
	{
		cout << "查找的数据" << item << "位于表中第" << pos << "个位置." << endl;
	}
	else
	{
		cout << "查找的数据" << item << "在表中不存在." << endl;
	}
}

void LinkList::length()
{
	cout << "表中一共有" << mylist.size() << "个数据." << endl;
}

void LinkList::clearList()
{
	mylist.clear();
	cout << "表已被清空!" << endl;
}

void LinkList::delete_val()
{
	//删除所有值为item的数据
	ElemType item;
	cout << "请输入要删除的值:";
	cin >> item;

	auto it = std::find(mylist.cbegin(), mylist.cend(), item);
	if (it != mylist.cend())  //表中存在要删除的值
	{
		mylist.remove(item);
		cout << "所有值为" << item << "的数据都已被删除！" << endl;
	}
	else
	{
		cout << "要删除的数据在表中不存在！" << endl;
	}
}

void LinkList::delete_pos()
{
	int pos;
	cout << "您想删除第几个数据:";
	while (1)//检查位置的合法性
	{
		cin >> pos;
		if (pos <= 0 || pos > mylist.size())
		{
			cout << "删除的位置非法，请重新输入:";
		}
		else
			break;
	}
	
	int i = 1;
	list<ElemType>::const_iterator it;
	for (it = mylist.cbegin(); i < pos; it++, i++);   //循环结束， it指向要删除的数据的位置
	ElemType elem = *it;      //保存要删除的数据
	mylist.erase(it);
	cout << "表中第" << pos << "个数据" << elem << "已被删除!" << endl;
}

void LinkList::reverse()
{
	mylist.reverse();
	cout << "数据逆序成功！" << endl;
}

void LinkList::sort()
{
	mylist.sort();
	cout << "排序完成!" << endl;
}