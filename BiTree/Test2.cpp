
#include<iostream>
#include<stdio.h>
#include<vector>
#include<conio.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

typedef char ElemType;

//二叉树链式结构实现
typedef struct BinaryTreeNode
{
	ElemType data;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode(char n = 0)
	{
		data = n;
		left = NULL;
		right = NULL;
	}
}BiTree, * tree;

/*先序遍历二叉树的节点*/
void PreOrderTraverse(const tree& T);
/*中序遍历二叉树的节点*/
void InOrderTraverse(const tree& T);
/*后续遍历二叉树的节点*/
void PostOrderTraverse(const tree& T);
void CreateTree(tree& T);

void PreOrderTraverse(const tree& T)
{
	if (!T)//空树
	{
		return;
	}
	cout << T->data << " ";
	PreOrderTraverse(T->left);
	PreOrderTraverse(T->right);
}

void InOrderTraverse(const tree& T)
{
	if (!T)//空树
	{
		return;
	}
	InOrderTraverse(T->left);
	cout << T->data << " ";
	InOrderTraverse(T->right);
}

void PostOrderTraverse(const tree& T)
{
	if (!T)//空树
	{
		return;
	}
	PostOrderTraverse(T->left);
	PostOrderTraverse(T->right);
	cout << T->data << " ";
}

void CreateTree(tree& T)
{
	char input;
	cout << "Please input a char: ";
	cin >> input;
	if ('#' == input)//默认'#'为结束标示
	{
		return;
	}
	else
	{
		T = new BiTree;
		T->data = input;
		if (!T)//new failed
		{
			return;
		}
		CreateTree(T->left);
		CreateTree(T->right);
	}
}

tree CreateTreeByPI(vector<char>pre, vector<char>mid)
{
	if (0 == pre.size() ||
		(pre.size() != mid.size()) || 0 == mid.size())
	{
		return NULL;
	}
	tree root = new BiTree(pre[0]);
	int index = 0;
	vector<char>left_pre, right_pre, left_mid, right_mid;
	for (int i = 0; i < mid.size(); i++) {
		if (root->data == mid[i]) {
			index = i;
		}
	}
	int a = 0, b = 0, c = 0, d = 0;
	for (int i = 0; i < index; i++) {
		left_pre.push_back(pre[i + 1]);
		left_mid.push_back(mid[i]);
		a += (int)pre[i + 1];
		b += (int)mid[i];
	}
	if (a - b != 0) {
		cout << "Unmmatched" << endl;
		return NULL;
	}
	root->left = CreateTreeByPI(left_pre, left_mid);
	for (int j = index + 1; j < pre.size(); j++) {
		right_pre.push_back(pre[j]);
		right_mid.push_back(mid[j]);
		c += (int)pre[j];
		d += (int)mid[j];
	}
	if (c - d != 0) {
		cout << "Unmmatched" << endl;
		return NULL;
	}
	root->right = CreateTreeByPI(right_pre, right_mid);
	return root;
}

int Judge(char a[], char b[]) {
	int len_a = strlen(a);
	int len_b = strlen(b);
	if (len_a != len_b) {
		cout << "ERROR" << endl;
		return 0;
	}
	if (len_a <= 2 || len_b <= 2) {
		cout << "Too short!" << endl;
		return 0;
	}
	return 1;
}

bool paint(tree T, int x, int y) {
	char e[2] = { '\0','\0' };
	if (T) {
		e[0] = T->data;
		circle(x, y, 10);
		settextstyle(0, 0, _T("宋体"));
		outtextxy(x, y, e);
		Sleep(1000);
		if (T->left != NULL) {
			line(x, y, x + (200 - y), y + 40);
			paint(T->left, x + (200 - y), y + 40);
		}
		if (T->right != NULL) {
			line(x, y, x - (200 - y), y + 40);
			paint(T->right, x - (200 - y), y + 40);
		}
		return 1;
	}
	return 0;
}


int main(){
	tree T1;
	vector<char>pre, mid, post;
	// pre = "ABCDEF";
	// mid = "CBAEDF";
	// post = "CBEFDA";
	char a[100], b[100];
	cout << "Preorder:" << endl;
	cin >> a;
	cout << "Midorder:" << endl;
	cin >> b;
	int total = strlen(a);
	if (Judge(a, b)) {
		for (int i = 0; i < total; i++) {
			pre.push_back(a[i]);
		}
		for (int i = 0; i < total; i++) {
			mid.push_back(b[i]);
		}
	}
	T1 = CreateTreeByPI(pre, mid);
	//cout << "树T1的后序遍历为：　";
	PostOrderTraverse(T1);
	int x = 600;
	int y = 350;
	int GraphDriver = DETECT;
	int GraphMode;
	int color;
	color = WHITE;
	initgraph(1440, 960, SHOWCONSOLE); setcolor(color);
	paint(T1, x, y);
	//getchar();
	//closegraph();
	system("pause");
}