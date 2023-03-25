#pragma once

#define OK     1     
#define ERROR  -1
typedef int Status;    //״̬��

typedef char ElemType;      //�ڵ�Ԫ������

typedef enum { Link, Thread } PointerTag;    //Link��ʾ�ڵ㣬Thread��ʾǰ�����ߺ��
//�������ڵ�
typedef struct BinTreeNode
{
	ElemType data;    //������
	BinTreeNode* lChild;     //����ָ��
	BinTreeNode* rChild;    //�Һ���ָ��
	PointerTag lTag;      //���־
	PointerTag rTag;     //�ұ�־
}BiThrNode, * BiThrLink;


//������
struct BinTree
{
public:
	BinTree():root(nullptr),Null('*'),head(nullptr) {}     //���캯����ʼ��������

	Status CreateBinTree();     //����������,�ڲ�����BinTreeNode::CreateBinTree()��ɴ���

	Status InOrderThread();   //�������������������ڲ�����BinTreeNode::InOrderThread()��ɴ���

	Status InOrderTraverse();   //������������������,�ڲ�����BinTreeNode::InOrderTraverse()��ɴ���

	~BinTree();          //��������delete��������

private:
	BinTreeNode* root;     //ָ����������ڵ��ָ��
	ElemType    Null;    //��ʾ�սڵ�
	BinTreeNode* head;    //ͷ���
};


namespace help
{
	Status CreateBinTree(BinTreeNode*& root, ElemType& Null);     //����������,Ϊ��ͨ���������ã�����static

	Status InOrderThread(BinTreeNode*& root, BinTreeNode*& head);  //����������������������ͷ�������һ��Ԫ�ؽڵ�
	void InThreading(BinTreeNode*& root, BinTreeNode*& pre);   //����������������

	Status InOrderTraverse(BinTreeNode*& root, BinTreeNode*& head);   //�������������


	/*
	* ���������ĸ��������п��ܸı��βε�ָ�������ββ������ã������������
	* ���磬BinTreeNode* first(BinTreeNode*& root);   //��ȡ��һ������ڵ�;  ���󣬻�ı���BinTree�е�root��Ա�����½������
	*/
	BinTreeNode* first(BinTreeNode* root);   //��ȡ��һ������ڵ�;
	BinTreeNode* last(BinTreeNode* root);   //��ȡ���һ������ڵ�
	BinTreeNode* prior(BinTreeNode* cur);  //��ȡ��һ������ڵ㣬��ǰ��
	BinTreeNode* next(BinTreeNode* cur);  //��ȡ��һ������ڵ㣬�����

	Status visit(ElemType& elem);

	void deleteBinTree(BinTreeNode* root);        //delete��new�����Ķ�����
}
