/*
应用条件：必须是DAG(有向无环图),且图中只有一个源点（入度为0）和一个汇点（出度为0）
关键路径是AOE
*/

#include <iostream>
#include<vector>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;

#define x first
#define y second

const int N = 25;
int n, m;   //n个顶点m条边
vector<pair<int, int>> out[N];   //out[2][i]={3,5}表示从第2个顶点到第3号顶点有一条边，权为5
int indegree[N];   //统计各顶点入度

struct edge
{
    int v1, v2, w;
};
vector<edge> res;

stack<int> topo;
int ve[N];   //最早开始时间
int vl[N];   //最晚开始时间

void get_map()
{
    /*
    9 11
    1 2 6
    1 3 4
    1 4 5
    2 5 1
    3 5 1
    4 6 2
    5 7 9
    5 8 7
    6 8 4
    7 9 2
    8 9 4
    */
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        out[v1].push_back({ v2,w });
        indegree[v2]++;
    }
}

bool topo_sort()
{
    queue<int> q;    //存放顶点编号
    for (int i = 1; i <= n; ++i)
        if (!indegree[i]) q.push(i);   //入度为0则进队列

    int count = 0;   //统计输出顶点个数
    while (!q.empty())
    {
        int v1 = q.front();
        q.pop();

        topo.push(v1);
        count++;
        for (auto elem : out[v1])
        {
            int v2 = elem.x;
            int w = elem.y;
            indegree[v2]--;
            if (!indegree[v2]) q.push(v2);
            if (ve[v1] + w > ve[v2])          //统计最早开始时间
                ve[v2] = ve[v1] + w;
        }
    }
    if (count < n) return true;    //有环
    return false;     //无环
}

bool critical_path()
{
    if (topo_sort()) return true;  //有环
   
    for (int i = 1; i <= n; ++i)
        vl[i] = 0x3f3f3f3f;
    vl[topo.top()] = ve[topo.top()];

    //统计最晚开始时间
    //topo.pop();      //去掉汇点
    while (!topo.empty())         //循环内逆拓扑排序求最晚开始时间
    {
        int v1 = topo.top();
        topo.pop();
        for (auto elem : out[v1])
        {
            int v2 = elem.x;
            int w = elem.y;
            if (vl[v2] - w < vl[v1])
                vl[v1] = vl[v2] - w;
        }
    }

    //统计关键路径
    for (int i = 1; i <= n; ++i)
    {
        for (auto elem : out[i])
        {
            int j = elem.x;
            int w = elem.y;
            if (ve[i] + w == vl[j])
                res.push_back({ i,j,w });
        }
    }

    return false;
}

void print()
{
    cout << "图中的关键路径为:" << endl;
    for (auto elem : res)
        cout << elem.v1 << "->" << elem.v2 << "    " << elem.w << endl;
}

int main()
{
    get_map();
    bool flag = critical_path();
    if (flag)
        cout << "图中有环" << endl;
    else
        print();

    return 0;
}