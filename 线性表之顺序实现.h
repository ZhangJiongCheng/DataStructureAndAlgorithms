#pragma once

#include<deque>
#include<iostream>
using namespace std;

typedef int ElemType;    //顺序表元素类型

void menu();

void push_back(deque<ElemType>& mylist);
void push_front(deque<ElemType>& mylist);

void pop_back(deque<ElemType>& mylist);
void pop_front(deque<ElemType>& mylist);

void showList(deque<ElemType>& mylist);

void insert_pos(deque<ElemType>& mylist);
void insert_val(deque<ElemType>& mylist);

void find(deque<ElemType>& mylist);

void delete_val(deque<ElemType>& mylist);
void delete_pos(deque<ElemType>& mylist);
