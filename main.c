//
// Created by camaron.williams on 11/29/2022.
//
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Point
{
    int x;
    int y;
}Point;

typedef struct Line
{
    struct Point a;
    struct Point b;
    float length;
}Line;

struct Line * readFile(char file_name[], int *n)
{
    FILE *fp;
    fp=fopen(file_name,"r");
    fscanf(fp,"%d",n);
    struct Line *lines=(struct Line *)malloc(sizeof(struct Line)*(*n));
    printf("Array of size %d created\n",*n);
    int i;
    for(i=0;i<*n;i++)
    {
        fscanf(fp,"%d %d %d %d",&lines[i].a.x,&lines[i].a.y,&lines[i].b.x,&lines[i].b.y);
    }
    printf("Data read\n");
    fclose(fp);
    return lines;
}

void computeLengths(struct Line *lines, int n)
{
    printf("Computing lengths...\n");
    int i;
    for(i=0;i<n;i++)
    {
        lines[i].length=sqrt(pow(lines[i].a.x-lines[i].b.x,2)+pow(lines[i].a.y-lines[i].b.y,2));
    }
    printf("Length computation completed\n");
}

void saveLengths(struct Line *lines, int n)
{
    printf("Saving lengths...\n");
    FILE *fp;
    fp=fopen("lengths_LastName_firstName.txt","w");
    int i;
    for(i=0;i<n;i++)
    {
        fprintf(fp,"%f\n",lines[i].length);
    }
    fclose(fp);
}

void printStats(struct Line *lines, int n)
{
    float max=lines[0].length;
    float min=lines[0].length;
    float sum=0;
    int i;
    for(i=0;i<n;i++)
    {
        if(lines[i].length>max)
            max=lines[i].length;
        if(lines[i].length<min)
            min=lines[i].length;
        sum+=lines[i].length;
    }
    printf("Line of max length: %f\nLine with min length: %f\nAverage line length: %f\n",max,min,sum/n);
}

int main(int argc, char *argv[])
{
    int n;
    struct Line *lines=readFile(argv[1],&n);
    computeLengths(lines,n);
    saveLengths(lines,n);
    printStats(lines,n);
    return 0;
}
