/*插入InsertRBT是可以的，*/
#include "rbt.h"

void printBiTreeNode(BiTree T)
{
	if (T)
		printf("%d ", T->data.key);
}

void testInsert()
{
	freopen("in2.txt", "r", stdin);
	RedBlackTree redBlackTree;
	redBlackTree.CreateRBT();

	redBlackTree.PreOrderVisit(printBiTreeNode); printf("\n");
	redBlackTree.MidOrderVisit(printBiTreeNode); printf("\n");

	Elem e;
	e.key = 15;
	redBlackTree.InsertRBT(e);
	e.key = 15;
	redBlackTree.InsertRBT(e);
	e.key = 16;
	redBlackTree.InsertRBT(e);

	redBlackTree.PreOrderVisit(printBiTreeNode); printf("\n");
	redBlackTree.MidOrderVisit(printBiTreeNode); printf("\n");
}

void testDelete()
{
	freopen("in.txt", "r", stdin);
	RedBlackTree redBlackTree;
	redBlackTree.CreateRBT();

	redBlackTree.PreOrderVisit(printBiTreeNode); printf("\n");
	redBlackTree.MidOrderVisit(printBiTreeNode); printf("\n");

	Elem e;
	e.key = 12;
	redBlackTree.DeleteRBT(e.key);

	redBlackTree.PreOrderVisit(printBiTreeNode); printf("\n");
	redBlackTree.MidOrderVisit(printBiTreeNode); printf("\n");
}

void test1()
{
	freopen("in.txt", "r", stdin);
	RedBlackTree redBlackTree;
	redBlackTree.CreateRBT();

}

int main()
{
	//testInsert();

	testDelete();

	//test1();

	freopen("con", "r", stdin);
	system("pause");
	return 0;
}