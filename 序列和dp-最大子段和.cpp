/*
求一个序列的最大连续子段和。
*/

/*
1. 状态：dp[i]表示以i结尾的最大连续子段和
2. 转移方程：dp[i]=max(dp[i-1]+a[i],a[i])
3. 边界: dp[1]=a[1]
*/

#include<iostream>
using namespace std;

long n;
long a[101];
long dp[101];  //dp[i]表示以i结尾的最大子段和

int main()
{
	cin >> n;
	for (long i = 1; i <= n; ++i) cin >> a[i];

	long maxx;
	maxx = dp[1] = a[1];
	for (long i = 2; i <= n; ++i)
	{
		dp[i] = max(dp[i - 1] + a[i], a[i]);
		maxx = max(maxx, dp[i]);
	}
	cout << maxx << endl;
	cout << "=============dp[i]================" << endl;
	for (long i = 1; i <= n; ++i)
		cout << dp[i] << " ";
	cout << endl;
	return 0;
}