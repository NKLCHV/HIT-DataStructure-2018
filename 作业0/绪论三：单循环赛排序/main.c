#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    int n;
    printf("Input the n:");
    scanf("%d",&n);

    int p[n];
    int a[n][n];
    int i,j;

    srand((int)time(NULL));
    for(i=0; i<n; i++)
    {
        p[i]=rand()%100;
        printf("%d\t",p[i]);
    }
    printf("\n");

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(p[i]<p[j])
            {
                a[i][j]=1;
            }
            else
                a[i][j]=0;
        }
    }

    int temp,sum[n];
    for(i=0; i<n; i++)
    {
        sum[i]=0;
        for(j=0; j<n; j++)
        {
            sum[i]=sum[i]+a[i][j];
        }
    }
    int ans[n];
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(sum[j]==i)
            {
                ans[i]=p[j];
            }
        }
    }
    for(i=0; i<n; i++)
    {
        //int total=sum[i];
        printf("%d\n",ans[i]);
    }
    return 0;
}
