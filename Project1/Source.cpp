#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
	anuala,bianuala,perena
}Tip_planta;
typedef enum
{
	primavara,vara,toamna
}Perioada_infl;

typedef struct nod
{
	char nume[30];
	Tip_planta tip;
	Perioada_infl per;
	float pret;
	struct nod *st, *dr;
}nod;
nod *rad = NULL;
float suma;
nod *adaugare(nod *t, char *nume, Tip_planta tip, Perioada_infl per, float pret)
{
	if (t == NULL)
	{
		t = (nod*)malloc(sizeof(nod));
		strcpy(t->nume, nume);
		t->tip = tip;
		t->per = per;
		t->pret = pret;
		t->dr = NULL;
		t->st = NULL;
	}
	else
	{
		if (strcmp(t->nume, nume) < 0)
			t->dr = adaugare(t->dr, nume, tip, per, pret);
		if (strcmp(t->nume, nume) > 0)
			t->st = adaugare(t->st, nume, tip, per, pret);
	}
	return t;
}
void citire()
{
	FILE *f;
	f = fopen("plante.txt", "r");
	char nume[30];
	float pret;
	Tip_planta tip;
	Perioada_infl per;
	while (!feof(f))
	{
		fscanf(f, "%s %d %f %d", nume, &tip, &pret, &per);
		rad = adaugare(rad, nume, tip, per, pret);
	}
}
void afisare(nod *t)
{
	if (t != NULL)
	{
		afisare(t->dr);
		printf("Nume:%s\nTip:%d\nPret:%f\nPer:%d\n-------------\n", t->nume, t->tip, t->pret, t->per);
		afisare(t->st);
	}
}
nod *twoson(nod *p, nod *t)
{
	nod *q,*aux;
	q = p;
	if (q->dr != NULL)
		q->dr = twoson(q->dr, t);
	else
	{
		strcpy(t->nume, q->nume);
		t->tip = q->tip;
		t->pret = q->pret;
		t->per = q->per;
		aux = q;
		q = q->st;
		free(aux);
	}
	return q;
}
nod *stergere(nod *t, char *nume)
{
	nod *aux;
	if (t == NULL)
		printf("nu exista nod");
	else

		if (strcmp(t->nume, nume) < 0)
			t->dr = stergere(t->dr, nume);
		else
			if (strcmp(t->nume, nume) > 0)
				t->st = stergere(t->st, nume);
			else
				if (t->st == NULL)
				{
					aux = t;
					t = t->dr;
					free(aux);
					return t;
				}
				else
					if (t->dr == NULL)
					{
						aux = t;
						t = t->st;
						free(aux);
						return t;
					}
					else
						t->st = twoson(t->st, t);
	return t;
					

	
}
void cauta(nod *t,char *nume)
{
	FILE *f;
	f = fopen("fact.txt", "a");
	if (t != NULL)
	{
		cauta(t->st, nume);
		if (strcmp(t->nume, nume) == 0)
		{
			fprintf(f, "%s %d %f %d\n", t->nume, t->tip, t->pret, t->per);
			suma = suma + t->pret;
		}
		cauta(t->dr, nume);
	}
	fclose(f);

}
void cautare()
{
	FILE *f;
	f = fopen("fact.txt", "a");
	char nume[30];
	while (scanf("%s", nume) && strcmp(nume, "gata") != 0)
	{
		cauta(rad, nume);
	}
	fprintf(f, "\n%f", suma);
}
int main()
{
	int opt;
	do
	{
		printf("\nOptiune:");
		scanf("%d", &opt);
		switch (opt) {
		case 1: {
			citire();
			break;
		}
		case 2: {
			afisare(rad);
			break;
		}
		case 3: {
			char nume[30];
			scanf("%s", nume);
			rad = stergere(rad, nume);
			break;
		}
		case 4: {
			cautare();
			break;
		}
		case 5: {exit(0); break; }
		default: {break; }
		}
	} while (opt != 5);
	return 0;
}