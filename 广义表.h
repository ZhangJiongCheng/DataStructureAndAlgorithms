#pragma once
#include<iostream>
#include<cassert>
#include<string>
using namespace std;

typedef enum{ATOM,LIST} ElemTag; //ATOM表示原子，LIST表示字表

typedef int ElemType;

struct GLNode
{
	ElemTag tag;    //节点标志
	union
	{
		ElemType atom;   //原子节点的值
		GLNode* hp;       //表节点的头指针
	};
	GLNode* tp;    //相当于next,指向下一个元素节点
};

class GList
{
public:
	GList();

	//创建广义表
	void CreateGList(string& s);

	void print();   //打印广义表的内容
	
	bool empty();

	int length();

	int depth();
	
	void getHead(string& s);   //获取表头

	void getTail(string& s);  //获取表尾

	~GList();

private:
	GLNode* list;    //广义表的头结点
	string strlist;   //广义表的字符串表示
};

namespace help
{
	void CreateGList(GLNode*& list, string& s);
	bool separate(string& sub, string& hsub);  //分离表头表尾
	void DeleteGList(GLNode*& p);  //由析构函数调用，回收资源
	void print(GLNode* p);   //打印广义表的内容
	int depth(GLNode*& p);
}