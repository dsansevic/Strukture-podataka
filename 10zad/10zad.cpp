#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define MAX_FILE_NAME 256
#define ERROR -1
#define MAX 100

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	char cityName[MAX];
	int population;
	Position right;
	Position left;
}tree;

struct _list;
typedef struct _list* ListPosition;
typedef struct _list {
	char stateName[MAX];
	char fileName[MAX_FILE_NAME];
	ListPosition Next;
	Position TreeP;
}list;

int ReadStateFromFile(ListPosition P, Position, char*);
int CheckDynamicAllocationList(ListPosition);
int InsertAfter(ListPosition, ListPosition);
int InsertSort(ListPosition, ListPosition);
int ReadStateFile(ListPosition, Position);
int CheckDynamicAllocationTree(Position);
int printBiggerCities(Position, int);
int CheckIfFileOpened(FILE*);
int DeleteAll(ListPosition);
int PrintTreeInOrder(Position);
int DeleteTree(Position);
int Print(ListPosition);

Position InsertInTree(Position*, Position);
ListPosition FindCity(ListPosition, char*);

int main()
{
	struct _list head;
	head.Next = NULL;
	struct _tree root;
	root.right = NULL;
	root.left = NULL;
	ListPosition state;

	char fileName[MAX_FILE_NAME] = { 0 };
	char stateToFind[MAX] = { 0 };
	int minPopulation = 0;

	do {
		printf("Insert 'drzave.txt' > ");
		scanf("%s", fileName);
	} while (strcmp("drzave.txt", fileName));

	ReadStateFromFile(&head, &root, fileName);
	Print(head.Next);

	do {
		printf("Insert state you want to find > ");
		scanf("%s", stateToFind);
		state = FindCity(head.Next, stateToFind);
	} while (state == NULL);
	
	printf("\nInsert population > ");
	scanf("%d", &minPopulation);
	printBiggerCities(state->TreeP, minPopulation);
	
	DeleteAll(&head);

	return EXIT_SUCCESS;
}

int ReadStateFromFile(ListPosition P, Position T, char* fileName)
{
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	char stateName[MAX] = { 0 }, stateFile[MAX_FILE_NAME] = { 0 };

	CheckIfFileOpened(fp);

	while (!feof(fp))
	{
		fscanf(fp, "%s %s", stateName, stateFile);								
		ListPosition Q = NULL;
		Q = (ListPosition)malloc(sizeof(list));
		CheckDynamicAllocationList(Q);
		
		strcpy(Q->stateName, stateName);
		strcpy(Q->fileName, stateFile);
		Q->Next = NULL;
		Q->TreeP = NULL;
		InsertSort(P, Q);
		ReadStateFile(Q, T);
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

int ReadStateFile(ListPosition P, Position T)
{
	FILE* fp = NULL;
	fp = fopen(P->fileName, "r");
	CheckIfFileOpened(fp);
	
	char cityName[MAX] = { 0 };
	int population = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%s %d", cityName, &population);
		Position NewT = NULL;
		NewT = (Position)malloc(sizeof(tree));
		CheckDynamicAllocationTree(NewT);

		strcpy(NewT->cityName, cityName);
		NewT->population = population;
		NewT->left = NULL;
		NewT->right = NULL;
		InsertInTree(&(P->TreeP), NewT);
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

int CheckDynamicAllocationList(ListPosition P)
{
	if (P == NULL)
	{
		perror("Error");
		return ERROR;
	}
	return EXIT_SUCCESS;
}

int CheckDynamicAllocationTree(Position P)
{
	if (P == NULL)
	{
		perror("Error");
		return ERROR;
	}
	return EXIT_SUCCESS;
}


int InsertSort(ListPosition P, ListPosition Q)
{
	ListPosition head = P;
	while (head->Next != NULL && strcmp(head->Next->stateName, Q->stateName) < 0)
		head = head->Next;
	InsertAfter(head, Q);

	return EXIT_SUCCESS;
}

int InsertAfter(ListPosition P, ListPosition Q)
{
	Q->Next = P->Next;
	P->Next = Q;
	return EXIT_SUCCESS;
}

int Print(ListPosition P)
{
	while (P != NULL)
	{
		printf("*STATE: %s\n", P->stateName);
		if (P->TreeP != NULL)
		{
			printf("Cities:\n");
			PrintTreeInOrder(P->TreeP);
			printf("\n");
		}
		P = P->Next;
	}
	return EXIT_SUCCESS;
}

int CheckIfFileOpened(FILE* fp)
{
	if (fp == NULL)
	{
		perror("Error in file opnening");
		return ERROR;
	}
	return EXIT_SUCCESS;
}

Position InsertInTree(Position* P, Position Q)
{
	if (*P == NULL)
		*P = Q;
	else if ((*P)->population > Q->population)
		(*P)->left = InsertInTree(&(*P)->left, Q);
	else if ((*P)->population == Q->population)
	{
		if (strcmp((*P)->cityName, Q->cityName) > 0)
			(*P)->left = InsertInTree(&(*P)->left, Q);
		else (*P)->right = InsertInTree(&(*P)->right, Q);
	}
	else (*P)->right = InsertInTree(&(*P)->right, Q);

	return (*P);
}

int PrintTreeInOrder(Position T)
{
	if (T == NULL)
		return EXIT_SUCCESS;
	PrintTreeInOrder(T->left);
	printf("%s\t%d\n", T->cityName, T->population);
	PrintTreeInOrder(T->right);
	return EXIT_SUCCESS;

}
ListPosition FindCity(ListPosition P, char* stateName)
{
	while (P != NULL && strcmp(P->stateName, stateName))
		P = P->Next;

	if (P == NULL)
	{
		printf("State not found!Try Again:\n");
		return NULL;
	}

	return P;
}

int printBiggerCities(Position P, int minPopulation)
{
	if (P == NULL)
		return EXIT_SUCCESS;
		
	printBiggerCities(P->left, minPopulation);
	if (P->population > minPopulation)
		printf("%s\t%d\n", P->cityName, P->population);

	printBiggerCities(P->right, minPopulation);
	return EXIT_SUCCESS;
}

int DeleteTree(Position root)
{
	if (root == NULL)
			return EXIT_SUCCESS;
	DeleteTree(root->left);
	DeleteTree(root->right);
	free(root);

	return EXIT_SUCCESS;
}

int DeleteAll(ListPosition P)
{
	ListPosition temp = P;

	while (P->Next != NULL)
	{
		DeleteTree(P->TreeP);

		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}
