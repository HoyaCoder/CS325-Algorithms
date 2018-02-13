/*****************************
** Author: James Meehan
** Source: www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/
******************************/

#include <iostream>
#include <list>

using namespace std;

class Graph
{
	private:
	int v; //vertices
	list<int> *adj; //pointer to array of adjacency lists

public:
	Graph(int v);
	void addEdge(int v, int w);
	void BFS(int s); //print BFS traversal from point s
};

Graph::Graph(int v)
{
	this->v = v;
	adj = new list<int>[v];
}

void Graph::addEdge(int v, int w)
{
	//add w to v's adjacency list
	adj[v].push_back(w);
}

void Graph::BFS(int s)
{
	//mark all vertices as not yet visited
	bool *visited = new bool[v];
	for (int i = 0; i < v; i++)
	{
		visited[i] = false;
	}

	//create a queue for BFS
	list<int> queue;

	//mark the current node as visited and enqueue it
	visited[s] = true;
	queue.push_back(s);

	//'j' will be used to get all adjacent vertex vertices
	list<int>:: iterator j;

	while(!queue.empty())
	{
		//dequeue next vertex in queue and print it
		s = queue.front();
		cout << s << " ";
		queue.pop_front();

		//get all adjacent vertices of the dequeued 
		//vertes.  If an adjacent vertex has not been
		//visited, mark it visited and enqueue it
		for (j = adj[s].begin(); j != adj[s].end(); ++j)
		{
			if (!visited[*j]) 
			{
				visited[*j] = true;
				queue.push_back(*j);
			}
		}
	}
}

int main()
{
	Graph g(9);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 7);
 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(0);
 
    return 0;
}




