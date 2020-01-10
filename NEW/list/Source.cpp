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
struGrafikkarte* swapElement(struGrafikkarte* pIndex, struGrafikkarte* pStart);
void PrintList(struGrafikkarte* pList);
void QuitApplication(struGrafikkarte** pList);
char GenerateRandomChar();
int GenerateRandomYear();
void PrintMainMenuToConsole();

/*
*Autor: Philip Baumann / Leo Scherer
*Creates a list with a defined amount of elements
*@Param Amount of Element that will be created
*@Return pStart
*/

struGrafikkarte* CreateList(int Amount)
{
	// Initiate variables
	struGrafikkarte* pStart = NULL;
	struGrafikkarte* pEnd = NULL;

	// Iteratation
	for (int i = 0; i < Amount; i++)
	{
		// Memory allocation
		struGrafikkarte* pNewElement = (struGrafikkarte*)malloc(sizeof(struGrafikkarte));

			char Name = GenerateRandomChar();
			char Hersteller = GenerateRandomChar();

			pNewElement->name[0] = Name;
			pNewElement->hersteller[0] = Hersteller;

		int Herstellungsjahr = GenerateRandomYear();
		pNewElement->herstellungsjahr = Herstellungsjahr;
		pNewElement->name[1] = '\0';
		pNewElement->hersteller[1] = '\0';



		// Not first element
		if (i != 0) {
			pNewElement->pNext = pStart;
			pStart->pPrev = pNewElement;
		}
		else {
			pEnd = pNewElement;
		}
		pStart = pNewElement;
	}
	// Arrange pointers
	pStart->pPrev = pEnd;
	pEnd->pNext = pStart;
	return pStart;
}
/*Generates a random letter in the alaphabet
*Autor:  Philip Baumann
*@Param
*@Return random letter
*/

char GenerateRandomChar()
{
	// Create random character in the alaphabet
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
	// Create random number range 1900 - 2017
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
	//Iterate through entire list and free the space in the memory
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
	// User Interaction
	int element;
	printf("Wähle eines der 3 Elemente aus:\n");
	printf("1 = Name, 2 = Hersteller, 3 = Herstellungsjahr\n");
	scanf_s("%i", &element);
	char searchString[5];
	printf("\nGib den Namen des Elements ein\n");
	gets_s(searchString);
	gets_s(searchString);

	//casting
	int searchInt = atoi(searchString);

	struGrafikkarte* pCurrent = pStart;

	do
	{
		// Jump into case which user selected
		switch (element) {
		case name:
			// String comparison
			if (strcmp(pCurrent->name, searchString) == 0) {
				printf("Deleting %s\n", pCurrent->name);

				// If element is the starting element of the list
				if (pCurrent == pStart) {
					pStart = pCurrent->pNext;
				}

				// Rearranging pointers and freeing space in the memory
				struGrafikkarte* pTempPreDel = pCurrent->pPrev;
				struGrafikkarte* pTempAfterDel = pCurrent->pNext;
				pTempPreDel->pNext = pTempAfterDel;
				pTempAfterDel->pPrev = pTempPreDel;
				struGrafikkarte* pTempDel = pCurrent;
				pCurrent = pCurrent->pNext;
				free(pTempDel);
			}
			break;

		case hersteller:

			// String comparison
			if (strcmp(pCurrent->hersteller, searchString) == 0) {
				printf("Deleting %s\n", pCurrent->hersteller);

				// If Element is staring element of the list
				if (pCurrent == pStart) {
					printf("pCurrent==pStart");
					pStart = pCurrent->pNext;
				}
				// Rearranging pointers and freeing space in the memory
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
			// compare integers
			if (pCurrent->herstellungsjahr == searchInt) {
				printf("Deleting %i\n", pCurrent->herstellungsjahr);

				// if element is starting element of the list
				if (pCurrent == pStart) {
					pStart = pCurrent->pNext;
				}

				// Rearranging pointers and freeing space in the memory
				struGrafikkarte* pTempPreDel = pCurrent->pPrev;
				struGrafikkarte* pTempAfterDel = pCurrent->pNext;
				pTempPreDel->pNext = pTempAfterDel;
				pTempAfterDel->pPrev = pTempPreDel;
				struGrafikkarte* pTempDel = pCurrent;
				pCurrent = pCurrent->pNext;
				free(pTempDel);
			}

			break;
		case undefined:
			break;
		default:
			break;
		}

		// Rearrangement for the iteration
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
	// User interaction and variable declaration 
	int oCounter, iCounter;
	printf("1 = Descending, 2 = Ascending\n");
	int scendance;
	scanf_s(" %i", &scendance);
	printf("Sort by: (1 Name, 2 Hersteller, 3 Herstellungsjahr)\n");
	int sortby;
	scanf_s(" %i", &sortby);

	// forloop x-cordination
	for (oCounter = 0; oCounter < length - 1; oCounter++) {
		struGrafikkarte* pIndex = pStartOfList;
		// forloop y-cordination
		for (iCounter = 0; iCounter < length - oCounter - 1; iCounter++) {
			// users decision
			if (sortby == 1) {
				if (scendance == 1) {
					// comparison
					if (((int) pIndex->name[0]) > ((int) pIndex->pNext->name[0])) {
						pStartOfList = swapElement(pIndex, pStartOfList);
					}
					else {
						pIndex = pIndex->pNext;
					}
				}
				else {
					// comparison
					if (((int) pIndex->name[0]) < ((int) pIndex->pNext->name[0])) {
						pStartOfList = swapElement(pIndex, pStartOfList);
					}
					else {
						pIndex = pIndex->pNext;
					}
				}

			} else if (sortby == 2) {
				if (scendance == 1) {
					// comparison
					if (((int) pIndex->hersteller[0]) > ((int) pIndex->pNext->hersteller[0])) {
						pStartOfList = swapElement(pIndex, pStartOfList);

					}
					else {
						pIndex = pIndex->pNext;
					}
				}
				else {
					// comparison
					if (((int) pIndex->hersteller[0]) < ((int) pIndex->pNext->hersteller[0])) {
						pStartOfList = swapElement(pIndex, pStartOfList);
					}
					else {
						pIndex = pIndex->pNext;
					}
				}
			}
			else if (sortby == 3) {
				if (scendance == 1) {
					// comparison
					if ((pIndex->herstellungsjahr) > (pIndex->pNext->herstellungsjahr)) {
						pStartOfList = swapElement(pIndex, pStartOfList);
					}
					else {
						pIndex = pIndex->pNext;
					}
				}
				else {
					// comparison
					if ((pIndex->herstellungsjahr) < (pIndex->pNext->herstellungsjahr)) {
						pStartOfList = swapElement(pIndex, pStartOfList);
					}
					else {
						pIndex = pIndex->pNext;
					}
				}
			}
			

		}
	}
	return pStartOfList;
}

struGrafikkarte* swapElement(struGrafikkarte* pIndex, struGrafikkarte* pStart) {
	// switching pointer and rearranging subpointers
	struGrafikkarte* pTempNext = pIndex->pNext;
	struGrafikkarte* pTempPrev = pIndex->pPrev;
	pIndex->pNext = pIndex->pNext->pNext;
	pIndex->pNext->pPrev = pIndex;
	pIndex->pPrev = pTempNext;
	pIndex->pPrev->pNext = pIndex;
	pIndex->pPrev->pPrev = pTempPrev;
	pIndex->pPrev->pPrev->pNext = pIndex->pPrev;

	// if element is start of the list
	if (pStart == pIndex) {
		pStart = pIndex->pPrev;
	}
	return pStart;
}

/*
*Autor: Philip Baumann
*Prints entire list to the console. By iterating through the list which is possible due to the pNext which gets set to the current structure element
*@Param pointer, int
*@Return void
*/

void PrintList(struGrafikkarte* pStart) {
	// User interaction and variable declaration
	struGrafikkarte* pOutput = pStart;
	int Amount;
	int index = 0;
	printf("Geben Sie die Anzahl Elemente, welche ausgegeben werden sollen in Form einer Integerzahl ein. Falls alle Elemente ausgegeben werden solle geben sie 0 ein.\n");
	scanf_s("%i", &Amount);

	// if user wants all element to be seen then set amount to -1 to second condition of loop will never be reached
	if (Amount == 0) {
		Amount = -1;
	}
	// To iterate through list a list must already exist
	if (pOutput != NULL) {
		do {
			// looping and printing element to console
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
	// Delete list and exit application
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
	// print main menu to console
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
	// variable declaration
	char Hersteller;
	char Name;
	char selection;
	struGrafikkarte* pStart = NULL;
	int Amount = 0;

	// always do so appication keeps running
	while (true)
	{
		PrintMainMenuToConsole();
		scanf_s(" %c", &selection);
		switch (selection) {
		case 'a':
			// case add list
			printf("Wie viele Items soll die Liste beinhaten?	");
			scanf_s("%i", &Amount);
			pStart = CreateList(Amount);
			break;
		case 's':
			// case sort list
			pStart = SortList(pStart, Amount);
			break;
		case 'l':
			// case delete list
			DeleteList(pStart);
			pStart = NULL;
			break;
		case 'e':
			// case delete element
			pStart = DeleteElement(pStart);
			break;
		case 'p':
			// case print list
			PrintList(pStart);
			break;
		case 'v':
			// case quit application
			QuitApplication(pStart);
			break;
		}
	}
}
