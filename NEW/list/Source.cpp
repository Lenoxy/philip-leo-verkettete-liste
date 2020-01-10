#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// Typedefinition
typedef struct Grafikkarte
{
	char name[5];
	char hersteller[5];
	int herstellungsjahr;
	struct Grafikkarte* pNext;
	struct Grafikkarte* pPrev;
} struGrafikkarte;

enum attributes { name = 1, hersteller = 2, herstellungsjahr = 3, undefined = 4 };

// Function declaration
struGrafikkarte* CreateList(int Amount);
void DeleteList(struGrafikkarte* pList);
struGrafikkarte* DeleteElement(struGrafikkarte* pList);
struGrafikkarte* SortList(struGrafikkarte* pStartOfList, int length);
void PrintList(struGrafikkarte* pList);
void QuitApplication(struGrafikkarte** pList);
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


		struGrafikkarte* pNewElement = (struGrafikkarte*)malloc(sizeof(struGrafikkarte));

		for (int i = 0; i < 5; i++) {
			char Name = GenerateRandomChar();
			char Hersteller = GenerateRandomChar();

			pNewElement->name[i] = Name;
			pNewElement->hersteller[i] = Hersteller;
		}

		int Herstellungsjahr = GenerateRandomYear();
		pNewElement->herstellungsjahr = Herstellungsjahr;
		pNewElement->name[4] = '\0';
		pNewElement->hersteller[4] = '\0';




		if (i != 0) {
			pNewElement->pNext = pStart;
			pStart->pPrev = pNewElement;
		}
		else {
			pEnd = pNewElement;
		}
		pStart = pNewElement;
	}
	pStart->pPrev = pEnd;
	pEnd->pNext = pStart;
	return pStart;
}
/*Generates a random letter in the alaphabet
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

void DeleteList(struGrafikkarte* pStart) {
	struGrafikkarte* pCurrent = pStart;
	do {
		struGrafikkarte* pTemp = pCurrent;
		pCurrent = pCurrent->pNext;
		free(pTemp);
	} while (pCurrent != pStart);
}

/*
*Autor: Philip Baumann
*Deletes a single element in the list by comparing string and then rearranging pointers
*@Param pointer, char, char
*@Return void
*/

struGrafikkarte* DeleteElement(struGrafikkarte* pStart)
{
	int element;
	printf("W�hle eines der 3 Elemente aus:\n");
	printf("1 = Name, 2 = Hersteller, 3 = Herstellungsjahr\n");
	scanf_s("%i", &element);

	char searchString[5];
	printf("\nGib den Namen des Elements ein\n");
	gets_s(searchString);
	gets_s(searchString);

	struGrafikkarte* pCurrent = pStart;

	do
	{
		switch (element) {
		case name:
			break;
		case hersteller:
			if (strcmp(pCurrent->hersteller, searchString) == 0) {
				printf("Deleting %s\n", pCurrent->hersteller);

				if (pCurrent == pStart) {
					printf("pCurrent==pStart");
					pStart = pCurrent->pNext;
				}

				struGrafikkarte* pTempPreDel = pCurrent->pPrev;
				struGrafikkarte* pTempAfterDel = pCurrent->pNext;
				pTempPreDel->pNext = pTempAfterDel;
				pTempAfterDel->pPrev = pTempPreDel;

				struGrafikkarte* pTempDel = pCurrent;
				pCurrent = pCurrent->pNext;
				free(pTempDel);
			}

			break;
		case herstellungsjahr:
			break;
		case undefined:
			break;
		default:
			break;
		}

		pCurrent = pCurrent->pNext;

	} while (pCurrent != pStart);

	return pStart;
}

/*
*Autor: Leo Scherer
*Sorts list by using the bubblesort methode
*@Param pointer, int
*@Return
*/

struGrafikkarte* SortList(struGrafikkarte* pStartOfList, int length) {
	int oCounter, iCounter;
	printf("1 = Ascending, 2 = Descending");
	int decision;
	scanf_s(" %i", &decision);

	for (oCounter = 0; oCounter < length - 1; oCounter++) {
		struGrafikkarte* pIndex = pStartOfList;
		for (iCounter = 0; iCounter < length - oCounter - 1; iCounter++) {
			if (decision == 1) {
				if ((pIndex->herstellungsjahr) > (pIndex->pNext->herstellungsjahr)) {
					printf("Swapping %i for %i\n", pIndex->herstellungsjahr, pIndex->pNext->herstellungsjahr);

					struGrafikkarte* pTempNext = pIndex->pNext;
					struGrafikkarte* pTempPrev = pIndex->pPrev;

					pIndex->pNext = pIndex->pNext->pNext;
					pIndex->pNext->pPrev = pIndex;

					pIndex->pPrev = pTempNext;
					pIndex->pPrev->pNext = pIndex;

					pIndex->pPrev->pPrev = pTempPrev;
					pIndex->pPrev->pPrev->pNext = pIndex->pPrev;

					if (pStartOfList == pIndex) {
						pStartOfList = pIndex->pPrev;
					}

				}
				else {
					pIndex = pIndex->pNext;
				}
			}
			else {
				if ((pIndex->herstellungsjahr) < (pIndex->pNext->herstellungsjahr)) {
					printf("Swapping %i for %i\n", pIndex->herstellungsjahr, pIndex->pNext->herstellungsjahr);

					struGrafikkarte* pTempNext = pIndex->pNext;
					struGrafikkarte* pTempPrev = pIndex->pPrev;

					pIndex->pNext = pIndex->pNext->pNext;
					pIndex->pNext->pPrev = pIndex;

					pIndex->pPrev = pTempNext;
					pIndex->pPrev->pNext = pIndex;

					pIndex->pPrev->pPrev = pTempPrev;
					pIndex->pPrev->pPrev->pNext = pIndex->pPrev;

					if (pStartOfList == pIndex) {
						pStartOfList = pIndex->pPrev;
					}

				}
				else {
					pIndex = pIndex->pNext;
				}
			}

		}
	}

	return pStartOfList;
}

/*
*Autor: Leo Scherer
*Prints entire list to the console. By iterating through the list which is possible due to the pNext which gets set to the current structure element
*@Param pointer, int
*@Return void
*/

void PrintList(struGrafikkarte* pStart) {
	struGrafikkarte* pOutput = pStart;
	int Amount;
	int index = 0;
	printf("Geben Sie die Anzahl Elemente, welche ausgegeben werden sollen in Form einer Integerzahl ein. Falls alle Elemente ausgegeben werden solle geben sie 0 ein.\n");
	scanf_s("%i", &Amount);

	if (Amount == 0) {
		Amount = -1;
	}

	if (pOutput != NULL) {
		do {
			printf("Name: %s, Hersteller: %s, Herstellungsjahr: %i \n", pOutput->name, pOutput->hersteller, pOutput->herstellungsjahr);
			pOutput = pOutput->pNext;
			index++;
		} while (pOutput != pStart && index != Amount);
	}

}

/*
*Autor: Leo Scherer
*the application and deletes list aswell as freeing the memory
*@Param pointer
*@Return void
*/

void QuitApplication(struGrafikkarte* pList) {
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
			printf("Wie viele Items soll die Liste beinhaten?	");
			scanf_s("%i", &Amount);
			pStart = CreateList(Amount);
			break;
		case 's':
			pStart = SortList(pStart, Amount);
			break;
		case 'l':
			DeleteList(pStart);
			pStart = NULL;
			break;
		case 'e':
			pStart = DeleteElement(pStart);
			break;
		case 'p':
			PrintList(pStart);
			break;
		case 'v':
			QuitApplication(pStart);
			break;
		}
	}
}

