#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct elem 
{
	int data;
	elem* next;
};

struct node
{
	int data;
	node* left;
	node* right;
};

elem* create_list(ifstream& in) 
{
	if (in.eof()) return NULL;
	elem* top = new elem;
	in >> top->data;
	top->next = create_list(in);
	return top;
}

elem* create_list(int n)
{
	if (n == 0) return NULL;
	elem* top = new elem;
	cin >> top->data;
	top->next = create_list(n-1);
	return top;
}

void print_list(elem* top) 
{
	if (top == NULL)
	{
		cout << endl;
		return;
	}
	cout << top->data << ' ';
	print_list(top->next);
}

int count_x(elem* top, int x) 
{
	if (top == NULL) return 0;
	if (x == top->data)
		return 1 + count_x(top->next, x);
	else
		return count_x(top->next, x);
}

void addy_afterx(elem* top, int x, int y) 
{
	if (top == NULL) return;
	if (top->data == x) 
	{
		elem* p = new elem;
		p->data = y;
		p->next = top->next;
		top->next = p;
		top = top->next;
	}
	addy_afterx(top->next, x, y);
}

elem* copy_list(elem* top) 
{
	if (top == NULL) return NULL;
	return new elem{ top->data, copy_list(top->next) };
}

bool are_equal(elem* t1, elem* t2) 
{
	if (t1 != NULL && t2 == NULL || t1 != NULL && t2 == NULL) return false;
	if (t1 == NULL && t2 == NULL) return true;
	if (t1->data == t2->data) return are_equal(t1->next, t2->next);
	else return false;
}

int max(int a, int b)
{
	if (a >= b) return a;
	return b;
}
int max_in_list(elem* top)
{
	if (top->next == NULL) return top->data;
	return max(top->data, max_in_list(top->next));
}

void reverse_print(elem* top)
{
	if (top == NULL) return;
	reverse_print(top->next);
	cout << top->data << ' ';
}

void delete_list(elem*& top)
{
	if (top == NULL) return;
	delete_list(top->next);
	delete top;
	top = NULL;
}

//void lists_merger(elem* t1, elem* t2)
//{
//	if (t1 == NULL || t2 == NULL) return;
//	if (t1->data <= t2->data && t1->next->data >= t2->data)
//	{
//		elem* p = new elem;
//		p->data = t2->data;
//		p->next = t1->next;
//		t1->next = p;
//		p = t2;
//		t1 = t1->next;
//		t2 = t2->next;
//		delete p;
//		lists_merger(t1, t2);
//	}
//	else if (t2->data < t1->data && t2->next->data >= t1->data)
//	{
//		elem* p = new elem;
//		p->data = t1->data;
//		p->next = t2->next;
//		t2->next = p;
//		p = t1;
//		t2 = t2->next;
//		t1 = t1->next;
//		delete p;
//		lists_merger(t1, t2);
//	}
//	else
//	{
//		lists_merger(t1->next, t2->next);
//	}
//}

elem* merge_lists(elem* top1, elem* top2)
{
	if (!top1 && !top2)
		return NULL;
	if (top1 == NULL)
		return top2;
	if (top2 == NULL)
		return top1;

	elem* top3 = new elem;
	if (top1->data < top2->data)
	{
		top3->data = top1->data;
		top3->next = merge_lists(top1->next, top2);
	}
	else
	{
		top3->data = top2->data;
		top3->next = merge_lists(top1, top2->next);
	}
	return top3;
}

elem* intersect_lists(elem* top1, elem* top2)
{
	if (!top1 && !top2)
		return NULL;
	if (top1 == NULL)
		return NULL;
	if (top2 == NULL)
		return NULL;

	elem* top3 = new elem;
	if (top1->data == top2->data)
	{
		top3->data = top1->data;
		top3->next = merge_lists(top1->next, top2);
	}
	else
	{
		top3->next = merge_lists(top1, top2->next);
	}
	return top3;
}

int count_x(node* root, int x)
{
	if (root == NULL)
		return 0;
	if (root->data == x)
		return 1 + count_x(root->left, x) + count_x(root->right, x);
	else
		return count_x(root->left, x) + count_x(root->right, x);
}

int sum_of_nodes(node* root)
{
	if (root == NULL)
		return 0;
	return root->data + sum_of_nodes(root->right) + sum_of_nodes(root->left);
}

int depth(node* root)
{
	if (root == NULL)
		return 0;
	int left_depth = depth(root->left);
	int right_depth = depth(root->right);
	int max_depth = max(left_depth, right_depth) + 1;
	return max_depth;
}

int count_level_nodes(node* root, int n)
{
	if (n == 1 && root)
		return 1;
	else if (n == 1 && !root)
		return 0;
	return count_level_nodes(root->left, n - 1) + count_level_nodes(root->right, n - 1);
}

void del_tree(node* root)
{
	if (root == NULL)
		return;
	del_tree(root->left);
	del_tree(root->right);
	delete root;
}

node* copy_tree(node* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	node* p = new node;
	p->data = root->data;
	p->left = copy_tree(root->left);
	p->right = copy_tree(root->right);
	return p;
}

bool are_equal(node* r1, node* r2)
{
	if (r1 == NULL && r2 == NULL) return true;
	if (r1 == NULL && r2 != NULL || r1 != NULL && r2 == NULL)
		return false;
	if (r1->data != r2->data)
		return false;
	return are_equal(r1->left, r2->left) && are_equal(r1->right, r2->right);
}

node* search_in_tree(node* root, int data)
{
	if (!root) return nullptr;
	if (root->data == data) return root;
	if (data > root->data)
		return search_in_tree(root->right, data);
	if (data < root->data)
		return search_in_tree(root->left, data);
}

node* insert(node* root, int data)
{
	if (!root) return new node{ data, nullptr, nullptr };
	if (data > root->data)
		root->right = insert(root->right, data);
	else if (data < root->data)
		root->left = insert(root->left, data);
	return root;
}

void inorder(node* root)
{
	if (!root) return ;
	inorder(root->left);
	cout << root->data << ' ';
	inorder(root->right);
}

int main()
{
	elem* l1 = create_list(4);
	print_list(l1);

	/*cout << count_x(l1, 2) << endl;

	addy_afterx(l1, 2, 2);
	print_list(l1);*/

	/*elem* l2 = copy_list(l1);
	addy_afterx(l2, 1, 0);
	print_list(l2);
	cout << are_equal(l1, l2) << endl;*/

	//cout << max_in_list(l1);

	/*reverse_print(l1);
	delete_list(l1);
	print_list(l1);*/

	/*elem* l2 = create_list(4);
	elem* l3 = intersect_lists(l1, l2);
	print_list(l3);*/

	elem* l2 = create_list(4);
	elem* l3 = merge_lists(l1, l2);
	print_list(l3);

	/*node* root = new node{ 5, nullptr, nullptr };
	insert(root, 3);
	insert(root, 2);
	insert(root, 4);
	insert(root, 7);
	insert(root, 6);
	insert(root, 8);
	inorder(root);

	cout << endl;
	cout << count_x(root, 8) << endl;
	cout << sum_of_nodes(root) << endl;
	cout << depth(root) << endl;
	cout << count_level_nodes(root, 3) << endl;
	node* n = search_in_tree(root, 8);
	cout << n->data << endl;

	node* root1 = copy_tree(root);
	inorder(root1);*/

}
