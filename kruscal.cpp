#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define x first
#define y second

const int N = 55;
struct edge
{
    int v1, v2;
    int w;

    bool operator<(const edge& e) const
    {
        return w < e.w;
    }
};
vector<edge> result;
int sum;   //最小生成树的权

int n;
vector<pair<int, int>> e[N];

void get_map()
{
    n = 8;
    int edges[12][3] = {
        {7,8,1},
        {7,8,2},
        {7,2,7},
        {8,3,8},
        {6,5,4},
        {6,4,3},
        {5,4,5},
        {4,2,18},
        {2,3,4},
        {2,2,1},
        {2,1,2},
        {3,1,3}
    };

    for (int i = 0; i < 12; ++i)
    {
        int v1 = edges[i][0];
        int v2 = edges[i][1];
        int w = edges[i][2];

        e[v1].push_back({ v2,w });
      //  e[v2].push_back({ v1,w });
        //这里建单向图还是双向图都可以，不影响答案
    }
}

int find(int v, int* f)
{
    if (f[v] == v) return v;
    return find(f[v], f);
}

bool circle(int v1, int v2, int* f)
{
    return find(v1, f) == find(v2, f) ? true : false;
}

void mark(int v1, int v2, int* f)
{
    int f1 = find(v1, f);
    int f2 = find(v2, f);
    f[f1] = f2;
}

void kruscal()   
{
    edge* t = new edge[n * (n - 1) / 2]; //n个顶点最多有n*(n-1)/2条边

    int k = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (auto ed : e[i])
        {
            t[k] = { i,ed.x,ed.y };
            ++k;
        }
    }

    sort(t, t + k);

    int* f = new int[n + 1];
    for (int i = 0; i <= n; ++i)
        f[i] = i;

    int num = 0;
    for (int i = 0; i < k; ++i)
    {
        if (!circle(t[i].v1, t[i].v2, f))
        {
            sum += t[i].w;
            result.push_back(t[i]);
            mark(t[i].v1, t[i].v2, f);

            ++num;
            if (num == n - 1) break;
        }
    }

    delete[] t;
    delete[] f;
}

int main()
{
    get_map();
    kruscal();
    cout << "最小生成树如下：" << endl;
    cout << "顶点1  顶点2   权重" << endl;
    for (auto elem : result)
        cout << elem.v1 << "         " << elem.v2 << "      " << elem.w << endl;
    cout << "总权重：" << sum << endl;

    return 0;
}