#define _DEFAULT_SOURCE

#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "riotUnits.h"
#include "riotUI.h"


/*static void writeToFile(char message){
    FILE * file = fopen("test.txt","a");

    fprintf(file,"%c\n",message);

    fclose(file);
}*/

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

void removeUnit(struct UnitList *list,int position){
    struct UnitNode *nextNode,*temp;

    if (list->count <= position || list->count <= 0){
        printf("Error! Removing from an inexistent position!\n");
        exit(1);
    }
    nextNode = getHead(list);
    if (position == 0){
        free(list->head);
        list->head = NULL;
    }
    else{
        for (int i=0;i<position-1;i++){
            nextNode = getNext(nextNode);
        }
        temp = nextNode->next;
        nextNode->next = nextNode->next->next;
        free(temp);
    }
    list->count--;
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
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        case HOMEBOY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 4;
            unit->rep = 5;
            unit->panic = 2;
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        case BRUISER:
            unit->currentHealth = unit->maxHealth = 16;
            unit->speed = 4;
            unit->rep = 15;
            unit->panic = 6;
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        case LUNATIC:
            unit->currentHealth = unit->maxHealth = 16;
            unit->speed = 6;
            unit->rep = 10;
            unit->panic = 8;
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        case FATTY:
            unit->currentHealth = unit->maxHealth = 40;
            unit->speed = 2;
            unit->rep = 10;
            unit->panic = 4;
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        case SPEEDY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 8;
            unit->rep = 20;
            unit->panic = 2;
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        case CUTIE:
            unit->currentHealth = unit->maxHealth = 20;
            unit->speed = 4;
            unit->rep = 20;
            unit->panic = 1;
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        case ATTORNEY:
            unit->currentHealth = unit->maxHealth = 30;
            unit->speed = 4;
            unit->rep = 30;
            unit->panic = 2;
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        case DOCTOR:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 4;
            unit->rep = 40;
            unit->panic = 2;
            unit->dead = FALSE;
            unit->reachedEnd = FALSE;
            break;

        default:
            quit("Creating unsupported unit type INMATE.");
            break;
    }

    return unit;
}


struct Guard *createGuard(enum GuardType type) {

    struct Guard *guard = malloc(sizeof(struct Guard));

    guard->type = type;
    guard->position = -1;

    switch (type) {

        case GUARD:
            guard->damage = 5;
            guard->range = 2;
            guard->cooldown = 4;
            guard->cooldownRemaining = guard->cooldown;
            guard->ai = PROX;
            break;

        case DOGS:
            guard->damage = 4;
            guard->range = 4;
            guard->cooldown = 6;
            guard->cooldownRemaining = guard->cooldown;
            guard->ai = AOE;
            break;

        case LUNCH:
            guard->damage = 0;
            guard->range = 6;
            guard->cooldown = 12;
            guard->cooldownRemaining = guard->cooldown;
            guard->ai = AOE;
            break;

        case PSYCH:
            guard->damage = 0;
            guard->range = 6;
            guard->cooldown = 12;
            guard->cooldownRemaining = guard->cooldown;
            guard->ai = PROX;
            break;

        case SHARP:
            guard->damage = 6;
            guard->range = 10;
            guard->cooldown = 8;
            guard->cooldownRemaining = guard->cooldown;
            guard->ai = END;
            break;

        case WARDEN:
            guard->damage = 100;
            guard->range = 8;
            guard->cooldown = 2;
            guard->cooldownRemaining = guard->cooldown;
            guard->ai = PROX;
            break;

        case CYBORG:
            guard->damage = 12;
            guard->range = 8;
            guard->cooldown = 2;
            guard->cooldownRemaining = guard->cooldown;
            guard->ai = PROX;
            break;

        default:
            quit("Creating unsupported unit type");
            break;
    }

    return guard;
}


bool simulate(struct Windows *gameInterface,
    struct UnitList *guardList, struct UnitList *inmateList,
    struct Path *path, struct Map *map) {
    int i;
    struct UnitNode *nextInmate;
    //int prevPos[inmateList->count];
    struct timespec delay;

    delay.tv_sec = 0;
    delay.tv_nsec = 40000000L;  // Half second in nano seconds

    //While inmates exist, keep simulating
    while (inmateList->head != NULL) {

        nextInmate = getHead(inmateList);
        for (i = 0; i < inmateList->count; i++) {
            //prevPos[i] = ((struct Inmate *) nextInmate->unit)->position;
            nextInmate = nextInmate->next;
        }
        inmateMove(inmateList, path);
        guardAttack(guardList, inmateList,*map);
        nextInmate = getHead(inmateList);
        for (int i = 0; i < inmateList->count; i++) {
            /*Dequeues all units that are marked for deletion    vv SWITCHED FROM FALSE AND COMMENTED OUT LINES
            These are both units that are dead or that have reached the end of the map*/
            if (((struct Inmate *) nextInmate->unit)->dead == TRUE){
                removeUnit (inmateList, i); //needs to be written, removes an inmate fromthe middle of the list
            }
            else if (((struct Inmate *) nextInmate->unit)->reachedEnd == TRUE ){
                map->panicCur += ((struct Inmate *) nextInmate->unit)->panic;
                removeUnit (inmateList, i);
            }
                nextInmate = nextInmate->next; 
        }
        /*The only UI fucntion that Simulate needs to worry about*/
        gameplayRefresh (gameInterface->body,map,guardList,inmateList,path);
        //If you lose freeze for one second
        if (inmateList->head == NULL){
            sleep(1);
        }
        //Otherwise keep pausing half a second
        else{
            nanosleep(&delay, NULL);
        }
    }
    /*LOOP ENDS AND RETURNS TRUE REGARDLESS*/
    return true;  //TODO return win condition
}


/*Moves the units through the map and calls 'inmateRedraw to draw/erase the
 units*/
void inmateMove(struct UnitList *inmateList, struct Path *path) {
    struct UnitNode *nextInmate;
    struct TileNode *nextTile;
    int prevPos;

    nextInmate = getHead(inmateList);
    do {
        nextTile = path->first;
        for (int i = 0; i < path->count; i++) {
            if (nextTile->location ==
                (int) ((struct Inmate *) nextInmate->unit)->position)
                break;
            nextTile = nextTile->next;
        }

        //if ((struct Inmate *) nextInmate->prev == NULL) {
            prevPos = ((struct Inmate *) nextInmate->unit)->position;
            ((struct Inmate *) nextInmate->unit)->position =
            ((struct Inmate *) nextInmate->unit)->position +
            (float) ((struct Inmate *) nextInmate->unit)->speed / 8;
            moveAnimation(nextInmate, nextTile, prevPos);
        /*} else {
            prevPos = ((struct Inmate *) nextInmate->unit)->position;
            ((struct Inmate *) nextInmate->unit)->position =
            ((struct Inmate *) nextInmate->unit)->position +
            (float) ((struct Inmate *) nextInmate->unit)->speed / 8;
            if ((int)((struct Inmate *) nextInmate->unit)->position != (int) ((struct Inmate *) nextInmate->prev)->position) {
                moveAnimation(nextInmate, nextTile, prevPos);
            }
        }*/
        nextInmate = getNext(nextInmate);
    } while (getNext(nextInmate));
}
        /*prevPos = ((struct Inmate *) nextInmate->unit)->position;
        ((struct Inmate *) nextInmate->unit)->position =
        ((struct Inmate *) nextInmate->unit)->position +
        (float) ((struct Inmate *) nextInmate->unit)->speed / 8;
        if ((int)((struct Inmate *) nextInmate->unit)->position != (int) ((struct Inmate *) nextInmate->prev)->position) {
            if (nextTile->next != NULL && (int) ((struct Inmate *) nextInmate->unit)->position == prevPos + 1 
                && nextTile->next->type == '#' && ((struct Inmate *) nextInmate->unit)->doorSmash == 3) {
                ((struct Inmate *) nextInmate->unit)->position = nextTile->next->location;
                ((struct Inmate *) nextInmate->unit)->doorSmash = 0;
            }                
            else if (nextTile->next != NULL && (int) ((struct Inmate *) nextInmate->unit)->position == prevPos + 1 
                && nextTile->next->type == '#' && ((struct Inmate *) nextInmate->unit)->doorSmash != 3) {
                ((struct Inmate *) nextInmate->unit)->position = prevPos;
                ((struct Inmate *) nextInmate->unit)->doorSmash++;
            } 
            else if (nextTile->next->type != '&' && (int) ((struct Inmate *) nextInmate->unit)->position ==
                prevPos + 1)
                ((struct Inmate *) nextInmate->unit)->position = nextTile->next->location;
            else if (nextTile->next->type == '&'  && (int) ((struct Inmate *) nextInmate->unit)->position == prevPos + 1) {
                ((struct Inmate *) nextInmate->unit)->delUnit = TRUE;
                ((struct Inmate *) nextInmate->unit)->position = nextTile->location;            
            }
        } else {
            ((struct Inmate *) nextInmate->unit)->position = (int)((struct Inmate *) nextInmate->unit)->position;
        }
        nextInmate = getNext(nextInmate);
    } while (getNext(nextInmate));
}*/
    
void moveAnimation(struct UnitNode * nextInmate, struct TileNode *nextTile, int prevPos) {
    //int prevPos = 0;
    
    /*prevPos = ((struct Inmate *) nextInmate->unit)->position;
    ((struct Inmate *) nextInmate->unit)->position =
    ((struct Inmate *) nextInmate->unit)->position +
    (float) ((struct Inmate *) nextInmate->unit)->speed / 8;*/
    if (nextTile->next != NULL && (int) ((struct Inmate *) nextInmate->unit)->position == prevPos + 1 
        && nextTile->next->type == '#' && ((struct Inmate *) nextInmate->unit)->doorSmash == 3) {
        ((struct Inmate *) nextInmate->unit)->position = nextTile->next->location;
        ((struct Inmate *) nextInmate->unit)->doorSmash = 0;
    }                
    else if (nextTile->next != NULL && (int) ((struct Inmate *) nextInmate->unit)->position == prevPos + 1 
        && nextTile->next->type == '#' && ((struct Inmate *) nextInmate->unit)->doorSmash != 3) {
        ((struct Inmate *) nextInmate->unit)->position = prevPos;
        ((struct Inmate *) nextInmate->unit)->doorSmash++;
    } 
    else if (nextTile->next->type != '&' && (int) ((struct Inmate *) nextInmate->unit)->position ==
        prevPos + 1)
        ((struct Inmate *) nextInmate->unit)->position = nextTile->next->location;
    else if (nextTile->next->type == '&'  && (int) ((struct Inmate *) nextInmate->unit)->position == prevPos + 1) {
        ((struct Inmate *) nextInmate->unit)->reachedEnd = TRUE;
        ((struct Inmate *) nextInmate->unit)->position = nextTile->location;            
    }
}



void guardAttack(struct UnitList *guardList, struct UnitList *inmateList, struct Map map) {
    struct UnitNode *nextInmate;
    struct UnitNode *nextGuard;

    nextGuard = getHead(guardList);
    nextInmate = getHead(inmateList);

 	#ifdef _DEBUGN
	printf("Guard Attack has begun.\n\n");
	printf("Inmates List size: %d\n", inmateList->count);
	printf("Guards List size: %d\n\n", guardList->count);
	#endif
    
	for (int i=0;i<inmateList->count;i++){
		for (int j=0;j<guardList->count;j++){
			if (inRange(nextInmate, nextGuard)){
                if (((struct Inmate *) nextInmate->unit)->currentHealth <= 0){
                    ((struct Inmate *) nextInmate->unit)->dead = true;
                }
				else if (((struct Guard*)nextGuard->unit)->cooldownRemaining == 0){
					((struct Guard*)nextGuard->unit)->cooldownRemaining = ((struct Guard*)nextGuard->unit)->cooldown;
		        	dealDamage(nextInmate, nextGuard);
				}
				((struct Guard*)nextGuard->unit)->cooldownRemaining -= 1;
			}
			if (getNext(nextGuard) != NULL){
	    		nextGuard = getNext(nextGuard);
			}
		}
		if (getNext(nextInmate) != NULL){
			nextInmate = getNext(nextInmate);
		}
	}	
}


void dealDamage(struct UnitNode *inmateNode, struct UnitNode *guardNode) {
	int currentHealth;
	int damage;

	#ifdef DEBUGN
    printf("#####Inmate attacked#####\n");
    printf("Inmate Position: %f\n",
        ((struct Inmate *) inmateNode->unit)->position);
    printf("Guard Position: %d\n",
        ((struct Guard *) guardNode->unit)->position);
    printf("Health before attack: %d\n",
        ((struct Inmate *) inmateNode->unit)->currentHealth);
    printf("Damage dealt by guard: %d\n",
        ((struct Guard *) guardNode->unit)->damage);
    #endif

	currentHealth = ((struct Inmate *) inmateNode->unit)->currentHealth;
	damage = ((struct Guard *) guardNode->unit)->damage;
    ((struct Inmate *) inmateNode->unit)->currentHealth = currentHealth - damage;

    #ifdef DEBUGN
    printf("Health after attack: %d\n",
        ((struct Inmate *) inmateNode->unit)->currentHealth);
    printf("########################\n");
    printf("\n");
   #endif
}


bool inRange(struct UnitNode *inmate, struct UnitNode *guard) {
    int inmatePosition;
    int guardPosition;
    int range;
    int xDifference,yDifference;
    int inmateY,guardY;
    int totalDifference;

    inmatePosition = ((struct Inmate *) inmate->unit)->position;
    guardPosition = ((struct Guard *) guard->unit)->position;
    range = ((struct Guard *) guard->unit)->range;

    inmateY = (inmatePosition-1)/MAP_COLS;
    guardY = (guardPosition-1)/MAP_COLS;
    yDifference = (inmateY + 1) - (guardY + 1);
    xDifference = abs(guardPosition-(guardY*MAP_COLS))-abs(inmatePosition-(inmateY*MAP_COLS));
    yDifference = abs(yDifference);
    xDifference = abs(xDifference);
    totalDifference = xDifference + yDifference;

   #ifdef DEBUGN
    printf("#####Calculating Range#####\n");
    printf("Unit position: %d\n", inmatePosition);
    printf("Guard position: %d\n", guardPosition);
    printf("Y Difference: %d\n", yDifference);
    printf("X Difference: %d\n", xDifference);
    printf("Total Difference: %d\n", totalDifference);
    printf("Range of the Guard: %d\n", range);
    printf("############################\n");
    printf("\n");
   #endif

    return range >= totalDifference;
}


struct UnitList* getGuards(struct UnitList *guards, struct Map map) {

    struct Guard *guard;
    int i, j, position;
    char mapChar;

    /* Initialize guards list */
    guards->count = 0;
    guards->head = NULL;
    guards->tail = NULL;

    /* Get guards */
    for (i = 0; i < MAP_ROWS; i++) {
        for (j = 0; j < MAP_COLS; j++) {
            position = (i * MAP_COLS) + j;
            mapChar = toupper(map.overlay[i][j]);
            if (isalpha(mapChar)) {
                guard = createGuard(mapChar);
                guard->position = position;
                enqueue(guards, guard);
                printf("FOUND GUARD, Guard List size: %d %c\n",guards->count,mapChar);
            }
        }
    }

    return guards;
}
