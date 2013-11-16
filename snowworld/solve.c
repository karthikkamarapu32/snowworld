#include <stdio.h>
#include <stdlib.h>
#include "math.h"

typedef struct elem{
  int to;
  int from;
  double snow;
} edge;

typedef edge* edgeList;

edgeList getEdgeList(int e,FILE *file); 
int **adjacencyMatrix(int n, edgeList edges, int e); 
void freeMatrix(int **adjMat, int n); 
void solve();                        

int main(){
  int n, e;
  double alpha;
  char line[50];
  FILE *file = fopen("graph","r");
  
  
  fgets(line,50,file);
  sscanf(line,"%d",&n);
  fgets(line,50,file); 
  sscanf(line,"%d",&e);
  fgets(line,50,file);
  sscanf(line,"%lf",&alpha);
  
  //printf("values n %d,e %d,alpha %lf\n",n,e,alpha);

  //scanf("%d %d %lf", &n, &e, &alpha);

  edgeList edges = getEdgeList(e,file);
  int** adjMat = adjacencyMatrix(n, edges, e);
  
  solve();

  freeMatrix(adjMat, n);
  return 0;
}

/* Solves and prints out solution */

void solve(){
  /* Unimplemented */
}

/* Given functions */

/* Reads from stdin and forms an edgeList of type edgeList */
edgeList getEdgeList(int e,FILE *file){
  edgeList edges = (edge *)malloc(e*sizeof(edge));
  int a, b;
  double c;
  char line[50];

  for(int i = 0; i < e; i++){
    fgets(line,50,file);
    sscanf(line,"%d %d %lf", &a, &b, &c);
    //printf("a is %d\n",a);
    //printf("b is %d\n",b);
    //printf("c is %lf\n",c);
    edges[i].to = a;
    edges[i].from = b;
    edges[i].snow = c;
  }
  return edges;
}

/* Creates an adjacency matrix from the edgeList */
int **adjacencyMatrix(int n, edgeList edges, int e){
  int **adjMat;
  if( (adjMat = (int **)malloc(n*sizeof(edges)) ) == NULL)
    exit(1);
  for(int i = 0; i < n; i++){
    if((adjMat[i] = (int *)malloc(n*sizeof(int))) == NULL)
      exit(1);
  }
  int to, from;
  for(int i = 0; i < e; i++){
    to = edges[i].to;
    from = edges[i].from;
    adjMat[to][from] = 1;
    adjMat[from][to] = 1;
  }
  return adjMat;
}

/* Deletes what was allocated (using delete) */
void freeMatrix(int **adjMat, int n){
  if(adjMat == NULL) return;
  for(int i = 0; i < n; i++){
    if(adjMat[i] != NULL)
      free(adjMat[i]);
  }
  free(adjMat);
}
