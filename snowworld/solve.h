typedef struct pathlist{
	int data;
	struct pathlist* next;  
}pathlist;

typedef struct threadData{
	double accSnow;
	pathlist *path;
	int numEdges;
}threadData;

typedef struct elem{
	int to;
	int from;
	double snow;
	struct edge* next;  
} edge;

void  display(pathlist *r);
int delete(int num,pathlist *head);
void insert(int num,pathlist *head);
void addafter(int num, int loc,pathlist *head);
void add( int num,pathlist *head);
void append(int num,pathlist *head);

