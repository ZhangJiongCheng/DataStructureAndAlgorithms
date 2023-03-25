#include <iostream>
#include<deque>
#include"线性表之顺序实现.h"
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

void push_back(deque<ElemType>& mylist)
{
	ElemType item;
	cout << "请输入想要插入的数据(00结束):";
	while (cin >> item, item != 00)
		mylist.emplace_back(item);       //emplace原地拷贝插入，比push的效率更高
	cout << "添加数据成功！" << endl;
}

void push_front(deque<ElemType>& mylist)
{
	ElemType item;
	cout << "请输入想要插入的数据(0结束):";
	while (cin >> item, item != 0)
		mylist.emplace_front(item);
	cout << "添加数据成功！" << endl;
}

void pop_back(deque<ElemType>& mylist)
{
	if (mylist.size() != 0)
	{
		mylist.pop_back();
		cout << "删除数据成功！" << endl;
	}
	else
	{
		cout << "表已空，无数据可删除！" << endl;
	}
}

void pop_front(deque<ElemType>& mylist)
{
	if (mylist.size() != 0)
	{
		mylist.pop_front();
		cout << "删除数据成功！" << endl;
	}
	else
	{
		cout << "表已空，无数据可删除！" << endl;
	}
}

void showList(deque<ElemType>& mylist)
{
	for (const auto& elem : mylist)
	{
		cout << elem << "->";
	}
	cout << "Nul." << endl;
}

void insert_pos(deque<ElemType>& mylist)
{
	ElemType item;
	int pos;
	cout << "请输入想插入的位置:";
	while (1)
	{
		cin >> pos;      //插入数据的位置，非下标
		if (pos<=0 || pos>mylist.size())
			cout << "插入的位置非法，请重新输入:";
		else
			break;
	}
	cout << "请输入想插入的数据:";
	cin >> item;
	mylist.emplace(mylist.cbegin() + pos - 1, item);    //下标从0开始，位置从1开始 所以+pos-1	
	cout << "添加数据成功！" << endl;
}

void insert_val(deque<ElemType>& mylist)
{
	//按值插入，不管有没有排序，都从头开始遍历容器，找到第一个大于等于item(要插入的数据)的数据，在其前面插入
	ElemType item;
	cout << "请输入想插入的数据:";
	cin >> item;

	deque<ElemType>::const_iterator it;
	for (it = mylist.cbegin(); it != mylist.cend(); it++)
		if (*it >= item) break;
	mylist.emplace(it, item);
	cout << "添加数据成功！" << endl;
}

void find(deque<ElemType>& mylist)
{
	ElemType item;
	cout << "请输入想查找的数据:";
	cin >> item;
	//利用标准库的算法查找
	auto it = find(mylist.cbegin(), mylist.cend(), item);    //返回指向第一个匹配的值的迭代器
	if (it != mylist.end())
		cout << "查找的数据" << item << "位于表中第" << it - mylist.cbegin() + 1 << "个位置." << endl;
	else
		cout << "查找的数据" << item << "在表中不存在." << endl;
}

void delete_val(deque<ElemType>& mylist)
{
	ElemType item;
	cout << "请输入想删除的数据:";
	cin >> item;

	deque<ElemType>::const_iterator it;
	for (it = mylist.cbegin(); it != mylist.cend(); it++)
		if (*it == item) break;

	if (it != mylist.cend())    //要删除的数据存在表中
	{
		mylist.erase(it);
		cout << "删除数据成功！" << endl;
	}
	else   //表中不存在要删除的数据
		cout << "要删除的数据" << item << "在表中不存在." << endl;
}

void delete_pos(deque<ElemType>& mylist)
{
	int pos;
	cout << "您想删除第几个位置的数据:";
	while (1)
	{
		cin >> pos;   //插入数据的位置，非下标
		if (pos<0 || pos>mylist.size())
			cout << "删除的位置非法，请重新输入:";
		else
			break;
	}
	ElemType val = *(mylist.cbegin() + pos - 1);     //记下要删除的位置的值
	mylist.erase(mylist.cbegin() + pos - 1);
	cout << "表中第" << pos << "个数据" << val << "已被删除." << endl;
}
