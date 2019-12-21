#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>

typedef struct Person {
    char Vorname[40];
    char Nachname[40];
    int Jahrgang;
    struct Person *pNext;
} struPerson;

// Deklarationen
struPerson* CreateList(int Anzahl);
void ClearList(struPerson **pList);
void DeletePerson(struPerson **pList, char cVorname, char cNachname);
void PrintList(struPerson **pList, int count);
void PrintPerson(struPerson *pPerson);

void MergeSort(struPerson **pStart);
struPerson* SortedMerge(struPerson *a, struPerson *b);
void MoveNode(struPerson **destRef, struPerson **sourceRef);
void FrontBackSplit(struPerson *source, struPerson **frontRef, struPerson **backRef);

void InsertSort(struPerson **pList);
void SortedInsert(struPerson **pList, struPerson *newNode);

char GenerateName();
int GenerateYear();

bool CheckAscBothName(struPerson *a, struPerson *b);
bool CheckNames(struPerson *current, char cVorname, char cNachname);
bool CheckSortedList(struPerson **pList);

void PrintHauptMenu();


/*
 * Erstellt eine Liste von definierter Anzahl Elementen
 * Anzahl: Anzahl Elemente
 */
struPerson* CreateList(int Anzahl) {
    struPerson *pStart = NULL;
    struPerson *pLast = NULL;

    for (int iPers = 0; iPers < Anzahl; iPers++) {
        char cVorname = GenerateName();
        char cNachname = GenerateName();

        struPerson *pNew = (struPerson*)malloc(sizeof(struPerson));

		// Vorname und Nachname sind char Arrays und keine char Pointers (Strings)
		// In der Aufgabe ist beschrieben, Vorname und Nachname sollen als Strings
		// behandelt werden. Strings sind in C mit \0 terminiert.
		pNew->Vorname[0] = cVorname;
		pNew->Vorname[1] = '\0';
		pNew->Nachname[0] = cNachname;
		pNew->Nachname[1] = '\0';
        pNew->Jahrgang = GenerateYear();
        pNew->pNext = NULL;

        if (pStart == NULL) {
            pStart = pNew;
        }

        if (pLast != NULL) {
            pLast->pNext = pNew;
        }
        pLast = pNew;
    }
    return pStart;
}

/*
 * Loeschen einer ganzen Liste
 * pList: Referenz auf die Liste
 */
void ClearList(struPerson **pList) {
    struPerson *current = *pList;
    struPerson *next;

    while (current != NULL) {
        next = current->pNext;
        free(current);
        current = next;
    }

    *pList = NULL;
}

/*
 * Loeschen einer Person aus der Liste
 * pList: Referenz auf die Liste
 * cVorname: Vorname fuer die Suche nach der Person
 * cNachname: Nachname fuer die Suche nach der Person
 */
void DeletePerson(struPerson **pList, char cVorname, char cNachname) {
    struPerson *current = *pList;
    struPerson *prev = NULL;

    while (current != NULL) {
        if (CheckNames(current, cVorname, cNachname)) {
            if (prev == NULL) {
                *pList = current->pNext;
                free(current);
                current = *pList;
            } else {
                prev->pNext = current->pNext;
                free(current);
                current = prev->pNext;
            }
        } else {
            prev = current;
            current = current->pNext;
        }
    }
}

/*
 * Zeigt jedes Element aus der List an.
 * pList: Referenz auf die Liste
 * Anzahl: Anzahl Element die ausgegeben werden (0 = alle)
 */
void PrintList(struPerson **pList, int Anzahl) {
    int counter = 0;
    int toCount = (Anzahl == 0) ? -1 : Anzahl;
    // Gibt Liste aus
    struPerson *pOut = *pList;
    while (pOut != NULL && counter != toCount) {
        PrintPerson(pOut);
        pOut = pOut->pNext;
        counter++;
    }
}

/*
 * Ausgabe eines Elements (Person) in der Liste
 * pPerson: Referenz auf die Person
 */
void PrintPerson(struPerson *pPerson) {
    printf("Vorname: %s, Nachname: %s, Jahrgang: %i\n", pPerson->Vorname, pPerson->Nachname, pPerson->Jahrgang);
}

/*
 * Sortierfunktion: MergeSort
 * Sortiert mit Hilfe von aufteilen in Unterlisten und zusammenfuegen dieser am Schluss
 * Beispiel: Liste = {3, 2, 4, 5}
 * Aufteilung: a = {3, 2}, b = {4, 5}
 * Sortierung a: a = {2, 3}
 * Sortierung b: b = {4, 5}
 * Zusammenfuegen: a + b = {2, 3, 4, 5}
 * Diese Schritte koennen mehrmals gemacht werden (Rekursion)
 * pList: Referenz auf die Liste
 */
void MergeSort(struPerson **pList) {
    struPerson *head = *pList;
    struPerson *a;
    struPerson *b;

    // Bei leerer Liste oder Liste mit einem Element
    if ((head == NULL) || (head->pNext == NULL)) {
        return;
    }
    // Liste aufteilen in a und b
    FrontBackSplit(head, &a, &b);
    // Rekursiv die einzelnen Unterlisten sortieren
    MergeSort(&a);
    MergeSort(&b);
    // Liste ist das Zusammenfuegen aller Unterlisten
    *pList = SortedMerge(a, b);
}

/*
 * Sortiert und fuegt Unterlisten zusammen
 * a: Unterliste a
 * b: Unterliste b
 */
struPerson* SortedMerge(struPerson *a, struPerson *b) {
    struPerson dummy;
    struPerson* tail = &dummy;
    dummy.pNext = NULL;

    while (true) {
        // Ist eine Unterliste am Ende, verwende die andere Unterliste
        if (a == NULL) {
            tail->pNext = b;
            break;
        } else if (b == NULL) {
            tail->pNext = a;
            break;
        }

        // Ueberpruefe Nachname/Vorname
        if (CheckAscBothName(a, b)) {
            //Schiebe Element nach vorne
            MoveNode(&(tail->pNext), &a);
        } else {
            // Schiebe Element nach hinten
            MoveNode(&(tail->pNext), &b);
        }
        tail = tail->pNext;
    }
    return dummy.pNext;
}

/*
 * Teilt eine Liste auf in 2 Unterlisten. Ist die Anzahl der Elemente ungerade,
 * beinhaltet die erste Liste (a oder Front) mehr Elemente / 2 + 1
 * Beispiel: 5 Elemente -> a besitzt 3 Elemente, b besitzt 2 Elemente
 * source: Aktuelle Liste (kann auch eine Unterliste sein)
 * frontRef: Unterliste a
 * backRef: Unterliste b
 */
void FrontBackSplit(struPerson *source, struPerson **frontRef, struPerson **backRef) {
    // Zwei Pointers um eine Liste zu halbieren
    // fast Pointer sprint immer 2 Elemente weiter
    struPerson *fast;
    // slow Pointer sprint jeweils nur ein Element weiter
    struPerson *slow;

    // Liste ist kuerzer als 2 Elemente
    if (source == NULL || source->pNext == NULL) {
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->pNext;
        while (fast != NULL) {
            fast = fast->pNext;
            if (fast != NULL) {
                slow = slow->pNext;
                fast = fast->pNext;
            }
        }
        // slow Pointer ist in der Mitte der Liste angelangt (oder Mitte + 1)
        *frontRef = source;
        *backRef = slow->pNext;
        slow->pNext = NULL;
    }
}

/*
 * Verschiebe das erste Element von a nach b
 * destRef: Referenz auf b
 * sourceRef: Referenz auf a
 * Beispiel: a = {1, 2} und b = {3, 4}
 * MoveNode(&a, &b) => a = {3, 1, 2} und b = {4}
 */
void MoveNode(struPerson **destRef, struPerson **sourceRef) {
    struPerson *newNode = *sourceRef;
    // Wichtig: newNode darf nicht NULL sein
    assert(newNode != NULL);

    *sourceRef = newNode->pNext;
    newNode->pNext = *destRef;
    *destRef = newNode;
}

/*
 * Sortierfunktion: InsertSort
 * Sortiert mit Hilfe von einfuegen in eine neue temporaere Liste
 * Beispiel: Liste {3, 4, 1, 2}
 * Schritt 1: TListe {1}, Liste {3, 4, 2}
 * Schritt 2: TListe {1, 2}, Liste {3, 4}
 * Schritt 3: TListe {1, 2, 3}, Liste {4}
 * Schritt 4: TListe {1, 2, 3, 4}, Liste {}
 * pList: Referenz auf die Liste
 */
void InsertSort(struPerson **pList) {
    struPerson *result = NULL;
    struPerson *current = *pList;
    struPerson *next;

    while (current != NULL) {
        // Speichere das naechste Element, nicht vergessen
        next = current->pNext;
        SortedInsert(&result, current);
        current = next;
    }
    *pList = result;
}

/*
 * Fuegt ein neues Element sortiert in die Liste ein
 * pList: Referenz auf die Liste
 * newNode: Neues Element zum sortiert einfuegen
 */
void SortedInsert(struPerson **pList, struPerson *newNode) {
    struPerson dummy;
    struPerson* current = &dummy;
    dummy.pNext = *pList;

    // Folge der Liste solange sie nicht am Ende ist und der Nachname/Vorname kleiner ist
    while (current->pNext != NULL && CheckAscBothName(current->pNext, newNode)) {
        current = current->pNext;
    }

    newNode->pNext = current->pNext;
    current->pNext = newNode;
    *pList = dummy.pNext;
}

/*
 * Generiere einen Buchstaben von A-Z fuer den Namen
 */
char GenerateName() {
    return 'A' + rand() % 25;
}

/*
 * Generiere ein Jahr von 1900 - 2018 fuer den Jahrgang
 */
int GenerateYear() {
    return 1900 + rand() % 118;
}

/*
 * Hilfsfunktion: Ueberprueft ob Nachname & Vorname (falls Nachname gleich) von a kleiner b
 * a: Person a
 * b: Person b
 */
bool CheckAscBothName(struPerson *a, struPerson *b) {
    int nachNameResult = strncmp(a->Nachname, b->Nachname, 1);
    // Ist der Nachname gleich ..
    if (nachNameResult == 0) {
        // .. Vorname vergleichen
        return strncmp(a->Vorname, b->Vorname, 1) < 0;
    }
    // Sortieren nach Nachname
    return nachNameResult < 0;
}

/*
 * Hilfsfunktion: Ueberprueft ob Person->Vorname = Vorname und Person->Nachname = Nachname
 * current: Aktuelle Person
 * cVorname: Vorname zum Pruefen
 * cNachname: Nachname zum Pruefen
 */
bool CheckNames(struPerson *current, char cVorname, char cNachname) {
    return (strncmp(current->Vorname, &cVorname, 1) == 0 && strncmp(current->Nachname, &cNachname, 1) == 0);
}

/*
 * Hilfsfunktion: Ueberprueft ob die Liste wirklich sortiert ist
 * pList: Referenz auf die Liste
 */
bool CheckSortedList(struPerson **pList) {
    struPerson *current = *pList;
    struPerson *next;

    // Leere Liste oder Liste mit nur einem Element
    if (current == NULL || current->pNext == NULL) {
        return false;
    }

    next = current->pNext;
    while (current != NULL && next != NULL) {
        if (!CheckAscBothName(current, next)) {
            if (strncmp(current->Vorname, next->Vorname, 1) != 0) {
                return false;
            }
        }
        current = current->pNext;
        next = current->pNext;
    }
    return true;
}

/*
 * Gibt das Hauptmenue aus
 */
void PrintHauptMenu() {
    printf("\n\n===\n");
    printf("Menu\n");
    printf("Liste erzeugen (a)\n");
    printf("Liste loeschen (c)\n");
    printf("Element loeschen (d)\n");
    printf("Sortieren (s)\n");
    printf("Ausgabe Liste (p)\n");
    printf("Exit (e)\n");
    printf("===\n");
    //printf("Bonus\n");
    //printf("Ist Liste sortiert? (k)\n");
    //printf("Sortieren InsertSort (i)\n");
    //printf("Benchmark (b)\n");
    //printf("Eingabe: ");
}


int main() {
    // Zufallszahlen initialisieren, damit bei jedem Programmstart andere Werte erzeugt werden
    srand((unsigned) time(NULL));
    char menuEntry, cVorname, cNachname;
    int anzahlElemente;
    struPerson *pList = NULL;
    PrintHauptMenu();
    while (1) {
        scanf_s(" %c", &menuEntry);
        switch (menuEntry) {
        case 'a':
            printf("\nAnzahl Elemente: ");
            scanf_s("%d", &anzahlElemente);
            pList = CreateList(anzahlElemente);
            PrintHauptMenu();
            break;
        case 'c':
            ClearList(&pList);
            PrintHauptMenu();
            break;
        case 'd':
            printf("Vorname: ");
            scanf_s(" %c", &cVorname);
            printf("Nachname: ");
            scanf_s(" %c", &cNachname);
            DeletePerson(&pList, cVorname, cNachname);
            PrintHauptMenu();
            break;
        case 'i':
            InsertSort(&pList);
            PrintHauptMenu();
            break;
        case 'k':
            if (CheckSortedList(&pList)) {
                printf("Liste ist sortiert\n");
            } else {
                printf("Liste ist NICHT sortiert\n");
            }
            PrintHauptMenu();
            break;
        case 'p':
            PrintList(&pList, 0);
            PrintHauptMenu();
            break;
        case 's':
            MergeSort(&pList);
            PrintHauptMenu();
            break;
        case 'e':
			ClearList(&pList);
            return 0;
        }

    }
}