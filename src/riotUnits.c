#define _DEFAULT_SOURCE

#include <ctype.h>
#include <time.h>
#include "riotUnits.h"
#include "riotUI.h"

void writeToFile(char *string){
    FILE *file;

    file = fopen("temp.txt","a+");

    fprintf(file,"%s\n",string);
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
    struct UnitNode *temp, *target;

    if (list->count <= position || list->count <= 0) {
        exit(1);
    }
    //nextNode = getHead(list);
    if (position == 0) {
        if (list->head->next != NULL) {
            temp = list->head;
            list->head = list->head->next;
            list->head->prev = NULL;
            free(temp);
        } else {
            list->head = NULL;
            list->tail = NULL;
        }
    } else if (position  == list->count - 1) {
        temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);
    } else {
        target = moveTo(position - 1, list);
        temp = target->next;
        target->next = target->next->next;
        target->next->prev = target;
        free(temp);
    }
    list->count--;
}

struct UnitNode *moveTo(int position, struct UnitList *list) {
    struct UnitNode *target;
    target = list->head;
    for (int i = 0; i < position - 1; i++) {
        if (target->next != NULL){
            target = target->next;
        }
    }
    return target;
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


struct Inmate *createInmate(enum InmateType type) {

    struct Inmate *unit = malloc(sizeof(struct Inmate));

    unit->type = type;
    unit->position = -1;
    unit->dead = FALSE;
    unit->reachedEnd = FALSE;

    switch (type) {

        case PROTAGONIST:
            unit->currentHealth = unit->maxHealth = 5;
            unit->rep = REP_PROTAGONIST;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 0;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            break;

        case HOMEBOY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->rep = REP_HOMEBOY;
            unit->speed = 2;
            unit->maxSpeed = unit->speed;
            unit->panic = 2;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            break;

        case BRUISER:
            unit->currentHealth = unit->maxHealth = 16;
            unit->rep = REP_BRUISER;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 6;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            break;

        case LUNATIC:
            unit->currentHealth = unit->maxHealth = 16;
            unit->rep = REP_LUNATIC;
            unit->speed = 2;
            unit->maxSpeed = unit->speed;
            unit->panic = 8;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            break;

        case FATTY:
            unit->currentHealth = unit->maxHealth = 40;
            unit->rep = REP_FATTY;
            unit->speed = 8;
            unit->maxSpeed = unit->speed;
            unit->panic = 4;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            break;

        case SPEEDY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->rep = REP_SPEEDY;
            unit->rep = 20;
            unit->speed = 1;
            unit->maxSpeed = unit->speed;
            unit->panic = 2;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            break;

        case CUTIE:
            unit->currentHealth = unit->maxHealth = 20;
            unit->rep = REP_CUTIE;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 1;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            break;

        case ATTORNEY:
            unit->currentHealth = unit->maxHealth = 30;
            unit->rep = REP_ATTORNEY;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 2;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            break;

        case DOCTOR:
            unit->currentHealth = unit->maxHealth = 10;
            unit->rep = REP_DOCTOR;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 2;
            unit->doubleDamageCounter = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
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
    struct UnitNode *inmate,*nextUnit;
    int elapsed = 1;
    struct timespec delay;
    enum GameMode winCondition = WIN; //TODO placeholder, revise
    FILE *file;
    file = fopen("temp.txt","a+");

    deployed.count = 0;

    /* Set update interval frequency */
    delay.tv_sec = 0;
    delay.tv_nsec = CYCLE;

    /* Deploy first unit */
    nextUnit = getHead(queued);
    for (int i=0;i<queued->count;i++){
        ((struct Inmate*)nextUnit->unit)->currentTile = path->first;
        if (getNext(nextUnit) != NULL){
            nextUnit = getNext(nextUnit);
        }
    }
    enqueue(&deployed, dequeue(queued));

    /* Begin simulation loop; run while units left on game board */
    do {
       /* Deploy next unit */
        if (queued->count && !(elapsed % REL_DELAY))
            enqueue(&deployed, dequeue(queued));

        /* Process inmate moves (every other pass) */
        if (!(elapsed % 4)) inmateMove(&deployed, elapsed);

        /* Process guard attacks (every other pass) */
        else if (!(elapsed %5))
        {
            updateGuardAccuracy(guards, map->panicCur, map->panicMax);
            guardAttack(guards, &deployed, *path);

        } 

        inmate = getHead(&deployed);
        for (int i = 0; i < deployed.count; i++) {

            /* Remove dead inmates from the board */
            if (((struct Inmate *) inmate->unit)->dead) {
                removeUnit(&deployed, i);
            }

            /* Remove exited inmates from the board */
            if (((struct Inmate *) inmate->unit)->reachedEnd) {
                map->panicCur += ((struct Inmate *) inmate->unit)->panic;
                removeUnit(&deployed, i);
                updateGuardAccuracy(guards, map->panicCur, map->panicMax);
                updateHeader(gameInterface->header,map);
            }

            if (inmate->next) inmate = inmate->next;
        }

        /* Update display */
        gameplayRefresh(gameInterface->body, map, guards, &deployed, path);

        /* Sleep, increment elapsed time */
        nanosleep(&delay, NULL);
        elapsed++;

    } while (deployed.count);

    return winCondition;
}

void inmateMove(struct UnitList *inmates, int elapsed) {

    struct UnitNode *nextUnit,*otherUnit;
    struct Inmate *nextInmate,*otherInmate;
    bool moveUnit;
    
    nextUnit = getHead(inmates);
    nextInmate = nextUnit->unit; 
    nextInmate->position = nextInmate->currentTile->location;
    /* Iterate through list of inmates */
    for (int i=0;i<inmates->count;i++){

        moveUnit = true;
        //printf("POSITION OF INMATE: %d\n",nextInmate->);
        otherUnit = getHead(inmates);
        otherInmate = otherUnit->unit;
        for (int j=0;j<inmates->count;j++){
            if (nextInmate->currentTile->next->location == otherInmate->currentTile->location){
                moveUnit = false;
                break;
            }
            if (getNext(otherUnit) != NULL){
                otherUnit = getNext(otherUnit);
                otherInmate = otherUnit->unit;
            }
        }
        if (moveUnit){

            switch(nextInmate->currentTile->next->type){
                case '&':
                    nextInmate->reachedEnd = true;
                    break;
                case '#':
                    if (nextInmate->currentTile->next->durability > 0){
                        nextInmate->currentTile->next->durability -= 1;
                    }
                    else{
                        nextInmate->currentTile = nextInmate->currentTile->next;
                        nextInmate->position = nextInmate->currentTile->location;    
                    }
                    break;
                case '%':
                case '.':
                    if(!(elapsed%nextInmate->speed)) {
                        nextInmate->currentTile = nextInmate->currentTile->next;
                        nextInmate->position = nextInmate->currentTile->location;
                    }
                    break;
                default: quit("Attempted move to undefined tile");
            }
        }
        if (getNext(nextUnit) != NULL){
            nextUnit = getNext(nextUnit);
            nextInmate = nextUnit->unit;
        }   
    }
    return;
}

void setDeadInmates(struct UnitList *inmateList) {
    struct UnitNode *nextInmate;

    if (getHead(inmateList) != NULL){
        nextInmate = getHead(inmateList);
    }
    for (int i = 0; i < inmateList->count; i++) {
        if (((struct Inmate *) nextInmate->unit)->currentHealth <= 0) {
            removeUnit(inmateList,i);
        }
        if (getNext(nextInmate) != NULL){
            nextInmate = nextInmate->next;
        }
    }
}

void updateGuardAccuracy(struct UnitList *guardList, int currentPanic,
    int maximumPanic) {
    struct UnitNode *nextNode;
    struct Guard *nextGuard;

    nextNode = getHead(guardList);
    nextGuard = (struct Guard *) nextNode->unit;
    for (int j = 0; j < guardList->count; j++) {
        nextGuard->accuracy = 1 - ((double) currentPanic / (double) maximumPanic);
        if (nextNode->next != NULL) {
            nextNode = nextNode->next;
        }
        nextGuard = (struct Guard *) nextNode->unit;
    }
}

void guardAttack(struct UnitList *guardList, struct UnitList *inmateList,struct Path path) {
    struct UnitNode *nextGuard;
    int exitPosition;

    exitPosition = path.last->location;

    nextGuard = getHead(guardList);
    for (int j=0;j<guardList->count;j++){

        #ifdef _DEBUGN
        if (inmateExistsInRange(*inmateList,*nextGuard)){
            printf("Inmate exists in range!\n");
        }
        else{
            printf("No inmates exist in range!\n");
        }
        printf("Cooldown before decrement is: %d\n",((struct Guard *)nextGuard->unit)->cooldownRemaining);
        #endif

        //if cooldown is 0 attack and perform special abilities
        if (((struct Guard *)nextGuard->unit)->cooldownRemaining == 0 && inmateExistsInRange(*inmateList,*nextGuard)) {
            if (tryAttack(*nextGuard)){
                //Perform attack
                switch(((struct Guard*)nextGuard->unit)->ai){
                    case PROX:
                        // printf("PROX \n Guard Type: %c\n",
                        //      ((struct Guard*)nextGuard->unit)->type);
                        guardAttackProximity(nextGuard,inmateList);
                        break;
                    case AOE:
                        // printf("AOE \n Guard Position: %d\n",
                        //     ((struct Guard*)nextGuard->unit)->position);
                        guardAttackAOE(nextGuard,inmateList);
                        break;
                    case END:
                        //printf("END \n Guard Type: %c\n",
                        //    ((struct Guard*)nextGuard->unit)->type);
                        guardAttackEnd(nextGuard,inmateList,exitPosition);
                        break;
                    default:
                        exit(1);
                        break;
                }
                //Perform special abilities
                switch(((struct Guard*)nextGuard->unit)->type){
                    case DOGS:
                        //Double further damage once
                        break;
                    case LUNCH:
                        //Slow down speed by half for 12 cycles.
                        break;
                    case PSYCH:
                        //Inmates sleep for 6 cycles.
                        break;

                }
            }
        }
        else if (((struct Guard *)nextGuard->unit)->cooldownRemaining != 0){
            ((struct Guard *) nextGuard->unit)->cooldownRemaining -= 1;
        }

        #ifdef _DEBUBN
        printf("Cooldown after decrement is: %d\n",((struct Guard *)nextGuard->unit)->cooldownRemaining);
        #endif

        if (getNext(nextGuard) != NULL){
            nextGuard = getNext(nextGuard);
        }
    }

    setDeadInmates(inmateList);
}

void guardAttackAOE(struct UnitNode *guardNode,
    struct UnitList *inmateList) {
    int i;
    struct UnitNode *nextInmate;

    nextInmate = getHead(inmateList);
    for (i = 0; i < inmateList->count; i++) {
        if (inRange(nextInmate, guardNode)) {
            dealDamage(nextInmate, guardNode);
            //Apply special ability if it is a lunch lady
            if (((struct Guard*)guardNode->unit)->type == LUNCH){
                ((struct Inmate*)nextInmate->unit)->slowedCounter = EFFECT_LUNCH;
            }
        }
        if (getNext(nextInmate) != NULL) {
            nextInmate = getNext(nextInmate);
        }
    }
    if (((struct Guard *)guardNode->unit)->cooldownRemaining == 0){
        ((struct Guard *) guardNode->unit)->cooldownRemaining = ((struct Guard *) guardNode->unit)->cooldown;
    }
}

struct UnitNode* getClosestInmateToPosition(struct UnitList inmateList, int position){
    int i,distance,lowestDistance = MAP_COLS * MAP_ROWS + 1;
    struct UnitNode *nextUnit,*closestUnit;
    struct Inmate *nextInmate;

    nextUnit = getHead(&inmateList);
    nextInmate = nextUnit->unit;


    for (i=0;i<inmateList.count;i++){
        distance = (getDistance(position,nextInmate->position));
        if (distance < lowestDistance){
            closestUnit = nextUnit;
        }
        if (getNext(nextUnit) != NULL){
            nextUnit = getNext(nextUnit);
            nextInmate = nextUnit->unit;
        }
    }

    return closestUnit;
}

int getDistance(int positionFrom,int positionTo){

    int xDifference,yDifference;
    int fromY,toY;

    fromY = ((positionFrom - 1) / MAP_COLS);
    toY = ((positionTo - 1) / MAP_COLS);
    yDifference = (fromY + 1) - (toY + 1);
    xDifference = abs(positionFrom - (fromY * MAP_COLS))
                 - abs(positionTo - (toY * MAP_COLS));
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

    if (((struct Guard *)guardNode->unit)->cooldownRemaining == 0){
        ((struct Guard *) guardNode->unit)->cooldownRemaining = ((struct Guard *) guardNode->unit)->cooldown;
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

    //Get all the units in range and enqueue them into a list
    for (i=0;i<inmateList->count;i++){
        if(inRange(nextUnit,guardNode)){
            enqueue(&inRangeList,nextInmate);
            attacked = true;
        }
        if (getNext(nextUnit) != NULL){
            nextUnit = getNext(nextUnit);
            nextInmate = nextUnit->unit;
        }
    }

   // printf("In range list size: %d\n",inRangeList.count);

    if (((struct Guard *)guardNode->unit)->cooldownRemaining == 0){
        ((struct Guard *) guardNode->unit)->cooldownRemaining = 
        ((struct Guard *) guardNode->unit)->cooldown;
    }

    //Get the closest inmate to exit and attack
    if (attacked){
        #ifdef _DEBUGN
        printf("In Range List Size: %d\n",inRangeList.count);
        #endif
        unitToAttack = getClosestInmateToPosition(inRangeList,((struct Guard*)guardNode->unit)->position);
        dealDamage(unitToAttack,guardNode);
        //Apply special abilities if guard attacking has special ability
        if (((struct Guard*)guardNode->unit)->type == PSYCH){
            ((struct Inmate*)unitToAttack->unit)->sleepCounter = EFFECT_PSYCH;
        }
        else if(((struct Guard*)guardNode->unit)->type == DOGS){
            ((struct Inmate*)unitToAttack->unit)->sleepCounter = EFFECT_DOGS;
        }
    }
}

bool tryAttack(struct UnitNode guardNode) {
    float missChance, guardAccuracy;

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

bool inmateExistsInRange(struct UnitList inmateList,struct UnitNode guard){
    int inmatePosition,guardPosition, range;
    int xDifference, yDifference;
    int inmateY, guardY,totalDifference;
    int i;
    struct UnitNode* nextUnit;

    nextUnit = getHead(&inmateList);
    for (i=0;i<inmateList.count;i++){
        inmatePosition = ((struct Inmate*)nextUnit->unit)->position;
        guardPosition = ((struct Guard*)guard.unit)->position;
        range = ((struct Guard*)guard.unit)->range;

        inmateY = (inmatePosition - 1) / MAP_COLS;
        guardY = (guardPosition - 1) / MAP_COLS;
        yDifference = (inmateY +1) - (guardY + 1);
        xDifference = abs(guardPosition - (guardY * MAP_COLS)) -
                      abs(inmatePosition - (inmateY * MAP_COLS));
        yDifference = abs(yDifference);
        xDifference = abs(xDifference);
        totalDifference = xDifference + yDifference;
        if (totalDifference <= range){
            return true;
        }
        if (getNext(nextUnit) != NULL){
            nextUnit = getNext(nextUnit);
        }
    }

    return false;
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
