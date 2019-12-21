#include <stdlib.h>
#include <stdio.h>

void main() {
	typedef struct Grafikkarte {
		char name[40];
		char hersteller[40];
		int herstellungsjahr;
		struct Grafikkarte* pNext;
		struct Grafikkarte* pPrev;
	} struGrafikkarte;

}