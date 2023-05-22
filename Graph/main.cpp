#include <iostream>
#include "Graph.h"

using namespace std;

int test_graph_adt()
{
	Graph G(13);
	G.add_edge(0,5);
	G.add_edge(4,3);
	G.add_edge(0,1);
	G.add_edge(9,12);
	G.add_edge(6,4);
	G.add_edge(5,4);
	G.add_edge(0,2);
	G.add_edge(11,12);
	G.add_edge(9,10);
	G.add_edge(0,6);
	G.add_edge(7,8);
	G.add_edge(9,11);
	G.add_edge(5,3);
	cout << G << endl;
}

int test_dfs()
{
	Graph G(6);
	G.add_edge(0,5).add_edge(2,4).add_edge(2,3).add_edge(1,2).add_edge(0,1).add_edge(3,4).add_edge(3,5).add_edge(0,2);
	DepthFirstPath d(G,0);
	d.print_marked();
	d.print_edgeTo();
	vector<int> path;
	path = d.pathTo(1);
	for (int w : path)	cout << w << " ";
	cout << endl;
	path = d.pathTo(2);
	for (int w : path)	cout << w << " ";
	cout << endl;
	path = d.pathTo(3);
	for (int w : path)	cout << w << " ";
	cout << endl;
	path = d.pathTo(4);
	for (int w : path)	cout << w << " ";
	cout << endl;
	path = d.pathTo(5);	
	for (int w : path)	cout << w << " ";
	cout << endl;
}

int test_bfs()
{
	Graph G(6);
	G.add_edge(0,5).add_edge(2,4).add_edge(2,3).add_edge(1,2).add_edge(0,1).add_edge(3,4).add_edge(3,5).add_edge(0,2);
	BreadthFirstPath d(G,0);
	d.print_marked();
	d.print_edgeTo();
	vector<int> path;
	path = d.pathTo(1);
	for (int w : path)	cout << w << " ";
	cout << endl;
	path = d.pathTo(2);
	for (int w : path)	cout << w << " ";
	cout << endl;
	path = d.pathTo(3);
	for (int w : path)	cout << w << " ";
	cout << endl;
	path = d.pathTo(4);
	for (int w : path)	cout << w << " ";
	cout << endl;
	path = d.pathTo(5);	
	for (int w : path)	cout << w << " ";
	cout << endl;
}

int main()
{
	test_graph_adt();
	//test_dfs();
	//test_bfs();
}
