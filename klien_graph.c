// author Tennov

#include <stdio.h>
#include "graph.h"

int main(){
	Node node,*neighbours;  // *neighbours = NULL;
	unsigned int count,i; // count;
	
	Graph G = ConstructGraph(7);   //construct graph with 7 nodes
	int V = GetNumberOfNodes(G);	//get number of nodes
	printf("Number of Nodes in Graph: %u\n", V);
	
	//add node 1 to 7 to graph G iteratively
	for(i = 1; i<=7; ++i)
		G = AddNode(G, i);
	
	//search node 1
	node = SearchNode(G, 1);
	printf("Node is found, id = %d\n", GetNodeID(node));
	
	//add edge, 0 weight means graph with equal weights
	G = AddEdge(G, 1, 2, 0);
	G = AddEdge(G, 1, 4, 0);
	G = AddEdge(G, 1, 3, 0);
	G = AddEdge(G, 2, 4, 0);
	G = AddEdge(G, 2, 5, 0);
	G = AddEdge(G, 3, 6, 0);
	G = AddEdge(G, 4, 6, 0);
	G = AddEdge(G, 4, 7, 0);
	G = AddEdge(G, 4, 3, 0);
	G = AddEdge(G, 5, 4, 0);
	G = AddEdge(G, 5, 7, 0);
	G = AddEdge(G, 7, 6, 0);
	
	node = SearchNode(G, 4);
	count = CountNeighbours(node);
	neighbours = GetNeighbours(G,4);
	printf("neighbours of node %u:\n", GetNodeID(node));
	for(i=0; i<count; i++)
		printf("neighbours of %d = %d\n", i+1, GetNodeID(neighbours[i]));
	
	JumlahEdgeGraph(G);
	
	FindMinNeighbours(G,4);
	//node = SearchNode(G, -9);
	//printf("Node is found, id = %d\n", GetNodeID(node));
	FindMinNode(G);

	//G = RemoveNode(G, 2);
	//G = RemoveEdge(G, 1, 2);
	//G = RemoveNode(G, 5);
	
	
	return 0;
}
