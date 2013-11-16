#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node
{
	int data;
	struct node* next;
};

struct node *head = NULL;
struct node *head1 = NULL;
struct node *head2 =NULL;

void Push(struct node** head,int *val)
{
	struct node* dummy = NULL;

	if(head == NULL)
	{
		*head = (struct node*)malloc(sizeof(struct node));
		(*head)->data = *val;
		(*head)->next = NULL;
	}
	else
	{
		dummy = (struct node*)malloc(sizeof(struct node));
		dummy->data = *val;
		dummy->next = *head;
		*head = dummy;
	}
}

void Display(struct node** head)
{
	struct node* current = NULL;
	if(*head == NULL)
		printf("No values to display\n");
	else
	{
		printf("\n\nDISPLAY VALUES\n");
		printf("head data %d\n",(*head)->data);
		current = *head;

		do 
		{
			printf("VAL %d\n",current->data);
			current = current->next;
		}while(current!=NULL);

	}

}

void Pop()
{

	struct node* dummy;

	if(head == NULL)
		printf("Nothing to Pop\n");
	else
	{
		dummy = head;  
		head = head->next;
		free(dummy);      
	}
}

void CountInt()
{
	int value;
	int count =0;
	struct node* current;

	printf("\nEnter int to check:");
	scanf("%d",&value);

	for(current=head;current!=NULL;current=current->next)
	{
		if(current->data == value)
			count++;
	}

	printf("Int [%d] occurs [%d] times\n",value,count);
}

void GetNth()
{
	int n;
	int count =0;
	struct node* current;

	printf("Enter the value of N\n");
	scanf("%d",&n);

	for(current=head;current!=NULL;current=current->next)
	{
		count++;
		if(count == n)
		{
			printf("[%d]th value is [%d]\n",n,current->data);
			break;
		}
	}

}

void Release(struct node** head)
{

	struct node * current;

	if(*head!=NULL)
	{
		for(current=*head;current!=NULL;current=current->next)
		{
			free(current);
		}     
		*head = NULL; 
	}
}

void InsertNth(int *n,int *val)
{
	int count=0;
	struct node* current = NULL;
	struct node* prev = NULL;
	struct node* newNode = NULL;


	if(head == NULL)
	{
		if(*n!=1)
			printf("Invalid Position");
		else
		{
			Push(&head,val);
		}
	}
	else if(head!=NULL)
	{  
		newNode = (struct node *)malloc(sizeof(struct node));

		newNode->data = *val; 

		current=head;
		while(current!=NULL)
		{
			count ++;
			if(count == *n)
				break;

			prev = current;     
			current=current->next;
		}   

		if((*n)>(count+1))
		{
			printf("Invalid Position");
		}
		else 
		{
			if(*n ==1)
				head = newNode;


			newNode->next = current;

			if(prev!=NULL)
				prev->next = newNode;
		}
	}   

}

void swap(struct node** current,struct node** nextNode)
{

	struct node* temp1;

	temp1= (struct node *)malloc(sizeof(struct node));

	temp1->data = (*nextNode)->data;
	(*nextNode)->data = (*current)->data;
	(*current)->data = temp1->data;

}

void Sort()
{

	struct node* current = NULL;
	struct node* nextNode = NULL;

	if(head == NULL || head->next == NULL)
	{
		printf("Nothing to sort\n");
	}
	else
	{
		for(current=head;current!=NULL;current=current->next)
		{
			for(nextNode=current->next;nextNode!=NULL;nextNode=nextNode->next)
			{
				if(current->data > nextNode->data)
				{ 
					swap(&current,&nextNode);
				}
			}
		}
	}

}

bool isSorted()
{

	struct node* current;
	struct node* nextNode;
	bool unsorted = false;

	if(head!=NULL && head->next!=NULL)

		for(current=head,nextNode=head->next;nextNode!=NULL;current=current->next,nextNode=nextNode->next)
		{
			if(current->data > nextNode->data)
			{
				unsorted = true;
				break;
			}  
		}

	if(unsorted == true)
		return false;

	return true;

}

void Insert(int *val)
{
	struct node* prev = NULL;
	struct node* current;
	struct node* newNode; 
	bool inserted = false;

	if(head == NULL)
	{
		Push(&head,val);
	}
	else
	{
		newNode = (struct node*)malloc(sizeof(struct node));
		newNode->data = *val;

		for(current=head;current!=NULL;prev=current,current=current->next)
		{
			if(current->data > *val)
			{
				newNode->next = current;

				if(prev!=NULL)
					prev->next = newNode;
				else
					head = newNode;

				inserted = true;

				break;          
			}
		}

		if(inserted == false)
			prev->next = newNode;             

	}
}

void InsertSort(int *val)
{

	if(!isSorted())
	{
		Sort();
	}

	Insert(val);

}

void GetLastNode(struct node** head,struct node** lastNode)
{

	for(*lastNode=(*head);(*lastNode)->next!=NULL;(*lastNode)=(*lastNode)->next)
	{
		//Do Nothing.Just Return lastNode
	}

}

void Append()
{

	struct node* lastNode;

	if(head == NULL && head1 == NULL)
	{
		printf("No lists to append\n");
		return;
	}

	if(head!=NULL)
	{
		GetLastNode(&head,&lastNode);

		if(head1!=NULL)
			lastNode->next = head1;
	} 
	else
		head = head1; 


	head1=NULL;
}

void countList(int *count)
{
	struct node* current;

	for(current=head;current!=NULL;current=current->next)
		(*count)++;

}

void frontBackSplit()
{
	int count =0;
	int localCount =0;
	struct node* current;

	countList(&count);

	if(count%2==0)
	{
		for(current=head;current!=NULL;current=current->next)
		{
			if(++localCount == (count/2))
				break;
		}

	}
	else
	{
		for(current=head;current!=NULL;current=current->next)
		{
			if(++localCount == (count/2)+1)
				break;
		}
	}

	head1 = current->next; 
	current->next = NULL;

}

void removeDuplicates()
{
	struct node* current;
	struct node* nextNode;
	struct node* prevNode;
	struct node* temp;

	if(head == NULL)
	{
		printf("No List");
		return;
	}

	for(current=head;current!=NULL;current=current->next)
	{
		for(prevNode=current,nextNode=current->next;nextNode!=NULL;prevNode=nextNode,nextNode=nextNode->next)
		{
			if(current->data == nextNode->data)
			{
				temp = nextNode;                  
				nextNode = nextNode->next;
				prevNode->next = nextNode;
				free(temp);
			}
		}
	}
}

void moveNodeToAppend(struct node** head1,struct node** head)
{

	struct node* temp;
	struct node* current;

	printf("Appends instead of pushing.So as to help mergeShuffle\n");

	if(*head1!=NULL)
	{
		temp = *head1;

		if((*head1)->next!=NULL)
		{
			*head1 = (*head1)->next;
		}
		else
		{
			*head1 = NULL;
		}

		if(*head == NULL)
		{
			*head = temp;
			(*head)->next = NULL;
		}
		else
		{
			for(current=(*head);current->next!=NULL;current=current->next)
			{

			}

			current->next = temp;
			temp->next = NULL;
		}    

	}
	else
		printf("List2 is empty\n");

}

void moveNodeToPush(struct node** head1,struct node** head)
{

	struct node* temp;
	struct node* current;

	printf("Appends instead of pushing.So as to help mergeShuffle\n");

	if(*head1!=NULL)
	{
		temp = *head1;

		if((*head1)->next!=NULL)
		{
			*head1 = (*head1)->next;
		}
		else
		{
			*head1 = NULL;
		}

             
                temp->next = *head;
                *head = temp;
	}
	else
		printf("List2 is empty\n");

}

void AlternateSplit()
{

	struct node* current;
	struct node* temp;
	struct node* lastNode;
	printf("Deletes exisint List2 and inserts Data\n");

	Release(&head1);

	if(head->next==NULL)
		return;

	for(current=head;current!=NULL;current=current->next)
	{

		if(head1==NULL)
		{
			temp = current->next;
			head1=temp;
			current->next = temp->next;
			head1->next=NULL;

		}
		else
		{
			if(current->next == NULL)
				break;

			temp = current->next;
			GetLastNode(&head1,&lastNode);
			lastNode->next = temp;
			current->next = temp->next;
			temp->next=NULL;
		}

	}  

}

void shuffleMerge()
{
	struct node* current;
	struct node* current1;
	struct node* temp;
	struct node* temp1;

	if(head!=NULL && head1!=NULL)
	{
		current=head;
		current1=head1;
		while(current!=NULL || current1!=NULL)
		{
			if(current!=NULL && current!=NULL)
			{
				moveNodeToAppend(&current,&head2);

				moveNodeToAppend(&current1,&head2);     
			}
			else if(current==NULL && current1!=NULL)
			{
				GetLastNode(&head2,&temp);
				temp->next = current1;
				break;
			}
			else if(current1==NULL && current!=NULL) 
			{
				GetLastNode(&head2,&temp);
				temp->next = current;
				break;

			}
			else
				break;
		}

	}
}

void sortedMerge()
{

	struct node* temp;

	if(head == NULL || head1 ==NULL)
		printf("Nothing to sort\n");
	else
	{
		GetLastNode(&head,&temp);
		temp->next = head1;
		Sort();
		Display(&head);
	}

}

void Reverse()
{
  struct node* current = NULL;
  struct node* newNode=NULL;
  current=head;

  while(current!=NULL)
  {
   moveNodeToPush(&current,&newNode);
  }
  
  head = newNode;  

}

void printScreen(int *choice)
{

	printf("\n 1.Push \n 2.Display \n 3.Pop \n 4.CountInt \n 5.GetNth \n 6.DeleteLists \n 7.InsertNth \n 8.Sort \n 9.SortedInsert\n");
	printf(" 10.PushInNewList \n 11.DisplaySecondList \n 12.Append \n 13.FrontBackSplit \n 14.RemoveDup \n 15.MoveNode \n 16.Alternating Split\n");
	printf(" 17.ShuffleMeger \n 18.SortedMerge \n 19.Reverse \n 20.Exit\n"); 
	printf("Enter your choice:");
	scanf("%d",choice);
	system("clear");
}

int main(int argc,char **argv)
{

	int choice,val,n,listNo;

	if(argc!=1)
		printf("Invalid no. of arguments\n");

	do
	{
		printScreen(&choice);

		switch(choice)
		{
			case 1:
				printf("\nEnter the value to push:");
				scanf("%d",&val);
				Push(&head,&val);
				break;
			case 2: 
				Display(&head);
				break;
			case 3: 
				Pop();
				break;
			case 4: 
				CountInt();
				break;
			case 5: 
				GetNth();
				break;
			case 6: 
				Release(&head);
				Release(&head1);
				Release(&head2);
				break;
			case 7: 
				printf("Insert the position you want to enter:");
				scanf("%d",&n);

				printf("Enter the value to be inserted:\n");
				scanf("%d",&val);

				InsertNth(&n,&val);
				break;
			case 8:
				Sort();
				break;
			case 9:
				printf("Enter the value to be inserted:\n");
				scanf("%d",&val);

				InsertSort(&val);
				break;
			case 10: 
				printf("\nEnter the value to push:");
				scanf("%d",&val);
				Push(&head1,&val);
				break;
			case 11:
				Display(&head1);
				break;
			case 12:
				Append();
				break;
			case 13:
				frontBackSplit();
				break;
			case 14: 
				removeDuplicates();
				break;
			case 15: 
				moveNodeToAppend(&head1,&head);
				break;
			case 16:
				AlternateSplit();
				break;
			case 17:
				shuffleMerge();
				Display(&head);
				break;
			case 18: 
				sortedMerge();
				break;
                        case 19:
                                Reverse();
                                break;
			case 20:
			default: Release(&head);
				 Release(&head1);
				 Release(&head2);
				 exit(0);
		}
	}while(choice<21);   
}
