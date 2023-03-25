//#include <iostream>
//#include<vector>
//using namespace std;
//
//#define x first
//#define y second
//
//const int N = 55;
//struct edge
//{
//    int v1, v2;
//    int w;
//};
//vector<edge> result;
//int sum;   //最小生成树的权
//
//int n;
//vector<pair<int, int>> e[N];
//
//void get_map()
//{
//    n = 8;
//    int edges[12][3] = {
//        {7,8,1},
//        {7,8,2},
//        {7,2,7},
//        {8,3,8},
//        {6,5,4},
//        {6,4,3},
//        {5,4,5},
//        {4,2,18},
//        {2,3,4},
//        {2,2,1},
//        {2,1,2},
//        {3,1,3}
//    };
//
//    for (int i = 0; i < 12; ++i)
//    {
//        int v1 = edges[i][0];
//        int v2 = edges[i][1];
//        int w = edges[i][2];
//
//        e[v1].push_back({ v2,w });
//        e[v2].push_back({ v1,w });
//        //这里必须得建双向图
//    }
//}
//
//void Prim(int s)   //s是起点编号
//{
//    int* dis = new int[n + 1];    //存放未选定的顶点与已选定的集合S的距离
//    int* path = new int[n + 1];  //记录未选定的顶点与S中的哪一个顶点相连
//
//    for (int i = 1; i <= n; ++i)
//    {
//        dis[i] = 0x3f3f3f3f;
//        path[i] = s;
//    }
//    for (auto ed : e[s])
//    {
//        int v = ed.x;
//        int w = ed.y;
//        dis[v] = w;
//    }
//    dis[s] = 0;
//
//    for (int i = 1; i < n; ++i)  //最小生成树具有n-1条边
//    {
//        int minn = 0x3f3f3f3f;
//        int index = 0;
//        for (int j = 1; j <= n; ++j)
//        {
//            if (dis[j] && dis[j] < minn)
//            {
//                minn = dis[j];
//                index = j;
//            }
//        }
//
//        sum += minn;
//        result.push_back({ index,path[index],minn });
//        dis[index] = 0;
//
//        for (auto ed : e[index])
//        {
//            int v = ed.x;
//            int w = ed.y;
//            if (w < dis[v])
//            {
//                dis[v] = w;
//                path[v] = index;
//            }
//        }
//    }
//
//    delete[] dis;
//    delete[] path;
//}
//
//int main()
//{
//    get_map();
//    Prim(6);
//    cout << "最小生成树如下：" << endl;
//    cout << "顶点1  顶点2   权重" << endl;
//    for (auto elem : result)
//        cout << elem.v1 << "         " << elem.v2 << "      " << elem.w << endl;
//    cout << "总权重：" << sum << endl;
//
//    return 0;
//}