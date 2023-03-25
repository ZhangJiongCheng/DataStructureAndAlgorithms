#include<iostream>
#include<cassert>
#include"顺序栈.h"
using namespace std;

void menu()
{
	cout << "*******************************" << endl;
	cout << "*  [1] push        [2] pop    *" << endl;
	cout << "*  [3] traverse    [4] getTop *" << endl;
	//cout << "*  [5] length      [6] clear  *" << endl;
	cout << "*  [0] exit                   *" << endl;
	cout << "*******************************" << endl;
}

SqStack::SqStack()
{
	base = top = new ElemType[INIT_SIZE];
	assert(base != nullptr);
	size = 0;
	capacity = INIT_SIZE;
}

void SqStack::clear()
{
	size = 0;
	top = base;
	cout << "栈已被清空!" << endl;
}

bool SqStack::empty()
{
	return size == 0;
}

bool SqStack::isfull()
{
	return size == capacity;
}

bool SqStack::increase()
{
	ElemType* newbase = (ElemType*)realloc(base, sizeof(ElemType) * (capacity + INC_SIZE));
	if (!newbase)
	{
		cout << "内存不足，无法申请空间！" << endl;
		return false;
	}
	base = newbase;
	top = base + size;   
	capacity += INC_SIZE;
	return true;
}

void SqStack::length()
{
	cout << "栈的长度为" << size << endl;
}

void SqStack::getTop(ElemType& elem)
{
	if (size == 0)
	{
		cout << "栈已空，没有栈顶元素!" << endl;
		return;
	}
	cout << "栈顶元素为" << *(top - 1) << endl;   //top指向尾后位置
}

//void SqStack::push()
//{
//
//	ElemType elem;
//	cout << "请输入想要进栈的数据(-1结束):";
//	while (cin >> elem, elem != -1)
//	{
//		if (isfull() && !increase())
//		{
//			cout << "栈空间已满，" << elem << "不能入栈!" << endl;
//			return;
//		}
//
//		base[size] = elem;
//		size++;
//		top++;
//	}
//	cout << "数据入栈成功!" << endl;
//}
//
//void SqStack::pop()
//{
//	if (empty())
//	{
//		cout << "栈已空，无元素可出栈!" << endl;
//		return;
//	}
//	ElemType elem;
//	elem = *--top;   //top指向尾后位置
//	size--; 
//	cout << elem << "已经出栈" << endl;
//}

void SqStack::push(const ElemType& elem)
{
	if (isfull() && !increase())
	{
		cout << "栈空间已满，" << elem << "不能入栈!" << endl;
		return;
	}

	base[size] = elem;
	size++;
	top++;
}

void SqStack::pop(ElemType& elem)
{
	if (empty()) 	return;
	
	elem = *--top;   //top指向尾后位置
	size--;
}

void SqStack::traverse()  //遍历输出
{
	for (int i = 0; i < size; i++)
		cout << base[i] << "->";
	cout << "Nul." << endl;
}

SqStack::~SqStack()
{
	if (base)
	{
		delete [] base;
		base = top = nullptr;
	}
	
}