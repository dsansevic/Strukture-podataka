#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define EXIT_SUCCESS 0
#define FILE_NAME 256
#define ERROR -1
#define MAX 100
#define N 10
#define LOWER 10
#define UPPER 90

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	int element;
	Position right;
	Position left;
}tree;


Position Insert(Position, Position);
Position MakeNew(int, Position);
Position InsertRandom(Position);

int rnd();
int PrintPostorder(Position);
int PrintInFile(Position, char *);
int Replace(Position);
int InOrder(Position, FILE *);
int PrintInorder(Position);
int DeleteAll(Position);



int main()
{
	Position root = NULL;
	int i = 0, el = 0, choice = 0;
	Position Q = (Position)malloc(sizeof(_tree));
	int array[N] = { 2, 5, 1, 7, 4, 8, 2, 11, 7, 3 };
	char filename[MAX] = { 0 };
	srand(unsigned(time(0)));
	printf("Do you want 1) determined numbers or 2) randomly generated?\nEnter the number > ");
	scanf("%d", &choice);
	if (choice == 1)
	{
		for (i = 0; i < 10; i++)
		{
			Q = MakeNew(array[i], root);
			root = Insert(root, Q);
		}
	}
	else if (choice == 2)
	{
		for (i = 0; i < N; i++)
		{
			Q = MakeNew(rnd(), root);
			root = Insert(root, Q);
		}
	}
	printf("Insert filename > ");
	scanf("%s", filename);
	Replace(root);
	PrintInorder(root);
	PrintInFile(root, filename);
	DeleteAll(root);
	return EXIT_SUCCESS;
}

Position MakeNew(int x, Position P)
{
	P = (Position)malloc(sizeof(_tree));
	P->element = x;
	P->left = NULL;
	P->right = NULL;
	return P;
}

Position Insert(Position P, Position Q)
{
	if (P == NULL)
		return Q;
	else if (P->element <= Q->element)
		P->left = Insert(P->left, Q);
	else
		P->right = Insert(P->right, Q);
	return P;
}

int Replace(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;

	int temp = P->element;
	P->element = Replace(P->left) + Replace(P->right);
	return P->element + temp;
}

int InOrder(Position P, FILE *fp)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	InOrder(P->left, fp);
	fprintf(fp, "%d ", P->element);
	InOrder(P->right, fp);
	return EXIT_SUCCESS;
}

int PrintInFile(Position P, char *fileName) {
	FILE* fp = NULL;
	fp = fopen(fileName, "w");

	if (fp == NULL)
	{
		printf("Error in file opening!\n");
		return ERROR;
	}
	
	InOrder(P, fp);
	fclose(fp);
	return EXIT_SUCCESS;
}

int PrintInorder(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	PrintInorder(P->left);
	printf("%d\t", P->element);
	PrintInorder(P->right);
	return EXIT_SUCCESS;
}

int rnd()
{
	int el = 0;
	el = (rand() % (UPPER - LOWER)) + LOWER;
	return el;
}

int DeleteAll(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	DeleteAll(P->left);
	DeleteAll(P->right);
	return EXIT_SUCCESS;
}
