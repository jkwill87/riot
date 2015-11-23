#ifndef RIOT_TESTING
#define RIOT_TESTING

#include "riotExec.h"
#include "riotMap.h"
#include "riotUnits.h"
#include "riotUI.h"


/* DESCRIPTION: Prints out the guard list
 * ARGUMENTS: The guard list */
void unitsMove(char *loadDir);


/* DESCRIPTION: Testing the movement of the units
 * ARGUMENTS: The location of the directory */
void unitsTest(void);


/* DESCRIPTION: Testing the guard range and attacking
 * ARGUMENTS: */
void unitsPlay(char *argument);


/* DESCRIPTION: Tests the map
 * ARGUMENTS: The location of the directory */
void mapTest(char *loadDir);


void colorTest();

void testingHelp();

#endif //RIOT_TESTING
