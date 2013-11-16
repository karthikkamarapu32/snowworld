typedef struct node{
	double maxSnow;
	int numNodes;
	bool done;
}node;

typedef struct threadData{
	double accSnow;
	pathlist *path;
	int numNodes;
}threadData;


