#pragma once


#define INIT_SIZE 100   //ջ�洢�ռ�ĳ�ʼ������
#define INC_SIZE 10      //ջ�洢�ռ�ķ�������
typedef int ElemType;     //ջ�洢��Ԫ������


struct SqStack
{
	SqStack();    //���캯����ʼ��ջ

	void clear(); //���ջ

	bool empty(); //�п�

	bool isfull();  //����

	bool increase();  //����capacity

	void length();  //�󳤶�

	void getTop(ElemType& elem); //ȡջ��Ԫ�أ�����ջ

	void push(const ElemType& elem);  //ѹջ

	void pop(ElemType& elem);  //��ջ����ջ��Ԫ�ش���ȥ

	void traverse();  //����ջ����ӡջ������

	~SqStack();  //���������ͷ���Դ

private:
	ElemType* base;  //ջ��ָ��
	ElemType* top;  //ջ��ָ��
	size_t size;    //ջ��Ԫ�ظ���
	size_t capacity;  //ջ������
};

void menu();
