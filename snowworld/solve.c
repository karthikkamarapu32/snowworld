#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <pthread.h>

typedef struct elem{
	int to;
	int from;
	double snow;
	struct edge* next;  
} edge;

typedef struct pathlist{
	int data;
	struct pathlist* next;  
}pathlist;

typedef edge* edgeList;

edgeList getEdgeList(int e,FILE *file); 
int **adjacencyMatrix(int n, edgeList edges, int e); 
void freeMatrix(int **adjMat, int n); 
void solve();                        

void traverse(threadData *threadSent)
{

	int temp;
        pathlist *current;

	for(i=0;i<numNodes;i++)
	{
		if(adjmat[((threadSent->path)->next)->data][i]!=0 && i!=0)
		{

			while(threadSent->path->next!=null)
			{
				if(threadSent->path->data==i)
				{
                                        break;
                                }
                                else
                                {
                                  
					threadSent[j] = (threadData *)malloc(sizeof(threadData)); 
                                        while(current->next!=null)
                                        {
                                         append(current->data,threadSent[j]);
                                         current = current->next;
					 threadSent[j].accSnow = adjMat[0][j]; 

					//threadSent[j].path=(pathlist *)malloc(sizeof(pathlist));
					//path->node = 0;
					append(0,threadSent[j]->path);
					append(j,threadSent[j]->path);
					threadSent[j].numEdges = 1;
					pthread_create(threads[j],NULL,traverse,((threadSent[j])));     
                                        }
                                        
				}
			}
		}
	}
}

int main(){
	int n, e;
	double alpha;
	char line[50];
	FILE *file = fopen("graph","r");
	pthread_t *threads;

	fgets(line,50,file);
	sscanf(line,"%d",&n);
	fgets(line,50,file); 
	sscanf(line,"%d",&e);
	fgets(line,50,file);
	sscanf(line,"%lf",&alpha);

	//printf("values n %d,e %d,alpha %lf\n",n,e,alpha);

	//scanf("%d %d %lf", &n, &e, &alpha);

	edgeList edges = getEdgeList(e,file);
	double** adjMat = adjacencyMatrix(n, edges, e);
	threadData **threadSent;
	threads = (pthread_t *)malloc(n*sizeof(pthread_t));

	for(j=0;j<n;j++)
	{
		threadSent[j] = (threadData *)malloc(sizeof(threadData)); 
		threadSent[j].accSnow = adjMat[0][j]; 
		//threadSent[j].path=(pathlist *)malloc(sizeof(pathlist));
		//path->node = 0;
		append(0);
		append(j);
		threadSent[j].numEdges = 1;
		pthread_create(threads[j],NULL,traverse,((threadSent[j]));     

				}
				for(j=0;j<n;j++)
				{
				pthread_join(threads[j],NULL);
				}

				for(j=0;j<n;j++)
				{
				if(threadSent[j].accSnow > maxSnow)
				{

				maxSnow = threadSent[j].accSnow;
				maxThread = j;
				}
				}

				printf("max snow is %lf\n",maxSnow);
				display(threadSent[maxThread].path);

				//solve();

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
double **adjacencyMatrix(int n, edgeList edges, int e){
	double **adjMat;
	if( (adjMat = (int **)calloc(n*sizeof(edges)),1) == NULL)
		exit(1);
	for(int i = 0; i < n; i++){
		if((adjMat[i] = (int *)calloc(n*sizeof(double)),1) == NULL)
			exit(1);
	}

	int to, from;
	for(int i = 0; i < e; i++){
		to = edges[i].to;
		from = edges[i].from;
		//adjMat[to][from] = 1;
		//adjMat[from][to] = 1;
		adjMat[from][to] = edges[i].snow; 
		adjMat[to][from] = edges[i].snow;
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
