#pragma once
#include <iostream>
#include <fstream>

template<typename T>
class DLL
{
	struct Node
	{
		T data;
		Node* next{nullptr};
		Node* prev{nullptr};
		Node(){}
		Node(T&& d,Node *p=nullptr, Node *n=nullptr) : data{std::move(d)}, prev{p},next{n} {}
		Node(const T& d, Node *p=nullptr,Node *n=nullptr) : data{d}, prev{p},next{n} {}
	};	
	int csize{0};
	Node* head{nullptr};
	public:
	DLL(){}
	DLL(const DLL& obj)
	{
		for (auto& node : obj)	push_back(node);
	}
	~DLL()
	{
		delete head;
	}
	DLL& operator=(const DLL& obj)
	{
		std::swap(*this,obj);
	}
	//DLL(DLL&&);
	//DLL& operator=(DLL&&);
	int size() const{return csize;} 
	bool empty() const;
	void clear();
	void push_front(const T& data)
	{
		Node* newNode = new Node(data);
		if (!head)
		{
			head = newNode;
			csize++;
		}
		else
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
			csize++;
			
		}
	}
	void push_front(T&& data)
	{
		Node* newNode = new Node(data);
		if (!head)
		{
			head = newNode;
			csize++;
		}
		else
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
			csize++;
			
		}
	}
	void push_back(const T& data)
	{
		insert(csize+1,data);
	}
	void push_back(T&& data)
	{
		insert(csize+1,data);
	}
	void insert(int pos, const T& data)
	{
		if (pos == 1)	push_front(data);
		else if (pos > 1 && pos <= csize+1)
		{
			Node* node = new Node(data);
			Node* prev = head;
			for (int i=1; i<=pos-2;i++)	prev = prev->next;
			node->next = prev->next;
			prev->next = node;
			node->prev = prev;
			if (node->next)	node->next->prev = node;
			csize++;
		}
		else
		{
			std::cout << "Error in insert index. Index should be between (1," << csize << ")" << std::endl;
			return;
		}
	}
	void insert(int pos, T&& data)
	{
		if (pos == 1)	push_front(data);
		else if (pos > 1 && pos <= csize+1)
		{
			Node* node = new Node(data);
			Node* prev = head;
			for (int i=1; i<=pos-2;i++)	prev = prev->next;
			node->next = prev->next;
			prev->next = node;
			node->prev = prev;
			if (node->next)	node->next->prev = node;
			csize++;
		}
		else
		{
			std::cout << "Error in insert index. Index should be between (1," << csize << ")" << std::endl;
			return;
		}
	}
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	
	void pop_front()
	{
		Node* temp = head;
		head = temp->next;
		head->prev = nullptr;
		delete temp;
		csize--;
	}
	void pop_back()
	{
		remove(csize);
	}
	
	void remove(int pos)
	{
		if (pos == 1)	pop_front();
		else if (pos > 1 && pos <= csize+1)
		{
			Node* p = head;
			for (int i=1; i<=pos-2;i++)	p = p->next;
			Node* c = p->next;  // node to be deleted
			Node* n = c->next;
			p->next = n;
			if (n)	n->prev = p;
			delete c;
			csize--;
		}
		else
		{
			std::cout << "Error in remove index. Index should be between (1," << csize << ")" << std::endl;
			return;
		}
	}
	void remove(int from, int to)
	{
		for (int i=from; i<=to;i++)	remove(i);
	}
	friend std::ostream& operator<<(std::ostream &oss,DLL& obj)
	{
		Node *tmp = obj.head;
		while(tmp->next)
		{
			oss << " " << tmp->data;
			tmp = tmp->next;
		}
		oss << " " << tmp->data;
		return oss;
	}  
};

