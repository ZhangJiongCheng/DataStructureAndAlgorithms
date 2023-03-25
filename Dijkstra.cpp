/////*
////本题为填空题，只需要算出结果后，在代码中使用输出语句将所填结果输出即可。
////
////小蓝学习了最短路径之后特别高兴，他定义了一个特别的图，希望找到图 中的最短路径。
////
////小蓝的图由 2021 个结点组成，依次编号 1 至 2021。
////
////对于两个不同的结点 a, b，如果 a 和 b 的差的绝对值大于 21，则两个结点
////之间没有边相连；如果 a 和 b 的差的绝对值小于等于 21，则两个点之间有一条
////长度为 a 和 b 的最小公倍数的无向边相连。
////
////例如：结点 1 和结点 23 之间没有边相连；结点 3 和结点 24 之间有一条无 向边，
////长度为 24；结点 15 和结点 25 之间有一条无向边，长度为 75。
////
////请计算，结点 1 和结点 2021 之间的最短路径长度是多少。
////
////提示：建议使用计算机编程解决问题。
////*/
////
/////*
////单源最短路径——Dijkstra
////Dijkstra算法是经典的最短路径算法，用于计算一个节点到其他所有节点的最短路径。
////
////主要特点是以起始点为中心向外层层扩展，直到扩展到终点为止。
////
////时间复杂度：O(n^2)
////
////处理问题：单源、无负权、有向图、无向图最短路径
////
////不能使用的情况：边中含有负权值（无法判断）
////*/
////
/////*
////基本思想：把带权图中所有的点分为两部分S∪U，S为已经求出从起点到该点的最短路径的点集合，
////U中为未确定最短路径的点集合。把U中的点一个一个加入到S中，最后求出全部最短路径。
////
////如何把U中的点加入S中呢？
////
////①初始时，S只包含源点s，即S＝{s}，dis[s]=0。U包含除v外的其他顶点，即U={其余顶点}，
////若s与U中顶点u有边，则dis[u]=e[s][u]，否则，dis[u]=∞。
////
////②从U中找到一个与源点s距离最小（min(dis[])）的顶点k，把k加入S中，
////dis[k]确定（仔细想想，s与k最短路径必定是dis[k]=e[s][k]，找不到更短的）。
////
////③以k为新考虑的中间点，修改源点s到U中各顶点的距离dis[]：
////若从源点s到顶点u的距离（dis[k]+e[k][u]，经过顶点k）比原来距离（dis[u]，不经过顶点k）短，
////则修改顶点u的距离值，修改后的距离值的顶点k的距离加上边上的权。（这一过程称为“松弛”）
////
////④重复步骤②和③直到所有顶点都包含在S中。
////
////算法优化：这里面每次都要寻找距离最短的那个点和距离，时间复杂度为O(n)，
////可以用“堆”来优化，是时间复杂度降为O(lgn)。
////*/
////
////#include <iostream>
////#include<cstring>
////using namespace std;
////
////int map[2022][2022];
////int path[2022];
////int dis[2022];
////
////int gcd(int a, int b)
////{
////    return b ? gcd(b, a % b) : a;
////}
////
////int lcm(int x, int y)
////{
////    return x * y / gcd(x, y);
////}
////
////void get_map()
////{
////    for (int i = 1; i < 2021; ++i)
////    {
////        for (int j = i + 1; j <= 2021; ++j)
////        {
////            if (abs(i - j) > 21)
////                map[i][j] = map[j][i] = 0x3f3f3f3f;
////            else
////                map[i][j] = map[j][i] = lcm(i, j);
////        }
////    }
////}
////
////void getShortestPath()
////{
////    int vis[2022];
////    memset(vis, 0, sizeof(vis));
////
////    for (int i = 1; i <= 2021; ++i)
////        dis[i] = map[1][i];
////    path[1] = -1;
////    vis[1] = 1;
////
////    for (int i = 1; i < 2021; ++i)
////    {
////        int minn = 0x3f3f3f3f;
////        int v = 0;
////        for (int j = 2; j <= 2021; ++j)
////        {
////            if (!vis[j] && dis[j] < minn)
////            {
////                minn = dis[j];
////                v = j; 
////            }
////        }
////
////        vis[v] = 1;
////        for (int i = 2; i <= 2021; ++i)
////        {
////            if (!vis[i] && dis[v] + map[v][i] < dis[i])
////            {
////                dis[i] = dis[v] + map[v][i];
////                path[i] = v;
////            } 
////        }
////    }
////}
////
////int main()
////{
////    get_map();
////    getShortestPath();
////    cout << dis[2021] << endl;
////
////    return 0;
////}
////
//
////下面是优化版
//#include <iostream>
//#include<vector>
//#include<queue>
//using namespace std;
//
//#define x first
//#define y second
//
//const int N = 1e5 + 10;
//
//int dis[N];
//int path[N];
//vector<pair<int, int>> e[N];
//
//bool vis[N]; //判断顶点是否被访问过
//int n;
//int s;
//
//void get_map()
//{
//    n = 4;
//    int edges[5][3] = {
//        {3,1,6},
//        {3,2,1},
//        {2,1,1},
//        {2,4,5},
//        {1,4,3}
//    };
//    for (int i = 0; i < 5; ++i)
//    {
//        int v1 = edges[i][0];
//        int v2 = edges[i][1];
//        int w = edges[i][2];
//
//        e[v1].push_back({ v2,w });
//        e[v2].push_back({ v1,w }); //若为有向图，则去掉这一行代码
//    }
//}
//
//void get_shortest_path(int s)
//{
//    memset(dis, 0x3f, sizeof(dis));
//    dis[s] = 0;
//
//    priority_queue<pair<int, int>> q;
//    q.push({ 0,s });  //距离，前顶点
//    while (!q.empty())
//    {
//        auto t = q.top();
//        q.pop();
//
//        int u = t.y;
//        if (vis[u]) continue;
//        vis[u] = 1;
//
//        for (auto ed : e[u])
//        {
//            int v = ed.x;
//            int w = ed.y;
//            if (dis[u] + w < dis[v])
//            {
//                dis[v] = dis[u] + w;
//                path[v] = u;
//                q.push({ -dis[v],v });
//            }
//        }
//    }
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
//    get_map();
//    s = 4;
//    get_shortest_path(s);
//    print_path();
//   
//    return 0;
//}