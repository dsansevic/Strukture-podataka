#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1

struct node;
typedef struct node* Position;
typedef struct node
{
	int data;
	Position right;
	Position left;
}Node;

Position InsertNew(Position, Position);
Position MakeNew(Position, int);
int PrintInorder(Position);
int PrintPreorder(Position);
int PrintPostorder(Position);
int PrintLevelorder(Position);
int PrintCurrentLevel(Position, int);
int Height(Position);
Position DeleteElement(Position, int);
Position FindElement(Position, int);
Position FindMax(Position);
Position FindMin(Position);

int main()
{
	Position root;
	root->data = 0;
	root->left = NULL;
	root->right = NULL;
	Position element;
	int x = 0, i = 0, option = 0, number = 0;
	element = (Position)malloc(sizeof(Node));
	do
	{
		switch (option)
		{
		case 1:
			scanf("%d", &x);
			Q = MakeNew(root, x);
			root = InsertNew(root, Q);
			break;
		case 2;
			PrintInorder(root);
			break;
		case 3:
			PrintPostorder(root);
			break;
		case 4:
			PrintPreorder(root);	
			break;
		case 5:
			printf("Which element do you want do delete?\n");
			scanf("%d", &number);
			root = DeleteElement(root, number);
			break;
		case 6:
			printf("Which element do you want to find?\n");
			scanf("%d", &number);
			element = FindElement(root, number);
			if (element == NULL)
				{
					printf("Element not found!\n");
					return ERROR;
				}
				else
					printf("Element %d is found!\n", number);
			break;
		case 7:
			printf("Exit.\n");
			break;
		default:
			printf("Invalid input.\n");
			break;
		}while (option != 7);
}return EXIT_SUCCESS;

Position InsertNew(Position P, Position Q)
{
	if (P == NULL)
		return Q;
	else if (P->data > Q->data)
		P->right = InsertNew(P->right, Q);
	else
		P->left = InsertNew(P->left, Q);
	return P;
}

Position MakeNew(Position P, int x)
{
	P = (Position)malloc(sizeof(Node));
	if (P == NULL)
	{
		printf("Failed in dynamic allocation!");
		return NULL;
	}
	P->data = x;
	P->left = NULL;
	P->right = NULL;
	return P;
}

int PrintInorder(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	PrintInorder(P->left);
	printf("%d\t", P->data);	
	PrintInorder(P->right);
	return EXIT_SUCCESS;
}

int PrintPreorder(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	printf("%d", P->data);
	PrintPreorder(P->left);
	PrintPreorder(P->right);
	return EXIT_SUCCESS;
}

int PrintPostorder(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	PrintPostorder(P->left);
	PrintPostorder(P->right);
	printf("%d", P->data);
	return EXIT_SUCCESS;
}

int PrintLevelorder(Position P)
{
	int h = height(P);
	int i = 0;
	for (i = 1; i <= h; i++)
		printCurrentLevel(root, i);
}

int printCurrentLevel(Position P, int level)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	if (level == 1)
		printf("%d ", P->data);
	else if (level > 1) {
		printCurrentLevel(P->left, level - 1);
		printCurrentLevel(P->right, level - 1);
	}
	return EXIT_SUCCESS;
}

int Height(Position P)
{
	int right = 0, left = 0;
	if (P == NULL)
		return EXIT_SUCCESS;
	else {
		left = Height(P->left);
		right = Height(P->right);

		if (left > right)
			return (left + 1);
		else
			return (right + 1);
	}
}
Position DeleteElement(Position P, int data)
{
	if (P == NULL)
		return NULL;
	if (P->data < data)
		P->right = DeleteElement(P->right, data);
	else if (P->data > data)
		P->left = DeleteElement(P->left, data);
	else
	{
		if (P->left)
		{
			Position tmp = FindMax(P->left);
			P->data = tmp->data;
			P->left = DeleteElement(P->left, tmp->data);
		}
		else if (P->right)
		{
			Position tmp = FindMin(P->right);
			P->data = tmp->data;
			P->right = DeleteElement(P->right, tmp->data);
		}
		else
		{
			free(P);
			return NULL;
		}
	}

	return P;
}

Position FindElement(Position P, int data)
{
	if (P == NULL)
	{
		printf("Error!");
		return NULL;
	}
	if (P->data == data)
		return P;

	else if (P->data > data)
	{
		P->left = FindElement(P->left, data);
		return P;
	}
	else
	{
		P->right = FindElement(P->right, data);
		return P;
	}
}

Position FindMax(Position P)
{
	if (P == NULL)
	{
		printf("Error!");
		return NULL;
	}
	while (P->left != NULL)
		P = P->left;

	return P;
}

Position FindMin(Position P)
{
	if (P == NULL)
	{
		printf("Error!");
		return NULL;
	}
	while (P->right != NULL)
		P = P->right;
	
	return P;
}