#pragma once

#define MAXSIZE 20
typedef int KeyType;
typedef KeyType SeqList[MAXSIZE + 1];

#include<iostream>
#include<cassert>
#include<queue>
#include<array>
using namespace std;

namespace sort
{
	//排序菜单
	void menu();

	//打印排序后的数据
	void print(SeqList& r, const int length);

	//直接插入排序
	void InsertSort(SeqList& r, const int length);

	//折半插入排序
	void BInsertSort(SeqList& r, const int length);

	//快速排序
	void QuickSort(SeqList& r, int low, int high);
	int Partition(SeqList& r, int low, int high);

	//树形选择排序
	void TreeSelectSort(SeqList& r, const int length);
	void SelectMin(KeyType* e, const int n, int pos);
	void GetValue(KeyType* e, const int n, const int pos, KeyType& value);
	void Select(KeyType* e, const int n, int pos);
	void WorkForSelect(KeyType* e, const int n, const int pos);

	//堆排序
	void HeapSort(SeqList& r, const int length);
	void ShiftDown(KeyType* heap, const int n, int pos);
	KeyType RemoveMin(KeyType* heap, int n);

	//归并排序
	void MergeSort(SeqList& r, SeqList& tr, int left, int right);
	void Merge(SeqList& r, SeqList& tr, int left, int mid, int right);

	//基数排序
	void RadixSort(SeqList& r, const int length);
	void Distribute(SeqList& r, const int n, array<queue<KeyType>, 10>& alist, int k);
	void Collect(SeqList& r, array<queue<KeyType>, 10>& alist);
	void GetKey(KeyType data, int k, int& key);
}





//排序菜单
void sort::menu()
{
	cout << "***************************" << endl;
	cout << "*     1. 直接插入排序     *" << endl;
	cout << "*     2. 折半插入排序     *" << endl;
	cout << "*     3. 快速排序         *" << endl;
	cout << "*     4. 树形选择排序     *" << endl;
	cout << "*     5. 堆排序           *" << endl;
	cout << "*     6. 归并排序         *" << endl;
	cout << "*     7. 基数排序         *" << endl;
	cout << "*     0. 退出             *" << endl;
	cout << "***************************" << endl;
}

//直接插入排序
void sort::InsertSort(SeqList& r, const int length)     //length为元素个数，下标从1开始
{
	int i;
	int j;
	for (i = 2; i <= length; ++i)     //从第二个到最后一个依次排序
	{
		if (r[i] < r[i - 1])       //当前元素比前一个元素小才需要插入排序，否则保持原位置不变
		{
			r[0] = r[i];
			r[i] = r[i - 1];
			for (j = i - 2; r[0] < r[j]; --j)     //寻找插入的位置
				r[j + 1] = r[j];

			r[j + 1] = r[0];
		}
	}//for
}

//折半插入排序
void sort::BInsertSort(SeqList& r, const int length)
{
	int i;
	for (i = 2; i <= length; ++i)   //从第二个到最后一个依次排序
	{
		r[0] = r[i];
		int low = 1;
		int high = i - 1;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (r[0] >= r[mid])
				low = mid + 1;
			else
				high = mid - 1;
		}    //循环结束，low=high+1

		for (int j = i; j > low; --j)
			r[j] = r[j - 1];

		r[low] = r[0];

	}//for
}

//快速排序
void sort::QuickSort(SeqList& r, int low, int high)
{
	if (low < high)
	{
		int pivotloc = Partition(r, low, high);
		QuickSort(r, low, pivotloc - 1);
		QuickSort(r, pivotloc + 1, high);
	}
}
int sort::Partition(SeqList& r, int low, int high)
{
	r[0] = r[low];
	while (low < high)
	{
		while (low < high && r[high] >= r[0])      //从右往左找到第一个小于枢轴量的
			--high;
		r[low] = r[high];     //将小于数轴量的赋值到枢轴量左边
		while (low < high && r[low] <= r[0])    //从左往右找到第一个大于枢轴量的
			++low;
		r[high] = r[low];      //将大于数轴量的赋值到枢轴量右边
	}
	r[low] = r[0];       //为枢轴量赋值
	return low;     //返回枢轴量的位置
}

//树形选择排序
void sort::TreeSelectSort(SeqList& r, const int length)   //length为元素个数，下标从1开始
{
	int n = 2 * length - 1;
	KeyType* e = new KeyType[n];  //开辟二叉完全数的空间
	assert(e != nullptr);

	int i;
	for (i = length - 1; i < n; ++i)     //把r的数据移到二叉完全数的叶子结点，r下标从1开始，e下标从0开始
		e[i] = r[i - length + 2];

	int curpos = length - 2;
	SelectMin(e, n, curpos);     //执行完该函数，e[0]即为最小值的下标
	r[1] = e[e[0]];   //将最小值赋值会原数组
	e[e[0]] = INT_MAX;

	for (i = 2; i <= length; ++i)    //对其他元素一一进行排序
	{
		curpos = (e[0] - 1) / 2;
		Select(e, n, curpos);      //执行完该函数，e[0]即为次小值的下标
		r[i] = e[e[0]];
		e[e[0]] = INT_MAX;
	}

	delete[] e;
	e = nullptr;
}
void sort::SelectMin(KeyType* e, const int n, int pos)   //第一次选择，选择最小值的下标
{
	while (pos >= 0)
	{
		WorkForSelect(e, n, pos);
		--pos;
	}//while
}
void sort::GetValue(KeyType* e, int n, const int pos, KeyType& value)
{
	if (pos >= n)   //如果下标越界，即没有这个节点
		value = INT_MAX;
	else
	{
		if (pos >= n / 2) //pos是叶子结点的下标
			value = e[pos];
		else
			value = e[e[pos]];
	}
}
void sort::Select(KeyType* e, const int n, int pos)
{
	bool flag = true;    //true进行循环
	while (flag && pos >= 0)
	{
		WorkForSelect(e, n, pos);

		if (pos == 0) flag = false;     //false表示这一次选出的最小值是所有待选的最小值
		pos = (pos - 1) / 2;
	}
}
void sort::WorkForSelect(KeyType* e, const int n, const int pos)
{
	int left;
	int right;
	KeyType lValue;
	KeyType rValue;

	left = 2 * pos + 1;
	right = left + 1;
	GetValue(e, n, left, lValue);
	GetValue(e, n, right, rValue);
	if (lValue <= rValue)
	{
		if (left >= n / 2)    //left是叶子节点的下标
		{
			e[pos] = left;
		}
		else
		{
			e[pos] = e[left];
		}
	}
	else
	{
		if (right >= n / 2)    //right是叶子节点的下标
		{
			e[pos] = right;
		}
		else
		{
			e[pos] = e[right];
		}
	}
}

//堆排序
void sort::HeapSort(SeqList& r, const int length)
{
	KeyType* heap = new KeyType[length];
	assert(heap != nullptr);

	int i;
	for (i = 1; i <= length; ++i)    //r下标从1开始，heap下标从0开始
		heap[i - 1] = r[i];

	int curpos = length / 2 - 1;
	while (curpos >= 0)
	{
		ShiftDown(heap, length, curpos);
		--curpos;
	}

	//对r数组较小排序
	for (i = 1; i <= length; ++i)
		r[i] = RemoveMin(heap, length - i);

	delete[] heap;
	heap = nullptr;
}
void sort::ShiftDown(KeyType* heap, const int n, int pos)  //调整堆
{
	int j = pos * 2 + 1;
	while (j < n)     //该节点存在
	{
		if (j + 1 < n && heap[j] > heap[j + 1])   //选择两个叶子节点中较小的
			++j;
		if (heap[j] >= heap[pos])
			break;
		else
		{
			heap[j] = heap[j] ^ heap[pos];
			heap[pos] = heap[j] ^ heap[pos];
			heap[j] = heap[j] ^ heap[pos];
			pos = j;
			j = pos * 2 + 1;
		}
	}//while
}
KeyType sort::RemoveMin(KeyType* heap, int n)    //返回堆中的最小值，同时调整堆
{
	KeyType min = heap[0];
	heap[0] = heap[n];
	ShiftDown(heap, n, 0);
	return min;
}

//归并排序
void sort::MergeSort(SeqList& r, SeqList& tr, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	MergeSort(r, tr, left, mid);
	MergeSort(r, tr, mid + 1, right);
	Merge(r, tr, left, mid, right);
}
void sort::Merge(SeqList& r, SeqList& tr, int left, int mid, int right)
{
	for (int i = left; i <= right; ++i)
		tr[i] = r[i];
	int k1 = left;
	int k2 = mid + 1;
	int k = left;
	while (k1 <= mid && k2 <= right)
	{
		if (tr[k1] <= tr[k2])
		{
			r[k++] = tr[k1++];
		}
		else
		{
			r[k++] = tr[k2++];
		}
	}//while
	while (k1 <= mid)
		r[k++] = tr[k1++];
	while (k2 <= right)
		r[k++] = tr[k2++];
}

//基数排序
void sort::RadixSort(SeqList& r, const int length)
{
	array<queue<KeyType>, 10> alist;
	int i;
	for (i = 0; i < 3; ++i)     //假设整数最大值为3位数
	{
		Distribute(r, length, alist, i);
		Collect(r, alist);
	}
}
void sort::Distribute(SeqList& r, const int n, array<queue<KeyType>, 10>& alist, int k)
{
	int i;
	int key;
	for (i = 1; i <= n; ++i)
	{
		GetKey(r[i], k, key);
		alist[key].push(r[i]);
	}
}
void sort::Collect(SeqList& r, array<queue<KeyType>, 10>& alist)
{
	int i;
	int k = 1;
	for (i = 0; i < 10; ++i)
	{
		while (!alist[i].empty())
		{
			r[k++] = alist[i].front();
			alist[i].pop();
		}
	}
}
void sort::GetKey(KeyType data, int k, int& key)
{
	int temp;
	while (k >= 0)
	{
		temp = data % 10;
		data /= 10;
		--k;
	}
	key = temp;
}

//打印排序后的数据
void sort::print(SeqList& r, const int length)
{
	int i;
	cout << "排序后的数据为:          ";
	for (i = 1; i <= length; ++i)
		cout << r[i] << " ";
	cout << endl;
}



int main()
{
	system("color fd");
	SeqList r;
	KeyType data;
	int i;    //下标从1开始
	int length;
	int choice;

	while (1)
	{
		sort::menu();
		cout << "     请选择（0-7）:";
		cin >> choice;
		if (choice == 0)  exit(0);

		cout << "输入要排序的数据(-1结束):";
		i = 1;    //下标从1开始
		while (cin >> data, data != -1)
		{
			r[i++] = data;
		}
		length = i - 1;
		switch (choice)
		{
		case 1:
			sort::InsertSort(r, length);
			sort::print(r, length);
			break;
		case 2:
			sort::BInsertSort(r, length);
			sort::print(r, length);
			break;
		case 3:
			sort::QuickSort(r, 1, length);
			sort::print(r, length);
			break;
		case 4:
			sort::TreeSelectSort(r, length);
			sort::print(r, length);
			break;
		case 5:
			sort::HeapSort(r, length);
			sort::print(r, length);
			break;
		case 6:
			SeqList tr;
			sort::MergeSort(r, tr, 1, length);
			sort::print(r, length);
			break;
		case 7:
			sort::RadixSort(r, length);
			sort::print(r, length);
			break;
		}
	}

	return 0;
}