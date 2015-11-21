#define _DEFAULT_SOURCE

#include <ctype.h>
#include <time.h>
#include "riotUnits.h"
#include "riotUI.h"


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


void *dequeue(struct UnitList *queue) {

    struct UnitNode *tempNode;
    void *request = NULL;

    if (queue->count) {
        tempNode = queue->tail->prev;
        if (!tempNode) queue->head = NULL;
        request = queue->tail->unit;
        queue->count--;
        queue->tail = tempNode;
    }

    if (queue->head) queue->head->prev = NULL;

    return request;
}

void removeUnit(struct UnitList *list, int position) {
    struct UnitNode *nextNode, *temp;

    if (list->count <= position || list->count <= 0) {
        exit(1);
    }
    nextNode = getHead(list);
    if (position == 0) {
        free(list->head);
        list->head = NULL;
    }
    else {
        for (int i = 0; i < position - 1; i++) {
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
            unit->speed = 4;
            unit->rep = 0;
            unit->panic = 0;
            break;

        case HOMEBOY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 2;
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
            unit->speed = 2;
            unit->rep = 10;
            unit->panic = 8;
            break;

        case FATTY:
            unit->currentHealth = unit->maxHealth = 40;
            unit->speed = 8;
            unit->rep = 10;
            unit->panic = 4;
            break;

        case SPEEDY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 1;
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
            unit->speed = 4;
            unit->rep = 30;
            unit->panic = 2;
            break;

        case DOCTOR:
            unit->currentHealth = unit->maxHealth = 10;
            unit->speed = 4;
            unit->rep = 40;
            unit->panic = 2;
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
            guard->cooldownRemaining = 0;//guard->cooldown;
            guard->ai = PROX;
            guard->accuracy = 1;
            break;

        case DOGS:
            guard->damage = 4;
            guard->range = 4;
            guard->cooldown = 6;
            guard->cooldownRemaining = 0;//guard->cooldown;
            guard->ai = AOE;
            guard->accuracy = 1;
            break;

        case LUNCH:
            guard->damage = 0;
            guard->range = 6;
            guard->cooldown = 12;
            guard->cooldownRemaining = 0;//guard->cooldown;
            guard->ai = AOE;
            guard->accuracy = 1;
            break;

        case PSYCH:
            guard->damage = 0;
            guard->range = 6;
            guard->cooldown = 12;
            guard->cooldownRemaining = 0;//guard->cooldown;
            guard->ai = PROX;
            guard->accuracy = 1;
            break;

        case SHARP:
            guard->damage = 6;
            guard->range = 10;
            guard->cooldown = 8;
            guard->cooldownRemaining = 0;//guard->cooldown;
            guard->ai = END;
            guard->accuracy = 1;
            break;

        case WARDEN:
            guard->damage = 100;
            guard->range = 8;
            guard->cooldown = 20;
            guard->cooldownRemaining = 0;//guard->cooldown;
            guard->ai = PROX;
            guard->accuracy = 1;
            break;

        case CYBORG:
            guard->damage = 12;
            guard->range = 8;
            guard->cooldown = 2;
            guard->cooldownRemaining = 0;//guard->cooldown;
            guard->ai = PROX;
            guard->accuracy = 1;
            break;

        default:
            quit("Creating unsupported unit type");
            break;
    }

    return guard;
}



enum GameMode simulate(struct Windows *gameInterface, struct UnitList *guards,
                       struct UnitList *queued, struct Path *path,
                       struct Map *map) {

    struct UnitList deployed;
    int elapsed = 1;
    struct timespec delay;
    enum GameMode winCondition = WIN; //TODO placeholder, revise

    deployed.count = 0;

    /* Set update interval frequency */
    delay.tv_sec = 0;
    delay.tv_nsec = CYCLE;

    /* Deploy first unit */
    enqueue(&deployed, dequeue(queued));

    /* Begin simulation loop; run while units left on game board */
    do {

        /* Deploy next unit */
        if (queued->count && !(elapsed % REL_DELAY))
            enqueue(&deployed, dequeue(queued));

        /* Process inmate moves */
        if(elapsed%2) inmateMove(&deployed, path);

        /* Process guard attacks */
//      else guardAttack(guards, &deployed);

        /* Update display */
        gameplayRefresh(gameInterface->body, map, guards, &deployed, path);

        /* Sleep, increment elapsed time */
        nanosleep(&delay, NULL);
        elapsed++;

    } while (deployed.count);

    return winCondition;
}

/*Moves the units through the map and calls 'inmateRedraw to draw/erase the
 units*/
void inmateMove(struct UnitList *inmates, struct Path *path) {
    struct UnitNode *inmateN;
    struct TileNode *tileN;
    struct Inmate *inmate;
    float lastPos;

    /* Start with first inmate in list */
    inmateN = getHead(inmates);

    /* Iterate through list of inmates */
    do {

        inmate = inmateN->unit; //prevents having to do crazy casting

        /* Find inmate's placement on path */
        tileN = path->first; //starting with path origin
        for (int i = 0; i < path->count; i++) {
            if (tileN->location == (int) inmate->position) break;
            tileN = tileN->next;
        }

        /* Save current position for later */
        lastPos = ((struct Inmate *) inmateN->unit)->position;

        /* Move inmate based on its speed */
        inmate->position += (float) inmate->speed / 8;

        // TODO: document and revise cases below
        if (tileN->next
            && inmate->position == (int) lastPos + 1
            && tileN->next->type == '#'
            && inmate->doorSmash == 3) {
            inmate->position = tileN->next->location;
            inmate->doorSmash = 0;

        } else if (tileN->next
                   && (int) inmate->position == (int) lastPos + 1
                   && tileN->next->type == '#'
                   && inmate->doorSmash != 3) {
            inmate->position = (int) lastPos;
            inmate->doorSmash++;


        } else if (tileN->next->type != '&'
                   && (int) inmate->position == (int) lastPos + 1) {
            inmate->position = tileN->next->location;

        } else if (tileN->next->type == '&'
                   && inmate->position == (int) lastPos + 1) {
//            inmate->reachedEnd = TRUE;
            inmate->position = tileN->location;
            inmateN = getNext(inmateN);
        }

    } while (getNext(inmateN));
}


/*void setDeadInmates(struct UnitList *inmateList) {
    struct UnitNode *nextInmate;

    nextInmate = getHead(inmateList);
    for (int i = 0; i < inmateList->count; i++) {
        if (((struct Inmate *) nextInmate->unit)->currentHealth <= 0) {
//            ((struct Inmate *) nextInmate->unit)->dead = true;
        }
    }
}*/

void updateGuardAccuracy(struct UnitList *guardList, int currentPanic,
    int maximumPanic) {
    struct UnitNode *nextNode;
    struct Guard *nextGuard;

    nextNode = getHead(guardList);
    nextGuard = (struct Guard *) nextNode->unit;
    for (int j = 0; j < guardList->count; j++) {
        nextGuard->accuracy = (double) currentPanic / (double) maximumPanic;
        if (nextNode->next != NULL) {
            nextNode = nextNode->next;
        }
        nextGuard = (struct Guard *) nextNode->unit;
    }
}

void guardAttack(struct UnitList *guardList, struct UnitList *inmateList,
     struct Map map,struct Path path) {
    struct UnitNode *nextGuard;

    int exitPosition;
    exitPosition = path.last->location;

    nextGuard = getHead(guardList);
    for (int j=0;j<guardList->count;j++){
        switch(((struct Guard*)nextGuard->unit)->ai){
            case PROX:
                guardAttackProximity(nextGuard,inmateList);
                break;
            case AOE:
                guardAttackAOE(nextGuard,inmateList);
                break;
            case END:
                guardAttackEnd(nextGuard,inmateList,exitPosition);
                break;
            default:
                exit(1);
                break;
        }
        if (getNext(nextGuard) != NULL){
            nextGuard = getNext(nextGuard);
        }
    }

   // setDeadInmates(inmateList);
}

void guardAttackAOE(struct UnitNode *guardNode,
    struct UnitList *inmateList) {
    int i;
    struct UnitNode *nextInmate;

    if (((struct Guard *) guardNode->unit)->cooldownRemaining == 0) {
        if (tryAttack(*guardNode)){
            nextInmate = getHead(inmateList);
            for (i = 0; i < inmateList->count; i++) {
                if (inRange(nextInmate, guardNode)) {
                    dealDamage(nextInmate, guardNode);
                }
                if (getNext(nextInmate) != NULL) {
                    nextInmate = getNext(nextInmate);
                }
            }
        }
        ((struct Guard *) guardNode->unit)->cooldownRemaining = ((struct Guard *) guardNode->unit)->cooldown;
    }
    else {
        ((struct Guard *) guardNode->unit)->cooldownRemaining -= 1;
    }
}

struct UnitNode* getClosestInmateToPosition(struct UnitList inmateList, int position){
    int i,distance,lowestDistance = MAP_COLS * MAP_ROWS + 1;
    struct UnitNode *nextUnit,*closestUnit;
    struct Inmate *nextInmate;

    nextUnit = getHead(&inmateList);
    nextInmate = nextUnit->unit;


    for (i=0;i<inmateList.count;i++){
        distance = getDistance(position,nextInmate->position);
        if (distance < lowestDistance){
            closestUnit = nextUnit;
        }
        if (getNext(nextUnit) != NULL){
            nextUnit = getNext(nextUnit);
        }
    }

    return closestUnit;
}

int getDistance(int positionFrom,int positionTo){

    int xDifference,yDifference;

    yDifference = (((positionFrom - 1) / MAP_COLS) + 1) - (((positionTo - 1) / MAP_COLS) + 1);
    xDifference = abs(positionFrom - ((((positionFrom - 1) / MAP_COLS) + 1) * MAP_COLS))
                 - abs(positionTo - ((((positionTo - 1) / MAP_COLS) + 1) * MAP_COLS));
    yDifference = abs(yDifference);
    xDifference = abs(xDifference);
    return xDifference + yDifference;

}

void guardAttackEnd(struct UnitNode *guardNode,
    struct UnitList *inmateList,int exitPosition) {
    struct UnitList inRangeList;   
    struct UnitNode *nextUnit,*unitToAttack;
    struct Inmate *nextInmate;
    int i;
    bool attacked = false;

    inRangeList.count = 0;
    inRangeList.head = NULL;
    inRangeList.tail = NULL;

    nextUnit = getHead(inmateList);
    nextInmate = nextUnit->unit;

    if (((struct Guard *) guardNode->unit)->cooldownRemaining == 0) {
        if (tryAttack(*guardNode)){
            //Get all the units in range and enqueue them into a list
            for (i=0;i<inmateList->count;i++){
                if(inRange(nextUnit,guardNode)){
                    attacked = true;
                    enqueue(&inRangeList,nextInmate);
                }
                if (getNext(nextUnit) != NULL){
                    nextUnit = getNext(nextUnit);
                }
            }
        }
        ((struct Guard *) guardNode->unit)->cooldownRemaining = ((struct Guard *) guardNode->unit)->cooldown;
    }
    else{
        ((struct Guard *) guardNode->unit)->cooldownRemaining -= 1;
    }

    //Get the closest inmate to exit and attack
    if (attacked){
        unitToAttack = getClosestInmateToPosition(inRangeList,exitPosition);
        dealDamage(unitToAttack,guardNode);
    }
}

void guardAttackProximity(struct UnitNode *guardNode,
    struct UnitList *inmateList) {
    struct UnitList inRangeList;   
    struct UnitNode *nextUnit,*unitToAttack;
    struct Inmate *nextInmate;
    int i;
    bool attacked = false;

    inRangeList.count = 0;
    inRangeList.head = NULL;
    inRangeList.tail = NULL;

    nextUnit = getHead(inmateList);
    nextInmate = nextUnit->unit;

    if (((struct Guard *) guardNode->unit)->cooldownRemaining == 0) {
        if (tryAttack(*guardNode)){
            //Get all the units in range and enqueue them into a list
            for (i=0;i<inmateList->count;i++){
                if(inRange(nextUnit,guardNode)){
                    enqueue(&inRangeList,nextInmate);
                    attacked = true;
                }
                if (getNext(nextUnit) != NULL){
                    nextUnit = getNext(nextUnit);
                }
            }
        }
        ((struct Guard *) guardNode->unit)->cooldownRemaining = ((struct Guard *) guardNode->unit)->cooldown;
    }
    else{
        ((struct Guard *) guardNode->unit)->cooldownRemaining -= 1;
    }
    //Get the closest inmate to exit and attack
    if (attacked){
        #ifdef _DEBUGN
        printf("In Range List Size: %d\n",inRangeList.count);
        #endif
        unitToAttack = getClosestInmateToPosition(inRangeList,((struct Guard*)guardNode->unit)->position);
        dealDamage(unitToAttack,guardNode);
    }
}

bool tryAttack(struct UnitNode guardNode) {
    float missChance, guardAccuracy;
    time_t t;

    srand((unsigned) time(&t));
    guardAccuracy = ((struct Guard *) guardNode.unit)->accuracy;
    missChance = 100 - (guardAccuracy * 100);

    return (rand() % 100) > missChance;
}


void dealDamage(struct UnitNode *inmateNode, struct UnitNode *guardNode) {
    int currentHealth;
    int damage;


    currentHealth = ((struct Inmate *) inmateNode->unit)->currentHealth;
    damage = ((struct Guard *) guardNode->unit)->damage;
    ((struct Inmate *) inmateNode->unit)->currentHealth =
        currentHealth - damage;
}


bool inRange(struct UnitNode *inmate, struct UnitNode *guard) {
    int inmatePosition;
    int guardPosition;
    int range;
    int xDifference, yDifference;
    int inmateY, guardY;
    int totalDifference;

    inmatePosition = ((struct Inmate *) inmate->unit)->position;
    guardPosition = ((struct Guard *) guard->unit)->position;
    range = ((struct Guard *) guard->unit)->range;

    inmateY = (inmatePosition - 1) / MAP_COLS;
    guardY = (guardPosition - 1) / MAP_COLS;
    yDifference = (inmateY + 1) - (guardY + 1);
    xDifference = abs(guardPosition - (guardY * MAP_COLS)) -
                  abs(inmatePosition - (inmateY * MAP_COLS));
    yDifference = abs(yDifference);
    xDifference = abs(xDifference);
    totalDifference = xDifference + yDifference;

    return range >= totalDifference;
}


struct UnitList *getGuards(struct UnitList *guards, struct Map map) {

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
            }
        }
    }

    return guards;
}
