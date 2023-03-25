/*
多源最短路径——Floyd算法
Floyd算法是一种利用动态规划思想的计算加权图中多源点之间最短路径的算法。
可以正确处理有向图或负权的最短路径问题。

时间复杂度：O(N^3）

空间复杂度：O(N^2）

处理问题：多源、可有负权、有向图、无向图最短路径
*/

/*
算法思想：

①如果不允许有中转点，那么最短路径就是我们的e[][]原始矩阵；

②现在只允许经过1号顶点进行中转，判断e[i][1]+e[1][j]是否比e[i][j]要小，修改e[][]；

③接下来只允许经过1和2号顶点进行中转……

④最后，允许经过1~n号所有顶点进行中转，得到最后的e[][]，就是要求的任意两点之间的最短路程。

这里面是动态规划思想的体现。状态转移方程：e[i,j]=max{e[i,k]+e[k,j],e[i,j]}；

算法过程：对于每一对顶点 i 和 j，看看是否存在一个顶点 k 使得从 i 到 k 再到 j 
比已知的路径更短。如果是，则更新它。
*/

#include <iostream>
using namespace std;

const int N = 25;
int dis[N][N];
int path[N][N];
int n, m;  //n个点m条边

void get_map()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i != j)
                dis[i][j] = 0x3f3f3f3f;
        }
    }

    /*
    8 12
    7 8 1
    8 7 2
    7 2 7
    8 3 8
    4 6 3
    5 6 4
    4 5 5
    2 4 18
    3 2 4
    2 2 1
    2 1 2
    1 3 3
    */

    for (int i = 1; i <= m; ++i)
    {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        if (w < dis[v1][v2])
        {
            dis[v1][v2] = w;
            dis[v2][v1] = w;   //若为有向图，则去掉这一行代码
        }
    }
}

void floyd()
{
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (dis[i][k] + dis[k][j] < dis[i][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

void print(int i, int j)
{
    int k = path[i][j];
    if (!k) return;
    print(i, k);
    cout << k << "->";
    print(k, j);
}

void print_path()
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i == j) continue;

            cout << i << "-" << j << "的最短距离为:";
            if (dis[i][j] == 0x3f3f3f3f)
                cout << "无法到达" << endl;
            else
            {
                cout << dis[i][j] << "      ";
                cout << "路径为:" << i << "->";
                print(i, j);
                cout << j << endl;
            }
        }
    }
}

int main()
{
    get_map();
    floyd();
    print_path();

    return 0;
}