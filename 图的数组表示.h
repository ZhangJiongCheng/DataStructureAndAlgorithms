#pragma once

#include<iostream>
#include<cassert>
#include<iomanip>
using namespace std;

#define INFINITE INT_MAX      //�����
#define MAX_VERTEX  20       //�������10��10��

typedef enum { DG, DN, UDG, UDN } GraphKind;    //����ͼ��������������ͼ��������
typedef char T;

struct edge    //��³˹����С�������ã�һ��edge��ʾͼ�ϵı�,x,y�Ǳߵ�����������±꣬cost��Ȩ��
{
	int x;
	int y;
	int cost; 
};

class MGraph   //ͼ���ڽӴ洢��ʾ
{
public:
	MGraph();

	//��ӡ�ڽӾ���
	void PrintGraph();

	//���붥��
	void InsertVex(const T vex);

	//�����
	void InsertEdge(const T v1, const T v2, const int& cost); 

	//ɾ����
	void RemoveEdge(const T v1, const T v2);

	//ɾ������
	void RemoveVex(const T vex);

	//����ķ��С������
	void prim_MST(const T& vex);

	//��³˹����С������
	void kruscal_MST();

	//�ؼ�·��
	void CriticalPath();

	//��ָ�����㵽�������������·��
	void ShortestPath(const T& vex, int* path, int* dist);

	//������ȱ���,��vex���㿪ʼ
	void DFTraverse(const T vex);  
	void DFS(const T vex, bool visit[]);

private:
	int vexnum;  //��������
	int edgenum;  //����
	T vexs[MAX_VERTEX];   //�洢�ڵ������
	int edges[MAX_VERTEX][MAX_VERTEX];  //�ڽӾ���
};

namespace graph
{
	//��ȡ�����ڵ��±�λ��
	void GetVexIndex(const T* vexs, const int n, const T& vex, int& index);

	//��ȡ��һ���ڽӶ���
	void GetFirstNeighbor(const int edges[][MAX_VERTEX], const T* vexs,int vexnum, const T vex, T& neighborvex);
	//��ȡ��һ���ڽӶ��������
	void GetFirstNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T vex, int& index);

	//��ȡv1����v2����һ���ڽӶ���
	void GetNextNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T v1, const T v2, T& nextneighborvex);
	//��ȡv1����v2����һ���ڽӶ��������
	void GetNextNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T v1, const T v2, int& index);

	//��ȡ��������Ȩ��
	int getWeight(int edges[][MAX_VERTEX], int& index1, int& index2);

	//�ȽϺ���
	int comp(const void* p1, const void* p2);

	//�ж��Ƿ�ɻ�
	bool circle(int* father, int i, int j);
	//���ͬһ����ͨ��ͼ
	void mark(int* father, int i, int j, int n);
}