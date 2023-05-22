#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
class Graph
{
	int _V;
	int _E;
	std::vector<int> *adj_list;	
	public:
	Graph(int V) : _V(V) 						// create a graph of V vertex
	{
		adj_list = new std::vector<int>[V];
		_E = 0;
	}	
	Graph(std::ifstream in);					// read graph from input stream
	
	int V() const {return _V;}					// returns the number of vertices
	int E() const {return _E;}					// returns the number of edges
	Graph& add_edge(int v,int w)				// add edge v-w to the graph - typically used when constructor with numer of vertex is invoked to build graph in step
	{
		adj_list[v].push_back(w);
		adj_list[w].push_back(v);
		_E = _E+1;
		return *this;
	}
	std::vector<int> adj(int v)	const 			// returns vertices adjacent to v
	{
		return adj_list[v];
	}
	friend std::ostream &operator<<(std::ostream& oss,const Graph& G)
	{
		for (int v = 0;v<G.V();v++)
		{
			oss << v << ":";
			for (int w : G.adj(v))	oss << " " << w;
			if (v < G.V()-1)	oss << std::endl;
		}
		return oss;
	}

	// graph processing 
	static int degree(Graph& G, int v)
	{
		int degree = 0;
		for (int w : G.adj(v))	degree++;
		return degree;
	}
	static int max_degree(Graph& G)
	{
		int max_degree = 0;
		for (int v=0;v<G.V();v++)
		{
			if (degree(G,v)>max_degree) max_degree = degree(G,v);
		}
		return max_degree;
	}
	static int number_of_self_loop(Graph& G)
	{
		int count = 0;
		for (int v=0;v<G.V();v++)
		{
			for (int w : G.adj(v))
			{
				if (v == w) count++;
			}
		}
		return count/2;
	}
};

/*
class Digraph
{
	int _V;
	int _E;
	std::vector<int> *adj_list;
	public:
	Digraph(int V) : _V(V)
	{
		adj_list = new std::vector<int>[V];
		_E = 0;
	}
	Digraph(std::ifstream in);
	int V() const {return _V;}
	int E() const {return _E;}
	void add_edge(int v,int w)
	{
		adj_list[v].push_back(w);
		_E++;
	}
	std::vector<int> adj(int v)	const // returns vertices adjacent to v
	{
		return adj_list[v];
	}
	Digraph reverse()
	{
		Digraph G = new Diagraph(V);
		for (int v=0;v<V;v++)
		{
			for (int w:adj(v))
			{
				G.add_edge(w,v);
			}
		}
		return G;
	}
	
};

class SymbolGraph
{
	map<string,int> table;
	string *keys;
	Graph *_G;
};
*/
class DepthFirstPath
{
	int source;
	bool *marked;
	int *edgeTo;
	Graph& G;
	public:
	DepthFirstPath(Graph& G, int s) : G(G),source(s)
	{
		int V = G.V();
		marked = new bool[V];
		edgeTo = new int[V];
		dfs(G,source);
	}
	bool hasPathTo(int v) // is there any path from s to v
	{
		return marked[v];
	}
	std::vector<int> pathTo(int v) // path from s to v if it exists
	{
		std::vector<int> cpath;
		if (!hasPathTo(v))	return cpath;
		std::stack<int> path;
		int no_of_edge = 0;
		for (int x = v; x != source; x = edgeTo[x]) 
		{
			path.push(x);
			no_of_edge++;
		}
		path.push(source);
		no_of_edge++;
		for (int i=0;i<no_of_edge;i++)	
		{	
			cpath.push_back(path.top());
			path.pop();
		}
		return cpath;
	}
	void print_marked()
	{
		std::cout << "Marked Array: " << std::endl;
		for (int v=0;v < G.V(); v++)	std::cout << marked[v] << std::endl;
	}
	void print_edgeTo()
	{
		std::cout << "edgeTo Array: " << std::endl;
		for (int v=0;v < G.V(); v++)	std::cout << v << " : " << edgeTo[v] << std::endl;
	}
	private:
	void dfs(Graph& G,int v)
	{
		marked[v] = true;
		for (int w : G.adj(v))
		{
			if (!marked[w])
			{
				edgeTo[w] = v;
				dfs(G,w);
			}
		}
	}
};

class BreadthFirstPath
{
	int source;
	bool *marked;
	int *edgeTo;
	Graph& G;
	public:
	BreadthFirstPath(Graph& G, int source) : G(G), source(source)
	{
		int V = G.V();
		marked = new bool[V];
		edgeTo = new int[V];
		bfs(G,source);
	}
	void print_marked()
	{
		std::cout << "Marked Array: " << std::endl;
		for (int v=0;v < G.V(); v++)	std::cout << marked[v] << std::endl;
	}
	void print_edgeTo()
	{
		std::cout << "edgeTo Array: " << std::endl;
		for (int v=0;v < G.V(); v++)	std::cout << v << " : " << edgeTo[v] << std::endl;
	}
	bool hasPathTo(int v) // is there any path from s to v
	{
		return marked[v];
	}
	std::vector<int> pathTo(int v) // path from s to v if it exists
	{
		std::vector<int> cpath;
		if (!hasPathTo(v))	return cpath;
		std::stack<int> path;
		int no_of_edge = 0;
		for (int x = v; x != source; x = edgeTo[x]) 
		{
			path.push(x);
			no_of_edge++;
		}
		path.push(source);
		no_of_edge++;
		for (int i=0;i<no_of_edge;i++)	
		{	
			cpath.push_back(path.top());
			path.pop();
		}
		return cpath;
	}
	private:
	void bfs(Graph& G, int s)
	{
		std::queue<int> q;
		q.push(s);
		while(!q.empty())
		{
			int v = q.front();
			q.pop();
			marked[v] = true;
			for (int w : G.adj(v))
			{
				if (!marked[w])
				{
					marked[w] = true;
					edgeTo[w] = v;
					q.push(w);
				}
			} 
		}
	}
};
/*
class ConnectedComponent
{
	bool *marked;
	int *id;
	int count{0};
	Graph& G;
	public:
	ConnectedComponent(Graph& G) : G(G)
	{
		marked = new bool[G.V()];
		id     = new int[G.V()];
		for (int s=0;s<G.V();s++)
		{
			if (!marked[s])
			{
				dfs(G,s);
				count++;
			}
		}		
	}
	bool connected(int v, int w)
	{
		return (id[v] == id[w]);
	}
	int get_id(int v) const {return id[v];}
	int get_count() const {return count;}
	private:
	void dfs(Graph& G,int v)
	{
		marked[v] = true;
		id[v] = count;
		for (int w : G.adj(v))
		{
			if (!marked[w])
			{
				edgeTo[w] = v;
				dfs(G,w);
			}
		}
	}
};

class Cycle
{
	bool *marked;
	bool cycle{false};
	
	public:
	Cycle(Graph& G)
	{
		marked = new bool[G.V()];
		for (int s = 0; s < G.V(); s++)
		{
			if (!marked[s])
			{
				dfs(G,s,s);
			}
		}
	}
	bool hasCycle() const {return cycle;}
	private:
	void dfs(Graph G, int v, int u)
	{
		marked[v] = true;
		for (int w:G.adj(v))
		{
			if (!marked[w])
			{
				dfs(G,w,v);
			}
			else if(w != u)	cycle = true; 
		}
	}
};

class TwoColor
{
	bool *marked;
	bool *color;
	bool isTwoColorable{true};
	
	public:
	TwoColor(Graph &G)
	{
		marked = new bool[G.V()];
		color = new bool[G.V()];
		for (int s=0;s<G.V();s++)
		{
			if (!marked[s])	dfs(G,s);
		}
	}
	bool isBipartite() const {return isTwoColorable;}
	private:
	void dfs(Graph &G, int v)
	{
		marked[v] = true;
		for (int w : G.adj(v))
		{
			if (!marked[w])
			{
				color[w] = !color[v];
				dfs(G,w);
			}
			else if (color[w] == color[v]) isTwoColorable = false;
		}
	}
};

*/




