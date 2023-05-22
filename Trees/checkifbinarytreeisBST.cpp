#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int data;
	Node* left{nullptr};
	Node* right{nullptr};
	Node(int data) : data{data} {}
};

// Approach 1: Bruteforce - pretty expensive approach and redundant checks 
bool IsBinarySearchTree(Node* root); // Check if a binary tree is a binary search tree
bool IsSubTreeLesser(Node* root, int value);
bool IsSubTreeGreater(Node* root, int value);

// Approach 2: Range based check - removal of IsSubTreeLesser/Greater
bool IsBinarySearchTree(Node* root, int min, int max);

int main()
{
	Node* tree1 = new Node(7);
	tree1->left = new Node(4); tree1->right = new Node(9);
	tree1->left->left = new Node(1); tree1->left->right = new Node(6);
	cout << IsBinarySearchTree(tree1) << endl;
	cout << IsBinarySearchTree(tree1,INT_MIN,INT_MAX) << endl;
}

bool IsBinarySearchTree(Node* root, int min, int max)
{
	if (!root) return true;
	if ((root->data > min) && (root->data < max) && (IsBinarySearchTree(root->left,min,root->data)) && (IsBinarySearchTree(root->right,root->data,max)))	return true;
	else																													return false;
}

bool IsBinarySearchTree(Node* root)
{
	if (!root)	return true;
	if (IsSubTreeLesser(root->left,root->data) && IsSubTreeGreater(root->right,root->data) && IsBinarySearchTree(root->left) && IsBinarySearchTree(root->right))
	    return true;
 	else 
 		return false;
}

bool IsSubTreeLesser(Node* root,int value)
{
	if (!root) return true;
	if ((root->data <= value) && IsSubTreeLesser(root->left,value) && IsSubTreeLesser(root->right,value))	return true;
	else 																									return false;
}

bool IsSubTreeGreater(Node* root,int value)
{
	if (!root) return true;
	if ((root->data >= value) && IsSubTreeGreater(root->right,value) && IsSubTreeGreater(root->right,value))	return true;
	else 																									return false;
}
