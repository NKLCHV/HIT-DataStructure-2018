#include<stdio.h>
#include<string.h>

int newstrcmp(char *str1, char *str2)
{
    int i=0,j=0;
    while(1)
    {
        int a,b;
        a=str1[i];
        b=str2[j];
        a=fun(a);
        b=fun(b);
        if(a=='\0'&&b!='\0')
            return -1;
        else if(b=='\0'&&a!='\0')
            return 1;
        else if(a=='\0'&&b=='\0')
            return 1;
        if(a==b)
        {
            i++;
            j++;
        }
        else if(a!=b)
        {
            return a-b;
        }
    }
}

int fun (int ch)
{
    if(ch>=48&&ch<=57)
        ch=ch+100;
    return ch;
}

int main()
{
    char *m[]= {"pab","5c","pabc","cxy","crsi","7","b899","b9"};
    char *temp=NULL;
    int i,j,test;
    for(i=0; i<8; i++)
    {
        for(j=i+1; j<8; j++)
        {
            if(newstrcmp(m[i],m[j])>0)
            {
                temp=m[i];
                m[i]=m[j];
                m[j]=temp;
            }
        }

    }
    for(i=0; i<8; i++)
    {
        printf("%s\n",m[i]);
    }

}

