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
	//����˵�
	void menu();

	//��ӡ����������
	void print(SeqList& r, const int length);

	//ֱ�Ӳ�������
	void InsertSort(SeqList& r, const int length);

	//�۰��������
	void BInsertSort(SeqList& r, const int length);

	//��������
	void QuickSort(SeqList& r, int low, int high);
	int Partition(SeqList& r, int low, int high);

	//����ѡ������
	void TreeSelectSort(SeqList& r, const int length);
	void SelectMin(KeyType* e, const int n, int pos);
	void GetValue(KeyType* e, const int n, const int pos, KeyType& value);
	void Select(KeyType* e, const int n, int pos);
	void WorkForSelect(KeyType* e, const int n, const int pos);

	//������
	void HeapSort(SeqList& r, const int length);
	void ShiftDown(KeyType* heap, const int n, int pos);
	KeyType RemoveMin(KeyType* heap, int n);

	//�鲢����
	void MergeSort(SeqList& r, SeqList& tr, int left, int right);
	void Merge(SeqList& r, SeqList& tr, int left, int mid, int right);

	//��������
	void RadixSort(SeqList& r, const int length);
	void Distribute(SeqList& r, const int n, array<queue<KeyType>, 10>& alist, int k);
	void Collect(SeqList& r, array<queue<KeyType>, 10>& alist);
	void GetKey(KeyType data, int k, int& key);
}





//����˵�
void sort::menu()
{
	cout << "***************************" << endl;
	cout << "*     1. ֱ�Ӳ�������     *" << endl;
	cout << "*     2. �۰��������     *" << endl;
	cout << "*     3. ��������         *" << endl;
	cout << "*     4. ����ѡ������     *" << endl;
	cout << "*     5. ������           *" << endl;
	cout << "*     6. �鲢����         *" << endl;
	cout << "*     7. ��������         *" << endl;
	cout << "*     0. �˳�             *" << endl;
	cout << "***************************" << endl;
}

//ֱ�Ӳ�������
void sort::InsertSort(SeqList& r, const int length)     //lengthΪԪ�ظ������±��1��ʼ
{
	int i;
	int j;
	for (i = 2; i <= length; ++i)     //�ӵڶ��������һ����������
	{
		if (r[i] < r[i - 1])       //��ǰԪ�ر�ǰһ��Ԫ��С����Ҫ�������򣬷��򱣳�ԭλ�ò���
		{
			r[0] = r[i];
			r[i] = r[i - 1];
			for (j = i - 2; r[0] < r[j]; --j)     //Ѱ�Ҳ����λ��
				r[j + 1] = r[j];

			r[j + 1] = r[0];
		}
	}//for
}

//�۰��������
void sort::BInsertSort(SeqList& r, const int length)
{
	int i;
	for (i = 2; i <= length; ++i)   //�ӵڶ��������һ����������
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
		}    //ѭ��������low=high+1

		for (int j = i; j > low; --j)
			r[j] = r[j - 1];

		r[low] = r[0];

	}//for
}

//��������
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
		while (low < high && r[high] >= r[0])      //���������ҵ���һ��С����������
			--high;
		r[low] = r[high];     //��С���������ĸ�ֵ�����������
		while (low < high && r[low] <= r[0])    //���������ҵ���һ��������������
			++low;
		r[high] = r[low];      //�������������ĸ�ֵ���������ұ�
	}
	r[low] = r[0];       //Ϊ��������ֵ
	return low;     //������������λ��
}

//����ѡ������
void sort::TreeSelectSort(SeqList& r, const int length)   //lengthΪԪ�ظ������±��1��ʼ
{
	int n = 2 * length - 1;
	KeyType* e = new KeyType[n];  //���ٶ�����ȫ���Ŀռ�
	assert(e != nullptr);

	int i;
	for (i = length - 1; i < n; ++i)     //��r�������Ƶ�������ȫ����Ҷ�ӽ�㣬r�±��1��ʼ��e�±��0��ʼ
		e[i] = r[i - length + 2];

	int curpos = length - 2;
	SelectMin(e, n, curpos);     //ִ����ú�����e[0]��Ϊ��Сֵ���±�
	r[1] = e[e[0]];   //����Сֵ��ֵ��ԭ����
	e[e[0]] = INT_MAX;

	for (i = 2; i <= length; ++i)    //������Ԫ��һһ��������
	{
		curpos = (e[0] - 1) / 2;
		Select(e, n, curpos);      //ִ����ú�����e[0]��Ϊ��Сֵ���±�
		r[i] = e[e[0]];
		e[e[0]] = INT_MAX;
	}

	delete[] e;
	e = nullptr;
}
void sort::SelectMin(KeyType* e, const int n, int pos)   //��һ��ѡ��ѡ����Сֵ���±�
{
	while (pos >= 0)
	{
		WorkForSelect(e, n, pos);
		--pos;
	}//while
}
void sort::GetValue(KeyType* e, int n, const int pos, KeyType& value)
{
	if (pos >= n)   //����±�Խ�磬��û������ڵ�
		value = INT_MAX;
	else
	{
		if (pos >= n / 2) //pos��Ҷ�ӽ����±�
			value = e[pos];
		else
			value = e[e[pos]];
	}
}
void sort::Select(KeyType* e, const int n, int pos)
{
	bool flag = true;    //true����ѭ��
	while (flag && pos >= 0)
	{
		WorkForSelect(e, n, pos);

		if (pos == 0) flag = false;     //false��ʾ��һ��ѡ������Сֵ�����д�ѡ����Сֵ
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
		if (left >= n / 2)    //left��Ҷ�ӽڵ���±�
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
		if (right >= n / 2)    //right��Ҷ�ӽڵ���±�
		{
			e[pos] = right;
		}
		else
		{
			e[pos] = e[right];
		}
	}
}

//������
void sort::HeapSort(SeqList& r, const int length)
{
	KeyType* heap = new KeyType[length];
	assert(heap != nullptr);

	int i;
	for (i = 1; i <= length; ++i)    //r�±��1��ʼ��heap�±��0��ʼ
		heap[i - 1] = r[i];

	int curpos = length / 2 - 1;
	while (curpos >= 0)
	{
		ShiftDown(heap, length, curpos);
		--curpos;
	}

	//��r�����С����
	for (i = 1; i <= length; ++i)
		r[i] = RemoveMin(heap, length - i);

	delete[] heap;
	heap = nullptr;
}
void sort::ShiftDown(KeyType* heap, const int n, int pos)  //������
{
	int j = pos * 2 + 1;
	while (j < n)     //�ýڵ����
	{
		if (j + 1 < n && heap[j] > heap[j + 1])   //ѡ������Ҷ�ӽڵ��н�С��
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
KeyType sort::RemoveMin(KeyType* heap, int n)    //���ض��е���Сֵ��ͬʱ������
{
	KeyType min = heap[0];
	heap[0] = heap[n];
	ShiftDown(heap, n, 0);
	return min;
}

//�鲢����
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

//��������
void sort::RadixSort(SeqList& r, const int length)
{
	array<queue<KeyType>, 10> alist;
	int i;
	for (i = 0; i < 3; ++i)     //�����������ֵΪ3λ��
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

//��ӡ����������
void sort::print(SeqList& r, const int length)
{
	int i;
	cout << "����������Ϊ:          ";
	for (i = 1; i <= length; ++i)
		cout << r[i] << " ";
	cout << endl;
}



int main()
{
	system("color fd");
	SeqList r;
	KeyType data;
	int i;    //�±��1��ʼ
	int length;
	int choice;

	while (1)
	{
		sort::menu();
		cout << "     ��ѡ��0-7��:";
		cin >> choice;
		if (choice == 0)  exit(0);

		cout << "����Ҫ���������(-1����):";
		i = 1;    //�±��1��ʼ
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