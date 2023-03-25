/*
��Դ���·������Floyd�㷨
Floyd�㷨��һ�����ö�̬�滮˼��ļ����Ȩͼ�ж�Դ��֮�����·�����㷨��
������ȷ��������ͼ��Ȩ�����·�����⡣

ʱ�临�Ӷȣ�O(N^3��

�ռ临�Ӷȣ�O(N^2��

�������⣺��Դ�����и�Ȩ������ͼ������ͼ���·��
*/

/*
�㷨˼�룺

���������������ת�㣬��ô���·���������ǵ�e[][]ԭʼ����

������ֻ������1�Ŷ��������ת���ж�e[i][1]+e[1][j]�Ƿ��e[i][j]ҪС���޸�e[][]��

�۽�����ֻ������1��2�Ŷ��������ת����

�����������1~n�����ж��������ת���õ�����e[][]������Ҫ�����������֮������·�̡�

�������Ƕ�̬�滮˼������֡�״̬ת�Ʒ��̣�e[i,j]=max{e[i,k]+e[k,j],e[i,j]}��

�㷨���̣�����ÿһ�Զ��� i �� j�������Ƿ����һ������ k ʹ�ô� i �� k �ٵ� j 
����֪��·�����̡�����ǣ����������
*/

#include <iostream>
using namespace std;

const int N = 25;
int dis[N][N];
int path[N][N];
int n, m;  //n����m����

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
            dis[v2][v1] = w;   //��Ϊ����ͼ����ȥ����һ�д���
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

            cout << i << "-" << j << "����̾���Ϊ:";
            if (dis[i][j] == 0x3f3f3f3f)
                cout << "�޷�����" << endl;
            else
            {
                cout << dis[i][j] << "      ";
                cout << "·��Ϊ:" << i << "->";
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