#pragma once
#include<iostream>
#include<cassert>
#include<string>
using namespace std;

typedef enum{ATOM,LIST} ElemTag; //ATOM��ʾԭ�ӣ�LIST��ʾ�ֱ�

typedef int ElemType;

struct GLNode
{
	ElemTag tag;    //�ڵ��־
	union
	{
		ElemType atom;   //ԭ�ӽڵ��ֵ
		GLNode* hp;       //��ڵ��ͷָ��
	};
	GLNode* tp;    //�൱��next,ָ����һ��Ԫ�ؽڵ�
};

class GList
{
public:
	GList();

	//���������
	void CreateGList(string& s);

	void print();   //��ӡ����������
	
	bool empty();

	int length();

	int depth();
	
	void getHead(string& s);   //��ȡ��ͷ

	void getTail(string& s);  //��ȡ��β

	~GList();

private:
	GLNode* list;    //������ͷ���
	string strlist;   //�������ַ�����ʾ
};

namespace help
{
	void CreateGList(GLNode*& list, string& s);
	bool separate(string& sub, string& hsub);  //�����ͷ��β
	void DeleteGList(GLNode*& p);  //�������������ã�������Դ
	void print(GLNode* p);   //��ӡ����������
	int depth(GLNode*& p);
}