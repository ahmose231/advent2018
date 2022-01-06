#include<stdio.h>

#define COUNT 16000

int m[COUNT];

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

int process_node(int index)
{
    int temp=index;
    
    int cn=m[index++];
    int md=m[index++];
    
    int cnlength[cn];
    for(int i=0;i<cn;i++)
    {
        cnlength[i]=index;
        index=skip_node(index);
        cnlength[i]=index-cnlength[i];
    }
    
    int sum=0;
    int mdlist[md];
    int k=0;
    for(int i=0;i<md;i++)
    {
        mdlist[k++]=m[index];
        sum += m[index++];
    }
    if(cn==0)
        return sum;
        
    index=temp+2;
    sum=0;
    temp=index;
    for(int i=0;i<cn;i++)
    {
        for(int j=0;j<md;j++)
        {
            if(i+1==mdlist[j])
            {
                index=temp;
                for(int a=0;a<i;a++)
                    index+=cnlength[a];
                sum=sum+process_node(index);

            }
        }
    }
    return sum;
}

int main() {
    int x;
    int i=0;
    while(scanf("%i",&x)!=EOF)
        m[i++]=x;
        
    int sum=process_node(0);    
    
    printf("%d\n",sum);
    return 0;
}
