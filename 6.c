#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 32

void main(int argc, char *argv[])
{
	char line[LEN];
	FILE *fp=fopen(argv[1],"r");
	if(fp==NULL) {
		printf("no file\n");
		exit(0);
	}
	
	int coordinate_count=0;
	while(fgets(line,LEN,fp)!=NULL)
	{
		if(strlen(line)<2) continue;
		coordinate_count++;
	}
	
	int coordinates[coordinate_count][2];
	rewind(fp);
	int k=0;
	while(fgets(line,LEN,fp)!=NULL)
	{
		if(strlen(line)<2) continue;
		coordinates[k][0]=atoi(strtok(line,","));
		coordinates[k][1]=atoi(strtok(NULL,","));
		k++;
	}
	
	int min_x, min_y, max_x, max_y;
	min_x=max_x=coordinates[0][0];
	min_y=max_y=coordinates[0][1];
	for(int i=0;i<coordinate_count;i++)
	{
		if(min_x > coordinates[i][0])
			min_x = coordinates[i][0];
		if(max_x < coordinates[i][0])
			max_x = coordinates[i][0];
		if(min_y > coordinates[i][1])
			min_y = coordinates[i][1];
		if(max_y < coordinates[i][1])
			max_y = coordinates[i][1];
	}
	int manhattan;
	int min_manhattan;
	int y_edge = max_y+1;
	int x_edge = max_x+2;
	int grid[y_edge][x_edge];
	int equal;
	int closest_coordinate;
	for(int y=0;y<y_edge;y++)
		for(int x=0;x<x_edge;x++)
		{
			min_manhattan=max_x*max_y;
			for(int i=0;i<coordinate_count;i++)
			{
				manhattan=abs(coordinates[i][0] - x) + abs(coordinates[i][1] - y);
				if(min_manhattan >= manhattan)
				{
					if(min_manhattan == manhattan)
						equal=1;
					else
					{
						min_manhattan = manhattan;
						equal=0;
						closest_coordinate = i;
					}
				}
			}
			
			if(equal)
				grid[y][x]=-1;
			else
				grid[y][x]=closest_coordinate;
		}
	
	int edges[coordinate_count];
	for(int i=0;i<coordinate_count;i++)
		edges[i]=0;

	for(int i=0;i<x_edge;i++)
	{
		if(grid[0][i]<0 || grid[y_edge-1][i]<0)
			continue;
		edges[grid[0][i]]++;
		edges[grid[y_edge-1][i]]++;
	}
	for(int i=0;i<y_edge;i++)
	{
		if(grid[i][0]<0 || grid[i][x_edge-1]<0)
			continue;
		edges[grid[i][0]]++;
		edges[grid[i][x_edge-1]]++;
	}
	
	int area[coordinate_count];
	for(int i=0;i<coordinate_count;i++)
		area[i]=0;
	for(int y=0;y<y_edge;y++)
		for(int x=0;x<x_edge;x++)
			if(grid[y][x]!='.')
				area[grid[y][x]]++;
	
	int max_area = 0;
	for(int i=0;i<coordinate_count;i++)
		if(!edges[i])
			if(max_area < area[i])
				max_area = area[i];
			
	printf("%d\n",max_area);
			
	return;
}
