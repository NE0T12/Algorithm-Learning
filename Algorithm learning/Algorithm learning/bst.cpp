#include <stdio.h>
#include <iostream>

#define Status bool
#define KeyType int

typedef struct elem
{
	KeyType key;
}ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode * lchild;
	struct BiTNode * rchild;
}*BiTree;

Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p)
{
	if (!T)
	{
		p = f;
		return false;
	}
	else if (key == T->data.key)
	{
		p = T;
		return true;
	}
	else if (key < T->data.key)
		return SearchBST(T->lchild, key, T, p);
	else
		return SearchBST(T->rchild, key, T, p);
}

Status InsertBST(BiTree &T, ElemType e)
{
	if (!T)
	{
		BiTree s = new BiTNode;
		s->data = e; s->lchild = s->rchild = NULL;
		T = s;
	}
	else if (e.key == T->data.key)
		return false;//关键字等于e.key的数据元素，返回錯誤
	else if (e.key < T->data.key)
		return InsertBST(T->lchild, e);
	else
		return InsertBST(T->rchild, e);

	return true;
}

Status Delete(BiTree &T)
{
	BiTree q, s;
	if (!T->lchild && !T->rchild)
	{
		delete T;
		T = NULL;
	}
	else if (!T->rchild)
	{
		q = T->lchild;
		T->data = q->data;
		T->lchild = q->lchild; T->rchild = q->rchild;
		
		delete q;
	}
	else if (!T->lchild)
	{
		q = T->rchild;
		T->data = q->data;
		T->lchild = q->lchild; T->rchild = q->rchild;

		delete q;
	}
	else
	{
		q = T;
		s = q->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		T->data = s->data;
		if (q != T)
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;

		delete s;
	}
	return true;
}

Status DeleteBST(BiTree &T, KeyType key)
{
	if (!T)
		return false;
	
	if (key == T->data.key)
		return Delete(T);
	else if (key < T->data.key)
		DeleteBST(T->lchild, key);
	else
		DeleteBST(T->rchild, key);
}

void CreateBST(BiTree &T)
{
	ElemType e;
	while (scanf("%d", &e.key) == 1)
		InsertBST(T, e);
}

void printBST(BiTree T)
{
	if(T)
		printf("%d ", T->data.key);
}

void PreOrderBST(BiTree T)
{
	printBST(T);
	if (T->lchild)
		PreOrderBST(T->lchild);
	if (T->rchild)
		PreOrderBST(T->rchild);
}

void MidOrderBST(BiTree T)
{
	if (T->lchild)
		MidOrderBST(T->lchild);
	printBST(T);
	if (T->rchild)
		MidOrderBST(T->rchild);
}

void LastOrderBST(BiTree T)
{
	if (T->lchild)
		LastOrderBST(T->lchild);
	if (T->rchild)
		LastOrderBST(T->rchild);
	printBST(T);
}

void test0()
{
	BiTree T = NULL;

	//create
	CreateBST(T);
	PreOrderBST(T);	printf("\n");
	MidOrderBST(T);	printf("\n");

	//search
	BiTree p;
	bool status;
	status = SearchBST(T, 2, T, p);
	printf("search '2':\n");
	printf("search status: %d\n", status);
	printf("search result: "); printBST(p); printf("\n");

	//insert
	//ElemType e;
	//e.key = 5;
	//InsertBST(T, e);
	//printf("insert '5':\n");
	//PreOrderBST(T);	printf("\n");
	//MidOrderBST(T);	printf("\n");
	//ElemType e;
	//e.key = 5;
	//bool flag = InsertBST(T, e);
	//printf("insert '5':\n");
	//printf("insert status: %d\n", flag);
	//PreOrderBST(T);	printf("\n");
	//MidOrderBST(T);	printf("\n");

	////delete
	////delete leaf
	//DeleteBST(T, 10);
	//printf("after delete '10': \n");
	////delete tree with right child
	//DeleteBST(T, 9);
	//printf("after delete '9': \n");
	//DeleteBST(T, 5);
	//printf("after delete '5': \n");
	////delete tree with both child
	//DeleteBST(T, 4);
	//printf("after delete '4': \n");
	//DeleteBST(T, 6);
	//printf("after delete '6': \n");
	//DeleteBST(T, 50);
	//printf("after delete '50': \n");
	//PreOrderBST(T);	printf("\n");
	//MidOrderBST(T);	printf("\n");
}


int main()
{
	freopen("in.txt", "r", stdin);
	//freopen("in1.txt", "r", stdin);

	test0();

	freopen("con", "r", stdin);
	system("pause");
	return 0;
}