#include "stdlib.h"
#include "stdio.h"

// Typedefinition
typedef struct Grafikkarte
{
	char name[40];
	char hersteller[40];
	int herstellungsjahr;
	struct Grafikkarte *pNext;
	struct Grafikkarte *pPrev;
} struGrafikkarte;

// Function declaration
struGrafikkarte *CreateList(int Amount);
void DeleteList(struGrafikkarte **pList);
void DeleteElement(struGrafikkarte **pList, char name, char hersteller);
//void SortList();
//void PrintList(struGrafikkarte** pList, int Amount);
//void QuitApplication();
void PrintUserInterface();
char GenerateRandomChar();
int GenerateRandomYear();

/*
*Autor: Philip Baumann
*Creates a list with a defined amount of elements
*@Param Amount of Element that will be created
*@Return pStart
*/

struGrafikkarte *CreateList(int Amount)
{
	struGrafikkarte *pStart = NULL;
	struGrafikkarte *pEnd = NULL;

	for (int i = 0; i < Amount; i++)
	{
		char Name = GenerateRandomChar();
		char Hersteller = GenerateRandomChar();
		int Herstellungsjahr = GenerateRandomYear();

		struGrafikkarte *pNewElement = (struGrafikkarte *)malloc(sizeof(struGrafikkarte));

		pNewElement->name[0] = Name;
		pNewElement->name[1] = '\0';
		pNewElement->hersteller[0] = Hersteller;
		pNewElement->hersteller[1] = '\0';
		pNewElement->herstellungsjahr = Herstellungsjahr;
		pNewElement->pNext = NULL;

		if (pStart == NULL)
		{
			pStart = pNewElement;
		}

		if (pEnd != NULL)
		{
			pEnd->pNext = pNewElement;
		}
		return pStart;
	}
}

/*
*Autor: Philip Baumann
*Generates a random letter in the alaphabet
*@Param
*@Return random letter 
*/

char GenerateRandomChar()
{
	char value = 'A';
	value = value + rand() % 25;
	return value;
}

/*
*Autor: Philip Baumann
*Generates a Random Year
*@Param
*@Return random year as an integer
*/

char GenerateRandomYear()
{
	int value = 1900;
	value + rand() % 118;
	return value;
}

/*
*Autor: Philip Baumann
*Deletes a whole List and frees it from the memory
*@Param pointer to the List
*@Return
*/

void DeleteList(struGrafikkarte **pList)
{
	struGrafikkarte *pCurrent = *pList;
	struGrafikkarte *pNext = NULL;

	while (pCurrent != NULL)
	{
		pNext = pCurrent->pNext;
		free(pCurrent);
		pCurrent = pNext;
	}
	*pList = NULL;
}

void DeleteElement(struGrafikkarte **pList, char Name, char hersteller)
{
	struGrafikkarte *pCurrent = *pList;
	struGrafikkarte *pPrevious = NULL;

	while (pCurrent != NULL)
	{
		// if ()
		// TODO @Philip
	}
}


/*
*Autor: Leo Scherer
*Prints the Main Menu
*@Param
*@Return
*/

void PrintUserInterface()
{
	printf("\n----------\n");
	printf("Main Menu\n");
	printf("Liste erstellen [a]\n");
	printf("Liste l\94schen [l]\n");
	printf("Element l\94chen [e]\n");
	printf("Liste sortieren [s]\n");
	printf("Liste ausgeben [p]\n");
	printf("Programm verlassen [e]\n");
    printf("----------\n");
}

void main()
{
	PrintUserInterface();
}
