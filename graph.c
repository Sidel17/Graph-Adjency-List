//author Tennov

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "elementtype.h"
#include "graph.h"

struct GraphNode{
	ElementType ID;		//node identifier
	Edge next;			//edge as pointer ke next struct GraphNode
	
	
};

struct GraphEdge{
	PtrToGraphNode node;
	int weight;			//weight of edge
	Edge next;
};
 
struct GraphADT{
	unsigned int V;			//cardinality of set of nodes
	Node *adjlist;			//adjacency list as dynamic array of pointers
};

Graph ConstructGraph(unsigned int V){
	Graph graph = malloc(sizeof(struct GraphADT));
	graph->V = V;
	/*memory of adjacency list is allocated
	  each block size is equal to the size of PtrToGraphNode*/
	  graph->adjlist = malloc(V * sizeof(PtrToGraphNode));
	  
	  return graph;
}

unsigned int GetNumberOfNodes(Graph g){
	return g->V;
}

Graph AddNode(Graph g, ElementType X){
	static int count;
	Node node = malloc(sizeof(struct GraphNode));
	if(count < g->V){
		node->ID	= X;
		node->next	= NULL;
		
		g->adjlist[count] = node;
		
		count ++;
	}else{
		printf("New Node cannot be added");
		exit(1); //force exit
	}
	
	return g;
}

Node SearchNode(Graph g, ElementType X){
	int i = 0;
	unsigned int limit = GetNumberOfNodes(g);
	Node node;
	for(i = 0; i < limit ; ++i){
		if(g->adjlist[i]->ID == X)
			node = g->adjlist[i];
	}
	
	return node;
}

ElementType GetNodeID(Node node){
	return node->ID;
}

Graph RemoveNode(Graph g, ElementType X){
	Node rem_node, n;
	Edge temp;
	unsigned int i, index = 0, limit = g->V;
	
	printf("initiate remove\n\n");
	//find node to be removed
	for(i=0; i<limit ; i++){
		if(g->adjlist[i]->ID == X){
			rem_node = g->adjlist[i];
			index = i;
			break;
		}
	}
	printf("remove edge to removed node \n\n");
	//delete edge from each node in the graph to removed_node
	for(i=0; i<limit ; i++){
		n = g->adjlist[i];
		if((n != NULL) && (n->ID != rem_node->ID)){
			printf("prepare to remove edge from node-%u to removed node-%u \n", n->ID, rem_node->ID);
			g = RemoveEdge(g, n->ID, rem_node->ID);
		}
	}
	
	printf("Removed all edge from the removed node-%u \n\n", rem_node->ID);
	//delete edge from removed_node
	while (rem_node->next != NULL){
		temp = rem_node->next;
		rem_node->next = temp->next;
		printf("edge from node-%u to node-%u is removed\n", rem_node->ID, temp->node->ID);
		free(temp);
	}
	
	free(rem_node);
	
	/* the adjacency list sliding as consequence of array imp for it
		this can be avoided by implementing adjacency list as linked list*/
	if(index != (limit - 1)){
		for(i = index +1; i<limit; i++)
			g->adjlist[i-1] = g->adjlist[i];
		g->adjlist[limit-1] = NULL;
	}
	
	g->V = g->V - 1;
	i=0;
	while(g->adjlist[i] != NULL){
		printf("adjlist[%u] = node-%u\n", i, g->adjlist[i]->ID);
		i++;
	}
	return g;
}


Graph RemoveEdge(Graph g, ElementType Start, ElementType End){
	Node source = SearchNode(g, Start);
	printf("Find start node = node-%u\n", source->ID);
	Edge temp, e;
	
	temp = source->next;
	if(temp == NULL)
		return g;
	else if(temp->node->ID == End){
		source->next = temp->next;
		printf("Edge from node-%u to node-%u is removed\n", source->ID, temp->node->ID);
		free(temp);
		return g;
	}else if((temp->node->ID != End) && (temp->next != NULL)){
		while((temp->next != NULL) && (temp->next->node->ID != End))
			temp = temp->next;
		if(temp->next == NULL)
			return g;
		else{
			e = temp->next;
			temp->next = e->next;
			printf("Edge from node-%u to node-%u is removed\n", source->ID, e->node->ID);
			free(e);
			return g;
		}
	}else
		return g;
}

Graph AddEdge(Graph g, ElementType Start, ElementType End, int weight){
	Node s = SearchNode(g, Start);
	Node e = SearchNode(g, End);
	Edge edge = s->next;
	
	if(s == NULL){
		printf("Simpul Start tidak ada\n");
		return g;
	}else{
		Edge new = malloc(sizeof(struct GraphEdge));
		new->node = e;
		new->weight = weight;
		new->next = NULL;
		if(edge == NULL)
			s->next = new;
		else{
			while(edge->next != NULL)
				edge = edge->next;
			edge->next = new;
		}
		return g;
	}
}

unsigned int CountNeighbours(Node n){
	int count = 0;
	Edge edge = n->next;
	
	if(edge != NULL){
		count = 1;
		while(edge->next != NULL){
			edge = edge->next;
			count++;
		}
	}
	return count;
}

Node *GetNeighbours(Graph g, ElementType ID){
	unsigned int count=0, i=0;
	Edge edge; 
	
	Node node = SearchNode(g, ID);
	
	count = CountNeighbours(node);
	if(count == 0) return NULL;
	else{
		//printf("Number of neighbours of node %u = %u\n", node->ID, count);
		Node *neighbours = malloc(count * sizeof(PtrToGraphNode));
		
		edge = node->next;
		while(i<count){
			neighbours[i] = edge->node;
			edge = edge->next;
			
			i++;
		}
		return neighbours;
	}
}

void FindMinNeighbours(Graph g, ElementType X){
	Node node,*neighbours;
	node =  SearchNode(g, X);
	unsigned int count,i,min;
	count = CountNeighbours(node);
	neighbours = GetNeighbours(g,X);
	min = GetNodeID(neighbours[0]);
	for(i=0;i<count;i++){
		if(GetNodeID(neighbours[i]) < min){
			min = GetNodeID(neighbours[i]);
		}
	}
	printf("Tetangga terkecil dari node %d adalah %d\n",X,min);
}
void JumlahEdgeGraph(Graph g){
	Node node;
	int n,i,count,total=0;
	n = GetNumberOfNodes(g);
	for(i=0;i<n;i++){
		node = g->adjlist[i];
		count = CountNeighbours(node);
		//printf("Total Edge node %d pada Graph adalah : %d\n",node->ID,count);
		total += count;
	}
	printf("Total Edge pada Graph adalah : %d\n",total);
}
void UpdateNode(Graph g, ElementType X, ElementType Y){
	Node node;
	node = SearchNode(g, X);
	node->ID = Y;
}
void FindMinNode(Graph g){
	//Node node;
	unsigned int n,i,min;
	n = GetNumberOfNodes(g);
	min = g->adjlist[0]->ID;
	for(i=0;i<n;i++){
		if(g->adjlist[i]->ID < min){
			min = g->adjlist[i]->ID;
		}
	}
	printf("Nilai minimum pada graph adalah : %d",min);
}
void DestroyGraph(Graph g){
	unsigned int i = 0;
	Node node = NULL;
	Edge e;
	printf("Graph is ready to destroy\n");
	for(i=0; i<g->V; i++){
		node = g->adjlist[i];
		if(node != NULL){
			while(node->next != NULL){
				e = node->next;
				node->next = e->next;
				printf("Edge from node-%u to node-%u is free\n", node->ID, e->node->ID);
				free(e);
			}			
		}
	}
	for(i=0; i<g->V; i++){
		node = g->adjlist[i];
		printf("Node-%u is free,\n", node->ID);
		free(node);
	}
	free(g->adjlist);
	free(g);	
}

