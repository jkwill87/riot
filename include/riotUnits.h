#ifndef RIOT_UNITS
#define RIOT_UNITS

#include "riotExec.h"
#include "riotMap.h"
/* Data Types */

#define CYCLE 50000000L;
#define REL_DELAY 5
#define HEALCOOLDOWN 12

enum Effect{
    EFFECT_LUNCH = 12,
    EFFECT_PSYCH = 6,
    EFFECT_DOGS = 1,
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
    int slowedCounter;
    int sleepCounter;
    int healCooldown;
    bool healer;
    bool doubleDamage;
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

void writeToFile(char *string);

/*DESCRIPTION: Deallocate memory for a UnitList struct.
  ARGUMENTS: -A Pointer to the UnitList to be destroyed (struct UnitList *list).
  POSTCONDITIONS: Each node listed within the UnitList is destroyed and the
  memory used for it is returned to the calling OS.*/
void destroyList(struct UnitList *);


/*DESCRIPTION: Get a pointer to the next UnitNode stored within the UnitList.
  ARGUMENTS: The UnitList to be querried (struct UnitList *list).
  POSTCONDITIONS: Will return a pointer to the UnitNode, else NULL.*/
struct UnitNode *getNext(struct UnitNode *list);


/*DESCRIPTION: Get a pointer to the first UnitNode stored within the UnitList.
  ARGUMENTS: The UnitList to be querried (struct UnitList *).
  POSTCONDITIONS: Will return a pointer to the UnitNode, else NULL.*/
struct UnitNode *getHead(struct UnitList *);


/*DESCRIPTION: Get a pointer to the last UnitNode stored within the UnitList.
  ARGUMENTS: -The UnitList to be querried (struct UnitList *). 
  POSTCONDITIONS: Will return a pointer to the UnitNode, else NULL.*/
struct UnitNode *getTail(struct UnitList *);


/*DESCRIPTION: Get the number of nodes containted within a UnitList.
  ARGUMENTS: The UnitList to be examined (struct UnitList *).
  POSTCONDITIONS: Will return a int value corresponding to the number of
  UnitNodes contained withing the UnitList*/
int getLength(struct UnitList *);


/*DESCRIPTION: Will store any data type (Guard or Unit) at the back of a UnitList/GuardList.
  ARGUMENTS: -The list to be extended (struct UnitList *queue)
             -A pointer to the data to be added (void *unit).
  POSTCONDITIONS: Will store either the newly created UnitNode containing the
  unit within it's data member or NULL if not possible.*/
struct UnitNode *enqueue(struct UnitList *queue, void *unit);


/*DESCRIPTION: Remove the front UnitNode of the passed UnitList. 
  Memory is not freed by this function.
  ARGUMENTS: -The list to be modified (struct UnitList *queue).
  POSTCONDITIONS: The front UnitNode is either removed from the passed UnitList
  and its pointer is returned, else NULL is returned.*/
void *dequeue(struct UnitList *queue);


/*DESCRIPTION: Removes the unit node at position.
  ARGUMENTS: -The unit to be removed from the list (struct UnitList *list).
             -Position to be removed at (int position).*/
void removeUnit(struct UnitList *list, int position);


/*DESCRIPTION: Moves the list node to the targeted node to be removed
  ARGUMENTS: -Position of the node to be removed (int position).
             -List of units (struct UnitList *list).*/
struct UnitNode *moveTo(int position, struct UnitList *list);


/*DESCRIPTION: Remove the back UnitNode of the passed UnitList.
  Memory is not freed by this function.
  ARGUMENTS: The list to be modified (struct UnitList *stack).
  POSTCONDITIONS: The back UnitNode is either removed from the passed UnitList
  and its pointer is returned, else NULL is returned.*/
struct UnitNode *pop(struct UnitList *stack);


/*DESCRIPTION: Initializes a new inmate with its associated base stats.
  ARGUMENTS: -An InmateType enum associated with the Inmate to be initiated (enum InmateType type).
  PRECONDITIONS: The enum value is a valid inmate type.
  POSTCONDITIONS: Memory is allocated for a new Inmate struct.*/
struct Inmate *createInmate(enum InmateType type);


/*DESCRIPTION: Initializes a new guard with its associated base stats
  ARGUMENTS: -An GuardType enum associated with the Guard to be initiated (enum GuardType type).
  PRECONDITIONS: The enum value is a valid guard type.
  POSTCONDITIONS: Memory is allocated for a new Guard struct.*/
struct Guard *createGuard(enum GuardType type);


/*DESCRIPTION: Simulates all unit interactions and drawing for a period of time.
  ARGUMENTS: -The win interface (struct Windows *win)
             -List of guards and the list of inmates (struct UnitList *guards)
             -List of units in the wave (struct UnitList *queued)
             -The path of the map (struct Path *path)
             -The map that is being played (struct Map *map)*/
enum GameMode simulate(struct Windows *win, struct UnitList *guards,  
  struct UnitList *queued, struct Path *path, struct Map *map);


/*DESCRIPTION: Handles the movement of the units on the screen.
  ARGUMENTS: -The list of inmates (UnitList * inmateList).
             -The path of the map (Path *path.) */
void inmateMove(struct UnitList *inmates, int elapsed);


/*DESCRIPTION: Returns a boolean based on if an inmate exists within a guards range.
  ARGUMENTS: -List of units (struct UnitList inmateList)*/
void setDeadInmates(struct UnitList *inmateList);


/*DESCRIPTION: Updates all of the guards accuracy based on the panic.
  ARGUMENTS: -Guard list to be updated(struct UnitList *guardList).
             -Current game panic (int currentPanic).
             -Maximum game panic (int maximumPanic).*/
void updateGuardAccuracy(struct UnitList *guardList, int currentPanic, int maximumPanic);


/*DESCRIPTION: Has every guard attack an inmate within its range.
  ARGUMENTS: -List of guards (struct UnitList * guardList)
             -List of the units (struct UnitList *inmateList) 
             -Path of the map (struct Path path)*/
void guardAttack(struct UnitList * guardList, struct UnitList *inmateList, struct Path path);


/*DESCRIPTION: Guard attacks all inmates within its range.
  ARGUMENTS: -Specific guard attacking the units (struct UnitNode *guardNode).
             -List of units (struct UnitList *inmateList).*/
void guardAttackAOE(struct UnitNode *guardNode, struct UnitList *inmateList);


/*DESCRIPTION: Returns the UnitNode closest to position.
  ARGUMENTS: -Inmate List that the closest inmate will be chosen from (struct UnitList inmateList).
             -Position to calculate the distance of the inmate from (int position).*/
struct UnitNode* getClosestInmateToPosition(struct UnitList inmateList, int position);


/*DESCRIPTION: Returns the distance between two positions.
  ARGUMENTS: -Position to calculate from (int positionFrom).
             -Position to calculate to (int positionTo).*/
int getDistance(int positionFrom, int positionTo);


/*DESCRIPTION: Guard attacks the unit closest to the exit of the map.
  ARGUMENTS: -Guard that is attacking the inmate(struct UnitNode *guardNode).
             -Inmate list that the inmates are found in(struct UnitList *inmateList). 
             -The furthest distance that the guard can attack the units*/
void guardAttackEnd(struct UnitNode *guardNode, struct UnitList *inmateList, int exitPosition);


/*DESCRIPTION: Guard attacks the inmate closest to it.
  ARGUMENTS: -Guard that is attacking the inmate(struct UnitNode *guardNode).
             -Inmate list that the inmates are found in (struct UnitList *inmateList).*/
void guardAttackProximity(struct UnitNode *guardNode, struct UnitList *inmateList);


/*DESCRIPTION: Returns a boolean based on if the guard missed or not, this depends on the 
current ingame panic.
  ARGUMENTS: -Guard that is trying to attack (struct UnitNode guardNode).*/
bool tryAttack(struct UnitNode guardNode);


/*DESCRIPTION: Decrements the inmates health by the guards damage during an attack
  ARGUMENTS: -Inmate that is being dealt damage (struct UnitNode *inmateNode).
             -Guard that is dealing damage (struct UnitNode *guardNode).*/
void dealDamage(struct UnitNode * inmateNode, struct UnitNode * guardNode);


/*DESCRIPTION: Returns a boolean based on if the inmate is within the guards range
  ARGUMENTS: -Inmate that is being checked if within range of guard (UnitNode *inmate).
             -Guard that is comparing with the inmate position (struct UnitNode *guard).*/
bool inRange(struct UnitNode *inmate, struct UnitNode *guard);


/*DESCRIPTION: Returns a boolean based on if an inmate exists within a guards range.
  ARGUMENTS: -List of units (struct UnitList inmateList).
             -Guard whos range is to be compared (struct UnitNode guard). */
bool inmateExistsInRange(struct UnitList inmateList, struct UnitNode guard);


/*DESCRIPTION: Parses the map and and finds all the guards to put them into the guard list
  ARGUMENTS: -List of guards (struct UnitList *guards).
             -The map that is being loaded in (struct Map map).*/
struct UnitList *getGuards(struct UnitList *guards, struct Map map);


#endif //RIOT_UNITS
