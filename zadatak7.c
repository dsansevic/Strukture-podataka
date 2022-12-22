/* zadatak7.cpp :Napisati program koji pomoću vezanih listi(stabala) predstavlja
strukturu direktorija. Omogućiti unos novih direktorija i pod - direktorija,
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

int Menu(Position, Position, Position, StackPosition);
int PrintDirectory(Position);
int DeleteAll(Position);
int InsertSort(Position, Position);
int Push(Position, StackPosition);
int InsertAfter(StackPosition, StackPosition);
Position Pop(StackPosition);
Position FindDirectory(Position, char*, StackPosition);
Position MakeDirectory(Position, char*);
Position ReturnToPrevious(StackPosition);

int main() {
    directory Root, Current, prev;
    Root.child = NULL;
    Root.sibling = NULL;
    Current.child = NULL;
    Current.sibling = NULL;
    prev.child = NULL;
    prev.sibling = NULL;
    stack head;
    head.Next = NULL;
    Position p_Root = &Root;

    Menu(p_Root, &Current, &prev, &head);
    return EXIT_SUCCESS;
}

int Menu(Position Root, Position curr, Position previous, StackPosition st)
{
    char command[MAX] = { 0 }, directoryName[MAX] = { 0 };
    

    printf("Insert command:\n");
    do {

        scanf(" %s %s", command, directoryName);

        if (strcmp(command, "md") == 0)
        {
            Root = MakeDirectory(Root, directoryName);
            printf("Directory %s has been made!\n", directoryName);
        }

        else if (strcmp(command, "dir") == 0)
            PrintDirectory(Root);

        else if (strcmp(command, "cd") == 0)
        {
            curr = FindDirectory(Root, directoryName, st);
            printf("You are now in %s directory\n", directoryName);

        }
        else if (strcmp(command, "cd dir") == 0)
            previous = ReturnToPrevious(st);

        else {
            printf("%s : The term '%s' is not recognized as the name of a cmdlet, function, script file, or operable program.", directoryName, directoryName);
            printf("Check the spelling of the name, or if a path was included, verify that the path is correct and try again.\n");
        }
    } while (strcmp(command, "exit") != 0);

    DeleteAll(Root);
    return EXIT_SUCCESS;
}

Position MakeDirectory(Position current, char* name) {
    Position NewDirectory;
    NewDirectory = (Position)malloc(sizeof(directory));

    if (NewDirectory == NULL) {
        printf("Memory allocation error!\n");
        return NULL;
    }

    strcpy(NewDirectory->Name, name);
    NewDirectory->child = NULL;
    NewDirectory->sibling = NULL;

    if (current->child == NULL) {
        current->child = NewDirectory;
        return NewDirectory;
    }
    else {
        if (strcmp(current->child->Name, name) > 0) {
            NewDirectory->child = current->child;
            current->child = NewDirectory;
        }
        else
        {
            current = current->child;
            while (strcmp(current->sibling->Name, name) < 0)
                current = current->sibling;
            NewDirectory->sibling = current->sibling;
            current->sibling = NewDirectory;
        }
    }

    return NewDirectory;
}

int PrintDirectory(Position current) {
    if (current->child == NULL) {
        printf("This directory is empty!\n");
        return EXIT_SUCCESS;
    }
    current = current->child;
    printf("Directory of C:\\users %s\n\n", current->Name);
    //printf("Directory of C: users %s\n", current->Name);
    

    printf("%s\n", current->Name);
    while (current->sibling != NULL) {
        //dodaj Mode                 LastWriteTime         Length Name
        printf("%s\n", current->sibling->Name);
        current = current->sibling;
    }

    return EXIT_SUCCESS;
}

int Push(Position current, StackPosition s_head) {
    StackPosition NewEl = NULL;

    NewEl = (StackPosition)malloc(sizeof(stack));
    if (NewEl == NULL) {
        printf("Allocation error!");
        return FILE_ERROR;
    }
    NewEl->dir = current;
    NewEl->Next = s_head->Next;
    s_head->Next = NewEl;

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

Position FindDirectory(Position current, char* name, StackPosition P) {
    current = current->child;
    if (strcmp(current->Name, name) == 0)
        return current;

    while (current != NULL && strcmp(current->Name, name) != 0)
        current = current->sibling;

    if (current == NULL || strcmp(current->Name, name) != 0)
    {
        printf("Directory not found!\n");
        return current;
    }

    else Push(current, P);

    return current;
}
