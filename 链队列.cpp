#include<iostream>
#include<cassert>
#include"链队列.h"
using namespace std;

void menu()
{
	cout << "*********************************" << endl;
	cout << "*  [1] push        [2] pop      *" << endl;
	cout << "*  [3] traverse    [4] getFront *" << endl;
	cout << "*  [0] exit                     *" << endl;
	cout << "*********************************" << endl;
}

LinkQueue::LinkQueue() :size(0)
{
	back = head = new Node;
	assert(head != nullptr);    //断言头结点开辟成功,不成功终止程序

	head->next = nullptr;
}

Status LinkQueue::push(const ElemType& elem)
{
	Node* p = new Node;
	if (!p)
		return ERROR;

	p->data = elem;
	p->next = back->next;
	back->next = p;
	back = p;
	size++;
	return OK;
}

Status LinkQueue::pop(ElemType& elem)
{
	if (empty())
		return ERROR;

	Node* p = head->next;   //p指向对头元素
	elem = p->data;
	head->next = p->next;
	delete p;
	size--;
	if (size == 0) back = head;
	return OK;
}

void LinkQueue::clear()
{
	if (head->next)    
	{
		Node* p;
		while (head->next)  //从对头到队尾一个一个释放节点
		{
			p = head->next;
			head->next = p->next;
			delete p;
		}
		back = head;   //像初始化一样，back指向头结点
		head->next = nullptr;
		size = 0;
	}
}

Status LinkQueue::getHead(ElemType& e)
{
	if (!head->next)
		return ERROR;

	e = head->next->data;
	return OK;
}

Status LinkQueue::traverse()    //遍历队列并输出数据
{
	Node* p = head->next;
	while (p)
	{
		cout << p->data << "->";
		p = p->next;
	}
	cout << "Nul." << endl;
	return OK;
}

bool LinkQueue::empty()
{
	return size == 0;
}

LinkQueue::~LinkQueue()
{
	clear();    //释放元素节点
	delete head;
}