#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "solve.h"
double **adjMat;
	


typedef edge* edgeList;
int numNodes, numEdges;

edgeList getEdgeList(int e,FILE *file); 
void adjacencyMatrix(int n, edgeList edges, int e); 
void freeMatrix(double **adjMat, int n); 
//void solve();                        

void traverse(threadData *threadSent)
{

	int temp, j=0, i;
        pathlist *curr1, *next1, *curr2, *next2;
	pthread_t *threads;
	threadData **thisThreadSent;
	double maxSnow=0;
	int maxThread=-1;

	threads = (pthread_t *)malloc(numNodes*sizeof(pthread_t));
	thisThreadSent = (threadData **)malloc(numNodes*sizeof(threadData*));
	
	curr1 = (threadSent->path);

	for(i=0;i<numNodes;i++)
	{
		if(adjMat[((threadSent->path)->next)->data][i]!=0 && i!=0)
		{
			int good = 1;

			while(curr1!=NULL)
			{
				if(curr1->data==i)
				{
					good = 0;
                                        break;
                                }
				curr1 = curr1->next;
			}
			if(good)
			{
				thisThreadSent[j] = (threadData *)malloc(sizeof(threadData));
				curr2 = (threadSent->path);
				while(curr2!=NULL)
				{
					insert(curr2->data,thisThreadSent[j]->path);
					curr2 = curr2->next;
				}
				thisThreadSent[j]->accSnow = thisThreadSent[j]->accSnow + pow(adjMat[((threadSent->path)->next)->data][i], thisThreadSent[j]->numEdges);
				thisThreadSent[j]->numEdges++;
				pthread_create(&threads[j],NULL,(void*)&traverse,(void*)thisThreadSent[j]);
				j++;
			}
		}
	}
	// do the join for all threads created
	for(i=0;i<j;i++)
	{
		pthread_join(threads[j],NULL);
		if(thisThreadSent[j]->accSnow > maxSnow)
		{

			maxSnow = thisThreadSent[j]->accSnow;
			maxThread = j;
		}
	}

	curr1 = thisThreadSent[maxThread]->path;
	threadSent->path = NULL;

	while(curr1 != NULL)
	{
		insert(curr1->data, threadSent->path);
		curr1 = curr1->next;
	}
	                               
}

int main(){
	int n, e, j, i;
	double alpha;
	char line[50];
	FILE *file = fopen("graph","r");
	pthread_t *threads;
	int maxThread=-1;
	double maxSnow=0;

	fgets(line,50,file);
	sscanf(line,"%d",&n);
	fgets(line,50,file); 
	sscanf(line,"%d",&e);
	fgets(line,50,file);
	sscanf(line,"%lf",&alpha);

	numNodes = n;
	numEdges = e;

	//printf("values n %d,e %d,alpha %lf\n",n,e,alpha);

	//scanf("%d %d %lf", &n, &e, &alpha);

	edgeList edges = getEdgeList(e,file);
	adjacencyMatrix(n, edges, e);
	threadData **threadSent;
	threads = (pthread_t *)malloc(n*sizeof(pthread_t));
	threadSent = (threadData **)malloc(n*sizeof(threadData*));
	for(j=0;j<n;j++)
	{
		threadSent[j] = (threadData *)malloc(sizeof(threadData)); 
		threadSent[j]->accSnow = adjMat[0][j]; 
		//threadSent[j].path=(pathlist *)malloc(sizeof(pathlist));
		//path->node = 0;
		threadSent[j]->path = NULL;
		insert(0, threadSent[j]->path);
		insert(j, threadSent[j]->path);
		threadSent[j]->numEdges = 1;
		pthread_create(&threads[j],NULL,(void*)&traverse,(void*)threadSent[j]);     

	}
	for(j=0;j<n;j++)
	{
		pthread_join(threads[j],NULL);
	}

	for(j=0;j<n;j++)
	{
		if(threadSent[j]->accSnow > maxSnow)
		{

			maxSnow = threadSent[j]->accSnow;
			maxThread = j;
		}
	}

	printf("max snow is %lf\n",maxSnow);
	display(threadSent[maxThread]->path);

	//solve();

	freeMatrix(adjMat, n);
	return 0;
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
void adjacencyMatrix(int n, edgeList edges, int e){
	if( (adjMat = (double **)calloc(n*sizeof(double*),1) == NULL))
		exit(1);
	for(int i = 0; i < n; i++){
		if((adjMat[i] = (double *)calloc(n*sizeof(double),1) == NULL))
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
void freeMatrix(double **adjMat, int n){
	if(adjMat == NULL) return;
	for(int i = 0; i < n; i++){
		if(adjMat[i] != NULL)
			free(adjMat[i]);
	}
	free(adjMat);
}
