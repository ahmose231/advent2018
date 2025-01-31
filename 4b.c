#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 64
#define MAXLINE 1300

int main(void) {

	char line[LEN];
	char lines[MAXLINE][LEN];
	char sorted[MAXLINE][LEN];
	int len;
	int linecount=0;
	
	while(fgets(line,LEN,stdin)!=NULL)
	{
		len=strlen(line);
		if(line[len-1]=='\n')
			line[--len]=0;
		strcpy(lines[linecount++], line);
	}
	
	int sortindex=0;
	int check[MAXLINE];
	for(int i=0;i<linecount;i++)
		check[i]=1;
	
	int min;
	for(int i=0;i<linecount;i++)
		if(check[i])
		{
			min=i;
			for(int j=0;j<linecount;j++)
				if(check[j])
					if(strcmp(lines[min], lines[j])>0)
						min=j;
				
			strcpy(sorted[sortindex++], lines[min]);
			check[min]=0;
		}
	
/*	for(int i=0;i<sortindex;i++)
		printf("%s\n",sorted[i]);
	*/
	
	int guardcount=0;
	int guardlist[100];
	char word[8];
	int k;
	for(int i=0;i<sortindex;i++)
	{
		k=0;
		len=strlen(sorted[i]);
		for(int j=0;j<len;j++)
			if(sorted[i][j]=='#')
			{
				j++;
				while(sorted[i][j]!=' ')
					word[k++] = sorted[i][j++];
			
				word[k]=0;
			
			}
		
		int guardfound;
		if(k)
		{
			guardfound=0;
			for(int j=0;j<guardcount;j++)
				if(atoi(word)==guardlist[j])
				{
					guardfound=1;
					break;
				}
			
			if(!guardfound)
				guardlist[guardcount++] = atoi(word);
		}
	
	}

	struct proto_guard {
		int id;
		int shiftcount;
		int sleepcount;
		int sleeptime[40][60];
		int maxminute;
	};
	
	struct proto_guard guard[guardcount];
	
	for(int i=0;i<guardcount;i++)
	{
		guard[i].id = guardlist[i];
		guard[i].shiftcount = 0;
		guard[i].sleepcount = 0;
	}
	
	int dash;
	len=strlen(sorted[0]);
	for(dash=0;dash<len;dash++)
		if(sorted[0][dash]=='#')
			break;
	int m;
	int currentguard;
	int gid;
	int from;
	int to;
	
	for(int i=0;i<sortindex;i++)
	{
		if(strlen(sorted[i])>dash+7)
		{
			k=0;
			m=dash+1;
			
			while(sorted[i][m]!=' ')
				word[k++] = sorted[i][m++];
			word[k]=0;

			currentguard = atoi(word);
			
			for(int j=0;j<guardcount;j++)
				if(guard[j].id == currentguard)
				{
					gid = j;
					guard[gid].shiftcount++;
					break;
				}

			continue;
		}
		
		
		
		word[0]=sorted[i][15];
		word[1]=sorted[i][16];
		word[2]=0;

		from = atoi(word);
		
		i++;

		word[0]=sorted[i][15];
		word[1]=sorted[i][16];
		word[2]=0;

		to = atoi(word);
		
		for(int j=0;j<60;j++)
			guard[gid].sleeptime[guard[gid].sleepcount][j]=0;
		
		for(int j=from;j<to;j++)
			guard[gid].sleeptime[guard[gid].sleepcount][j]=1;
		
		
		guard[gid].sleepcount++;
		
	}
	
	
	int max1=0;
	int max2;
	
	int maxguard;
	int minutecount;
	
	int maxminute;
	int max2minute;
	
	for(int i=0;i<guardcount;i++)
	{
		max2=0;
		
		for(int z=0;z<60;z++)
		{
			minutecount=0;
		
			for(int j=0;j<guard[i].sleepcount;j++)
				if(guard[i].sleeptime[j][z])
					minutecount++;
			
			if(max2<minutecount)
			{
				max2=minutecount;
				max2minute=z;
			}
		}
		
		if(max1<max2)
		{
			max1 = max2;
			maxminute = max2minute;
			maxguard = i;
		}
	}
	
//	printf("guard id: %d maxminute: %d maxcount: %d", guard[maxguard].id, maxminute, max1);
	printf("%d\n", guard[maxguard].id * maxminute);	
/*	
	for(int i=0;i<guardcount;i++)
	{
		printf("guard id: %d\n",guard[i].id);
		for(int j=0;j<guard[i].sleepcount;j++)
		{
			for(int z=0;z<60;z++)
			{
				if(guard[i].sleeptime[j][z])
					printf("#");
				else
					printf(".");
			}
			printf("\n");
		}
	}
*/
	return 0;
}
