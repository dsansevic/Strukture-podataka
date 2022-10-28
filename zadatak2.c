#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define FILE_ERROR -1
#define EXIT_SUCCESS 0

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba
{
	char ime[MAX];
	char prezime[MAX];
	int godina;
	Pozicija Next;
}osoba;

int UnosPodataka(Pozicija);
int UnosNaPocetak(Pozicija);
int UnosNaKraj(Pozicija);
int IspisListe(Pozicija);
int BrisiElement(char*, Pozicija);
Pozicija PronadiElement(char*, Pozicija);
Pozicija TraziPrethodnog(char*, Pozicija);


int main()
{
	int a = 0, b = 0, c = 0, i = 0;
	char prez[MAX] = { 0 };
	Pozicija Head = NULL;
	
	Head = (Pozicija)malloc(sizeof(osoba));
	Head->Next = NULL;

	printf("UNOS OCJENA\n");
	printf("Za unos na pocetak liste upisite 1\nZa unos na kraj liste upisite 2\n");
	scanf("%d", &a);
	if (a == 1)
	{
		printf("Odabrali ste unos na pocetak liste. Mozete poceti s unosom podataka\n");
		UnosNaPocetak(Head);

		printf("Zelite li unijeti jos jednu osobu na pocetak liste? \nUkoliko zelite unesite 1.\n");
		scanf("%d", &b);
		if (b == 1)
		{
			printf("Koliko osoba zelite unijeti?\n");
			scanf("%d", &c);
			for (i = 0; i < c; i++)
				UnosNaPocetak(Head);
		}
	}

	else if (a == 2)
	{
		printf("Odabrali ste unos na kraj liste. Mozete poceti s unosom podataka\n");
		UnosNaKraj(Head);

		printf("Zelite li unijeti jos jednu osobu na kraj liste? \nUkoliko zelite unesite 1.\n");
		scanf("%d", &b);
		if (b == 1)
		{
			printf("Koliko osoba zelite unijeti?\n");
			scanf("%d", &c);
			for (i = 0; i < c; i++)
				UnosNaKraj(Head);
		}
	}
	else
		printf("Krivi unos");
	
	printf("\nVasa lista:\n");
	IspisListe(Head->Next);

	printf("\nZelite li obrisati korisnike?\nAko zelite, upisite 1\n");
	scanf("%d", &a);
	if (a == 1)
	{
		printf("Koliko korisnika zelite izbrisati?\n");
		scanf("%d", &b);

		for (i = 0; i < b; i++)
		{

			printf("Unesite prezime korisnika:\n");
			scanf(" %s", prez);
			BrisiElement(prez, Head);
			
		}
		printf("\nVasa nova lista:\n");
		IspisListe(Head->Next);
	}

	printf("\nZelite li naci odredenog korisnika?\nAko zelite, upisite 1.\n");
	scanf("%d", &a);
	if (a == 1)
	{
		printf("Upisite prezime korisnika kojeg zelite pronaci\n");
		scanf(" %s", prez);
		PronadiElement(prez, Head);
	}


	return EXIT_SUCCESS;
}


int UnosNaPocetak(Pozicija P)
{
	Pozicija Q = NULL;
	Q = (Pozicija)malloc(sizeof(osoba));
	
	if (Q == NULL)
	{
		printf("Greska u alociranju!");
		return FILE_ERROR;
	}
	UnosPodataka(Q);

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int UnosNaKraj(Pozicija P)
{
	Pozicija Q = NULL;
	Q = (Pozicija)malloc(sizeof(osoba));
	
	if (Q == NULL)
	{
		printf("Greska u alociranju memorije!");
		return FILE_ERROR;
	}
	UnosPodataka(Q);

	while (P->Next != NULL)
		P = P->Next;

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

Pozicija PronadiElement(char* x, Pozicija P)
{
	while (P != NULL && strcmp(P->prezime, x))
		P = P->Next;

	if (P == NULL)
	{
		printf("Element ne postoji");
		return NULL;
	}
	printf("Ime: %s\nPrezime: %s\nGodina: %d\n", P->ime, P->prezime, P->godina);
	return P;
}

int UnosPodataka(Pozicija Q)
{
	printf("Unesite ime korisnika:\n");
	scanf(" %[^\n]", Q->ime);
	printf("Unesite prezime korisnika:\n");
	scanf(" %[^\n]", Q->prezime);
	printf("Unesite godinu rodenja korisnika:\n");
	scanf("%d", &Q->godina);

	return EXIT_SUCCESS;
}


int IspisListe(Pozicija P)
{
	if (P == NULL)
	{
		printf("Lista je prazna!\n");
		return FILE_ERROR;
	}

	while (P != NULL)
	{
		printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d\n", P->ime, P->prezime, P->godina);
		P = P->Next;
	}
	return EXIT_SUCCESS;
}

Pozicija TraziPrethodnog(char* x, Pozicija P)
{
	Pozicija Pret = P;
	P = P->Next;
	
	while (P != NULL && strcmp(P->prezime, x))
	{
		Pret = Pret->Next;
		P = P->Next;
	}

	if (P == NULL)
		return NULL;
	else
		return Pret;
}

int BrisiElement(char* x, Pozicija P)
{
	Pozicija Pret, temp;
	Pret = TraziPrethodnog(x, P);
	
	if (Pret == NULL)
	{
		printf("Nema prethodnika!");
		return FILE_ERROR;
	}

	temp = Pret->Next;
	Pret->Next = temp->Next;
	free(temp);

	return EXIT_SUCCESS;
}
