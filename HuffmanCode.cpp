#include <iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int N = 1e5 + 10;

struct node
{
	int lchild, rchild;
	int parent;
	int w;
	int id;

	bool operator>(const node& t) const
	{
		return w > t.w;
	}
}tree[2 * N];

vector<string> code;
int n = 7;
int a[] = { 0,15,8,20,25,7,5,20 };

void init()
{
	for (int i = 1; i <= n; ++i)
		tree[i].w = a[i];
	for (int i = 1; i <= 2 * n; ++i)
		tree[i].id = i;
}

void build_tree()
{
	priority_queue<node, vector<node>, greater<node>> que;
	for (int i = 1; i <= n; ++i)
		que.push(tree[i]);

	for (int i = n + 1; i < 2 * n; ++i)
	{
		node t1 = que.top();
		que.pop();
		node t2 = que.top();
		que.pop();

		tree[i].lchild = t1.id;
		tree[i].rchild = t2.id;
		tree[i].w = t1.w + t2.w;
		tree[t1.id].parent = tree[t2.id].parent = i;

		que.push(tree[i]);
	}
}

void get_code()
{
	for (int i = 1; i <= n; ++i)
	{
		string tem;
		for (int c = i, f = tree[i].parent; f; c = f, f = tree[f].parent)
			if (c == tree[f].lchild)
				tem.append("0");
			else
				tem.append("1");

		reverse(tem.begin(), tem.end());
		code.push_back(tem);
	}
}

int main()
{
	init();

	build_tree();
	get_code();

	for (int i = 0; i < code.size(); ++i)
		cout << code[i] << endl;

	return 0;
}