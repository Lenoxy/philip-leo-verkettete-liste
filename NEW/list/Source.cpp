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
void SortList();
void PrintList(struGrafikkarte **pList, int Amount);
void PrintSingleItem(struGrafikkarte* pPrint);
void QuitApplication();
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

		printf("%i \n", i);

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
	
		pEnd = pNewElement;
	}

	return pStart;
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

int GenerateRandomYear()
{
	int value = 1900 + rand() % 118;
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

void SortList() {

}

void PrintList(struGrafikkarte **pList, int Amount) {
	int counter = 0;
	int index;

	printf("Hallo");

	if (Amount == 0) 
	{
		index = -1;
	}
	else
	{
		index = Amount;
	}

	struGrafikkarte* pOutput = *pList;
	while (pOutput != NULL && counter != index)
	{
		PrintSingleItem(pOutput);
		pOutput = pOutput->pNext;
		counter++;
	}
}

void PrintSingleItem(struGrafikkarte *pPrint) {
	printf("Name: %s, Hersteller: %s, Herstellungsjahr: %i \n", pPrint->name, pPrint->hersteller, pPrint->herstellungsjahr);
}

void QuitApplication() {
	exit(1);
}



/*
*Autor: Leo Scherer
*Prints the Main Menu and lets the User select a Function
*@Param
*@Return
*/

void main()
{
	
	char selection;
	struGrafikkarte* pStart = NULL;
	int Amount = 0;
	while (true) 
	{
		printf("\n\n--------------------\n");
		printf("--- Hauptmenu ---\n");
		printf("[a] Liste erstellen\n");
		printf("[s] Liste sortieren\n");
		printf("[l] Liste l\x94schen\n");
		printf("[e] Element l\x94schen\n");
		printf("[p] Liste ausgeben\n");
		printf("[v] Programm verlassen\n");
		printf("--------------------\n");

		scanf_s("%c", &selection);
		switch (selection) {
		case 'a':
			printf("Wie viele Items soll die Liste beinhaten?	");
			scanf_s("%i", &Amount);
			printf("Hallo");
			pStart = CreateList(Amount);
			break;
		case 's':
			SortList();
			break;
		case 'l':
			DeleteList(&pStart);
			break;
		case 'e':
			DeleteElement(NULL, NULL, NULL);
			break;
		case 'p':
			printf("%i", Amount);
			PrintList(&pStart, Amount);
			break;
		case 'v':
			QuitApplication();
			break;
		}
	}
}
