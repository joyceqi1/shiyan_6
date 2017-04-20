#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
typedef char DataType;
int judge(char a, char b)
{
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
class BinaryTree;
class BinTreeNode {
	friend  class BinaryTree;
public:
	BinTreeNode() { leftChild = NULL; rightChild = NULL; }
	BinTreeNode(DataType x, BinTreeNode *left = NULL, BinTreeNode *right = NULL) : data(x), leftChild(left), rightChild(right) { }               //构造函数  
	~BinTreeNode() { }
private:
	BinTreeNode *leftChild, *rightChild;
	DataType data;
};
class BinaryTree {
public:
	BinaryTree() : root(NULL) { }
	BinaryTree(DataType value) { RefValue = value; root = NULL; }
	void CreateBinTree() { CreateBinTree(root); }
	bool IsEmpty() { return (root == NULL) ? true : false; }
	BinTreeNode  *Parent(BinTreeNode  *current)
	{
		return (root == NULL || root == current) ? NULL : Parent(root);
	}
	BinTreeNode  *LeftChild(BinTreeNode  *current)
	{
		return (current != NULL) ? current->leftChild : NULL;
	}
	BinTreeNode  *RightChild(BinTreeNode  *current)
	{
		return (current != NULL) ? current->rightChild : NULL;
	}
	int calculate() { return calculate(root); }
	int getres( int left, int right) { return getres(root,left,right); }
	int ischar() { return ischar(root); }
	BinTreeNode  *GetRoot() const { return root; }
	void show() { show(root); }
private:
	BinTreeNode  *root;
	DataType RefValue;
	void CreateBinTree(BinTreeNode *&subTree);
	int ischar(BinTreeNode  * subTree);
	int calculate(BinTreeNode  * subTree);
	int getres(BinTreeNode  * subTree, int left, int right);
	void show(BinTreeNode * subTree);
};
void BinaryTree::show(BinTreeNode  *subTree)
{
	if (subTree != NULL) {
		if ((ischar(subTree)==1&& judge(subTree->data, subTree->leftChild->data) == 1)|| (ischar(subTree) == 1 && judge(subTree->data, subTree->rightChild->data) == 1))
		{
			show(subTree->leftChild);
			cout << subTree->data;
			cout << "(";
			show(subTree->rightChild);
			cout << ")";
		} 
		else
		{
			show(subTree->leftChild);
			cout << subTree->data;
			show(subTree->rightChild);
		}
	}
}
void BinaryTree::CreateBinTree(BinTreeNode *&subTree) {
	DataType item;	cin >> item;
	if (item != '@') {
		subTree = new   BinTreeNode(item);
		CreateBinTree(subTree->leftChild);
		CreateBinTree(subTree->rightChild);
	}
	else subTree = NULL;
};
int BinaryTree::calculate( BinTreeNode  * subTree) //求左右子树的值
{
	int left, right;
	if (subTree == NULL)
	{
		return 0;//空树的计算结果为0
	}
	else if (ischar(subTree) == 0)
	{
		return subTree->data;
	}
	else if (ischar(subTree->leftChild)==1)//判断子节点中有运算符
	{
		calculate(subTree->leftChild);
		calculate(subTree);
	}
	else if (ischar(subTree->rightChild) == 1)//判断子节点中有运算符
	{
		calculate(subTree->rightChild);
		calculate(subTree);
	}
	else 
	{
		 left = (int)subTree->leftChild->data - 48;
		 right = (int)subTree->rightChild->data - 48;
		 subTree->data = getres(subTree, left, right)+48 ;
	}
}
int BinaryTree::getres(BinTreeNode  * subTree,int left,int right)
{
	switch (subTree->data)
	{
	case '+':
		return left + right;
		break;
	case '-':
		return left - right;
		break;
	case '*':
		return left * right;
		break;
	case '/':
		return left / right;
		break;
	default:
		return 111;
		break;
	}
}
int BinaryTree::ischar(BinTreeNode  * subTree)//判断节点是否是运算符，是返回1，不是返回0
{
	if (subTree==NULL)
	{
		return 2;
	}
	else if (subTree->data<=57 && subTree->data >= 48)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int main()
{
    BinaryTree tree;
	BinTreeNode subTree1;
	tree.CreateBinTree();
	tree.show();
	cout <<"="<< tree.calculate() - 48<< endl;
	system("pause");
	return 1;
}

