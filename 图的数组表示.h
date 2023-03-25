#pragma once

#include<iostream>
#include<cassert>
#include<iomanip>
using namespace std;

#define INFINITE INT_MAX      //无穷大
#define MAX_VERTEX  20       //假设最多10行10列

typedef enum { DG, DN, UDG, UDN } GraphKind;    //有向图，有向网，无向图，无向网
typedef char T;

struct edge    //克鲁斯克最小生成树用，一个edge表示图上的边,x,y是边的两个顶点的下标，cost是权重
{
	int x;
	int y;
	int cost; 
};

class MGraph   //图的邻接存储表示
{
public:
	MGraph();

	//打印邻接矩阵
	void PrintGraph();

	//插入顶点
	void InsertVex(const T vex);

	//插入边
	void InsertEdge(const T v1, const T v2, const int& cost); 

	//删除边
	void RemoveEdge(const T v1, const T v2);

	//删除顶点
	void RemoveVex(const T vex);

	//普里姆最小生成树
	void prim_MST(const T& vex);

	//克鲁斯克最小生成树
	void kruscal_MST();

	//关键路径
	void CriticalPath();

	//从指定顶点到其余各顶点的最短路径
	void ShortestPath(const T& vex, int* path, int* dist);

	//深度优先遍历,从vex顶点开始
	void DFTraverse(const T vex);  
	void DFS(const T vex, bool visit[]);

private:
	int vexnum;  //顶点数量
	int edgenum;  //边数
	T vexs[MAX_VERTEX];   //存储节点的数组
	int edges[MAX_VERTEX][MAX_VERTEX];  //邻接矩阵
};

namespace graph
{
	//获取顶点在的下标位置
	void GetVexIndex(const T* vexs, const int n, const T& vex, int& index);

	//获取第一个邻接顶点
	void GetFirstNeighbor(const int edges[][MAX_VERTEX], const T* vexs,int vexnum, const T vex, T& neighborvex);
	//获取第一个邻接顶点的索引
	void GetFirstNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T vex, int& index);

	//获取v1关于v2的下一个邻接顶点
	void GetNextNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T v1, const T v2, T& nextneighborvex);
	//获取v1关于v2的下一个邻接顶点的索引
	void GetNextNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T v1, const T v2, int& index);

	//获取两顶点间的权重
	int getWeight(int edges[][MAX_VERTEX], int& index1, int& index2);

	//比较函数
	int comp(const void* p1, const void* p2);

	//判断是否成环
	bool circle(int* father, int i, int j);
	//标记同一个连通子图
	void mark(int* father, int i, int j, int n);
}