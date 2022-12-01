#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define MAX 100

struct Point
{
    int x;
    int y;
};

struct Line
{
    struct Point a;
    struct Point b;
    float length;
};

struct Line * readFile(char file_name[], int *n)
{
    int i, j, size;
    FILE *fp = fopen(file_name, "r");
    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return NULL;
    }

    fscanf(fp, "%d", &size);
    struct Line *lines = (struct Line *) malloc(sizeof(struct Line) * size);

    printf("Array of size %d created\n", size);
    for(i = 0; i < size; i++)
    {
        fscanf(fp, "%d %d %d %d", &(lines[i].a.x), &(lines[i].a.y), &(lines[i].b.x), &(lines[i].b.y));
    }

    *n = size;

    printf("Data read\n");

    fclose(fp);

    return lines;
}

void computeLengths(struct Line *lines, int n)
{
    int i;

    printf("Computing lengths...\n");

    for(i = 0; i < n; i++)
    {

        lines[i].length = sqrt(pow((lines[i].a.x - lines[i].b.x), 2) + pow((lines[i].a.y - lines[i].b.y), 2));
    }

    printf("Length computation completed\n");
}
void saveLengths(struct Line* lines, int n)
{
    int i;

    // open file lengths_LastName_firstName.txt to write
    FILE *fp = fopen("lengths_LastName_firstName.txt", "w");

    // check if file opened successfully
    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Saving lengths...\n");
    for(i = 0; i < n; i++)
    {
        fprintf(fp, "%.1f\n", lines[i].length);
    }

    fclose(fp);
}
void printStats(struct Line* lines, int n)
{
    int i;
    float max, min, avg;
    max = min = avg = lines[0].length;

    for(i = 1; i < n; i++)
    {
        if(max < lines[i].length)
        {
            max = lines[i].length;
        }

        if(min > lines[i].length)
        {
            min = lines[i].length;
        }

        avg += lines[i].length;
    }

    avg /= n;

    printf("Line of max length: %.1f\n", max);
    printf("Line with min length: %.1f\n", min);
    printf("Average line length: %.1f\n", avg);
}

int main(int argc, char* argv[])
{
    int i, n;
    if(argc != 2)
    {
        printf("Error! Please enter filename as command-line argument.\n");
        return 1;
    }

    struct Line *lines = readFile(argv[1], &n);

    computeLengths(lines, n);

    saveLengths(lines, n);

    printStats(lines, n);

    return 0;
}