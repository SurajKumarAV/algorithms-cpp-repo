#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Node
{
	int data;
	Node* left{nullptr};
	Node* right{nullptr};
	Node(int data) : data{data} {}
};

class BST
{
	Node* root{nullptr};
	int SPACE{5};
	void insert(int x, Node* &t)
	{
		if (!t) t = new Node(x);
		else if (x < t->data)	insert(x,t->left);
		else if (x > t->data) 	insert(x,t->right);
		else {/*do nothing*/}
	}
	void remove(int x,Node* &t)
	{
		if (!t) return;
		else if (x < t->data)	remove(x,t->left);
		else if (x > t->data) remove(x,t->right);
		else 	// found the data
		{
			if (t->left && t->right)	// Two child
			{
				t->data = min(t->right); // set min of right to data
				remove(t->data,t->right); // remove that node
			}
			else 
			{
				Node* oldNode = t;
				t = (t->left != nullptr) ? t->left : t->right;
				delete oldNode;
			}
			
		}
		
	}
	bool search(int x,Node* t)
	{
		if (!t) return false;
		else if (t->data == x) return true;
		else if (x < t->data) return search(x,t->left);
		else if (x > t->data) return search(x,t->right);
	}
	int min(Node* t)
	{
		if (t->left)	 return min(t->left);
		else return t->data;
	}
	int height(Node* t)
	{
		if (!t) return -1;
		return max(height(t->left),height(t->right)) + 1;
	}
	void print(Node* t,int space)
	{
		if (!t) return;
		space += SPACE;
		print(t->right,space);
		cout << endl;
		for (int i=SPACE; i< space; i++)	cout << " ";
		cout << t->data << "\n";
		print(t->left,space); 
	}
	void PreOrderTraversal(Node* t)
	{
		if (!t) return;
		cout << t->data << " ";
		PreOrderTraversal(t->left);
		PreOrderTraversal(t->right);
	}
	void InOrderTraversal(Node* t)
	{
		if (!t) return;
		InOrderTraversal(t->left);
		cout << t->data << " ";
		InOrderTraversal(t->right);
	}
	
	void PostOrderTraversal(Node* t)
	{
		if (!t) return;
		PostOrderTraversal(t->left);
		PostOrderTraversal(t->right);
		cout << t->data << " ";
	}
	public:
	BST(){}
	~BST(){delete root;}
	void insert(int data)
	{
		insert(data,root);
	}
	void insert_nc(int data)
	{
		if (!root)	
		{
			root = new Node{data}; return;
		}
		Node* curr = root;
		Node* parent = root;
		while(curr)
		{
			parent = curr;
			if (data < curr->data)	
				curr = curr->left;	
			
			else if (data > curr->data)	
				curr = curr->right;
		}
		Node *node = new Node(data);
		if (data < parent->data) parent->left = node;
		else if (data > parent->data) parent->right = node;	
	} 
	void remove(int data)
	{
		remove(data,root);
	}
	bool search(int data)
	{
		bool ret = search(data,root);
		return ret;
	}
	int min_nc()
	{
		if (!root) return -1;
		Node* curr = root;
		while(curr->left)
			curr = curr->left;
		return curr->data;
	}
	int min()
	{
		min(root);
	}
	int get_height()
	{
		return height(root);
	}
	void LevelOrderTraversal() // start with root and push in queue, now while queue is empty, read root and push its child
	{
		if (!root) return;
		queue<Node*> Q;
		Node* rootNode = root;
		Q.push(rootNode);
		while(!Q.empty())
		{
			Node* curr = Q.front();
			cout << curr->data << " ";
			if (curr->left) Q.push(curr->left);
			if (curr->right) Q.push(curr->right);
			Q.pop();
		}
		cout << endl;
	}
	void PreOrderTraversal() // <root> <left> <right>
	{
		PreOrderTraversal(root);cout << endl;
	}
	void InOrderTraversal() // <left> <root> <right>
	{
		InOrderTraversal(root); cout << endl;
	}
	void PostOrderTraveral() // <left> <right> <root>
	{
		PostOrderTraversal(root);
	}
	void print()
	{
		print(root,5);
	}
	
};

int main()
{
	BST a;
	a.insert_nc(15);
	a.insert_nc(10);
	a.insert_nc(20);
	a.insert_nc(25);
	a.insert_nc(8);
	a.insert_nc(12);
	a.insert(7);
	a.print();
	
	/*
	BST b;
	b.insert(15);
	b.insert(10);
	b.insert(20);
	b.insert(25);
	b.insert(8);
	b.insert(12);
	b.insert(7);
	b.print();
	*/
	cout << a.search(11) << " " << a.search(8) << endl;
	cout << a.min_nc() << " " << a.min() << endl;
	cout << a.get_height() << endl;
	a.LevelOrderTraversal();
	//a.PreOrderTraversal();
	cout  << endl;
	cout << endl;
	BST b;
	b.insert(12);
	b.insert(5);
	b.insert(3);
	b.insert(1);
	b.insert(7);
	b.insert(9);
	b.insert(15);
	b.insert(13);
	b.insert(17);
	b.print();
	cout << endl;
	b.remove(15); b.print();
	
	
}	
