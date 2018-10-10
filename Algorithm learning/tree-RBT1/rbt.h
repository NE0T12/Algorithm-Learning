/*
 * 红黑树(red-black tree, rbt)
 * language: C++
 * Author: ne0t12
*/

#ifndef _RBT_H_
#define _RBT_H_

#include <stdio.h>
#include <iostream>

#define KeyType int
#define Status bool

const static int RED = 1;
const static int BLACK = 2;

typedef struct Elem
{
	KeyType key;
}ElemType;

typedef struct BiTreeNode
{
	ElemType data;
	int color;
	struct BiTreeNode * parent;
	struct BiTreeNode * lchild;
	struct BiTreeNode * rchild;
}*BiTree;

class RedBlackTree
{
public:
	RedBlackTree(): _root(NULL)
	{
		_nil = new BiTreeNode();
		_nil->color = BLACK;
	}

	~RedBlackTree()
	{
		if(_root)
			delete _root;
		delete _nil;
	}

	void CreateRBT();
	Status InsertRBT(ElemType &e);
	Status SearchRBT(BiTree T, KeyType key, BiTree f, BiTree &p);
	Status DeleteRBT(KeyType key);

	void PreOrderVisit(void (*function)(BiTree));
	void MidOrderVisit(void(*function)(BiTree));
	void LastOrderVisit(void(*function)(BiTree));
	
private:
	Status InsertRBT_real(BiTree &T, BiTree &parent, ElemType &e);
	void insert_adjust_color(BiTree &T);

	Status DeleteRBT_real(BiTree &T, KeyType key);
	void delete_one_child(BiTree &T);
	void delete_adjust_color(BiTree &T);
	void swap_data(BiTree &T1, BiTree &T2);
	BiTree & get_smallest_child(BiTree &T);

	Status SearchRBT_real(BiTree T, KeyType key, BiTree f, BiTree &p);

	void PreOrderVisit_real(BiTree T, void(*function)(BiTree));
	void MidOrderVisit_real(BiTree T, void(*function)(BiTree));
	void LastOrderVisit_real(BiTree T, void(*function)(BiTree));

	BiTree & uncle(BiTree T);
	BiTree & grandparent(BiTree T);
	BiTree & sibling(BiTree T);

	void rotate_right(BiTree & T);
	void rotate_left(BiTree & T);

private:
	BiTree _root;
	BiTree _nil; //不存储数据，只为了表示黑色叶子
};

#endif