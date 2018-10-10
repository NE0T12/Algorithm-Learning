#include "rbt.h"

void RedBlackTree::CreateRBT()
{
	ElemType e;
	while (scanf("%d", &e.key) == 1)
		InsertRBT(e);
	printf("\n");
}

Status RedBlackTree::InsertRBT(ElemType &e)
{
	bool s = InsertRBT_real(_root, _root, e);
	return s;
}

Status RedBlackTree::InsertRBT_real(BiTree &T, BiTree &parent, ElemType &e)
{
	if (!T || T == _nil)
	{
		BiTree s = new BiTreeNode;
		s->data = e; s->lchild = s->rchild = _nil;	s->parent = parent;
		s->color = RED;
		T = s;

		insert_adjust_color(T);

		return true;
	}
	else if (e.key == T->data.key)
		return false;//�ؼ��ֵ���e.key������Ԫ�أ������e�`
	else if (e.key < T->data.key)
		return InsertRBT_real(T->lchild, T, e);
	else if (e.key > T->data.key)
		return InsertRBT_real(T->rchild, T, e);

}

void RedBlackTree::insert_adjust_color(BiTree &T)
{
	// case1: �����
	if (NULL == T->parent) 
		T->color = BLACK;
	else
	{
		// case2: ���ڵ�Ϊ��
		if (BLACK == T->parent->color)
			return;
		else
		{
			// case3: ���ڵ�Ϊ�죬�常���ҲΪ��
			if (RED == uncle(T)->color)
			{
				T->parent->color = BLACK;
				uncle(T)->color = BLACK;
				grandparent(T)->color = RED;
				insert_adjust_color(grandparent(T)); //�ݹ�����游�����ɫ
			}
			else
			{
				// case4: ���ڵ�Ϊ�죬�常���Ϊ�ڻ��
				if (T == T->parent->rchild && T->parent == grandparent(T)->lchild) //����
				{
					T->color = BLACK; grandparent(T)->color = RED;

					rotate_left(T->parent);
					rotate_right(grandparent(T));
				}
				else if (T == T->parent->lchild && T->parent == grandparent(T)->rchild) //����
				{
					T->color = BLACK; grandparent(T)->color = RED;

					rotate_right(T->parent);
					rotate_left(grandparent(T));
				}
				else if (T == T->parent->lchild && T->parent == grandparent(T)->lchild) //����
				{
					T->parent->color = BLACK;  grandparent(T)->color = RED;
					rotate_right(grandparent(T));
				}
				else if (T == T->parent->rchild && T->parent == grandparent(T)->rchild) //����
				{
					T->parent->color = BLACK;  grandparent(T)->color = RED;
					rotate_left(grandparent(T));
				}
			}
		}
	}

}

Status RedBlackTree::DeleteRBT(KeyType key)
{
	Status s = DeleteRBT_real(_root, key);
	return s;
}

Status RedBlackTree::DeleteRBT_real(BiTree &T, KeyType key)
{
	if (!T || T == _nil)
		return false;
	else if (key < T->data.key)
		return DeleteRBT_real(T->lchild, key);
	else if (key > T->data.key)
		return DeleteRBT_real(T->rchild, key);
	else
	{
		if(T->rchild == _nil)
			delete_one_child(T);
		else
		{
			BiTree smallest_child = get_smallest_child(T->rchild);
			swap_data(smallest_child, T);
			delete_one_child(smallest_child); //������ת��Ϊɾ��һ�����ӵ����
		}
	}

	return true;
}

BiTree & RedBlackTree::get_smallest_child(BiTree &T)
{
	if (T->lchild == _nil)
		return T;
	else
		return get_smallest_child(T->lchild);
}

void RedBlackTree::delete_one_child(BiTree &T)
{
	if (!T->parent && T->lchild == _nil && T->rchild == _nil)
	{
		delete T; T = NULL;
		return;
	}

	BiTree child = (T->lchild == _nil ? T->rchild : T->lchild);
	if (!T->parent)
	{
		child->parent = NULL;
		delete T;
		T = child;
		T->color = BLACK;
		return;
	}

	//ע�⣺���￪ʼ�Ѿ��൱�ڰ� Ҫɾ�����T �޳���ȥ�ˣ�����parent->T->child ==> parent->child��
	if (T == T->parent->lchild)
		T->parent->lchild = child;
	else
		T->parent->rchild = child;

	child->parent = T->parent;


	if (T->color == BLACK)
	{
		if (child->color == RED)
			child->color = BLACK;
		else
			delete_adjust_color(child); //T��T->child����ɫ���Ǻ�ɫ����Ҫ������ɫ����
	}
	delete T; //����ɾ�� Ҫɾ���Ľ��T
	
}

void RedBlackTree::delete_adjust_color(BiTree &T) //T->color = BLACK;
{
	/*case1 */
	if (!T->parent)
		return;

	/*case2 */
	//��Ϊ T��T�ĳ�ʼ��ĸ ���Ǻ�ɫ����������sibling(T)�������ǿ�
	if (sibling(T)->color == RED) //��sibling(T)->color == RED���ɺ����������֪ T->parent->color == BLACK
	{
		T->parent->color = RED; sibling(T)->color = BLACK;
		if (T == T->parent->lchild)
			rotate_left(T->parent);
		else
			rotate_right(T->parent);
	}

	/*case3 */
	if (T->parent->color == BLACK
			&& sibling(T)->color == BLACK
			&& sibling(T)->lchild->color == BLACK
			&& sibling(T)->rchild->color == BLACK
		)
	{
		sibling(T)->color = RED; //ʵ�����������ֱ����case2
		delete_adjust_color(T->parent); //�ݹ����
	}
	else if (T->parent->color == RED	//case4
				&& sibling(T)->color == BLACK
				&& sibling(T)->lchild->color == BLACK
				&& sibling(T)->rchild->color == BLACK
			 )
	{
		T->parent->color = BLACK;
		sibling(T)->color = RED;
	}
	else
	{
		//case5
		if (sibling(T)->color == BLACK)
		{
			if (T == T->parent->lchild
				&& sibling(T)->lchild->color == RED
				&& sibling(T)->rchild->color == BLACK
				)
			{
				sibling(T)->color = RED;
				sibling(T)->lchild->color = BLACK;
				rotate_right(sibling(T));
			}
			else if (T == T->parent->rchild
						&& sibling(T)->lchild->color == BLACK
						&& sibling(T)->rchild->color == RED
					 )
			{
				sibling(T)->color = RED;
				sibling(T)->rchild->color = BLACK;
				rotate_left(sibling(T));
			}
		}

		//case6
		sibling(T)->color = T->parent->color;
		T->parent->color = BLACK;
		if (T == T->parent->lchild)
		{
			sibling(T)->rchild->color = BLACK;
			rotate_left(T->parent);
		}
		else
		{
			sibling(T)->lchild->color = BLACK;
			rotate_right(T->parent);
		}
	}

}

inline
BiTree & RedBlackTree::uncle(BiTree T)
{
	if (grandparent(T)->lchild == T->parent)
		return grandparent(T)->rchild;
	else if (grandparent(T)->rchild == T->parent)
		return grandparent(T)->lchild;
		
}

inline
BiTree & RedBlackTree::grandparent(BiTree T)
{
	return T->parent->parent;

}

inline
BiTree & RedBlackTree::sibling(BiTree T)
{
	if (T == T->parent->lchild)
		return T->parent->rchild;
	else
		return T->parent->lchild;
}

inline
void RedBlackTree::swap_data(BiTree &T1, BiTree &T2)
{
	Elem e = T1->data;
	T1->data = T2->data;
	T2->data = e;
}

//*�ɰ���ת����Ҫnew�ѿռ䣬�Լ�delete�ѿռ䣬�������ã�Ч�ʵ�*/
////ע�⣺��תҪ����parentָ��ı䣬�Լ���ɫ����
//void RedBlackTree::rotate_left(BiTree & T)
//{
//	BiTree q = new BiTreeNode;
//	q->data = T->data; q->lchild = T->lchild;
//	if (T->lchild)
//		T->lchild->parent = q;
//	q->color = T->color;
//
//	BiTree tmp_rchild = T->rchild;
//	T->data = tmp_rchild->data; T->color = tmp_rchild->color;
//
//	q->rchild = tmp_rchild->lchild;
//	if (tmp_rchild->lchild)
//		tmp_rchild->lchild->parent = q;
//
//	T->lchild = q;	q->parent = T;
//
//	T->rchild = tmp_rchild->rchild;
//	if (tmp_rchild->rchild)
//		tmp_rchild->rchild->parent = T;
//
//	delete tmp_rchild;
//}
//
//void RedBlackTree::rotate_right(BiTree & T)
//{
//	BiTree q = new BiTreeNode;
//	q->data = T->data; q->rchild = T->rchild;
//	if (T->rchild)
//		T->rchild->parent = q;
//	q->color = T->color;
//
//	BiTree tmp_lchild = T->lchild;
//	T->data = tmp_lchild->data; T->color = tmp_lchild->color;
//
//	q->lchild = tmp_lchild->rchild;
//	if (tmp_lchild->rchild)
//		tmp_lchild->rchild->parent = q;
//
//	T->rchild = q; q->parent = T;
//
//	T->lchild = tmp_lchild->lchild;
//	if (tmp_lchild->lchild)
//		tmp_lchild->lchild->parent = T;
//
//	delete tmp_lchild;
//}

void RedBlackTree::rotate_left(BiTree & T)
{
	BiTree parent = T->parent;
	BiTree r = T->rchild;

	T->rchild = r->lchild;
	if (r->lchild && r->lchild != _nil)
		r->lchild->parent = T;

	r->lchild = T;
	T->parent = r;

	if (parent)
	{
		if (T == parent->rchild)
			parent->rchild = r;
		else
			parent->lchild = r;
	}
	else
		_root = r;
	r->parent = parent;
}

void RedBlackTree::rotate_right(BiTree & T)
{
	BiTree parent = T->parent;
	BiTree l = T->lchild;

	T->lchild = l->rchild;
	if (l->rchild && l->rchild != _nil)
		l->rchild->parent = T;

	l->rchild = T;
	T->parent = l;

	if (parent)
	{
		if (T == parent->rchild)
			parent->rchild = l;
		else
			parent->lchild = l;
	}
	else
		_root = l;
	l->parent = parent;
}

void RedBlackTree::PreOrderVisit(void (*function)(BiTree))
{
	PreOrderVisit_real(_root, function);
}

void RedBlackTree::MidOrderVisit(void(*function)(BiTree))
{
	MidOrderVisit_real(_root, function);
}

void RedBlackTree::LastOrderVisit(void(*function)(BiTree))
{
	LastOrderVisit_real(_root, function);
}

void RedBlackTree::PreOrderVisit_real(BiTree T, void(*function)(BiTree))
{
	if(T != _nil)
		function(T);
	if (T->lchild)
		PreOrderVisit_real(T->lchild, function);
	if (T->rchild)
		PreOrderVisit_real(T->rchild, function);
}

void RedBlackTree::MidOrderVisit_real(BiTree T, void(*function)(BiTree))
{
	if (T->lchild)
		MidOrderVisit_real(T->lchild, function);
	if (T != _nil)
		function(T);
	if (T->rchild)
		MidOrderVisit_real(T->rchild, function);
}

void RedBlackTree::LastOrderVisit_real(BiTree T, void(*function)(BiTree))
{
	if (T->lchild)
		LastOrderVisit_real(T->lchild, function);
	if (T->rchild)
		LastOrderVisit_real(T->rchild, function);
	if (T != _nil)
		function(T);
}