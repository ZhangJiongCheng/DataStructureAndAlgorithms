#pragma once

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#define OVERFLOW -2 
typedef int Status;   //��������ֵ����

typedef char ElemType;  //Ԫ������

struct Node     //Ԫ�ؽڵ�
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
	Node* head;  //ָ��ͷ���
	Node* back;   //ָ��βԪ��
	size_t size;  //Ԫ�ظ���
};

void menu();
