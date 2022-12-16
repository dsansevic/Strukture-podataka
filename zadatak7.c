/* zadatak7.cpp :Napisati program koji pomoæu vezanih listi(stabala) predstavlja
strukturu direktorija. Omoguæiti unos novih direktorija i pod - direktorija,
ispis sadržaja direktorija i povratak u prethodni direktorij.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define MAX_LINE 256
#define FILE_ERROR -1
#define EXIT_SUCCESS 0

typedef struct Directory* Position;
typedef struct Stack* StackPosition;
typedef struct Directory {
    char Name[MAX];
    Position child;
    Position sibling;
} directory;

typedef struct Stack {
    Position dir;
    StackPosition Next;
} stack;

int PrintDirectory(Position);
int DeleteAll(Position);
Position ReturnToPrevious(StackPosition);
int MakeDirectory(Position, char*);
int InsertSort(Position, Position);
int Push(Position, StackPosition);
Position Pop(StackPosition);
int InsertAfter(StackPosition, StackPosition);
Position FindDirectory(Position, char*);

int main() {
    directory Root, Current;
    Root.child = 0;
    Root.sibling = 0;

    char command[MAX] = { 0 }, directoryName[MAX] = { 0 };

    do {
        scanf(" %s %s", command, directoryName);

        if (strcmp(command, "md") == 0)
            MakeDirectory(&Root, directoryName);

        else if (strcmp(command, "dir") == 0)
            PrintDirectory(&Root);

        //else if (strcmp(command, "cd") == 0)
         // FindDirectory(&Root, directoryName);

        else if (strcmp(command, "cd dir") == 0);
    }while (strcmp(command, "exit") != 0);

        return 0;
}

int MakeDirectory(Position current, char* name) {
    Position NewDirectory;
    NewDirectory = (Position)malloc(sizeof(directory));

    if (NewDirectory == NULL) {
        printf("Memory allocation error!\n");
        return FILE_ERROR;
    }

    strcpy(NewDirectory->Name, name);
    NewDirectory->child = NULL;
    NewDirectory->sibling = NULL;

    if (current->child == NULL) {
        current->child = NewDirectory;
        return EXIT_SUCCESS;
    }
    else {
        if (strcmp(current->child->Name, name) > 0) {
            NewDirectory->child = current->child;
            current->child = NewDirectory;
        }
        else
            current = current->child;
        while (strcmp(current->sibling->Name, name) < 0)
            current = current->sibling;
        NewDirectory->sibling = current->sibling;
        current->sibling = NewDirectory;
    }

    return EXIT_SUCCESS;
}

int PrintDirectory(Position current) {
    if (current->child == NULL) {
        printf("This directory is empty!\n");
        return EXIT_SUCCESS;
    }

    printf("Directory of C:\\users\%s\n\n", current->Name);
    current = current->child;

    printf("%s\n", current->Name);
    while (current->sibling != NULL) {
        printf("%s\n", current->sibling->Name);
        current = current->sibling;
    }

    return EXIT_SUCCESS;
}

int Push(Position current, StackPosition s_head) {
    StackPosition NewEl = NULL;
    ;
    StackPosition tmp = s_head;
    NewEl = (StackPosition)malloc(sizeof(stack));
    if (NewEl == NULL) {
        printf("Allocation error!");
        return FILE_ERROR;
    }
    NewEl->dir = current;
    NewEl->Next = tmp->Next;
    tmp->Next = NewEl;

    return EXIT_SUCCESS;
}

Position Pop(StackPosition head) {
    if (head->Next == NULL) {
        printf("The stack is empty!");
        return NULL;
    }

    StackPosition temp = head->Next;
    Position ReturnedElement = head->Next->dir;
    head->Next = temp->Next;
    free(temp);
    return ReturnedElement;
}

int InsertAfter(StackPosition P, StackPosition Q) {
    Q->Next = P->Next;
    P->Next = Q;
    return EXIT_SUCCESS;
}

int DeleteAll(Position P) {
    if (P == NULL)
        return EXIT_SUCCESS;

    DeleteAll(P->child);
    DeleteAll(P->sibling);
    free(P);
    return EXIT_SUCCESS;
}

Position ReturnToPrevious(StackPosition s) { return Pop(s); }

Position FindDirectory(Position current, char* name) {
    current = current->child;
    if (strcmp(current->Name, name) == 0)
        return current;

    while (current != NULL && strcmp(current->Name, name) != 0)
        current = current->sibling;

    return current;
}