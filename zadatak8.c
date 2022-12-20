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

Position InsertNew(Position, int);
Position MakeNew(Position, int);
int PrintInorder(Position);
int PrintPreorder(Position);
int PrintPostorder(Position);
int PrintLevelorder(Position);
Position DeleteElement(Position, int);
Position FindElement(Position, int);
Position FindMax(Position);
Position FindMin(Position);

int main()
{
	struct node root;
	root.data = 0;
	root.left = NULL;
	root.right = NULL;
	Position tmp;
	int x = 0, i = 0;
	tmp = (Position)malloc(sizeof(node));
	for (i = 0; i < 6; i++)
	{
		scanf("%d", &x);
		tmp = InsertNew(&root, x);
	}
	PrintInorder(&root);
	return EXIT_SUCCESS;
}

Position InsertNew(Position P, int x)
{
	if (P == NULL)
		P = MakeNew(P, x);
	else if (P->data > x)
		P->right = InsertNew(P->right, x);
	else
		P->left = InsertNew(P->left, x);
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