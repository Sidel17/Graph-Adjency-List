//author Tennov
#include "elementtype.h"
//typedef unsigned int ElementType;

#ifndef _Graph_H
#define _Graph_H

enum Chromatic{NONE, WHITE, GRAY, BLACK};
typedef enum Chromatic Colours;

struct GraphNode;		//structure of node
typedef struct GraphNode *PtrToGraphNode;	//pointer to struct node
typedef PtrToGraphNode Node;		//node

struct GraphEdge;		//struct of edge
typedef struct GraphEdge *PtrToGraphEdge;
typedef PtrToGraphEdge Edge;		//edge

struct GraphADT;		//structure of graph
typedef struct GraphADT *PtrToGraph;	//pointer to struct graph
typedef PtrToGraph Graph;		//grsph representated as pointer

Graph ConstructGraph (unsigned int V);		//construct an empty graph
unsigned int GetNumberOfNodes(Graph g);
Graph AddNode(Graph g, ElementType X);
Node SearchNode(Graph g, ElementType X);
ElementType GetNodeID (Node node);
Graph RemoveNode(Graph g, ElementType ID);
Graph AddEdge(Graph g, ElementType Start, ElementType End, int weight);
Graph RemoveEdge(Graph g, ElementType Start, ElementType End);
unsigned int CountNeighbours (Node n);
Node *GetNeighbours (Graph g, ElementType ID);  //get neigbours (successor of node ID)
Node PreparedTraverse(Graph g, ElementType s);
void BFS(Graph g, ElementType s);
void DFS(Graph g);
void DFS_VISIT(Graph g, Node u, unsigned int *time);
void DestroyGraph(Graph g);

//Fungsi Tambahan
void FindMinNode(Graph g);
void FindMinNeighbours(Graph g, ElementType X);
void JumlahEdgeGraph(Graph g);
void UpdateNode(Graph g, ElementType X, ElementType Y);

#endif
