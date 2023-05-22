#pragma once
#include <iostream>
#include <fstream>
#include <initializer_list>

template<typename T> 
class SingleLinkedList 
{
	int csize{0};
	struct Node
	{
		T data;
		Node* next{nullptr};
		Node(){}
		Node(const T& d) : data{d} {}
		Node(T&& d) : data{std::move(d)} {}
	};
	Node* head{nullptr};
	public:
	SingleLinkedList(){} 
	SingleLinkedList(const SingleLinkedList& obj)
	{
		for (auto& node : obj)	
		{
			push_back(node);		
		}
	}
	SingleLinkedList& operator=(const SingleLinkedList& obj)
	{
		std::swap(*this,obj);
		return *this;
	}
	~SingleLinkedList()
	{
		delete head;
	}
	//SingleLinkedList(SingleLinkedList&&);
	//SingleLinkedList& operator=(SingleLinkedList&&);
	void push_front(const T& data)
	{
		Node* newNode = new Node(data);
		if(!head)	
		{
			head = newNode; 
			csize++;
			return;
		}
		newNode->next = head;
		head = newNode;
		csize++;
	}
	void push_front(T&& data)
	{
		Node* newNode = new Node(data);
		if(!head)	
		{
			head = newNode; 
			csize++;
			return;
		}
		newNode->next = head;
		head = newNode;
		csize++;
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
			Node* newNode = new Node(data);
			Node* temp = head;
			for (int i=1;i<=pos-2;i++)	temp = temp->next;
			newNode->next = temp->next;
			temp->next = newNode;
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
			Node* newNode = new Node(data);
			Node* temp = head;
			for (int i=1;i<=pos-2;i++)	temp = temp->next;
			newNode->next = temp->next;
			temp->next = newNode;
			csize++;
		}
		else
		{
			std::cout << "Error in insert index. Index should be between (1," << csize << ")" << std::endl;
			return;
		}	
	}
	void pop_back()
	{
		remove(csize);
	}
	void pop_front()
	{
		Node* tmp = head;
		head = tmp->next;
		delete tmp;
		csize--;
	}
	void remove(int pos)
	{
		if (pos == 1)	pop_front();
		else if (pos > 1 && pos <= csize+1)
		{
			Node* prevNode = head;
			for (int i=1;i<=pos-2;i++)	prevNode = prevNode->next;
			Node* dnode = prevNode->next;
			prevNode->next = dnode->next;
			delete dnode;
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
	
	int size(){return csize;};

	friend std::ostream& operator<<(std::ostream &oss,SingleLinkedList& obj)
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
	template<typename U> class forward_iterator
	{
	};
	template<typename U> class const_forward_iterator
	{
	};
	typedef forward_iterator<T> iterator;
	typedef const_forward_iterator <T> const_iterator;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
};
