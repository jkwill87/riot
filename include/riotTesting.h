#ifndef RIOT_TESTING
#define RIOT_TESTING

#include "riotExec.h"
#include "riotMap.h"
#include "riotUnits.h"
#include "riotUI.h"

/* DESCRIPTION: tests all colors that can fit on a screen*/
void colorDumpTest ();


/*DESCRIPTION: Prints the path of the map.
  ARGUMENTS: -Path struct (struct Path *path).*/
void printPath(struct Path *path);


/*DESCRIPTION: Prints out the guard list.
  ARGUMENTS: -The guard list (struct UnitList *guardList).*/
void printGuardList(struct UnitList *guardList);


/*DESCRIPTION: Prints out the Inmate list.
  ARGUMENTS: -The Unit list (struct UnitList *list). */
void printInmateList(struct UnitList *inmateList);


/*DESCRIPTION: Tests the different colour schemes.*/
void colorTest();

void guardTest();
/* DESCRIPTION: Testing the movement of the units.
   ARGUMENTS: -The location of the directory (char *loadDir).*/
void unitsMove(char *loadDir);



/* DESCRIPTION: Tests the map
   ARGUMENTS: -The location of the directory (char *argument).*/
void unitsPlay(char *argument);

void mapTest(char *loadDir);

void printInmate(struct Inmate *inmate);

void printGuard(struct Guard *guard);

void printCoordinates(int position);

void testingHelp();


#endif //RIOT_TESTING
