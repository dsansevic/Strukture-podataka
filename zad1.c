#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_DIDNT_OPEN_ERROR -1
#define MAX 50

typedef struct
{
    char name[20];
    char lastname[20];
    int score;
}STUDENT;


int countStudentsFromFile(char *f)
{
    FILE* fp = NULL;
    int count = 0;
    fp = fopen(f, "r");
    if (fp == NULL)
    {
        printf("Neuspjesno otvaranje datoteke %s!\r\n", f);
        return FILE_DIDNT_OPEN_ERROR;
    }
    while (!feof(fp))
    {
        if(fgetc(fp) == '\n')
            count++;
    }
    rewind(fp); 
    fclose(fp);
    return count - 1;
}

void EnterStudents(char* file, int number, STUDENT* s)
{
    int i;
    FILE* f = NULL;
    f = fopen(file, "r");
    if (f == NULL)
    {
        printf("Failed in file opening!");
        return;
    }

    for (i = 0; i < number; i++)
        fscanf(f, "%s %s %d", (s + i)->name, (s + i)->lastname, &(s + i)->score);

    fclose(f);
    return;
}


void PrintStudents(int number, STUDENT* s)
{
    int i;
    for (i = 0; i < number; i++)
        printf("Student: %s %s\nAbsolutely score %d\nRelative score: %f\n", (s + i)->name, (s + i)->lastname, (s + i)->score, ((double)(s + i)->score / MAX) * 100);
    return;
}

int main()
{
    STUDENT *st = NULL;
    int result;
    result = countStudentsFromFile("c:\\tmp\\bodovi.txt");

    st = (STUDENT*)malloc(result * sizeof(STUDENT));
    if (st == NULL)
        printf("Failed in dynamic allocation!");
    
    EnterStudents("c:\\tmp\\bodovi.txt", result, st);
    PrintStudents(result, st);
    free(st);
    return 0;
}
