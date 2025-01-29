#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINES 500
#define LEN 128

struct {
	int x;
	int y;
	int vx;
	int vy;
} point[LINES];
int pointindex;

int main(void) {
	// your code goes here
	char line[LEN];
	while(fgets(line,LEN,stdin)!=NULL)
	{
		int k=0;
		
		while(line[k]!='<')
			k++;
		k++;
		
		char word[8];
		int w=0;
		while(line[k]!=',')
			word[w++]=line[k++];
		word[w]=0;
		
		point[pointindex].x = atoi(word);
		
		k+=2;
		w=0;
		while(line[k]!='>')
			word[w++]=line[k++];
		word[w]=0;
		
		point[pointindex].y = atoi(word);
		
		while(line[k]!='<')
			k++;
		k++;
		
		w=0;
		while(line[k]!=',')
			word[w++]=line[k++];
		word[w]=0;
		
		point[pointindex].vx = atoi(word);
		
		k+=2;
		w=0;
		while(line[k]!='>')
			word[w++]=line[k++];
		word[w]=0;
		
		point[pointindex].vy = atoi(word);
		
		pointindex++;
	}
	
	int dx;
	int dy;
	
	dx = point[0].x - point[1].x;
	dy = point[0].y - point[1].y;
	
	int s=0;
	while(abs(dx)>15 || abs(dy)>15)
	{
		s++;
		for(int i=0;i<LINES;i++)
		{
			point[i].x += point[i].vx;
			point[i].y += point[i].vy;
		}
		
		dx = point[0].x - point[1].x;
		dy = point[0].y - point[1].y;
		
	}
	printf("%d %d\n",dx,dy);
//	for(int i=0;i<pointindex;i++)
//		printf("%d %d\n", point[i].x, point[i].y);


	int times=2;
	
	while(times>0)
	{
		
		for(int i=0;i<LINES;i++)
		{
			point[i].x += point[i].vx;
			point[i].y += point[i].vy;
		}
	

		for(int i=140;i<170;i++)
		{
			for(int j=100;j<190;j++)
			{
				int flag=1;
				for(int k=0;k<pointindex;k++)
					if(point[k].x == j && point[k].y == i)
					{
						printf("#");
						flag=0;
						break;
					}
				if(flag)
					printf(".");
			}
			printf("\n");
		}
			
		times--;
	}
	
	printf("seconds:%d/n",s+2);
	return 0;
}
