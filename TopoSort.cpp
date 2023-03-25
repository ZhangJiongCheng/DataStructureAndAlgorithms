///*
//应用条件：必须是DAG(有向无环图)
//拓扑排序是AOV
//*/
//
//#include <iostream>
//#include<queue>
//#include<stack>
//#include<vector>
//using namespace std;
//
//const int N = 25;
//int n, m;       //n个顶点m条边
//vector<int> e[N];   //e[i]的元素表示顶点编号
//int in[N];     //统计各顶点入度
//queue<int> res;  //存放顶点编号
//
//void get_map()
//{
//    /*
//    * 
//    12 16
//    1 4
//    1 2
//    1 12
//    1 3
//    4 5
//    2 3
//    3 5
//    5 7
//    3 7
//    3 8
//    9 10
//    9 11
//    9 12
//    11 6
//    6 8
//    10 12
//    */
//
//    cin >> n >> m;
//    for (int i = 1; i <= m; ++i)
//    {
//        int v1, v2;
//        cin >> v1 >> v2;
//        e[v1].push_back(v2);
//        in[v2]++;
//    }
//}
//
//bool topo_sort()
//{
//    stack<int> stk;    //存放顶点编号
//    for (int i = 1; i <= n; ++i)
//        if (!in[i]) stk.push(i);   //入度为0则进栈
//
//    int count = 0;   //统计输出顶点个数
//    while (!stk.empty())
//    {
//        int v1 = stk.top();
//        stk.pop();
//
//        res.push(v1);
//        count++;
//        for (auto v2 : e[v1])
//        {
//            in[v2]--;
//            if (!in[v2]) stk.push(v2);
//        } 
//    }
//    if (count < n) return true;    //有环
//    return false;     //无环
//}
//
//void print()
//{
//    while (!res.empty())
//    {
//        cout << res.front() << " ";
//        res.pop();
//    }
//    cout << endl;
//
//}
//
//int main()
//{
//    get_map();
//    bool flag = topo_sort();
//    if (flag)
//        cout << "图中有环" << endl;
//    else
//        print();
//
//    return 0;
//}