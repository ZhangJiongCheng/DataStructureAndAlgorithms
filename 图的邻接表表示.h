#pragma once

#define MAX_VEX 20    //��󶥵����

#include<iostream>
#include<cassert>
using namespace std;

typedef char T;    //����Ԫ������
 
struct ANode   //�ڽӶ���ڵ�
{
	int index;   //�ڽӶ�����±�
	ANode* next;   //��һ���ڽӶ���
};

struct VNode  //����ڵ�
{
	T data;     //���������
	ANode* first;   //����ĵ�һ���ڽӶ���
}; 

class AGraph
{
public:
	AGraph();

	//���붥��
	void InsertVex(const T vex);

	//�����
	void InsertEdge(const T v1, const T v2);

	//��ӡͼ
	void PrintGraph();

	//ɾ������
	void RemoveVex(const T vex);
	 
	//ɾ����
	void RemoveEdge(const T v1, const T v2);

	//������ȱ���
	void DFTraverse(const T vex);
	
	//������ȱ���
	void BFTraverse(const T vex);
	
	//����ȫͼ
	void ComponentTraverse();

	//��������AOV
	void TopoSort();

	~AGraph();

private:
	int vexnum;   //�������
	int edgenum; //����
	VNode vexs[MAX_VEX];   //��������
};

namespace Agraph
{
	//��ȡ���������
	void GetVexIndex(const VNode* vexs, const int& vexnum, const T& vex, int& index);

	//��ȡ��һ���ڽӶ���
	void GetFirstNeighbor(const VNode* vexs, const int& vexnum, const T vex, T& neighborvex);
	//��ȡ��һ���ڽӶ��������
	void GetFirstNeighbor(const VNode* vexs, const int& vexnum, const T vex, int& index);

	//��ȡv1����v2����һ���ڽӶ���
	void GetNextNeighbor(const VNode* vexs, const int& vexnum, const T v1, const T v2, T& nextneighborvex);
	//��ȡv1����v2����һ���ڽӶ��������
	void GetNextNeighbor(const VNode* vexs, const int& vexnum, const T v1, const T v2, int& index);

	//������ȱ���
	void DFS(const VNode* vexs, const int& vexnum, const T& vex, bool visit[]);

	//������ȱ���
	void BFS(const VNode* vexs, const int& vexnum, const T& vex, bool visit[]);
}