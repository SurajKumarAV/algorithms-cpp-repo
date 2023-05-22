#include <iostream>
#include <fstream>
#include <algorithm>
#include <initializer_list>
using namespace std;

template<typename T>
class Vector
{
	int size;  // current size of list
	int capacity; // current capacity of list
	T* data;     // pointer to data
	public:
	static const int spare_capacity = 16;
	explicit Vector(int size=0) : size(size), capacity(size + spare_capacity)
	{
		data = new T[capacity];
	}
	Vector(initializer_list<T> l) : size(l.size()), capacity(size+spare_capacity)
	{
		data = new T[capacity];
		int itr = 0;
		for (auto it = l.begin(); it<=l.end(); it++)
		{
			data[itr++] = *it;
		}
	}
	// copy constructor with deep copy
	Vector(const Vector& obj) : size(obj.size), capacity(obj.capacity), T{nullptr}
	{
		data = new T[capacity];
		for (int i=0;i<size;i++)	data[i] = obj.data[i];
	}
	// operator assignment 
	Vector &operator=(const Vector &obj)
	{
		Vector copy = obj; // makes new Vector copy from obj using copy constructor
		std::swap(*this,copy); // uses swap to copy copy to this object
		return *this;
	}
	// destructor
	~Vector()
	{
		delete [] data;
	}
	// move constructor
	Vector(Vector &&obj) : size{obj.size},capacity{obj.capacity},data{obj.data}
	{
		obj.data = nullptr;
		obj.size = 0;
		obj.capacity = 0;
	}
	// move asignment operator
	Vector& operator=(Vector &&obj)
	{
		std::swap(size,obj.size);
		std::swap(capacity,obj.capacity);
		std::swap(data,obj.data);
		return *this;
	}
	void resize(int new_size)
	{
		if (new_size > capacity)
			reserve(new_size*2);
		size = new_size;
	}
	void reserve(int new_capacity)
	{
		if (new_capacity < size)
			return;
		T* newArray = new T[new_capacity];
		for (int k=0;k<size;++k)
			newArray[k] = std::move(data[k]);
			
		capacity = new_capacity;
		std::swap(data,newArray);
		delete [] newArray;
	}
	
	T& operator[](int index)
	{
		return data[index];
	}
	
	
	const T& operator[](int index) const
	{
		return data[index];
	}
	
	bool empty() const
	{
		return size == 0;
	}
	int get_size() const
	{
		return size;
	}
	int get_capacity() const
	{
		return capacity;
	}
	void push_back(const T& x)
	{
		if (size == capacity)
			reserve(2*capacity+1);
		data[size++] = x;
	}
	void push_back(T&& x)
	{
		if (size == capacity)
			reserve(2*capacity+1);
		data[size++] = std::move(x);
	}
	void pop_back()
	{
		--size;
	}
	const T& back() const
	{
		return data[size-1];
	}
	friend ostream& operator<<(ostream &oss, Vector& obj)
	{
		if (!obj.size)	return oss << "Empty!!";
		for (int i = 0;i<obj.size;i++)	oss << " " << obj.data[i];
		return oss;
	}
	template<typename U> struct Iterator
	{
		U* current;
		Iterator(U* current): current{current} {}
		
		bool operator!=(const Iterator<U>& other)
		{
			return current != other.current;
		}
		Iterator<U>& operator++()
		{
			current++;
			return *this;
		}
		Iterator<U>& operator--()
		{
			current--;
			return *this;
		}
		U& operator*()
		{
			return *current;
		}
		
	};
	typedef Iterator<T> iterator;
	iterator begin()
	{
		return iterator{&data[0]};
	}
	iterator end()
	{
		return iterator{&data[get_size()]};
	}
	
};

int main()
{
	/*
	Vector<int> a;
	cout << a << endl;
	Vector<double> b{3};
	cout << b << endl; 
	b.push_back(1.2);
	a.push_back(1);
	cout << a << endl;
	cout << b << endl;
	b[2] = b[1];
	
	cout << b << endl;
	cout << b[2] << endl;
	*/
	/*
	Vector<int> a{1,2,3};
	cout << a << endl;
	Vector<int> b = {1,2,3,4};
	cout << b << endl;
	Vector<int> c{2};
	cout << c << endl;
	*/
	Vector<int> a{1,2,3,4,5};
	cout << a << endl;
	Vector<int>::iterator it=a.begin();
	cout << *it << endl;
	++it;
	cout << *it << endl;
	while(++it != a.end())	cout << *it << endl;
	
	for (auto&& e : a)	cout << e << endl;
}
