#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h";

// Typedefinition
typedef struct Grafikkarte
{
	char name[40];
	char hersteller[40];
	int herstellungsjahr;
	struct Grafikkarte* pNext;
	struct Grafikkarte* pPrev;
} struGrafikkarte;

// Function declaration
struGrafikkarte* CreateList(int Amount);
void DeleteList(struGrafikkarte** pList);
void DeleteElement(struGrafikkarte** pList, char name, char hersteller);
void SortList(struGrafikkarte pList, int length);
void PrintList(struGrafikkarte** pList, int Amount);
void PrintSingleItem(struGrafikkarte* pPrint);
void QuitApplication();
char GenerateRandomChar();
int GenerateRandomYear();
void PrintMainMenuToConsole();

/*
*Autor: Philip Baumann
*Creates a list with a defined amount of elements
*@Param Amount of Element that will be created
*@Return pStart
*/

struGrafikkarte* CreateList(int Amount)
{

	struGrafikkarte* pStart = NULL;
	struGrafikkarte* pEnd = NULL;

	for (int i = 0; i < Amount; i++)
	{
		char Name = GenerateRandomChar();
		char Hersteller = GenerateRandomChar();
		int Herstellungsjahr = GenerateRandomYear();

		struGrafikkarte* pNewElement = (struGrafikkarte*)malloc(sizeof(struGrafikkarte));

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

void DeleteList(struGrafikkarte** pList)
{
	struGrafikkarte* pCurrent = *pList;
	struGrafikkarte* pNext = NULL;

	while (pCurrent != NULL)
	{
		pNext = pCurrent->pNext;
		free(pCurrent);
		pCurrent = pNext;
	}
	*pList = NULL;
}

/*
*Autor: Philip Baumann
*Deletes a single element in the list by comparing string and then rearranging pointers
*@Param pointer, char, char
*@Return void
*/

void DeleteElement(struGrafikkarte** pList, char hersteller, char name)
{
	struGrafikkarte* pCurrent = *pList;
	struGrafikkarte* pPrevious = NULL;

	while (pCurrent != NULL)
	{

		if (strncmp(pCurrent->hersteller, &hersteller, 1) == 0 && strncmp(pCurrent->name, &hersteller, 1))
		{
			if (pPrevious == NULL)
			{
				*pList = pCurrent->pNext;
				free(pCurrent);
				pCurrent = *pList;
			}
			else
			{
				pPrevious->pNext = pCurrent->pNext;
				free(pCurrent);
				pCurrent = pPrevious->pNext;
			}
		}
		else
		{
			pPrevious = pCurrent;
			pCurrent = pCurrent->pNext;
		}
	}
}

/*
*Autor: Leo Scherer
*Sorts list by using the bubblesort methodel
*@Param pointer, int
*@Return void
*/

void SortList(struGrafikkarte* pStartOfList, int length) {
	clock_t t;
	t = clock();
	int oCounter, iCounter;
	printf("Length: %i\n", length);
	for (oCounter = 0; oCounter !=length; oCounter++) {
		struGrafikkarte *pIndex = pStartOfList;
		while (pIndex->pNext != nullptr) {
			if ((pIndex->herstellungsjahr) > (pIndex->pNext->herstellungsjahr)) {
				printf("Swapping %i for %i\n", pIndex->herstellungsjahr, pIndex->pNext->herstellungsjahr);
				int temp = pIndex->herstellungsjahr;
				pIndex->herstellungsjahr = pIndex->pNext->herstellungsjahr;
				pIndex->pNext->herstellungsjahr = temp;

			}
			pIndex = pIndex->pNext;
		}
	}

	t = clock() - t;
	double pace = ((double)t) / CLOCKS_PER_SEC;
	printf("Sortierung erfolgte in %f", pace);
}

/*
*Autor: Philip Baumann
*Prints entire list to the console. By iterating through the list which is possible due to the pNext which gets set to the current structure element
*@Param pointer, int
*@Return void
*/

void PrintList(struGrafikkarte** pList, int Amount) {
	int counter = 0;
	int index;

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

/*
*Autor: Philip Baumann
*Prints single element to the console
*@Param pointer
*@Return void
*/

void PrintSingleItem(struGrafikkarte* pPrint) {
	printf("Name: %s, Hersteller: %s, Herstellungsjahr: %i \n", pPrint->name, pPrint->hersteller, pPrint->herstellungsjahr);
}


/*
*Autor: Leo Scherer
*the application and deletes list aswell as freeing the memory
*@Param pointer
*@Return void
*/

void QuitApplication(struGrafikkarte** pList) {
	DeleteList(pList);
	exit(1);
}

/*
*Autor: Leo Scherer
*Prints Mainmenu to the console
*@Param 
*@Return void
*/

void PrintMainMenuToConsole()
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
}



/*
*Autor: Leo Scherer
*Prints the Main Menu and lets the User select a Function
*@Param
*@Return
*/

void main()
{

	char Hersteller;
	char Name;

	char selection;
	struGrafikkarte* pStart = NULL;
	int Amount = 0;
	while (true)
	{
		PrintMainMenuToConsole();
		scanf_s(" %c", &selection);
		switch (selection) {
		case 'a':
			printf("Wie viele Items soll die Liste beinhaten? ");
			scanf_s("%i", &Amount);
			pStart = CreateList(Amount);
			break;
		case 's':
			SortList(pStart, Amount);
			break;
		case 'l':
			DeleteList(&pStart);
			break;
		case 'e':
			printf("Hersteller: ");
			scanf_s(" %c", &Hersteller);
			printf("Name: ");
			scanf_s(" %c", &Name);
			DeleteElement(&pStart, Hersteller, Name);
			break;
		case 'p':
			printf("Geben sie Anzahl Elemente ein, welche ausgegeben werden sollen oder 0 für alle Elemente: ");
			int outputAmount;
			scanf_s("%i", &outputAmount);
			printf("%i", Amount);
			PrintList(&pStart, outputAmount);
			break;
		case 'v':
			QuitApplication(&pStart);
			break;
		}
	}
}

