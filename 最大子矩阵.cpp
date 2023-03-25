/*
* 给定一个矩阵，求其最大子矩阵。
*/

/*
这是二维dp题，做法是降维成一维dp题（求序列的最大连续子序列）。
做法：对每一列进行求前缀和，这样就可以将每一列看成一个数。
     然后枚举行，就是 求序列的最大连续子序列 了。
*/

#include<iostream> 
using namespace std;

long n;
long a[101][101];  //矩阵
long presum[101][101];  //每一列的前缀和
long dp[101];  //将每一列集合成一个数 之后的序列，在这个序列上求最大连续子序列即可

int main()
{
    cin >> n;
    for (long i = 1; i <= n; ++i)
        for (long j = 1; j <= n; ++j)
        {
            cin >> a[i][j];
            presum[i][j] = presum[i - 1][j] + a[i][j];
        }

    long maxx = a[1][1];
    for ( long x1 = 1; x1 <= n; ++x1)
    {
        for (long x2 = x1; x2 <= n; ++x2)
        {
            for (long j = 1; j <= n; ++j)
                dp[j] = presum[x2][j] - presum[x1 - 1][j]; 
            for (long i = 1; i <= n; ++i)
            {
                dp[i] = max(dp[i - 1] + dp[i], dp[i]);
                maxx = max(maxx, dp[i]);
            }
        } 
    }
    cout << maxx << endl;
    return 0;
}
 