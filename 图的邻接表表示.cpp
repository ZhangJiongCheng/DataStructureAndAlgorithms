#include"图的邻接表表示.h"
#include"链队列.h"

AGraph::AGraph() :vexnum(0), edgenum(0)
{
	for (int i = 0; i < MAX_VEX; ++i)
	{
		vexs[i].data = 0;
		vexs[i].first = nullptr;
	}
}

//插入顶点
void AGraph::InsertVex(const T vex)
{
	if (vexnum < MAX_VEX)    //还没达到最大顶点数
	{
		vexs[vexnum].data = vex;
		vexnum++;
	}
}

//插入边
void AGraph::InsertEdge(const T v1, const T v2)
{
	int index1;   //-1说明不存在这个顶点
	int index2;
	Agraph::GetVexIndex(vexs, vexnum, v1, index1);
	Agraph::GetVexIndex(vexs, vexnum, v2, index2);

	if (index1 != -1 && index2 != -1)    //要插入边必须保证两顶点都存在
	{
		//v1-->v2
		ANode* p1 = new ANode;   //开辟节点
		assert(p1 != nullptr);

		p1->index = index2;   //v1的邻接顶点索引是v2的
		//图是无序的，所以直接头插比较方便
		p1->next = vexs[index1].first;
		vexs[index1].first = p1;

		//v2-->v1
		//ANode* p2 = new ANode;   //开辟节点
		//assert(p2 != nullptr);

		//p2->index = index1;   //v2的邻接顶点索引是v1的
		////图是无序的，所以直接头插比较方便
		//p2->next = vexs[index2].first;
		//vexs[index2].first = p2;

		edgenum++;
	}
}

//打印图
void AGraph::PrintGraph()
{
	int i;
	ANode* p;
	for (i = 0; i < vexnum; ++i)
	{
		cout << i << " " << vexs[i].data << ": ";
		p = vexs[i].first;
		while (p)   //有邻接顶点
		{
			cout << p->index << "-->";
			p = p->next;
		}
		cout << "null" << endl;
	}//for
}

//深度优先遍历
void AGraph::DFTraverse(const T vex)
{
	bool* visit = new bool[vexnum];
	assert(visit != nullptr);
	memset(visit, 0, sizeof(bool) * vexnum);   //全部置为false,表示未被遍历

	Agraph::DFS(vexs, vexnum, vex, visit);
	cout << "null" << endl;
	delete[] visit;
}


//广度优先遍历
void AGraph::BFTraverse(const T vex)
{
	bool* visit = new bool[vexnum];
	assert(visit != nullptr);
	memset(visit, 0, sizeof(bool) * vexnum);   //全部置为false,表示未被遍历

	Agraph::BFS(vexs, vexnum, vex, visit);
	cout << "null" << endl;
	delete[] visit;
}

//遍历全图
void AGraph::ComponentTraverse()
{
	bool* visit = new bool[vexnum];
	assert(visit != nullptr);
	memset(visit, 0, sizeof(bool) * vexnum);   //全部置为false,表示未被遍历

	for (int i = 0; i < vexnum; ++i)
	{
		if (!visit[i])
		{
			Agraph::DFS(vexs, vexnum, vexs[i].data, visit);
			cout << "null ";
		}
	}
	cout << endl;
	delete[]visit;
}

//删除顶点
void AGraph::RemoveVex(const T vex)
{
	int index;   //-1说明不存在这个顶点
	Agraph::GetVexIndex(vexs, vexnum, vex, index);

	if (index != -1)  //找到了删除的顶点
	{
		int k;
		ANode* p = nullptr;
		ANode* q = nullptr;
		ANode* pnext = nullptr;
		p = vexs[index].first;
		while (p)     //循环删除顶点的所有边
		{
			k = p->index;
			q = vexs[k].first;
			ANode* pre;
			//无向图的对称性，必须删除p的邻接点中指向vex的边
			if (q->index == index)     //要删除的是第一个节点
			{
				vexs[k].first = q->next;
				delete q;
			}
			else    //要删除的不是第一个节点
			{
				pre = q;
				q = q->next;
				while (q)
				{
					if (q->index == index)     //q的index是vex的index,删除q
					{
						pre->next = q->next;
						delete q;
						break;
					}//if
					pre = q;
					q = q->next;
				}//while

			}//else

			pnext = p->next;
			delete p;
			p = pnext;
		}//while 删除顶点的所有边

		//顶点数减少，然后，如果删除的顶点不是最后一个顶点，要修改边信息
		vexnum--;
		if (index != vexnum)     //删除的顶点不是最后一个顶点
		{
			vexs[index].data = vexs[vexnum].data;
			vexs[index].first = vexs[vexnum].first;

			p = vexs[index].first;
			while (p)
			{
				k = p->index;
				q = vexs[k].first;
				while (q)
				{
					if (q->index == vexnum)
					{
						q->index = index;
						break;
					}
					q = q->next;
				}//while

				p = p->next;

			}//while 修改所有边信息		
		}//if
	}//if(index != -1)
}

//删除边
void AGraph::RemoveEdge(const T v1, const T v2)
{
	int index1;   //-1说明不存在这个顶点
	int index2;
	Agraph::GetVexIndex(vexs, vexnum, v1, index1);
	Agraph::GetVexIndex(vexs, vexnum, v2, index2);

	if (index1 != -1 && index2 != -1)   //两个顶点都存在图中才可能有边
	{
		ANode* p;
		ANode* pre = nullptr;

		//delete v1-->v2
		p = vexs[index1].first;
		while (p && p->index != index2)
		{
			pre = p;
			p = p->next;
		}//while
		if (p)
		{
			if (p == vexs[index1].first)
				vexs[index1].first = p->next;
			else
				pre->next = p->next;

			delete p;
		}//if

		//delete v2-->v1
		p = vexs[index2].first;
		while (p && p->index != index1)
		{
			pre = p;
			p = p->next;
		}//while
		if (p)
		{
			if (p == vexs[index2].first)
				vexs[index2].first = p->next;
			else
				pre->next = p->next;

			delete p;
		}//if

	}//if
}

//拓扑排序AOV
void AGraph::TopoSort()
{
	int* indegree = new int[vexnum];
	assert(indegree != nullptr);
	memset(indegree, 0, sizeof(int) * vexnum);

	//统计每一个顶点的入度
	int i;
	ANode* p = nullptr;
	for (i = 0; i < vexnum; ++i)
	{
		p = vexs[i].first;
		while (p)
		{
			indegree[p->index]++;
			p = p->next;
		}
	}//for

	int top = -1;   //top和indegree模拟入栈和出栈
	for (i = 0; i < vexnum; ++i)
	{
		if (indegree[i] == 0)     //模拟入栈
		{
			indegree[i] = top;
			top = i;
		}
	}

	//n个顶点一个个的输出
	int index1;   //当前顶点的索引
	int index2;   //邻接顶点的索引
	for (i = 0; i < vexnum; ++i)
	{
		if (top == -1)
		{
			cout << "图中有回路" << endl;
			return;
		}
		index1 = top;
		top = indegree[top];    //模拟出栈
		cout << vexs[index1].data << "->";
		Agraph::GetFirstNeighbor(vexs, vexnum, vexs[index1].data, index2);
		while (index2 != -1)
		{
			if (--indegree[index2] == 0)
			{
				indegree[index2] = top;
				top = index2;
			}

			Agraph::GetNextNeighbor(vexs, vexnum, vexs[index1].data, vexs[index2].data, index2);
		}
	}//for
	cout << "null" << endl; 

	delete[] indegree;
}

AGraph::~AGraph()
{
	ANode* p;
	ANode* pnext;
	for (int i = 0; i < vexnum; ++i)
	{
		p = vexs[i].first;
		while (p)    //该顶点有邻接节点
		{
			pnext = p->next;
			delete p;
			p = pnext;
		}
	}//for
}

///////////////////////////////////////////////////////////////////////////////////

//获取顶点的索引
void Agraph::GetVexIndex(const VNode* vexs, const int& vexnum, const T& vex, int& index)
{
	int i;
	for (i = 0; i < vexnum; ++i)
	{
		if (vexs[i].data == vex)
		{
			index = i;
			return;
		}
	}//for

	index = -1;
}

//获取第一个邻接顶点
void Agraph::GetFirstNeighbor(const VNode* vexs, const int& vexnum, const T vex, T& neighborvex)
{
	int index;
	GetVexIndex(vexs, vexnum, vex, index);

	if (index != -1)   //图中存在vex顶点
	{
		ANode* p = vexs[index].first;
		if (p)
			neighborvex = vexs[p->index].data;
		else
			neighborvex = 0;
	}
	else  //图中不存在vex顶点
		neighborvex = 0;
}
//获取第一个邻接顶点的索引
void Agraph::GetFirstNeighbor(const VNode* vexs, const int& vexnum, const T vex, int& index)
{
	int index1;
	GetVexIndex(vexs, vexnum, vex, index1);
	if (index1 == -1)   //图中不存在该顶点，不存在的顶点不可能有邻接顶点
		index = -1;
	else
	{
		ANode* p = vexs[index1].first;
		if (p)   //有邻接顶点
			index = p->index;
		else
			index = -1;
	}
}

//获取v1关于v2的下一个邻接顶点的索引
void Agraph::GetNextNeighbor(const VNode* vexs, const int& vexnum, const T v1, const T v2, int& index)
{
	int index1;
	int index2;
	GetVexIndex(vexs, vexnum, v1, index1);
	GetVexIndex(vexs, vexnum, v2, index2);

	if (index1 == -1 || index2 == -1)   //两个顶点都必须存在，否则没有下一个邻接顶点
		index = -1;
	else
	{
		ANode* p = vexs[index1].first;
		while (p)
		{
			if (p->index == index2)
				break;
			p = p->next;
		}//while
		if (p && p->next)
			index = p->next->index;
		else
			index = -1;
	}//else
}
//获取v1关于v2的下一个邻接顶点
void Agraph::GetNextNeighbor(const VNode* vexs, const int& vexnum, const T v1, const T v2, T& nextneighborvex)
{
	int index1;   //-1说明不存在这个顶点
	int index2;
	GetVexIndex(vexs, vexnum, v1, index1);
	GetVexIndex(vexs, vexnum, v2, index2);

	if (index1 != -1 && index2 != -1)   //图中存在v1顶点
	{
		ANode* p = vexs[index1].first;
		while (p)
		{
			if (p->index == index2)
				break;
			p = p->next;
		}
		if (p && p->next)
			nextneighborvex = vexs[p->next->index].data;
		else
			nextneighborvex = 0;

	}//if
	else
		nextneighborvex = 0;
}

//深度优先遍历
void Agraph::DFS(const VNode* vexs, const int& vexnum, const T& vex, bool visit[])
{
	int index;
	T neig;
	cout << vex << "-->";
	GetVexIndex(vexs, vexnum, vex, index);
	visit[index] = true;

	GetFirstNeighbor(vexs, vexnum, vex, neig);
	while (neig)
	{
		GetVexIndex(vexs, vexnum, neig, index);
		if (!visit[index])
			DFS(vexs, vexnum, neig, visit);

		GetNextNeighbor(vexs, vexnum, vex, neig, neig);
	}
}

//广度优先遍历
void Agraph::BFS(const VNode* vexs, const int& vexnum, const T& vex, bool visit[])
{
	int index;
	T neig;
	T v;
	LinkQueue queue;

	cout << vex << "-->";
	GetVexIndex(vexs, vexnum, vex, index);
	visit[index] = true;
	queue.push(vex);
	while (!queue.empty())
	{
		queue.pop(v);
		GetFirstNeighbor(vexs, vexnum, v, neig);
		while (neig)
		{
			GetVexIndex(vexs, vexnum, neig, index);
			if (!visit[index])
			{
				cout << neig << "-->";
				visit[index] = true;
				queue.push(neig);
			}

			GetNextNeighbor(vexs, vexnum, v, neig, neig);
		}//while
	}//while

}
