#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
#define SIZE 10

void print(int t[],int s)
{
    int i;
    for(i=0; i<s; ++i)
    {
        printf("%d ", t[i]);
    }
    printf("\n");
    return;
}

void fill(int t[], int s)
{
    int i;
    for(i=0;i<s;++i)
    {
        t[i]=(rand()%17)+10;
    }
}

int isEven(int t[], int s)
{
    int i;
    for(i=0; i<s; ++i)
    {
        if(t[i]%2!=0) return 0;
    }
    return 1;
}

int sum(int t[], int s)
{
    int add;
    int i;
    add=0;
    for(i=0; i<s; ++i)
    {
        add+=t[i];
    }
    return add;
}

int isAvgEven(int t[], int s)
{
    int add;
    add = sum(t,s);
    return ((int)(floor( add / ((double) s)  )))%2 ? 1 : 0;
}

int findMax(int t[], int s)
{
    int v,i;
    v = INT_MIN;
    for(i = 0; i < s; ++i)
    {
        if(t[i] > v) 
            v=t[i];
    }
    return v;
}

void fillMax(int t[], int s, int x)
{
    int v, i;
    v = findMax(t, s);
    for(i = 0; i < s; ++i)
    {
        if(t[i] > x)
            t[i] = v;
    }
    return;
}

int main(int argc, char* argv[])
{    
    int i;
    int Array[SIZE];
    
    
    printf("Hello, world!\n");
    srand(time(NULL));
    
    fill(Array,SIZE);
    print(Array,SIZE);
    printf("%d\n", isEven(Array,SIZE));
    printf("%d\n", isAvgEven(Array,SIZE));
    fillMax(Array,SIZE,2);
    print(Array,SIZE);
    printf("Goodbye, world!\n");
    return 0;
}