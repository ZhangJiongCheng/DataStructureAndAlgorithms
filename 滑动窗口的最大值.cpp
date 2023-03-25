///*
//给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。
//例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，
//他们的最大值分别为{4,4,6,6,6,5}；针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： 
//{[2,3,4]，2，6，2，5，1}，{2，[3,4,2]，6，2，5，1}， {2，3，[4,2,6]，2，5，1}， 
//{2，3，4，[2,6,2]，5，1}，{2，3，4，2，[6,2,5]，1}， {2，3，4，2，6，[2,5,1]}。
//
//输入样例：
//8 3
//2 3 4 2 6 2 5 1
//
//输出样例：
//4 4 6 6 6 5
//*/
//
///*
//单调队列特点：
//1. 队列是窗口的子序列
//2. 队列从左往右单调递减
//3. 队列的头元素是窗口内的最大值
//*/
//#include<iostream>
//#include<vector>
//#include<deque>
//using namespace std;
//
//int n, m;//n个元素，窗口大小为m
//vector<int> nums;
//
//vector<int> maxValueInWindow()
//{
//	int size = nums.size();
//
//	deque<int> de; //用来存放元素的下标
//	vector<int> ans;
//	for (int i = 0; i < size; ++i)
//	{
//		int l = i - m;      //窗口的首元素的前一个元素的下标
//		if (!de.empty() && de.front() == l) 
//			de.pop_front();
//		while (!de.empty() && nums[de.back()] <= nums[i]) 
//			de.pop_back();
//		de.push_back(i);
//
//		if (i >= m - 1)  ans.push_back(nums[de.front()]);
//	}
//	return ans;
//}
//
//int main()
//{
//	cin >> n >> m;
//	int temp;
//	for (int i = 1; i <= n; ++i)
//	{
//		cin >> temp;  
//		nums.push_back(temp);
//	}
//
//	vector<int> ans = maxValueInWindow();
//	for (auto v : ans)
//		cout << v << " ";
//	cout << endl;
//	return 0;
//}