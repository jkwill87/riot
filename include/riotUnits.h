
#ifndef RIOT_UNITS
#define RIOT_UNITS

#include "riotExec.h"
#include "riotMap.h"
/* Data Types */

#define CYCLE 50000000L;
#define REL_DELAY 5

enum Effect{
    EFFECT_LUNCH = 12,
    EFFECT_PSYCH = 6,
    EFFECT_DOGS = 2,
};

struct UnitNode {/*

UnitNode stores the information related to inmate units.*/

    void *unit;
    struct UnitNode *next;
    struct UnitNode *prev;
};


struct Inmate {
    /*

     Inmate stores the stats related to inmate units.*/

    char type;
    int position;
    int currentHealth;
    int maxHealth;
    int speed;
    int maxSpeed;
    int rep;
    int panic;
    int doubleDamageCounter;
    int slowedCounter;
    int sleepCounter;
    bool dead;
    bool reachedEnd;
    struct TileNode *currentTile;
};


struct Guard {/*

 Inmate stores the stats related to guard units.*/

    char type;
    int position;
    int damage;
    int range;
    int cooldown;
    int cooldownRemaining;
    enum AI ai;
    float accuracy;
};


/* Linked UnitList Operations */  
bool inmateExistsInRange(struct UnitList inmateList,struct UnitNode guard);/*

DESCRIPTION: Returns a boolean based on if an inmate exists within a guards range.

ARGUMENTS: List of units (struct UnitList inmateList).
           Guard whos range is to be compared (struct UnitNode guard).
 */
void guardAttackProximity(struct UnitNode *guardNode,
    struct UnitList *inmateList);/*

DESCRIPTION: Guard attacks the inmate closest to it.

ARGUMENTS: Guard that is attacking the inmate(struct UnitNode *guardNode).
           Inmate list that the inmates are found in (struct UnitList *inmateList).
*/
void guardAttackAOE(struct UnitNode *guardNode,
    struct UnitList *inmateList);/*

DESCRIPTION: Guard attacks all inmates within its range.

ARGUMENTS: Guard that is attacking the inmates (struct UnitNode *guardNode).
           Inmate list that the inmates are found in(struct UnitList *inmateList).
*/
void guardAttackEnd(struct UnitNode *guardNode,
    struct UnitList *inmateList, int exitPosition);/*

DESCRIPTION: Guard attacks the unit closest to the exit of the map.

ARGUMENTS: Guard that is attacking the inmate(struct UnitNode *guardNode).
           Inmate list that the inmates are found in(struct UnitList *inmateList).
*/
void setDeadInmates(struct UnitList *inmateList);

bool tryAttack(struct UnitNode guardNode);/*

DESCRIPTION: Returns a boolean based on if the guard missed or not, this depends on the 
             current ingame panic.

ARGUMENTS: Guard that is trying to attack (struct UnitNode guardNode).
*/
void updateGuardAccuracy(struct UnitList *guardList, int currentPanic, int maximumPanic);/*

DESCRIPTION: Updates all of the guards accuracy based on the panic.

ARGUMENTS: Guard list to be updated(struct UnitList *guardList).
           Current game panic (int currentPanic).
           Maximum game panic (int maximumPanic).
*/

int getDistance(int positionFrom,int positionTo);/*

DESCRIPTION: Returns the distance between two positions.

ARGUMENTS: Position to calculate from (int positionFrom).
           Position to calculate to (int positionTo).
*/

struct UnitNode* getClosestInmateToPosition(struct UnitList inmateList, int position);/*

DESCRIPTION: Returns the UnitNode closest to position.

ARGUMENTS: Inmate List that the closest inmate will be chosen from (struct UnitList inmateList).
           Position to calculate the distance of the inmate from (int position).
*/

void destroyList(struct UnitList *);/*

DESCRIPTION: destroyList() is used to deallocate memory for a UnitList struct.

ARGUMENTS: A Pointer to the UnitList to be destroyed.

POSTCONDITIONS: Each node listed within the UnitList is destroyed and the
 memory used for it is returned to the calling OS.*/


int getLength(struct UnitList *);/*

DESCRIPTION: getLength() is used to get the number of nodes containted within
 a UnitList.

ARGUMENTS: The UnitList to be examined.

POSTCONDITIONS: Will return a int value corresponding to the number of
 UnitNodes contained withing the UnitList*/


bool isEmpty(struct UnitList *);/*

DESCRIPTION: isEmpty() is used to determine whether a UnitList has been
 initialized and is capable of storing UnitNodes.

ARGUMENTS: The UnitList to be examined.

PRECONDITIONS: The position is within the size of the list.

POSTCONDITIONS: Will return TRUE is empty, otherwide FALSE.*/


struct UnitNode *getHead(struct UnitList *);/*

DESCRIPTION: getHead() is used to get a pointer to the first UnitNode stored
 within the UnitList.

ARGUMENTS: The UnitList to be querried.

POSTCONDITIONS: Will return a pointer to the UnitNode, else NULL.*/


struct UnitNode *getTail(struct UnitList *);/*

DESCRIPTION: getTail() is used to get a pointer to the last UnitNode stored
 within the UnitList.

ARGUMENTS: The UnitList to be querried.

POSTCONDITIONS: Will return a pointer to the UnitNode, else NULL.*/


/* Linked UnitList Interfaces */

struct UnitNode *enqueue(struct UnitList *queue, void *unit);/*

DESCRIPTION: enqueue() will store any data type (presumably either an Inmate
 or Guard type) at the back of a UnitList.

ARGUMENTS: The list to be extended and a pointer to the data to be added.

POSTCONDITIONS: Will store either the newly created UnitStore cointaing the
 unit within it's data member or NULL if not possible.*/


void *dequeue(struct UnitList *queue);/*

DESCRIPTION: dequeue() will remove the front UnitNode of the passed UnitList.
 Memory is not freed by this funtion-- either its returned UnitNode will need
 to be freed by rmUnit or enqueued in a seperate UnitList which can later be
 destroyed.

ARGUMENTS: The list to be modified.

POSTCONDITIONS: The front UnitNode is either removed from the passed UnitList
 and its pointer is returned, else NULL is returned.*/

void removeUnit(struct UnitList *list,int position);/*

DESCRIPTION: Removes the unit node at position.

ARGUMENTS: List to be removed from (struct UnitList *list).
           Position to be removed at (int position).
*/

struct UnitNode *pop(struct UnitList *stack);/*

DESCRIPTION: pop() will remove the back UnitNode of the passed UnitList.
 Memory is not freed by this funtion-- either its returned UnitNode will need
 to be freed by rmUnit or enqueued in a seperate UnitList which can later be
 destroyed.

ARGUMENTS: The list to be modified.

POSTCONDITIONS: The back UnitNode is either removed from the passed UnitList
 and its pointer is returned, else NULL is returned.*/


struct Inmate *createInmate(enum InmateType type);/*

DESCRIPTION: Creates an inmate and initializes it

ARGUMENTS: The inmate type to be assigned to the inmate that is being created (enum InmateType type);
*/


void rmUnit(struct UnitNode* target);/*

DESCRIPTION: inmateRm() is used to remove a unit from the game.

ARGUMENTS: struct UnitNode *inmateList is the list of inmates present in
the game, this argument should be changed to a header node once one is
present.

PRECONDITIONS: The position is within the size of the list.

POSTCONDITIONS: The inmate at position has been removed.*/


struct Inmate *createInmate(enum InmateType type);/*

DESCRIPTION: createInmate() is used initialize a new inmate with its
 associated base stats.

ARGUMENTS: an InmateType enum associated with the Inmate to be initiated.

PRECONDITIONS: The enum value is a valid inmate type.

POSTCONDITIONS: Memory is allocated for a new Inmate struct.*/


enum GameMode simulate(struct Windows *win, struct UnitList *guards,
    struct UnitList *queued, struct Path *path, struct Map *map); /*

  DESCRIPTION: Simulates all unit interactions and drawing for a period of time
  
  ARGUMENTS: The win interface
             List of guards and the list of inmates
             The path of the map*/


void inmateMove(struct UnitList *inmates, int elapsed);/*
DESCRIPTION: Move inmate every turn by its speed/8.

ARGUMENTS: The list of inmates (UnitList * inmateList).
           The path of the map (Path *path.) */

void moveAnimation(struct UnitNode *inmateN, struct TileNode *tileN, int lastPos);

void guardAttack(struct UnitList * guardList, struct UnitList *inmateList, struct Path path);/*

DESCRIPTION: Has every guard attack an inmate within its range.

ARGUMENTS: The list of guards and the list of inmates */


bool inRange(struct UnitNode *inmate,struct UnitNode *guard);/*

DESCRIPTION: Returns a boolean based on if the inmate is within the guards range

ARGUMENTS: Size of the the map path horizontally (int rowSize).
           Inmate that is being checked if within range of guard(UnitNode *inmate).
           Guard that is comparing with the inmate position.*/


void dealDamage(struct UnitNode * inmateNode,struct UnitNode * guardNode);/*

DESCRIPTION: Decrements the inmates health by the guards damage during an attack

ARGUMENTS: Inmate that is being dealt damage (struct UnitNode *inmateNode).
           Guard that is dealing damage (struct UnitNode *guardNode).*/


#endif //RIOT_UNITS
