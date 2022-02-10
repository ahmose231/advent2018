#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 32
#define SAFEDISTANCE 10000

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

	int total_manhattan;
	int y_edge = max_y+1;
	int x_edge = max_x+2;
	int grid[y_edge][x_edge];
	int equal;
	int closest_coordinate;
	for(int y=0;y<y_edge;y++)
		for(int x=0;x<x_edge;x++)
		{
			total_manhattan=0;
			for(int i=0;i<coordinate_count;i++)
				total_manhattan += abs(coordinates[i][0] - x) + abs(coordinates[i][1] - y);
			grid[y][x]=total_manhattan;
		}
	
	int area=0;
	for(int y=0;y<y_edge;y++)
		for(int x=0;x<x_edge;x++)
			if(grid[y][x]<SAFEDISTANCE)
				area++;
			
	printf("%d\n",area);
	
	return;
}
