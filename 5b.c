#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 50002

int main(void) {
	char line[LEN];
	fgets(line,LEN,stdin);
	int valid[LEN];
	int len=strlen(line);
	int min, total;
	min=LEN;
	int a,b;
	if(line[len-1]=='\n')
		line[--len]=0;
	
	
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<len;j++)
			valid[j]=1;
		
		for(int j=0;j<len;j++)
		{
			if(line[j]=='a'+i || line[j]=='A'+i)
				valid[j]=0;
		}
		
		
		a=0;
		b=1;
		while(!valid[a])
			a++;
		b=a+1;
		while(!valid[b])
			b++;
			
			
		while(b<len)
		{
	
			if(abs(line[a]-line[b]) == 'a'-'A')
			{
				valid[a] = valid[b] = 0;
				while(!valid[a] && a>0)
					a--;
				
			} else 
				a++;

			while(!valid[a])
				a++;
			b=a+1;
			while(!valid[b])
				b++;
			
		}
		
		total=0;
		for(int j=0;j<len;j++)
			if(valid[j])
				total++;
		
		if(min>total)
			min=total;
	}

	printf("%d",min);
	
	return 0;
}
