#include"图的数组表示.h"

MGraph::MGraph() :vexnum(0), edgenum(0)
{
	for (int i = 0; i < MAX_VERTEX; ++i)
	{
		vexs[i] = 0;    //char类型变量为0表示不被输出的字符'\0'
		for (int j = 0; j < MAX_VERTEX; ++j)
		{
			//edges[i][j] = 0;
			if (i == j)
				edges[i][j] = 0;
			else
			    edges[i][j] = INFINITE;     //初始化是没点没边
		} 
	}
}

//打印邻接矩阵
void MGraph::PrintGraph()
{
	int i;
	int j;
	cout << "    ";
	for (i = 0; i < vexnum; ++i)
	{
		cout << vexs[i] << "  ";
	}
	cout << endl;
	for (i = 0; i < vexnum; ++i)
	{
		cout << " " << vexs[i] << "  ";
		for (j = 0; j < vexnum; ++j)
		{
			if (edges[i][j] == INFINITE)
				cout << "@  ";
			else
				cout << edges[i][j] << "  ";
		}
		cout << endl;
	}
}

//插入顶点
void MGraph::InsertVex(const T vex)
{
	if (vexnum >= MAX_VERTEX)
		return;

	vexs[vexnum] = vex;
	vexnum++;
}

//插入边
void MGraph::InsertEdge(const T v1, const T v2, const int& cost)
{
	int index1;   //表示图中不存在这个顶点
	int index2;
	graph::GetVexIndex(vexs, vexnum, v1, index1);
	graph::GetVexIndex(vexs, vexnum, v2, index2);

	if (index1 != -1 && index2 != -1)
	{
		edges[index1][index2] = cost;
		edgenum++;
	}
	
	//if (index1 != -1 && index2 != -1 && edges[index1][index2] == INFINITE)   //图中存在这两个顶点且着两个顶点之间没边
	//{
	//	edges[index1][index2] = edges[index2][index1] = cost;
	//	edgenum++;
	//}
}

//删除边
void MGraph::RemoveEdge(const T v1, const T v2)
{
	int index1;   //表示图中不存在这个顶点
	int index2;
	graph::GetVexIndex(vexs, vexnum, v1, index1);
	graph::GetVexIndex(vexs,vexnum, v2, index2);

	if (index1 != -1 && index2 != -1 && edges[index1][index2] == 1)   //图中存在这两个顶点且两个顶点之间有边
	{
		edges[index1][index2] = edges[index2][index1] = INFINITE;
		edgenum--;
	}
}

//删除顶点
void MGraph::RemoveVex(const T vex)
{
	int index;   //表示图中不存在这个顶点
	graph::GetVexIndex(vexs,vexnum,vex, index);

	int j;
	int k;

	if (index != -1)   //图中存在这个顶点
	{
		//顶点删除后边数减少,遍历i行的每一列以减少边数
		for (j = 0; j < vexnum; ++j)
		{
			if (edges[index][j] != INFINITE)   //存在边
				edgenum--;
		}
		//覆盖被删除的顶点
		for (j = index; j < vexnum - 1; ++j)
		{
			vexs[j] = vexs[j + 1];
		}
		//修改邻接矩阵，删除i行的矩阵,后面的行覆盖前面的行
		for (j = index; j < vexnum - 1; ++j)     //行 
		{
			for (k = 0; k < vexnum; ++k)     //列
			{
				edges[j][k] = edges[j + 1][k];
			}
		}
		//修改邻接矩阵，删除i列的矩阵,后面的列覆盖前面的列
		for (j = 0; j < vexnum - 1; ++j)    //行
		{
			for (k = index; k < vexnum - 1; ++k)   //列
			{
				edges[j][k] = edges[j][k + 1];
			}
		}

		vexnum--;   //顶点数减少
	}//if
}

//普里姆最小生成树
void MGraph::prim_MST(const T& vex)
{
	int* lowcost = new int[vexnum];   //存放最短路径的权重
	int* mst = new int[vexnum];     //存放最短路径的起点，下标为最短路径的终点
	assert(lowcost != nullptr);
	assert(mst != nullptr);

	//获取vex的下标
	int index;
	graph::GetVexIndex(vexs, vexnum, vex, index);

	int i;
	int k;
	for (i = 0; i < vexnum; ++i)
	{
		graph::GetVexIndex(vexs, vexnum, vexs[i], k);
		lowcost[i] = graph::getWeight(edges, index, k);    //从当前的顶点集出发的最短路径的权重
		mst[i] = index;            //当前顶点集出发的最短路径对应的起点
	}

	//找从当前顶点集出发的最短路径
	int min;    //最短路径的权重
	int min_index;    //最短路径的终点的下标
	int j;
	int begin;   //最短路径的起点下标
	int cost;
	for (i = 0; i < vexnum - 1; ++i)    //n个顶点的图的最小生成树有n-1条边，一条边一条边来处理
	{
		min = INFINITE;
		min_index = -1; 
		//找最短路径
		for (j = 0; j < vexnum; ++j)
		{
			if (lowcost[j] != 0 && lowcost[j] < min)    
			{
				min = lowcost[j];
				min_index = j;
			}
		}//for
		//输出最短路径
		begin = mst[min_index];
		cout << vexs[begin] << "->" << vexs[min_index] << ":" << min << endl;
		//将lowcost[min_index]改为0，表示下标为min_index的点已经并入最小生成树的顶点集
		lowcost[min_index] = 0;

		//重新计算从当前顶点集出发的最短路径
		for (j = 0; j < vexnum; ++j)
		{
			cost = graph::getWeight(edges, min_index, j);
			if (cost < lowcost[j])
			{
				lowcost[j] = cost;
				mst[j] = min_index;
			}
		}
	}//for

	delete[] lowcost;
	delete[] mst;
}

//克鲁斯克最小生成树
void MGraph::kruscal_MST()
{
	//记录下图上所有的边
	edge* e = new edge[vexnum * (vexnum - 1) / 2];     //n个顶点最多有n*(n-1)/2条边
	assert(e != nullptr);
	int i;
	int j;
	int k = 0;
	for (i = 0; i < vexnum; ++i)
	{
		for (j = 0; j < i; ++j)
		{
			if (edges[i][j] != INFINITE)
			{
				e[k].x = i;
				e[k].y = j;
				e[k].cost = edges[i][j];
				++k;
			}
		}//for
	}

	//把所有的边按权重排序
	qsort(e, k, sizeof(edge),graph::comp);

	//每次选择一条边组成最小生成树
	int* father = new int[vexnum];
	for (i = 0; i < vexnum; ++i)
		father[i] = i;

	int x, y;
	int n = 0;  //指示已经输出了多少条边
	for (i = 0; i < k; ++i)     
	{
		if (!graph::circle(father, e[i].x, e[i].y))
		{
			x = e[i].x;
			y = e[i].y;
			cout << vexs[x] << "->" << vexs[y] << ": " << e[i].cost << endl;
			graph::mark(father, x, y, vexnum);
			++n;
			if (n == vexnum - 1)    //n个顶点的最小生成树有n-1条边
				break;
		}
	}

	delete[] e;
	delete[] father;
}

//深度优先遍历,从vex顶点开始
void MGraph::DFTraverse(const T vex)
{
	bool* visit = new bool[vexnum];
	assert(visit != nullptr);
	memset(visit, 0, sizeof(bool) * vexnum);  //1全部置为0 

	DFS(vex, visit);
	cout << "null" << endl;
	delete[] visit;
}

void MGraph::DFS(const T vex, bool visit[])
{
	int index;
	T neig;;

	cout << vex << "-->";
	graph::GetVexIndex(vexs, vexnum, vex, index);
	visit[index] = true;
	graph::GetFirstNeighbor(edges, vexs, vexnum, vex, neig);
	while (neig)
	{
		graph::GetVexIndex(vexs, vexnum, neig, index);
		if (!visit[index])
		{
			DFS(neig, visit);
		}

		graph::GetNextNeighbor(edges, vexs, vexnum, vex, neig, neig);
	}

}

//关键路径
void MGraph::CriticalPath()
{
	int i;
	int* ve = new int[vexnum];   //最早开始时间
	int* vl = new int[vexnum];   //最晚开始时间
	assert(ve != nullptr);
	assert(vl != nullptr);
	memset(ve, 0, sizeof(int) * vexnum);
	for (i = 0; i < vexnum; ++i)
		vl[i] = INFINITE;

	int index;   
	int w;   //两顶点之间的权重
	//求最早开始时间
	for (i = 0; i < vexnum - 1; ++i)
	{
		graph::GetFirstNeighbor(edges, vexs, vexnum, vexs[i], index);
		while (index != -1)
		{
			w = graph::getWeight(edges, i, index);  
			if (ve[i] + w > ve[index])
			{
				ve[index] = ve[i] + w;
			}

			graph::GetNextNeighbor(edges, vexs, vexnum, vexs[i], vexs[index], index);
		}//while
	}

	//求最晚开始时间
	vl[vexnum - 1] = ve[vexnum - 1];
	for (i = vexnum - 2; i >= 0; --i)
	{
		graph::GetFirstNeighbor(edges, vexs, vexnum, vexs[i], index);
		while (index != -1)
		{
			w = graph::getWeight(edges, i, index);
			if (vl[index] - w < vl[i])
			{
				vl[i] = vl[index] - w;
			}

			graph::GetNextNeighbor(edges, vexs, vexnum, vexs[i], vexs[index], index);
		}//while
	}

	//求关键路径
	int e;    //关键路径的弧尾的最早开始时间
	int l;     //关键路径的弧头的最晚开始时间减去弧的权重
	//关键路径上的点最早开始时间和最晚开始时间相等，所以l==e
	for (i = 0; i < vexnum - 1; ++i)
	{
		graph::GetFirstNeighbor(edges, vexs, vexnum, vexs[i], index);
		while (index != -1)
		{
			e = ve[i];
			l = vl[index] - graph::getWeight(edges, i, index);
			if (l == e)
			{
				cout << "<" << vexs[i] << "," << vexs[index] << ">是关键路径" << endl;
			}

			graph::GetNextNeighbor(edges, vexs, vexnum, vexs[i], vexs[index], index);
		}//while
	}

	delete[] ve;
	delete[] vl;
}

//从指定顶点到其余各顶点的最短路径
void MGraph::ShortestPath(const T& vex, int* path, int* dist)
{
	//初始化
	int i;
	int index;
	graph::GetVexIndex(vexs, vexnum, vex, index);    //求指定顶点的索引
	for (i = 0; i < vexnum; ++i)
	{
		dist[i] = edges[index][i];
		path[i] = index;
	}
	path[index] = -1;    //-1表示顶点是指定顶点

	//求最短路径
	bool* s = new bool[vexnum];    //true表示顶点已经并入最短路径，初始化为false表示顶点未被并入最短路径
	assert(s != nullptr);
	memset(s, 0, sizeof(bool) * vexnum);
	s[index] = true;    //指定顶点已经并入最短路径
	
	int j;
	int min;
	int v = index;   //当前最短路径上前一个顶点的索引
	for (i = 1; i < vexnum; ++i)   //n-1条最短路径
	{
		min = INFINITE;
		for (j = 0; j < vexnum; ++j) //选最小的dist
		{
			if (!s[j] && dist[j] < min)
			{
				min = dist[j];
				v = j;
			}
		}//for
		s[v] = true; 
		for (j = 0; j < vexnum; ++j)   //更新dist和path
		{
			if (!s[j] && edges[v][j] < INFINITE && dist[v] + edges[v][j] < dist[j])
			{
				dist[j] = dist[v] + edges[v][j];
				path[j] = v;
			}
		}
	}//for

	delete[] s;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//获取顶点在的下标位置
void graph::GetVexIndex(const T* vexs, const int n, const T& vex, int& index)
{
	int k;
	for (k = 0; k < n; ++k)
	{
		if (vexs[k] == vex)
		{
			index = k;
			return;
		}
	}
	index = -1;
}

//获取第一个邻接顶点
void graph::GetFirstNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T vex, T& neighborvex)
{
	int index;   //表示图中不存在这个顶点
	graph::GetVexIndex(vexs, vexnum, vex, index);     //获取vex的下标位置

	if (index != -1)   //找到了vex,求他的第一个邻接顶点
	{
		int j;
		for (j = 0; j < vexnum; ++j)     //从index1行的每一列进行查找第一个邻接顶点
		{
			if (edges[index][j] != 0)
			{
				neighborvex = vexs[j];
				return;
			}
		}
		neighborvex = 0;    //走到这里说明没找到邻接顶点
	}//if
	else   //图中不存在vex
		neighborvex = 0;
}
//获取第一个邻接顶点的索引
void graph::GetFirstNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T vex, int& index)
{
	int index1;   //表示图中不存在这个顶点
	graph::GetVexIndex(vexs, vexnum, vex, index1);     //获取vex的下标位置

	if (index1 != -1)   //找到了vex,求他的第一个邻接顶点
	{
		int j;
		for (j = 0; j < vexnum; ++j)     //从index1行的每一列进行查找第一个邻接顶点
		{
			if (edges[index1][j] != 0)
			{
				index = j;
				return;
			}
		}
		index = -1;    //走到这里说明没找到邻接顶点
	}//if
	else   //图中不存在vex
		index = -1;
}

//获取v1关于v2的下一个邻接顶点
void graph::GetNextNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T v1, const T v2, T& nextneighborvex)
{
	int index1;
	int index2;
	graph::GetVexIndex(vexs, vexnum, v1, index1);
	graph::GetVexIndex(vexs, vexnum, v2, index2);

	if (index1 != -1 && index2 != -1)   //v1和v2都存在
	{
		for (int j = index2 + 1; j < vexnum; ++j)
		{
			if (edges[index1][j] != 0)
			{
				nextneighborvex = vexs[j];
				return;
			}
		}//for
		nextneighborvex = 0;  //能执行到这里说明v2是v1的最后一个邻接顶点
	}//if 
	else  //v1或者v2不存在
		nextneighborvex = 0;
}
//获取v1关于v2的下一个邻接顶点的索引
void graph::GetNextNeighbor(const int edges[][MAX_VERTEX], const T* vexs, int vexnum, const T v1, const T v2, int& index)
{
	int index1;
	int index2;
	graph::GetVexIndex(vexs, vexnum, v1, index1);
	graph::GetVexIndex(vexs, vexnum, v2, index2);

	if (index1 != -1 && index2 != -1)   //v1和v2都存在
	{
		for (int j = index2 + 1; j < vexnum; ++j)
		{
			if (edges[index1][j] != 0)
			{
				index = j;
				return;
			}
		}//for
		index = -1;  //能执行到这里说明v2是v1的最后一个邻接顶点
	}//if 
	else  //v1或者v2不存在
		index = -1;
}


//获取两顶点间的权重
int graph::getWeight(int edges[][MAX_VERTEX], int& index1, int& index2)
{
	if (index1 == -1 || index2 == -1)
		return INFINITE;

	return edges[index1][index2];
}

int graph::comp(const void* p1, const void* p2)
{
	return ((edge*)p1)->cost - ((edge*)p2)->cost;
}

//判断是否成环
bool graph::circle(int* father, int i, int j)
{
	return father[i] == father[j];
}
//标记同一个连通子图
void graph::mark(int* father, int i, int j, int n)
{
	int tem = father[j];
	for (int k = 0; k < n; ++k)
	{
		if (father[k] == tem)
			father[k] = father[i];
	}
}