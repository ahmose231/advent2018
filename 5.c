#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	struct node {
		char c;
		struct node* next;
		struct node* prev;
	};
	
	struct node *root, *newnode,*oldnode;
	
	root=malloc(sizeof(struct node));
	oldnode=root;
	oldnode->next=NULL;
	oldnode->prev=NULL;
	
	int count=0;
	char x;
	x=getchar();
	while(x!=EOF)
	{
		count++;
		newnode=malloc(sizeof(struct node));
		oldnode->next=newnode;
		newnode->c=x;
		newnode->next=NULL;
		newnode->prev=oldnode;
		oldnode=newnode;
		x=getchar();
	}
	count--;
	
	newnode=root->next;
	while(newnode->next!=NULL)
	{
		if(abs(newnode->c - newnode->next->c) == 'a'-'A')
		{
			newnode->prev->next=newnode->next->next;
			
			count=count-2;
			continue;
		}
		
		newnode=newnode->next;
	}
			
	printf("\n%d\n",count);
	return 0;
}
		
