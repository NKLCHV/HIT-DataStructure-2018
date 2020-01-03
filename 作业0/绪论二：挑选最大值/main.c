#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,s=0;
    double i;
    double a[100];
    printf("Please input the numbers:");
    for(i=0;i<10;i++)
    {
        scanf("%lf",&a[i]);
    }
    t=a[0];
    for(i=1;i<10;i++)
    {
        if(a[i]>t)
            t=a[i];
            s=i;
    }
    printf("The largest number is the %dth:%lf",s+1,t);
    return 0;
}
