#include <stdio.h>
#include <string.h>

#define LEN 512

void main()
{
	int count;
	char line[LEN];
	
	fgets(line,LEN,stdin);
	int len=strlen(line);
	int spacecount=0;
	int lettercount=0;
	
	//remove "initial state: "
	for(int i=0;i<len;i++)
	{
		lettercount++;
		if(line[i]==' ')
			spacecount++;
		line[i]='.';
		if(spacecount==2)
			break;
	}
	char m[len*3];
	char mcopy[len*3];
	
	//to make room for expansion to each side
	for(int i=0;i<len;i++)
		m[i]='.';
	for(int i=len;i<len*2-1;i++)
		m[i]=line[i-len];
	for(int i=len*2-1;i<len*3;i++)
		m[i]='.';
	m[len*3-1]='\0';
	
	char rules[32][16];
	
	fgets(line,LEN,stdin);
	int rulescount=0;
	while(fgets(line,LEN,stdin)!=NULL)
		strcpy(rules[rulescount++],line);
	
	for(int mindex=0;mindex<len*3;mindex++)
		mcopy[mindex]='.';
	

	for(int roundindex=0; roundindex < 20; roundindex++)
	{
		for(int mindex=2; mindex < len*3-3; mindex++)
			for(int rulesindex=0; rulesindex < rulescount; rulesindex++)
				if(	m[mindex-2]	==rules[rulesindex][0] &&
					m[mindex-1]	==rules[rulesindex][1] &&
					m[mindex]	==rules[rulesindex][2] &&
					m[mindex+1]	==rules[rulesindex][3] &&
					m[mindex+2]	==rules[rulesindex][4])
					{
						mcopy[mindex]=rules[rulesindex][9];
						break;
					}
					
					
		for(int mindex=0;mindex<len*3;mindex++)
		{
			m[mindex]=mcopy[mindex];
			mcopy[mindex]='.';
		}
	}
	
	int total=0;
	
	
	// lettercount accounts for "initial state: " in input
	for(int i=0;i<len;i++)
		if(m[i]=='#')
			total+=(len-i)*-1-lettercount;
		
	
	for(int i=len;i<len*3;i++)
		if(m[i]=='#')
			total+=i-len-lettercount;

	printf("%d\n",total);
	return;
}
