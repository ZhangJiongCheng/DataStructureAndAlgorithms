///*
//单源最短路径——SPFA算法
//上一种算法其实不好用，复杂度太高，SPFA算法是Bellman-ford算法的队列优化，
//比较常用。SPFA算法在负边权图上可以完全取代Bellman-ford算法，另外在稀疏图中也表现良好。
//但是在非负边权图中，为了避免最坏情况的出现，通常使用效率更加稳定的Dijkstra算法，
//以及它的使用堆优化的版本。通常的SPFA算法在一类网格图中的表现不尽如人意。
//不是很稳定，不如Dijkstra。
//
//处理问题：单源、可有负权、有向图、无向图最短路径（自身其实无法处理负权）
//*/
//
///*
//算法思想：
//
//设立一个队列用来保存待优化的点，优化时每次取出队首结点u，
//并且用u点当前的最短路径估计值对u点所指向的结点v进行松弛操作，
//如果v点的最短路径估计值有所调整，且v点不在当前的队列中，就将v点放入队尾。
//这样不断从队列中取出结点来进行松弛操作，直至队列空为止。
//*/ 
//#include <iostream>
//#include<vector>
//#include<cstring>
//#include<queue>
//using namespace std;
//
//#define x first
//#define y second
//
//const int N = 1e5 + 10;
//int dis[N];
//int path[N];
//vector<pair<int, int>> e[N];
////e[i]是第i个vector，每个元素是一个pair，first表示以第i个顶点连接的另一个顶点，
////second表示这两点之间的距离 
// 
//bool vis[N];  //true表示顶点在队列中
//int cnt[N];   //cnt[i]表示从源点到i点经过了多少条边
//int n;
//int s;
//
//void get_map()
//{
//    n = 5;
//    int edges[5][3] = {
//        {1,4,2},
//        {1,5,5},
//        {5,3,-3},
//        {4,3,2},
//        {3,2,3}
//    };
//
//    for (int i = 0; i < 5; ++i)
//    {
//        int v1 = edges[i][0];
//        int v2 = edges[i][1];
//        int w = edges[i][2];
//        e[v1].push_back({ v2,w });
//        e[v2].push_back({ v1,w });  //若为有向图，则去掉这一行代码
//    }
//}
//
////图中有环则返回true,否则返回false;
//bool get_shortest_path(int s)  //s是源点
//{
//    memset(dis, 0x3f, sizeof(dis));
//    dis[s] = 0;
//
//    queue<int> q;
//    q.push(s);
//    vis[s] = 1;
//    while (q.size())
//    {
//        int u = q.front();
//        q.pop();
//        vis[u] = 0;
//
//        for (auto ed : e[u])
//        {
//            int v = ed.x;
//            int w = ed.y;
//            if (dis[u] + w < dis[v])
//            {
//                dis[v] = w + dis[u];
//                cnt[v] = cnt[u] + 1;
//                path[v] = u;
//
//                if (cnt[v] >= n)   //有负环
//                    return true;  
//                if (!vis[v]) q.push(v), vis[v] = 1;
//            }
//        }
//    }
//    return false;
//}
//
//void print(int i)
//{
//    if (!path[i]) return;
//    print(path[i]);
//    cout << path[i] << "->";
//}
//
//void print_path()
//{
//    for (int i = 1; i <= n; ++i)
//    {
//        if (i == s) continue;
//
//        cout << s << "-" << i << "的最短距离为:";
//        if (dis[i] == 0x3f3f3f3f)
//            cout << "无法到达" << endl;
//        else
//        {
//            cout << dis[i] << "     ";
//            cout << "路径为";
//            print(i);
//            cout << i << endl;
//        }
//    }
//}
//
//int main()
//{
//    
//    get_map();
//    s = 3;
//    bool flag = get_shortest_path(s);
//    if (flag)
//        cout << "图中有负环" << endl;
//    else
//      print_path();
//
//    return 0;
//}