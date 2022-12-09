#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define ERROR -1
#define EXIT_SUCCESS 0
#define MAX_FILE_NAME 256

struct _node;
typedef struct _node* Position;
typedef struct _node
{
    float element;
    Position Next;
}node;

int Pop(Position);
int Push(Position, float);
int InsertAfter(Position, Position);
int CalculatePostfix(Position, float*);

int main()
{
    float a = 0.0f;
    node Head;
    Head.element = 0.0f;
    Head.Next = NULL;
    CalculatePostfix(&Head, &a);
    
    printf("Result is: %f", a);
    return EXIT_SUCCESS;
}

//6523+8*+3+*
//69*0+6-70*+3-1-

int CalculatePostfix(Position Head, float *res)
{
    int n = 0, i = 0, pom = 0;
    float first = 0.0f, second = 0.0f, result = 0.0f;
    char filename[MAX_FILE_NAME] = { 0 };
    char buffer[MAX] = { 0 };
    char* b = buffer;
    
    Head = (Position)malloc(sizeof(node));
    if (Head == NULL)
    {
        printf("Failed in dynamic allocation!");
        return ERROR;
    }

    Head->Next = NULL;
    FILE* fp = NULL;
    

    printf("Insert filename:\n");
    scanf(" %s", filename);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error in file opening!");
        return ERROR;
    }
    fgets(b, MAX, fp);
    
    while (strlen(b) > 0)
    {
        int br = 0;
        pom = sscanf(b, "%d %n ", &br, &n);
        if (pom == 1)
        {
            Push(Head, br);
            b += n;
            printf("%d", br);
        }
        else
        {
            char ch = ' ';
            if (sscanf(b, "%c %n", &ch, &n) == 1)
            switch (ch)
            {
                case '+':
                {
                    first = Pop(Head);
                    second = Pop(Head);
                    result = first + second;
                    Push(Head, result);
                    break;
                }
                case '-':
                {
                    first = Pop(Head);
                    second = Pop(Head);
                    result = second - first;
                    Push(Head, result);
                    break;
                }
                case '*':
                {
                    first = Pop(Head);
                    second = Pop(Head);
                    result = first * second;
                    Push(Head, result);
                    break;
                }
                case '/':
                {
                    first = Pop(Head);
                    second = Pop(Head);
                    result = second / first;
                    if (first == 0)
                    {
                        printf("Dividing by zero is undefined!");
                        return ERROR;
                    }
                    Push(Head, result);
                    break;
                }
                default:
                    printf("\nInvalid input.\n");
                    break;
                
            }
            b += n;
            printf("%c ", ch);
        }
    }
    fclose(fp);
    *res = Pop(Head);
    return EXIT_SUCCESS;
}

int Push(Position P, float newElement)
{
    Position Q = NULL;
    Q = (Position)malloc(sizeof(node));
    if (Q == NULL)
    {
        printf("Failed in dynamic allocation!");
        return ERROR;
    }
    Q->element = newElement;
    InsertAfter(P, Q);
    return EXIT_SUCCESS;
}

int Pop(Position P)
{
    if (P->Next == NULL) {
        printf("The stack is empty!\n");
        return ERROR;
    }
    else {
        float x = 0.0f;
        Position temp = NULL;
        temp = P->Next;
        x = temp->element;
        P->Next = temp->Next;
        free(temp);
        return x;
    }
}

int InsertAfter(Position P, Position Q)
{
    Q->Next = P->Next;
    P->Next = Q;
    return EXIT_SUCCESS;
}
