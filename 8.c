#include<stdio.h>

#define COUNT 15841

int m[COUNT];
int totalsum=0;

int skip_node(int index)
{
    int cn;
    int md;
    cn=m[index++];
    md=m[index++];
    for(int i=0;i<cn;i++)
        index=skip_node(index);
    for(int i=0;i<md;i++)
        index++;
    return index;
}

void process_node(int index)
{
    int cn=m[index++];
    int md=m[index++];
    for(int i=0;i<cn;i++)
    {
        process_node(index);
        index=skip_node(index);
    }
    
    for(int i=0;i<md;i++)
        totalsum += m[index++];
    
    return;
}

int main() {
    int x;
    int i=0;
    while(scanf("%i",&x)!=EOF)
        m[i++]=x;
        
    process_node(0);    
    
    printf("%d\n",totalsum);
    return 0;
}
