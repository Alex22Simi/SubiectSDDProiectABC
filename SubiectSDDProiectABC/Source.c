#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Proiect
{
	unsigned int id;
	char* titlu;
	char* contractant;
	unsigned char durataImplementare;
	float buget;
	float stadiu;
}Proiect;

typedef struct Nod
{
	Proiect* info;
	struct Nod* left;
	struct Nod* right;
}Nod;

Proiect* initializareProiect(unsigned int id, char* titlu, char* contractant, unsigned char durataImplementare,
float buget, float stadiu)
{
	Proiect* proiect = (Proiect*)malloc(sizeof(Proiect));
	proiect->id = id;
	proiect->titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(proiect->titlu, titlu);
	proiect->contractant = (char*)malloc(sizeof(char) * (strlen(contractant) + 1));
	strcpy(proiect->contractant, contractant);
	proiect->durataImplementare = durataImplementare;
	proiect->buget = buget;
	proiect->stadiu = stadiu;
	return proiect;
}
Nod* initializareNod(Proiect* proiect)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = proiect;
	nodNou->left = NULL;
	nodNou->right = NULL;
	return nodNou;
}
Nod* inserareProiect(Nod* radacina, Proiect* proiect)
{
	if (radacina == NULL)
	{
		return initializareNod(proiect);
	}
	else if (radacina->info->id > proiect->id)
	{
		radacina->left = inserareProiect(radacina->left, proiect);
	}
	else if (radacina->info->id < proiect->id)
	{
		radacina->right = inserareProiect(radacina->right, proiect);
	}
	return radacina;
}
void afisareInOrdine(Nod* radacina)
{
	if (radacina != NULL)
	{
		afisareInOrdine(radacina->left);
		printf("%hu %s %s %hhu %5.2f %5.2f\n", radacina->info->id, radacina->info->titlu,
			radacina->info->contractant, radacina->info->durataImplementare, radacina->info->buget,
			radacina->info->stadiu);

		afisareInOrdine(radacina->right);
	}
}
void dezalocare(Nod* radacina)
{
	if (radacina != NULL)
	{
		dezalocare(radacina->left);
		dezalocare(radacina->right);
		free(radacina->info->titlu);
		free(radacina->info->contractant);
		free(radacina->info);
		free(radacina);
	}
}
//det nr de proiecte avand acelasi contractant->numele. dneumirea contractantului este data cca param
int nrProiect(Nod* radacina, char* contractant)
{
	int nr = 0;
	if (radacina != NULL)
	{
		if (strcmp(radacina->info->contractant, contractant) == 0)
		{
			nr++;
		}
		nr += nrProiect(radacina->left, contractant);
		nr += nrProiect(radacina->right, contractant);
	}
	return nr;
}
//modifica stadiul unui proiect dat prin id in param, noua val este data tot in param
void modifica(Nod* radacina, unsigned int id, float stadiuNou)
{
	if (radacina != NULL)
	{
		if (radacina->info->id = id)
		{
			radacina->info->stadiu = stadiuNou;
		}
		else if (radacina->info->id < id)
		{
			return modifica(radacina->right, id, stadiuNou);
		}
		else if (radacina->info->id < id)
		{
			return modifica(radacina->left, id, stadiuNou);
		}

	}
}
//stergere nodurile frunza 
//void stergere(Nod* radacina)
//{
//	if (radacina != NULL)
//	{
//		if (radacina->left == NULL && radacina->right == NULL)
//		{
//			free(radacina->info->titlu);
//			free(radacina->info->contractant);
//			//free(radacina->info);
//			free(radacina);
//			radacina = NULL;
//		}
//		else
//		{
//			stergere(radacina->right);
//			stergere(radacina -> left);
//		}
//	}
//	else
//	{
//		return;
//	}
//}
void sterge_frunza(Nod** radacina) {
	//daca radacina nu are niciun fiu
	if (*radacina != NULL) {
		if ((*radacina)->right == NULL && (*radacina)->left == NULL) {
			free((*radacina)->info->titlu);
			free((*radacina)->info->contractant);
			free((*radacina));
			(*radacina) = NULL;
		}
		else {
			sterge_frunza(&((*radacina)->right));
			sterge_frunza(&((*radacina)->left));

		}
	}
	else {
		return;
	}
}



void main()
{
	FILE* f = fopen("Proiect.txt", "r");
	if (f != NULL)
	{
		char bufferline[100], split_line[] = ",\n";
		Nod* radacina = NULL;

		while (fgets(bufferline, sizeof(bufferline), f))
		{
			char* token = strtok(bufferline, split_line);
			unsigned int id = (unsigned int)atoi(token);

			 token = strtok(NULL, split_line);
			char* titlu = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(titlu, token);

			 token = strtok(NULL, split_line);
			char* contractant = (char*)malloc(sizeof(char)* (strlen(token) + 1));
			strcpy(contractant, token);

			 token = strtok(NULL, split_line);
			unsigned char durataImplementare = (unsigned char)atoi(token);

			 token = strtok(NULL, split_line);
			float buget = (float)atof(token);

			 token = strtok(NULL, split_line);
			float stadiu = (float)atof(token);


			Proiect* proiect = initializareProiect(id, titlu, contractant, durataImplementare,
				buget, stadiu);
			radacina = inserareProiect(radacina, proiect);

		}
		fclose(f);
		afisareInOrdine(radacina);

		printf("Cerinat 2: \n");
		int numar = 0;
		numar = nrProiect(radacina, "abb");
		printf("%d", numar);
		printf("\n\n\n");

		printf("Cerinta 3: \n");
		modifica(radacina, 1, 50);
		afisareInOrdine(radacina);

		printf("Cerinta 4: \n");
		sterge_frunza(&radacina);
		afisareInOrdine(radacina);

		dezalocare(radacina);
	}
}