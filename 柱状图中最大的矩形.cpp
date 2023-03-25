///*
//给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
//
//求在该柱状图中，能够勾勒出来的矩形的最大面积。
//
//输入样例;
//6
//2 1 5 6 2 3
//
//输出样例：
//10
//*/
//
///*
//思路：从左往右遍历每一个矩形， 对于当前遍历的矩形,它包含它在内的最大矩形是,
//向右和向左分别找到第一个高度小于它的矩形,它们围起来的矩形即为最大矩形。
//*/
//
//#include<iostream>
//#include<vector>
//#include<stack>
//using namespace std; 
//
//int largestRectangleArea(vector<int>& h)
//{
//	int size = h.size();
//
//	vector<int> w(size, 1);  //w[i]表示 以第i个柱子的高度为高 的矩形的宽度，w[i]*h[i]即为该矩形的面积
//	stack<int> stk;       //用来存放元素的下标
//	
//	//先对每一个柱子求其向左的高度 
//	for (int i = 0; i < size; ++i)
//	{
//		while (!stk.empty() && h[stk.top()] >= h[i])
//			stk.pop();
//
//		if (stk.empty()) //第i个柱子左边的柱子全部比它高
//			w[i] += i;
//		else  //stk.top()即为左边第一个比它低的柱子的编号
//			w[i] += i - stk.top() - 1;
//
//		stk.push(i);
//	}
//
//	while (!stk.empty()) stk.pop();
//
//	//再对每一个柱子求其向右的高度 
//	int ans = 0;
//	for (int i = size - 1; i >= 0; --i)
//	{
//		while (!stk.empty() && h[stk.top()] >= h[i])
//			stk.pop();
//
//		if (stk.empty()) //第i个柱子右边的柱子全部比它高
//			w[i] += size - i - 1;
//		else //stk.top()即为右边第一个比它低的柱子的编号
//			w[i] += stk.top() - i - 1;
//
//		stk.push(i);
//		
//		ans = max(ans, w[i] * h[i]);
//	}
//
//	return ans;
//}
//
//int main()
//{
//	int n; 
//	cin >> n;
//
//	vector<int> h;
//	int temp;
//	for (int i = 1; i <= n; ++i)
//	{
//		cin >> temp;
//		h.push_back(temp);
//	}
//	int ans = largestRectangleArea(h);
//	cout << ans << endl;
//
//	return 0;
//}