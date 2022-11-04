#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAX 50
#define MAX_LINE 1024
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


int Menu();
int BrisiSve(Pozicija);
int IspisListe(Pozicija);
int UnosNaKraj(Pozicija);
int UnosPodataka(Pozicija);
int UnosNaPocetak(Pozicija);
int SortiraniUnos(Pozicija);
int UnosIza(Pozicija, char*);
int UnosIspred(Pozicija, char*);
int BrisiElement(char*, Pozicija);
int UpisUDatoteku(Pozicija, char*);
int CitanjeIzDatoteke(Pozicija, char*);
int PostaviPokazivace(Pozicija, Pozicija);

Pozicija PronadiElement(char*, Pozicija);
Pozicija TraziPrethodnog(char*, Pozicija);

int main()
{
	int a = 0, i = 0;
	char izbor = ' ';
	char prez[MAX] = { 0 };
	char file[MAX_LINE] = { 0 };
	char file2[MAX_LINE] = { 0 };
	
	Pozicija Head = NULL;
	Head = (Pozicija)malloc(sizeof(osoba));
	Head->Next = NULL;

	printf("\n\t\t**VEZANA LISTA**\n\t\tOdaberite opciju:\n");
	do
	{
		Menu();
		scanf(" %c", &izbor);
		izbor = toupper(izbor);

		switch (izbor)
		{
		case 'A':
			printf("Koliko korisnika unosite?\n");
			scanf("%d", &a);
			for (i = 0; i < a; i++)
				UnosNaPocetak(Head);
			break;
		case 'B':
			printf("Koliko korisnika unosite?\n");
			scanf("%d", &a);
			for (i = 0; i < a; i++)
				UnosNaKraj(Head);
			break;
		case 'C':
			IspisListe(Head->Next);
			break;
		case 'D':
			printf("Prezime trazene osobe:\n");
			scanf(" %s", prez);
			PronadiElement(prez, Head->Next);
			if (PronadiElement(prez, Head->Next) != NULL)
				printf("Korisnik uspjesno pronaden!\n");
			break;
		case 'E':
			printf("Prezime osobe koju zelite izbrisati:\n");
			scanf(" %s", prez);
			BrisiElement(prez, Head);
			IspisListe(Head->Next);
			break;
		case 'F':
			printf("Prezime osobe nakon koje unosite:\n");
			scanf(" %s", prez);
			UnosIza(Head->Next, prez);
			IspisListe(Head->Next);
			break;
		case 'G':
			printf("Prezime osobe ispred koje unosite:\n");
			scanf(" %s", prez);
			UnosIspred(Head, prez);
			IspisListe(Head->Next);
			break;
		case 'H':
			SortiraniUnos(Head);
			IspisListe(Head->Next);
			break;
		case 'I':
			printf("Unesite ime datoteke:\n");
			scanf(" %s", file);
			UpisUDatoteku(Head->Next, file);
			IspisListe(Head->Next);
			break;
		case 'J':
			printf("Unesite ime datoteke:\n");
			scanf(" %s", file2);
			printf("\n");
			CitanjeIzDatoteke(Head->Next, file2);
			break;
				
		 case 'K':
			printf("Kraj programa. Dovidenja!");
			break;

		default:
			printf("Krivi unos slova\n");
			break;
		}
	}while (izbor != 'K');

	if (izbor == 'K')
	BrisiSve(Head);

	return EXIT_SUCCESS;
}

int PostaviPokazivace(Pozicija P, Pozicija Q)
{
	Q->Next = P->Next;
	P->Next = Q;
	
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
	PostaviPokazivace(P, Q);

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

	PostaviPokazivace(P, Q);
	return EXIT_SUCCESS;
}

Pozicija PronadiElement(char* x, Pozicija P)
{
	if (P == NULL)
	{
		printf("Element ne postoji");
		return NULL;
	}

	while (P != NULL && strcmp(P->prezime, x))
		P = P->Next;

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
	Pozicija Pret = NULL, temp = NULL;
	Pret = TraziPrethodnog(x, P);

	if (Pret == NULL)
	{
		printf("Nema prethodnika!\n");
		return FILE_ERROR;
	}

	temp = Pret->Next;
	Pret->Next = temp->Next;
	free(temp);

	return EXIT_SUCCESS;
}

int UnosIspred(Pozicija P, char* prez)
{
	Pozicija Pret = NULL;
	Pret = TraziPrethodnog(prez, P);

	if (Pret == NULL)
		return FILE_ERROR;
	
	UnosNaPocetak(Pret);

	return EXIT_SUCCESS;
}

int UnosIza(Pozicija P, char* prez)
{
	Pozicija X = NULL;
	X = PronadiElement(prez, P);

	if (X == NULL)
	{
		printf("Neuspjesna pretraga\n");
		return FILE_ERROR;
	}
	UnosNaPocetak(X);

	return EXIT_SUCCESS;
}

int UpisUDatoteku(Pozicija P, char* file)
{
	FILE* fp = NULL;
	fp = fopen(file, "w");
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return FILE_ERROR;
	}
	while (P != NULL)
	{
		fprintf(fp, "Student: %-20s %-20s, godina: %4d\n", P->ime, P->prezime, P->godina);
		P = P->Next;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int CitanjeIzDatoteke(Pozicija P, char* file)
{
	FILE* fp = NULL;
	fp = fopen(file, "r");
	char buff[MAX_LINE] = { 0 };
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return FILE_ERROR;
	}
	
	while (fgets(buff, MAX_LINE, fp) != NULL)
		puts(buff);

	fclose(fp);
	return EXIT_SUCCESS;
}


int SortiraniUnos(Pozicija P)
{
	Pozicija j = NULL, prev_j = NULL, temp = NULL, end = NULL;
	while (P->Next != end)
	{
		prev_j = P;
		j = P->Next;
		while (j->Next != end)
		{
			if (strcmp(j->prezime, j->Next->prezime) > 0) //prvi veci od drugoga po ASCII
			{
				temp = j->Next;
				prev_j->Next = temp;
				j->Next = temp->Next;
				temp->Next = j;

				j = temp;
			}

			prev_j = j;
			j = j->Next;
		}
		end = j;
	}

	return EXIT_SUCCESS;
}

int BrisiSve(Pozicija P)
{
	Pozicija temp = NULL;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int Menu()
{
	printf("\t-----------------------------------");
	printf("\n\tA  UNOS NA POCETAK\t\n");
	printf("\tB  UNOS NA KRAJ\t\n");
	printf("\tC  ISPIS LISTE\t\n");
	printf("\tD  TRAZENJE ELEMENTA\t\n");
	printf("\tE  BRISANJE ELEMENTA\t\n");
	printf("\tF  DODAVANJE NOVOG ELEMENTA IZA\t\n");
	printf("\tG  DODAVANJE NOVOG ELEMENTA ISPRED\t\n");
	printf("\tH  SORTIRANJE\t\n");
	printf("\tI  UPIS U DATOTEKU\t\n");
	printf("\tJ  CITANJE IZ DATOTEKE\t\n");
	printf("\tK  KRAJ\t\n");
	printf("\t-----------------------------------\n\n");

	return EXIT_SUCCESS;
}
