#ifndef RIOT_TESTING
#define RIOT_TESTING

#include "riotExec.h"
#include "riotMap.h"
#include "riotUnits.h"
#include "riotUI.h"

void printInmates(struct UnitList *list);
/* DESCRIPTION: Prints out the guard list
 * ARGUMENTS: The guard list */
void unitsMove(char *loadDir);

/* DESCRIPTION: Testing the movement of the units
 * ARGUMENTS: The location of the directory */
void unitsTest(void);

void guardTest();

/* DESCRIPTION: Testing the guard range and attacking
 * ARGUMENTS: */
void unitsPlay(char *argument);


/* DESCRIPTION: tests all colors that can fit on a screen*/
void colorDumpTest ();


/* DESCRIPTION: Tests the map
 * ARGUMENTS: The location of the directory */
void mapTest(char *loadDir);/*


void writeToFile(char *message);/*

DESCRIPTION: Function that writes information to a file for debugging purposes

ARGUMENTS: The message
*/


void colorTest();

void testingHelp();

#endif //RIOT_TESTING
