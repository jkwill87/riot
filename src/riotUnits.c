#include <riotMap.h>
#include <ctype.h>
#include "riotUnits.h"

struct UnitList *createList(void) {

    struct UnitList *newList = malloc(sizeof(struct UnitList));

    newList->count = 0;
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}


void destroyList(struct UnitList *list) {

    struct UnitNode *tempNode = NULL;

    while (list->count) {
        tempNode = list->head->next;
        free(list->head);
        list->count--;
        list->head = tempNode;
    }
    free(list);

    return;
}


bool isEmpty(struct UnitList *list) {

    bool eval = TRUE;

    if (list) {
        if (list->count)
            eval = FALSE;
    }

    return eval;

}

struct TileNode *getTile(struct Path *path) {
	return path ? path->first : NULL;
}

struct UnitNode *getNext(struct UnitNode *list) {
    return list ? list->next : NULL;
}


struct UnitNode *getHead(struct UnitList *listIn) {
    return listIn ? listIn->head : NULL;
}


struct UnitNode *getTail(struct UnitList *listIn) {
    return listIn ? listIn->tail : NULL;
}


int getLength(struct UnitList *listIn) {
    return listIn ? listIn->count : (int) -1;
}


struct UnitNode *enqueue(struct UnitList *queue, void *unit) {

    struct UnitNode *newNode = malloc(sizeof(struct UnitNode));
    newNode->unit = unit;

    if (queue->count) {
        newNode->next = queue->head;
        newNode->prev = NULL;
        queue->head = newNode;
        queue->head->next->prev = newNode;

    } else {
        queue->head = newNode;
        queue->tail = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
    }

    queue->count++;

    return newNode;

}


struct UnitNode *dequeue(struct UnitList *queue) {

    struct UnitNode *tempNode, *request = NULL;

    if (queue->count) {
        tempNode = queue->tail->prev;
        request = queue->tail;
        queue->count--;
        queue->tail = tempNode;
    }

    if (queue->head)
        queue->head->prev = NULL;

    return request;
}


struct UnitNode *pop(struct UnitList *stack) {

    struct UnitNode *tempNode, *request = NULL;

    if (stack->count) {
        tempNode = stack->head->next;
        request = stack->head;
        stack->count--;
        stack->head = tempNode;
    }

    if (stack->head)
        stack->head->prev = NULL;

    return request;
}


void rmUnit(struct UnitNode *target) {
    free(target->unit);
    free(target);
    return;
}


struct Inmate *createInmate(enum InmateType type) {

    struct Inmate *unit = malloc(sizeof(struct Inmate));

    unit->type = type;
    unit->position = -1;

    switch (type) {

        case PROTAGONIST:
            unit->currentHealth = unit->maxHealth = 5;
            unit->speed = 2;
            unit->rep = 0;
            unit->panic = 0;
            break;

        case HOMEBOY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 4;
            unit->rep = 5;
            unit->panic = 2;
            break;

        case BRUISER:
            unit->currentHealth = unit->maxHealth = 16;
            unit->speed = 4;
            unit->rep = 15;
            unit->panic = 6;
            break;

        case LUNATIC:
            unit->currentHealth = unit->maxHealth = 16;
            unit->speed = 6;
            unit->rep = 10;
            unit->panic = 8;
            break;

        case FATTY:
            unit->currentHealth = unit->maxHealth = 40;
            unit->speed = 2;
            unit->rep = 10;
            unit->panic = 4;
            break;

        case SPEEDY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 8;
            unit->rep = 20;
            unit->panic = 2;
            break;

        case CUTIE:
            unit->currentHealth = unit->maxHealth = 20;
            unit->speed = 4;
            unit->rep = 20;
            unit->panic = 1;
            break;

        case ATTORNEY:
            unit->currentHealth = unit->maxHealth = 30;
            unit->speed = 5;
            unit->rep = 30;
            unit->panic = 2;
            break;

        case DOCTOR:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 5;
            unit->rep = 40;
            unit->panic = 2;
            break;

        default:
            quit("Creating unsupported unit type.");
            break;
    }

    return unit;
}


struct Guard *createGuard(enum GuardType type) {

    struct Guard *unit = malloc(sizeof(struct Guard));

    unit->type = type;
    unit->position = -1;

    switch (type) {

        case GUARD:
            unit->damage = 5;
            unit->range = 2;
            unit->cooldown = 4;
            unit->ai = PROX;
            break;

        case DOGS:
            unit->damage = 4;
            unit->range = 4;
            unit->cooldown = 6;
            unit->ai = AOE;
            break;

        case LUNCH:
            unit->damage = 0;
            unit->range = 6;
            unit->cooldown = 12;
            unit->ai = AOE;
            break;

        case PSYCH:
            unit->damage = 0;
            unit->range = 6;
            unit->cooldown = 12;
            unit->ai = PROX;
            break;

        case SHARP:
            unit->damage = 6;
            unit->range = 10;
            unit->cooldown = 8;
            unit->ai = END;
            break;

        case WARDEN:
            unit->damage = 100;
            unit->range = 8;
            unit->cooldown = 2;
            unit->ai = PROX;
            break;

        case CYBORG:
            unit->damage = 12;
            unit->range = 8;
            unit->cooldown = 2;
            unit->ai = PROX;
            break;

        default:
            quit("Creating unsupported unit type.");
            break;
    }

    return unit;
}
/*Need to pass in interface?*/
void runSimulation(struct UnitList *guardList, struct UnitList *inmateList, struct Path *path) {
    struct UnitNode *nextInmate;
    //struct UnitNode *nextGuard;
    int simulate = 0;
    int prevPos = 0;

    nextInmate = getHead(inmateList);
    while (simulate < 10) {
        prevPos = ((struct Inmate *) nextInmate->unit)->position;
        inmateMove(inmateList, path);
        //drawUnit(win, nextInmate->unit, path, prevPos); (draw new position)
        guardAttack(guardList, inmateList);
        //drawUnit(); (new colour)
        printf("here");
    }
}


/*Moves the units through the map and calls 'inmateRedraw to draw/erase the
 units*/
void inmateMove(struct UnitList *inmateList, struct Path *path) {
   struct UnitNode *nextInmate;
   struct TileNode *nextTile;
   int prevPos;

   nextTile = getTile(path);
   nextInmate = getHead(inmateList);
   printf("Checking to move units");
   do {
       prevPos = ((struct Inmate *) nextInmate->unit)->position;
       ((struct Inmate *) nextInmate->unit)->position = ((struct Inmate *) nextInmate->unit)->position  + ((struct Inmate *) nextInmate->unit)->speed/8; 
       if ((int)((struct Inmate *) nextInmate->unit)->position == prevPos + 1) {
         printf("Unit Moved");
         ((struct Inmate *) nextInmate->unit)->position = ((struct TileNode *)nextTile)->location;
       }
       //inmateRedraw(int previousPosition, int currentPosition, char type),
       // need this function to draw redraw units onto the screen. UI
       //source perhaps?
       // inmateRedraw(prevPos,(int)inmate->pos,inmate->type);
       //essentially what is going to be called
       nextInmate = getNext(nextInmate);

   } while (getNext(nextInmate) != NULL);
}


void guardAttack(struct UnitList *guardList, struct UnitList *inmateList) {
    struct UnitNode *nextInmate;
    struct UnitNode *nextGuard;

    nextGuard = getHead(guardList);
    nextInmate = getHead(inmateList);

    printf("Guard Attack has begun.\n\n");

    do {
        do {
            if (inRange(nextInmate, nextGuard))
                dealDamage(nextInmate, nextGuard);
            nextInmate = getNext(nextInmate);
        } while (getNext(nextInmate) != NULL);
        nextGuard = getNext(nextGuard);
    } while (getNext(nextGuard) != NULL);
}


void dealDamage(struct UnitNode *inmateNode, struct UnitNode *guardNode) {
    printf("#####Inmate attacked#####\n");
    printf("Inmate Position: %f\n",
        ((struct Inmate *) inmateNode->unit)->position);
    printf("Guard Position: %d\n",
        ((struct Guard *) guardNode->unit)->position);
    printf("Health before attack: %d\n",
        ((struct Inmate *) inmateNode->unit)->currentHealth);
    printf("Damage dealt by guard: %d\n",
        ((struct Guard *) guardNode->unit)->damage);
    ((struct Inmate *) inmateNode->unit)->currentHealth =
        ((struct Inmate *) inmateNode->unit)->currentHealth -
            ((struct Guard *) guardNode->unit)->damage;

    printf("Health after attack: %d\n",
        ((struct Inmate *) inmateNode->unit)->currentHealth);
    printf("########################\n");
    printf("\n");
}


bool inRange(struct UnitNode *inmate, struct UnitNode *guard) {
    int inmatePosition;
    int guardPosition;
    int range;
    int xDifference;
    int yDifference;
    int totalDifference;

    inmatePosition = ((struct Inmate *) inmate->unit)->position;
    guardPosition = ((struct Guard *) guard->unit)->position;
    range = ((struct Guard *) guard->unit)->range;

    yDifference = (((inmatePosition - 1) / MAX_COLS) + 1) -
        -
            (((guardPosition - 1) / MAX_COLS) + 1);
    xDifference = (guardPosition + (yDifference * MAX_COLS)) - inmatePosition;
    yDifference = abs(yDifference);
    xDifference = abs(xDifference);
    totalDifference = xDifference + yDifference;
    printf("#####Calculating Range#####\n");
    printf("Unit position: %d\n", inmatePosition);
    printf("Guard position: %d\n", guardPosition);
    printf("Y Difference: %d\n", yDifference);
    printf("X Difference: %d\n", xDifference);
    printf("Total Difference: %d\n", totalDifference);
    printf("Range of the Guard: %d\n", range);
    printf("############################\n");
    printf("\n");

    return range >= totalDifference;
}


struct Path *getPath(struct Map map){
	int i,j, position;
	char mapChar;
	struct Path *path;

	path = (struct Path *)malloc(sizeof(struct Path));
	path->count = 0;

	for (i=0;i<MAP_ROWS;i++){
		for (j=0;j<MAP_COLS;j++){
			position = (i*MAP_COLS)+j;
			mapChar = map.overlay[i][j];
			if (isPathCharacter(mapChar) || isalpha(mapChar)){
				pushToPath(createTileNode(position,map.overlay[i][j]),path);
			}
		}
	}

	return path;
}

bool isPathCharacter(char tileChar){
	return (tileChar == '.' || tileChar == '#' || tileChar == '$' || tileChar == '&' || tileChar == '%');
}

struct TileNode * createTileNode(int location, char type){
	struct TileNode * tileNode = NULL;

	tileNode = (struct TileNode *)malloc(sizeof(struct TileNode));

	tileNode->next = NULL;
	tileNode->location = location;
	tileNode->type = type;

	return tileNode;
}
void destroyPath(struct Path * path){
	struct TileNode * nextNode = NULL;

	if (path->count > 0){
		nextNode = path->first;
	}

	for (int i=0 ;i< path->count;i++){
		while (nextNode->next != NULL){
			nextNode = nextNode->next;
			free(nextNode);
			path->count--;
		}	
	}
	free(path);
}
void pushToPath(struct TileNode* insertNode, struct Path* path){
	struct TileNode * nextNode = NULL;

	if (path->count > 0){
		nextNode = path->first;

		while (nextNode->next != NULL){
			nextNode = nextNode->next;
		}

		nextNode->next = insertNode;
		path->count++;
	}
	else{
		path->first = insertNode;
		path->count++;
	}
}
/*struct UnitList *getGuardList(struct Map map){

}*/
