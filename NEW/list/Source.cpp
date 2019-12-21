#include <stdlib.h>
#include <stdio.h>

void main() {

	// Typedefinition
	typedef struct Grafikkarte {
		char name[40];
		char hersteller[40];
		int herstellungsjahr;
		struct Grafikkarte* pNext;
		struct Grafikkarte* pPrev;
	} struGrafikkarte;

	// Function declaration
	struGrafikkarte* CreateList(int Amount);
	void DeleteList(struGrafikkarte **pList);
	void DeleteElement(struGrafikkarte **pList, char name, char hersteller);
	void SortList();
	void PrintList(struGrafikkarte **pList, int Amount);
	void QuitApplication();
	void PrintUserInterface();

	/*
	*Creates a list with a defined amount of elements
	*@Return
	*/






}