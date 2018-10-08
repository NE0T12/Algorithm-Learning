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
	int diff; //平衡因子，左子树高度hl - 右子树高度hr; -1、0、1表示平衡，此外不平衡
	struct BiTNode * lchild;
	struct BiTNode * rchild;
}*BiTree;

Status SearchAVL(BiTree T, KeyType key, BiTree f, BiTree &p);
Status InsertAVL(BiTree &T, ElemType &e);
Status DeleteAVL(BiTree &T, KeyType key); //参照 DeleteBST(BiTree &T, KeyType key);
void CreateAVL(BiTree &T);

void PreOrderBiTree(BiTree T);
void MidOrderBiTree(BiTree T);
void LastOrderBiTree(BiTree T);
void printBiTree(BiTree T);

static Status InsertAVL_real(BiTree &T, ElemType &e);
static Status DeleteAVL_real(BiTree &T, KeyType key);
static void rotate_right(BiTree &T);
static void rotate_left(BiTree &T);
static Status delete_node(BiTree &T);
static int count_tree_height(BiTree &T, int depth, int &height); //计算树的高度
static void balance(BiTree &T, BiTree &parent); //平衡
static void balance_tree_real(BiTree &T); //平衡树
static void balance_tree(BiTree &T); //平衡树
static void refresh_tree_diff(BiTree &T); //更新树的平衡因子

Status DeleteAVL(BiTree &T, KeyType key)
{
	bool status = DeleteAVL_real(T, key);
	if (status)
		balance_tree(T);

	return status;
}

Status DeleteAVL_real(BiTree &T, KeyType key)
{
	if (!T)
		return false;

	if (key == T->data.key)
		return delete_node(T);
	else if (key < T->data.key)
		DeleteAVL_real(T->lchild, key);
	else
		DeleteAVL_real(T->rchild, key);
}

Status delete_node(BiTree &T)
{	
	BiTree q, s;

	if (!T->lchild && !T->rchild)
	{
		delete T;
		T = NULL;
	}
	else if (!T->lchild)
	{
		q = T->rchild;
		T->data = q->data;
		T->lchild = q->lchild; T->rchild = q->rchild;

		delete q;
	}
	else if (!T->rchild)
	{
		q = T->lchild;
		T->data = q->data;
		T->rchild = q->rchild; T->lchild = q->lchild;

		delete q;
	}
	else
	{
		q = T;
		s = T->lchild;
	
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

void CreateAVL(BiTree &T)
{
	ElemType e;
	while (scanf("%d", &e.key) == 1)
		InsertAVL(T, e);
}

void printBiTree(BiTree T)
{
	if (T)
		printf("%d ", T->data.key);
}

void PreOrderBiTree(BiTree T)
{
	printBiTree(T);
	if (T->lchild)
		PreOrderBiTree(T->lchild);
	if (T->rchild)
		PreOrderBiTree(T->rchild);
}

void MidOrderBiTree(BiTree T)
{
	if (T->lchild)
		MidOrderBiTree(T->lchild);
	printBiTree(T);
	if (T->rchild)
		MidOrderBiTree(T->rchild);
}

void LastOrderBiTree(BiTree T)
{
	if (T->lchild)
		LastOrderBiTree(T->lchild);
	if (T->rchild)
		LastOrderBiTree(T->rchild);
	printBiTree(T);
}

Status SearchAVL(BiTree T, KeyType key, BiTree f, BiTree &p)
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
		return SearchAVL(T->lchild, key, T, p);
	else
		return SearchAVL(T->rchild, key, T, p);
}

Status InsertAVL(BiTree &T, ElemType &e)
{
	if (!T)
	{
		BiTree s = new BiTNode;
		s->data = e; s->lchild = s->rchild = NULL;
		s->diff = 0;
		T = s;
		return true;
	}
	else if (e.key == T->data.key)
		return false;//关键字等于e.key的数据元素，返回錯誤
	else
	{
		bool status = InsertAVL_real(T, e);
		if (status)
			balance_tree(T);
		return status;
	}
}

Status InsertAVL_real(BiTree &T, ElemType &e)
{
	if (!T)
	{
		BiTree s = new BiTNode;
		s->data = e; s->lchild = s->rchild = NULL;
		s->diff = 0;
		T = s;
		return true;
	}
	if (e.key == T->data.key)
		return false;//关键字等于e.key的数据元素，返回錯誤	
	else if (e.key < T->data.key)
		return InsertAVL_real(T->lchild, e);
	else if (e.key > T->data.key)
		return InsertAVL_real(T->rchild, e);

	return true;
}

void rotate_left(BiTree &T)
{
	BiTree q = new BiTNode;
	q->data = T->data; q->lchild = T->lchild;
	q->diff = 0;

	BiTree tmp_rchild = T->rchild;
	T->data = tmp_rchild->data;
	
	q->rchild = tmp_rchild->lchild;
	T->lchild = q;
	T->rchild = tmp_rchild->rchild;

	delete tmp_rchild;
}

void rotate_right(BiTree &T)
{
	BiTree q = new BiTNode;
	q->data = T->data; q->rchild = T->rchild;
	q->diff = 0;

	BiTree tmp_lchild = T->lchild;
	T->data = tmp_lchild->data;

	q->lchild = tmp_lchild->rchild;
	T->rchild = q;
	T->lchild = tmp_lchild->lchild;

	delete tmp_lchild;
}

static int count_tree_height(BiTree &T, int depth, int &height) //计算树的高度
{
	if (!T)
	{
		height = 0;
		return height;
	}

	if (T->lchild)
		count_tree_height(T->lchild, depth + 1, height);
	if (T->rchild)
		count_tree_height(T->rchild, depth + 1, height);
	if (depth > height)
		height = depth;

	return height;
}

static void refresh_tree_diff(BiTree &T)
{
	if (!T)
		return;
	if (T->lchild)
		refresh_tree_diff(T->lchild);
	if (T->rchild)
		refresh_tree_diff(T->rchild);

	int hl = 0, hr = 0;
	T->diff = count_tree_height(T->lchild, 1, hl) - count_tree_height(T->rchild, 1, hr);
}

static void balance_tree(BiTree &T)
{
	refresh_tree_diff(T);
	balance_tree_real(T);
	refresh_tree_diff(T);
}

static void balance_tree_real(BiTree &T)
{
	if (!T)
		return;

	if (2 == T->diff || -2 == T->diff)
	{
		balance(T, T);
		refresh_tree_diff(T);
	}

	if (T->lchild)
		balance_tree_real(T->lchild);
	if (T->rchild)
		balance_tree_real(T->rchild);
}

static void balance(BiTree &T, BiTree &parent) //平衡树
{
	if (2 == T->diff && T->lchild)
		balance(T->lchild, T);
	else if (-2 == T->diff && T->rchild)
		balance(T->rchild, T);
	else if (1 == T->diff)
	{
		if (2 == parent->diff) //左左
			rotate_right(parent);
		else if (-2 == parent->diff) //右左
		{
			rotate_right(T);
			rotate_left(parent);
		}
	}
	else if (-1 == T->diff)
	{
		if (-2 == parent->diff) //右右
			rotate_left(parent);
		else if (2 == parent->diff) //左右
		{
			rotate_left(T);
			rotate_right(parent);
		}
	}
}

void test0()
{
	BiTree T = NULL;

	//create
	CreateAVL(T);
	PreOrderBiTree(T);	printf("\n");
	MidOrderBiTree(T);	printf("\n");

	//search
	BiTree p;
	bool status;
	status = SearchAVL(T, 2, T, p);
	printf("search '2':\n");
	printf("search status: %d\n", status);
	printf("search result: "); printBiTree(p); printf("\n");

	////insert
	//ElemType e;
	//e.key = 11;
	//bool flag = InsertAVL(T, e);
	//printf("insert '11':\n");
	//printf("insert status: %d\n", flag);
	//PreOrderBiTree(T);	printf("\n");
	//MidOrderBiTree(T);	printf("\n");
	//e.key = 15;
	//flag = InsertAVL(T, e);
	//printf("insert '15':\n");
	//printf("insert status: %d\n", flag);
	//PreOrderBiTree(T);	printf("\n");
	//MidOrderBiTree(T);	printf("\n");
	//e.key = 16;
	//flag = InsertAVL(T, e);
	//printf("insert '16':\n");
	//printf("insert status: %d\n", flag);
	//PreOrderBiTree(T);	printf("\n");
	//MidOrderBiTree(T);	printf("\n");

	//delete
	////delete leaf
	//DeleteAVL(T, 10);
	//printf("after delete '10': \n");
	////delete tree with left child
	//DeleteAVL(T, 2);
	//printf("after delete '2': \n");
	//DeleteAVL(T, 5);
	//printf("after delete '5': \n");
	//delete tree with both child
	//DeleteAVL(T, 7);
	//printf("after delete '7': \n");
	//PreOrderBiTree(T);	printf("\n");
	//MidOrderBiTree(T);	printf("\n");

	printf("\n");
}

int main()
{
	freopen("in.txt", "r", stdin);
	//freopen("in1.txt", "r", stdin);
	//freopen("in2.txt", "r", stdin);
	//freopen("in3.txt", "r", stdin);

	test0();

	freopen("con", "r", stdin);
	system("pause");
	return 0;
}