/*
Ӧ��������������DAG(�����޻�ͼ),��ͼ��ֻ��һ��Դ�㣨���Ϊ0����һ����㣨����Ϊ0��
�ؼ�·����AOE
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
int n, m;   //n������m����
vector<pair<int, int>> out[N];   //out[2][i]={3,5}��ʾ�ӵ�2�����㵽��3�Ŷ�����һ���ߣ�ȨΪ5
int indegree[N];   //ͳ�Ƹ��������

struct edge
{
    int v1, v2, w;
};
vector<edge> res;

stack<int> topo;
int ve[N];   //���翪ʼʱ��
int vl[N];   //����ʼʱ��

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
    queue<int> q;    //��Ŷ�����
    for (int i = 1; i <= n; ++i)
        if (!indegree[i]) q.push(i);   //���Ϊ0�������

    int count = 0;   //ͳ������������
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
            if (ve[v1] + w > ve[v2])          //ͳ�����翪ʼʱ��
                ve[v2] = ve[v1] + w;
        }
    }
    if (count < n) return true;    //�л�
    return false;     //�޻�
}

bool critical_path()
{
    if (topo_sort()) return true;  //�л�
   
    for (int i = 1; i <= n; ++i)
        vl[i] = 0x3f3f3f3f;
    vl[topo.top()] = ve[topo.top()];

    //ͳ������ʼʱ��
    //topo.pop();      //ȥ�����
    while (!topo.empty())         //ѭ��������������������ʼʱ��
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

    //ͳ�ƹؼ�·��
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
    cout << "ͼ�еĹؼ�·��Ϊ:" << endl;
    for (auto elem : res)
        cout << elem.v1 << "->" << elem.v2 << "    " << elem.w << endl;
}

int main()
{
    get_map();
    bool flag = critical_path();
    if (flag)
        cout << "ͼ���л�" << endl;
    else
        print();

    return 0;
}