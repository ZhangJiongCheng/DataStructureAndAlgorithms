/*
题目背景
阿宝上学了，今天老师拿来了一块很长的涂色板。

题目描述
色板长度为L，L是一个正整数，所以我们可以均匀地将它划分成L块1厘米长的小方格。并从左到右标记为1, 2, ... L。
现在色板上只有一个颜色，老师告诉阿宝在色板上只能做两件事：
"C A B C" 指在A到 B 号方格中涂上颜色 C。
"P A B" 指老师的提问：A到 B号方格中有几种颜色。

学校的颜料盒中一共有 T 种颜料。为简便起见，我们把他们标记为 1, 2, ... T. 
开始时色板上原有的颜色就为1号色。 面对如此复杂的问题，阿宝向你求助，你能帮助他吗？

输入输出格式
输入格式：
第一行有3个整数 L (1 <= L <= 100000), T (1 <= T <= 30) 和 O (1 <= O <= 100000)。 
在这里O表示事件数。
接下来 O 行, 每行以 "C A B C" 或 "P A B" 得形式表示所要做的事情
(这里 A, B, C 为整数, 可能A> B，这样的话需要你交换A和B)

输出格式：
对于老师的提问，做出相应的回答。每行一个整数。

输入样例#1：
2 2 4
C 1 1 2
P 1 2
C 2 2 2
P 1 2

输出样例#1：
2
1
*/

//线段树加位运算

#include<iostream>
#include<vector>
#include<bitset>
using namespace std;

const int N = 1e5 + 10;
struct segnode
{
	int l, r;
	int add;
	bitset<30> v;
}tree[4*N];

void push_up(int u)
{
	tree[u].v = tree[u << 1].v | tree[u << 1 | 1].v;
}

void push_down(int u)
{
	if (tree[u].add)
	{
		tree[u << 1].v = (1 << tree[u].add - 1);
		tree[u << 1 | 1].v = (1 << tree[u].add - 1);
		tree[u << 1].add = tree[u].add;
		tree[u << 1 | 1].add = tree[u].add;
		tree[u].add = 0;
	}
}

void build(int u, int l, int r)
{
	/*tree[u].l = l;
	tree[u].r = r;
	tree[u].add = 0;*/
	tree[u] = { l,r,0 };
	if (l == r)
		tree[u].v = 1;
	else
	{
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		push_up(u);
	}
}

void modify(int u, int l, int r, int v)
{
	if (l <= tree[u].l && r >= tree[u].r)
	{
		tree[u].v = (1 << v - 1);
		tree[u].add = v;
	}
	else
	{
		push_down(u);
		int mid = tree[u].l + tree[u].r >> 1;
		if (l <= mid) modify(u << 1, l, r, v);
		if (r > mid) modify(u << 1 | 1, l, r, v);
		push_up(u);
	}
}

bitset<30> query(int u, int l, int r)
{
	if (l <= tree[u].l && r >= tree[u].r)
		return tree[u].v;
	else
	{
		push_down(u);
		bitset<30> v;
		int mid = tree[u].l + tree[u].r >> 1;
		if (l <= mid) v = query(u << 1, l, r);
		if (r > mid) v |= query(u << 1 | 1, l, r);
		return v;
	}
}

int main()
{
	int n, t, m;
	cin >> n >> t >> m;
	build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		char op;
		int x, y, z;
		cin >> op >> x >> y;
		if (x > y) swap(x, y);

		if (op == 'C')
		{
			cin >> z;
			modify(1, x, y, z);
		}
		else
		{
			bitset<30> temp = query(1, x, y);
			int ans = 0;
			for (int i = 0; i < 30; ++i)
				ans += temp[i];
			cout << ans << endl;
		}
	}

	return 0;
}