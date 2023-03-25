#pragma once
#include<list>
using namespace std;

typedef int ElemType;      //‘™Àÿ¿‡–Õ

struct LinkList
{
	void push_back();
	void push_front();
	void pop_back();
	void pop_front();

	void showList();

	void insert_pos();
	void insert_val();

	void find();
	void length();
	void clearList();

	void delete_val();
	void delete_pos();

	void sort();
	void reverse();

private:
	list<ElemType> mylist;
};

void menu();
