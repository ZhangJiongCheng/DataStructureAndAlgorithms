///*
//��Դ���·������SPFA�㷨
//��һ���㷨��ʵ�����ã����Ӷ�̫�ߣ�SPFA�㷨��Bellman-ford�㷨�Ķ����Ż���
//�Ƚϳ��á�SPFA�㷨�ڸ���Ȩͼ�Ͽ�����ȫȡ��Bellman-ford�㷨��������ϡ��ͼ��Ҳ�������á�
//�����ڷǸ���Ȩͼ�У�Ϊ�˱��������ĳ��֣�ͨ��ʹ��Ч�ʸ����ȶ���Dijkstra�㷨��
//�Լ�����ʹ�ö��Ż��İ汾��ͨ����SPFA�㷨��һ������ͼ�еı��ֲ��������⡣
//���Ǻ��ȶ�������Dijkstra��
//
//�������⣺��Դ�����и�Ȩ������ͼ������ͼ���·����������ʵ�޷�����Ȩ��
//*/
//
///*
//�㷨˼�룺
//
//����һ����������������Ż��ĵ㣬�Ż�ʱÿ��ȡ�����׽��u��
//������u�㵱ǰ�����·������ֵ��u����ָ��Ľ��v�����ɳڲ�����
//���v������·������ֵ������������v�㲻�ڵ�ǰ�Ķ����У��ͽ�v������β��
//�������ϴӶ�����ȡ������������ɳڲ�����ֱ�����п�Ϊֹ��
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
////e[i]�ǵ�i��vector��ÿ��Ԫ����һ��pair��first��ʾ�Ե�i���������ӵ���һ�����㣬
////second��ʾ������֮��ľ��� 
// 
//bool vis[N];  //true��ʾ�����ڶ�����
//int cnt[N];   //cnt[i]��ʾ��Դ�㵽i�㾭���˶�������
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
//        e[v2].push_back({ v1,w });  //��Ϊ����ͼ����ȥ����һ�д���
//    }
//}
//
////ͼ���л��򷵻�true,���򷵻�false;
//bool get_shortest_path(int s)  //s��Դ��
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
//                if (cnt[v] >= n)   //�и���
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
//        cout << s << "-" << i << "����̾���Ϊ:";
//        if (dis[i] == 0x3f3f3f3f)
//            cout << "�޷�����" << endl;
//        else
//        {
//            cout << dis[i] << "     ";
//            cout << "·��Ϊ";
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
//        cout << "ͼ���и���" << endl;
//    else
//      print_path();
//
//    return 0;
//}