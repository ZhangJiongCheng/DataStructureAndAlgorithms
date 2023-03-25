#pragma once

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#define OVERFLOW -2 
typedef int Status;   //函数返回值类型

typedef char ElemType;  //元素类型

struct Node     //元素节点
{
	ElemType data;
	Node* next;
};

class LinkQueue
{
public:
	LinkQueue();

	Status push(const ElemType& elem);

	Status pop(ElemType& elem);

	Status getHead(ElemType& e);

	Status traverse();

	bool empty();

	void clear();
	~LinkQueue();

private:
	Node* head;  //指向头结点
	Node* back;   //指向尾元素
	size_t size;  //元素个数
};

void menu();
