/*
有 N 种物品和一个容量是 V 的背包。

第 i 种物品最多有 si 件，每件体积是 vi，价值是 wi。

求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。
输出最大价值。

输入格式
第一行两个整数，N，V (0<N≤1000, 0<V≤20000)，用空格隔开，分别表示物品种数和背包容积。

接下来有 N 行，每行三个整数 vi,wi,si，用空格隔开，分别表示第 i 种物品的体积、价值和数量。

输出格式
输出一个整数，表示最大价值。

数据范围
0<N≤1000
0<V≤20000
0<vi,wi,si≤20000
提示
本题考查多重背包的单调队列优化方法。

输入样例
4 5
1 2 3
2 4 1
3 4 3
4 5 2
输出样例：
10
*/

#include<iostream>
#include<cstring>
using namespace std;

const int N = 1005;
const int M = 20005;
int f[N], g[N];
int n, m;
int q[M];

int main()
{
	cin >> n >> m;

	for (int i = 1; i <= n; ++i)  //枚举n个物品
	{
		int v, w, s;
		cin >> v >> w >> s;
		memcpy(g, f, sizeof(f));

		for (int j = 0; j < v; ++j)   //枚举v个同余类
		{
			int head = 0; 
			int tail = -1; 
			for (int k = j; k <= m; k += v)
			{
				//超过窗口最大值，头元素出队
				if (head <= tail && k - q[head] > s * v) head++;
				//尾元素出队，维持单调性  
				while (head <= tail && g[q[tail]] - (q[tail] - j) / v * w 
					<= g[k] - (k - j) / v * w)  
					tail--;
				//入队
				q[++tail] = k;
				//计算最大价值
				if (head <= tail)
					f[k] = max(f[k], g[q[head]] + (k - q[head]) / v * w);
			}
		}
	}
	cout << f[m] << endl;

	return 0;
}