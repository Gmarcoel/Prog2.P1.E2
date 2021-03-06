#include "graph.h"
#include <errno.h>

/*ESTRUCTURA GRAPH*/
struct _Graph {
	Node *nodes[MAX_NODES]; /*!<Array with the graph nodes */
	Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
	int num_nodes;
/*!<Total number of nodes in te graph */
	int num_edges;
/*!<Total number of connection in the graph*/
};


int find_node_index(const Graph * g, long nId1);
int* graph_getConnectionsIndex(const Graph * g, int index);

Graph * graph_init (){
	
	int i=0,j=0;
	Graph * g;
	
	g = (Graph*)calloc(1,sizeof(Graph));
	


	if (g == NULL){
		return NULL;
	} else {
		g->num_edges = 0;
		g->num_nodes = 0;
		
		for( i=0; i < MAX_NODES; i++ ){

			g->nodes[i]=NULL;
			
			for( j=0; j < MAX_NODES; j++ ) {
				g->connections[i][j] = 0;
			}

		}
		
		return g;
	}

}

void graph_free (Graph *g){
	int i;
	for(i=0;i<g->num_nodes;i++){
		free(g->nodes[i]);
	}
	free(g);
}

Status graph_insertNode (Graph *g, const Node *n){
	int i=0;
	for(i=0; i<g->num_nodes; i++){
		if(node_getId(g->nodes[i]) == node_getId(n)){
			return ERROR;
		}
	}
	g->nodes[i] = node_copy(n);
	g->num_nodes++;
	return OK;
}

Status graph_insertEdge (Graph *g, const long nId1, const long nId2) {
	if(!g) {
		return ERROR;
	}
	
	g->connections[find_node_index(g,nId1)][find_node_index(g,nId2)]=1;
	
	g->num_edges++;
	
	node_setNConnect(g->nodes[find_node_index(g,nId1)],node_getConnect(g->nodes[find_node_index(g,nId1)])+1);
	
	return OK;
}

Node *graph_getNode (const Graph *g, long nId){
	if(!g){
		return NULL;
	}

	return g->nodes[find_node_index(g, nId)];
}

Status graph_setNode (Graph *g, const Node *n){
	if(!n||!g){
		return ERROR;
	}
	int i;
	for(i=0;i<g->num_nodes;i++){
		if(node_getId(g->nodes[i]) == node_getId(n)){
			g->nodes[i] = node_copy(n);
			return OK;
		}
	}
}

long * graph_getNodesId (const Graph *g) {
	if(!g){
		return NULL;
	}
	int i=0;
	long *array;
	if(!(array=(long*)calloc(g->num_nodes,sizeof(long)))){
		return NULL;
	}
	for(i=0;i<g->num_nodes;i++){
		array[i]=node_getId(g->nodes[i]);
		}	
	return array;
}

int graph_getNumberOfNodes (const Graph *g){
	if(!g){
	}
		return -1;
	return g->num_nodes;


}

int graph_getNumberOfEdges (const Graph *g){
	if(!g){
	}
		return -1;
	return g->num_edges;

}

Bool graph_areConnected (const Graph *g, const long nId1, const long nId2){
	if (!g) {
		return FALSE;
	}
	int in1, in2;
	in1=find_node_index(g,nId1);
	in2=find_node_index(g,nId2);
	return g->connections[in1][in2];
}

int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId){
	if(!g){
		return -1;
	}
	return node_getConnect(g->nodes[find_node_index(g, fromId)]);
}

long* graph_getConnectionsFrom (const Graph *g, const long fromId){
	if(!g){
		return NULL;
	}
	int i=0;
	int* index = graph_getConnectionsIndex(g, find_node_index(g, fromId));

	long * array;
	if(!(array = (long*)calloc(graph_getNumberOfConnectionsFrom(g,fromId),sizeof(long)))){
			return NULL;
	}
	for (i=0;i<node_getConnect(g->nodes[find_node_index(g, fromId)]);i++){
		array[i] = node_getId(g->nodes[index[i]]);
	}
	free(index);
	return array;
}

int graph_print (FILE *pf, const Graph *g){
	if (!g){
		return -1;
	}
	int i=0;
	for(i=0;i<g->num_nodes;i++){
		node_print (pf,g->nodes[i]);
	}
}






// It returns the index of the node with id nId1
int find_node_index(const Graph * g, long nId1) {
	int i;
	if (!g) return -1;
	for(i=0; i < g->num_nodes; i++) {
		if (node_getId (g->nodes[i]) ==	nId1)
			return i;
	// ID not found
		return -1;
	}
}
// It returns an array with the indices of the nodes connected to the node
// whose index is index
// It also allocates memory for the array.
int* graph_getConnectionsIndex(const Graph * g, int index) {
	int *array = NULL, i, j = 0, size;
	if (!g) return NULL;
	if (index < 0 || index >g->num_nodes) return NULL;
	// get memory for the array
	size = node_getConnect (g->nodes[index]);
	array = (int *) malloc(sizeof (int) * size);
	if (!array) {
	// print error message
		fprintf (stderr, "%s\n", strerror(errno));
		return NULL;
	}
	// assign values to the array with the indices of the connected nodes
	for(i = 0; i< g->num_nodes; i++) {
		if (g->connections[index][i] == TRUE) {
			array[j++] = i;
		}
	}
	return array;
}
