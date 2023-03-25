/*
给定一个序列，求其最长连续上升子序列。
*/

/*
状态： dp[i]表示以i结尾的连续上升子序列的长度
转移方程：a[i]>a[i-1]?(dp[i]=dp[i-1]+1):(dp[i]=1)
*/

#include<iostream>
using namespace std;

long n;
long a[101];
long dp[101];

int main()
{
	cin >> n;
	for (long i = 1; i <= n; ++i)
		cin >> a[i];

	long maxx = 1;
	dp[1] = 1;
	for (long i = 2; i <= n; ++i)
	{
		a[i] > a[i - 1] ? (dp[i] = dp[i - 1] + 1) : (dp[i] = 1);
		maxx = max(maxx, dp[i]);
	}
	cout << maxx << endl;
	cout << "==================dp[i]===================" << endl;
	for (long i = 1; i <= n; ++i)
		cout << dp[i] << " ";
	cout << endl;

	return 0;
}