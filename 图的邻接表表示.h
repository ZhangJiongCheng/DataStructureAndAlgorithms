#pragma once

#define MAX_VEX 20    //最大顶点个数

#include<iostream>
#include<cassert>
using namespace std;

typedef char T;    //顶点元素类型
 
struct ANode   //邻接顶点节点
{
	int index;   //邻接顶点的下标
	ANode* next;   //下一个邻接顶点
};

struct VNode  //顶点节点
{
	T data;     //顶点的数据
	ANode* first;   //顶点的第一个邻接顶点
}; 

class AGraph
{
public:
	AGraph();

	//插入顶点
	void InsertVex(const T vex);

	//插入边
	void InsertEdge(const T v1, const T v2);

	//打印图
	void PrintGraph();

	//删除顶点
	void RemoveVex(const T vex);
	 
	//删除边
	void RemoveEdge(const T v1, const T v2);

	//深度优先遍历
	void DFTraverse(const T vex);
	
	//广度优先遍历
	void BFTraverse(const T vex);
	
	//遍历全图
	void ComponentTraverse();

	//拓扑排序AOV
	void TopoSort();

	~AGraph();

private:
	int vexnum;   //顶点个数
	int edgenum; //边数
	VNode vexs[MAX_VEX];   //顶点数组
};

namespace Agraph
{
	//获取顶点的索引
	void GetVexIndex(const VNode* vexs, const int& vexnum, const T& vex, int& index);

	//获取第一个邻接顶点
	void GetFirstNeighbor(const VNode* vexs, const int& vexnum, const T vex, T& neighborvex);
	//获取第一个邻接顶点的索引
	void GetFirstNeighbor(const VNode* vexs, const int& vexnum, const T vex, int& index);

	//获取v1关于v2的下一个邻接顶点
	void GetNextNeighbor(const VNode* vexs, const int& vexnum, const T v1, const T v2, T& nextneighborvex);
	//获取v1关于v2的下一个邻接顶点的索引
	void GetNextNeighbor(const VNode* vexs, const int& vexnum, const T v1, const T v2, int& index);

	//深度优先遍历
	void DFS(const VNode* vexs, const int& vexnum, const T& vex, bool visit[]);

	//广度优先遍历
	void BFS(const VNode* vexs, const int& vexnum, const T& vex, bool visit[]);
}