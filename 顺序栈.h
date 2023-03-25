#pragma once


#define INIT_SIZE 100   //栈存储空间的初始分配量
#define INC_SIZE 10      //栈存储空间的分配增量
typedef int ElemType;     //栈存储的元素类型


struct SqStack
{
	SqStack();    //构造函数初始化栈

	void clear(); //清空栈

	bool empty(); //判空

	bool isfull();  //判满

	bool increase();  //增大capacity

	void length();  //求长度

	void getTop(ElemType& elem); //取栈顶元素，不弹栈

	void push(const ElemType& elem);  //压栈

	void pop(ElemType& elem);  //弹栈并把栈顶元素带出去

	void traverse();  //遍历栈并打印栈的数据

	~SqStack();  //析构函数释放资源

private:
	ElemType* base;  //栈底指针
	ElemType* top;  //栈顶指针
	size_t size;    //栈的元素个数
	size_t capacity;  //栈的容量
};

void menu();
