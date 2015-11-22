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

    /*If a remove is requested from a position not within
      the list, exit the program */
    if (list->count <= position || list->count <= 0) {
        exit(1);
    }

    /*Remove head from list and free memory*/
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
    /*Remove tail from list and free memory*/
    } else if (position  == list->count - 1) {
        temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp);
    /*Remove node from list that is not the head or tail
       and free memory*/
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

    /*Return node at position within a list*/
    for (int i = 0; i < position - 1; i++) {
        if (target->next != NULL){
            target = target->next;
        }
    }

    return target;
}

struct UnitNode *pop(struct UnitList *stack) {

    struct UnitNode *tempNode, *request = NULL;

    /*Remove top of stack*/
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

    /*Create inmate based on the type that is passed in to the 
      function and initialize its values, than return the Inmate*/
    switch (type) {

        case PROTAGONIST:
            unit->currentHealth = unit->maxHealth = 5;
            unit->rep = REP_PROTAGONIST;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 0;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = false;
            break;

        case HOMEBOY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->rep = REP_HOMEBOY;
            unit->speed = 2;
            unit->maxSpeed = unit->speed;
            unit->panic = 2;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = false;
            break;

        case BRUISER:
            unit->currentHealth = unit->maxHealth = 16;
            unit->rep = REP_BRUISER;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 6;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = false;
            break;

        case LUNATIC:
            unit->currentHealth = unit->maxHealth = 16;
            unit->rep = REP_LUNATIC;
            unit->speed = 2;
            unit->maxSpeed = unit->speed;
            unit->panic = 8;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = false;
            break;

        case FATTY:
            unit->currentHealth = unit->maxHealth = 40;
            unit->rep = REP_FATTY;
            unit->speed = 8;
            unit->maxSpeed = unit->speed;
            unit->panic = 4;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = false;
            break;

        case SPEEDY:
            unit->currentHealth = unit->maxHealth = 10;
            unit->rep = REP_SPEEDY;
            unit->rep = 20;
            unit->speed = 1;
            unit->maxSpeed = unit->speed;
            unit->panic = 2;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = false;
            break;

        case CUTIE:
            unit->currentHealth = unit->maxHealth = 20;
            unit->rep = REP_CUTIE;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 1;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = false;
            break;

        case ATTORNEY:
            unit->currentHealth = unit->maxHealth = 30;
            unit->rep = REP_ATTORNEY;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 2;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = false;
            break;

        case DOCTOR:
            unit->currentHealth = unit->maxHealth = 10;
            unit->rep = REP_DOCTOR;
            unit->speed = 4;
            unit->maxSpeed = unit->speed;
            unit->panic = 2;
            unit->doubleDamage = 0;
            unit->slowedCounter = 0;
            unit->sleepCounter = 0;
            unit->healCooldown = 0;
            unit->healer = true;
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

    /*Create Guard based on the type that is passed in to the 
      function and initialize its values, than return the Guard*/

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
    bool moveUnit,inmateSlowed;
    
    nextUnit = getHead(inmates);
    nextInmate = nextUnit->unit; 
    nextInmate->position = nextInmate->currentTile->location;

    /* Iterate through list of inmates */
    for (int i=0;i<inmates->count;i++){
        moveUnit = true;
        inmateSlowed = false;

        otherUnit = getHead(inmates);
        otherInmate = otherUnit->unit;
        /*If the unit is a healer and the cooldown is greater than 0 than decrement it*/
        if (nextInmate->healCooldown > 0 && nextInmate->healer == true){
            nextInmate->healCooldown -= 1;
        }
        /*If the inmate is asleep than do not move and decrement the counter*/
        if (nextInmate->sleepCounter > 0){
            nextInmate->sleepCounter -= 1;
            moveUnit = false;
        }
        /*If the inmate is slowed than decrement slowed counter*/
        if (nextInmate->slowedCounter > 0){
            nextInmate->slowedCounter -= 1;
            inmateSlowed = true;
        }
        /*Iterate through list of inamtes that are being compared*/
        for (int j=0;j<inmates->count;j++){
            /*If another inmate exists with the location of the tile the current
              inmate is going to move to, set move to false and break*/
            if (nextInmate->currentTile->next->location == otherInmate->currentTile->location){
                moveUnit = false;
                /*If next inmate is a doctor and cooldown is 0 than heal the unit in front*/
                if (nextInmate->healer == true && nextInmate->healCooldown == 0){
                    otherInmate->currentHealth += 10;
                    if (otherInmate->currentHealth > otherInmate->maxHealth){
                        otherInmate->currentHealth = otherInmate->maxHealth;
                    }
                }
                break;
            }
            if (getNext(otherUnit) != NULL){
                otherUnit = getNext(otherUnit);
                otherInmate = otherUnit->unit;
            }
        }
        /*If move was not set to false than perform moving logic*/
        if (moveUnit){

            switch(nextInmate->currentTile->next->type){
                /*If the tile being moved to is the final tile in the path
                  than set reached end to true*/
                case '&':
                    nextInmate->reachedEnd = true;
                    break;
                /*If the tile being moved to is a door than damage the door*/
                case '#':
                    if (nextInmate->currentTile->next->durability > 0){
                        nextInmate->currentTile->next->durability -= 1;
                    }
                    else{
                        nextInmate->currentTile = nextInmate->currentTile->next;
                        nextInmate->position = nextInmate->currentTile->location;    
                    }
                    break;
                /*If the tile being to is a movable tile type than move to the
                  next tile and set the inmates position to that tiles location*/
                case '%':
                case '.':
                    /*Check for the inmate being slowed, if the inmate is being slowed
                       than increase the wait time to move*/
                    if(!(elapsed%(nextInmate->speed + (nextInmate->speed*inmateSlowed*2)))) {
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
    /*Iterate through inmates and remove all dead inmates*/
    for (int i = 0; i < inmateList->count; i++) {
        if (((struct Inmate *) nextInmate->unit)->currentHealth <= 0) {
          //  removeUnit(inmateList,i);
            ((struct Inmate*)nextInmate->unit)->dead = true;
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
    /*Iterate through guards and update every guards accuracy to the inverse
      of the percentage of panic present*/
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

        /*If cooldown is 0 than attack and perform special abilities on inmates*/
        if (((struct Guard *)nextGuard->unit)->cooldownRemaining == 0 &&
         inmateExistsInRange(*inmateList,*nextGuard)) {

            /*Attempts to attack based on current guard accuracy*/
            if (tryAttack(*nextGuard)){
                /*Apply different attack types based on the guards attack type*/
                switch(((struct Guard*)nextGuard->unit)->ai){
                    /*Attack closest inmate to guard that is in range*/
                    case PROX:
                        guardAttackProximity(nextGuard,inmateList);
                        break;
                    /*Attack all inmates within the guards range*/
                    case AOE:
                        guardAttackAOE(nextGuard,inmateList);
                        break;
                    /*Attack the inmate that is within range and closest to the end of
                      the path*/
                    case END:
                        guardAttackEnd(nextGuard,inmateList,exitPosition);
                        break;
                    default:
                        exit(1);
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
    /*Set all inmates that are below 1 health to dead*/
    setDeadInmates(inmateList);
}

void guardAttackAOE(struct UnitNode *guardNode,
    struct UnitList *inmateList) {
    int i;
    struct UnitNode *nextInmate;

    nextInmate = getHead(inmateList);
    /*Iterate through all inmates*/
    for (i = 0; i < inmateList->count; i++) {
        /*If the inmates position is within the range of the guard*/
        if (inRange(nextInmate, guardNode)) {
            /*Deal damage to the inmate*/
            dealDamage(nextInmate, guardNode);
            /*If the guard is a lunch lady than apply the lunch lady debuff*/
            if (((struct Guard*)guardNode->unit)->type == LUNCH){
                ((struct Inmate*)nextInmate->unit)->slowedCounter = EFFECT_LUNCH;
            }
        }
        if (getNext(nextInmate) != NULL) {
            nextInmate = getNext(nextInmate);
        }
    }
    /*Reset cooldown*/
    if (((struct Guard *)guardNode->unit)->cooldownRemaining == 0){
        ((struct Guard *) guardNode->unit)->cooldownRemaining = 
        ((struct Guard *) guardNode->unit)->cooldown;
    }
}

struct UnitNode* getClosestInmateToPosition(struct UnitList inmateList, int position){
    int i,distance,lowestDistance = MAP_COLS * MAP_ROWS + 1;
    struct UnitNode *nextUnit,*closestUnit;
    struct Inmate *nextInmate;

    nextUnit = getHead(&inmateList);
    nextInmate = nextUnit->unit;

    /*Iterate through inmates*/
    for (i=0;i<inmateList.count;i++){
        /*Get the distance of the current inmate*/
        distance = (getDistance(position,nextInmate->position));
        /*Get the closest unit*/
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

    /*Calculate the vertical value of the position from*/
    fromY = ((positionFrom - 1) / MAP_COLS);
    /*Calculate the vertical value of the position to*/
    toY = ((positionTo - 1) / MAP_COLS);
    /*Calculate the vertical difference between the positions*/
    yDifference = (fromY + 1) - (toY + 1);
    /*Calculate the horizontal difference between the positions*/
    xDifference = abs(positionFrom - (fromY * MAP_COLS))
                 - abs(positionTo - (toY * MAP_COLS));
    yDifference = abs(yDifference);
    xDifference = abs(xDifference);
    /*Return the total distance*/
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

    /*Iterate through all the inmates in the list*/
    for (i=0;i<inmateList->count;i++){
        /*Add all inmates in range of the guard to the inrange queue*/
        if(inRange(nextUnit,guardNode)){
            attacked = true;
            enqueue(&inRangeList,nextInmate);
        }
        if (getNext(nextUnit) != NULL){
            nextUnit = getNext(nextUnit);
        }
    }
    /*Reset the cooldown*/
    if (((struct Guard *)guardNode->unit)->cooldownRemaining == 0){
        ((struct Guard *) guardNode->unit)->cooldownRemaining = 
        ((struct Guard *) guardNode->unit)->cooldown;
    }

    /*Get the closest inmate to the guard in the inrange queue and deal damage*/
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

    /*Iterate through all the inmates in the list*/
    for (i=0;i<inmateList->count;i++){
        /*Add all inmates in range of the guard to the inrange queue*/
        if(inRange(nextUnit,guardNode)){
            enqueue(&inRangeList,nextInmate);
            attacked = true;
        }
        if (getNext(nextUnit) != NULL){
            nextUnit = getNext(nextUnit);
            nextInmate = nextUnit->unit;
        }
    }

    /*Reset the cooldown*/
    if (((struct Guard *)guardNode->unit)->cooldownRemaining == 0){
        ((struct Guard *) guardNode->unit)->cooldownRemaining =  
        ((struct Guard *) guardNode->unit)->cooldown;
    }

    /*Get the closest inmate to the last position in the path
        inside inrange queue and deal damage*/
    if (attacked){

        #ifdef _DEBUGN
        printf("In Range List Size: %d\n",inRangeList.count);
        #endif

        unitToAttack = getClosestInmateToPosition(inRangeList,
            ((struct Guard*)guardNode->unit)->position);

        dealDamage(unitToAttack,guardNode);
        /*Apply special ability debuff on the inmate if the guard attacking has special ability*/
        if (((struct Guard*)guardNode->unit)->type == PSYCH){
            ((struct Inmate*)unitToAttack->unit)->sleepCounter = EFFECT_PSYCH;
        }
        else if(((struct Guard*)guardNode->unit)->type == DOGS){
            ((struct Inmate*)unitToAttack->unit)->doubleDamage = EFFECT_DOGS;
        }
    }
}

bool tryAttack(struct UnitNode guardNode) {
    float missChance, guardAccuracy;

    /*Generate a number from 1-100, if the number lands higher than the missChance
      than return true*/
    guardAccuracy = ((struct Guard *) guardNode.unit)->accuracy;
    missChance = 100 - (guardAccuracy * 100);

    return (rand() % 100) > missChance;
}


void dealDamage(struct UnitNode *inmateNode, struct UnitNode *guardNode) {
    int currentHealth;
    int damage;

    /*Reduce the inmates dealth by the guards damage*/
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

    /*Calculate the vertical position of the inmate*/
    inmateY = (inmatePosition - 1) / MAP_COLS;
    /*Calculate the vertical position of the guard*/
    guardY = (guardPosition - 1) / MAP_COLS;
    /*Calculate vertical difference between the inmate and the guard*/
    yDifference = (inmateY + 1) - (guardY + 1);
    /*Calculate the horizontal difference between the inmate and the guard*/
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
    /*Iterate through inmate list*/
    for (i=0;i<inmateList.count;i++){
        inmatePosition = ((struct Inmate*)nextUnit->unit)->position;
        guardPosition = ((struct Guard*)guard.unit)->position;
        range = ((struct Guard*)guard.unit)->range;

        /*Calculate the y position of inmate*/
        inmateY = (inmatePosition - 1) / MAP_COLS;
        /*Calculate the y position of*/
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

    /*Iterate through the map overlay*/
    for (i = 0; i < MAP_ROWS; i++) {
        for (j = 0; j < MAP_COLS; j++) {
            position = (i * MAP_COLS) + j;
            mapChar = toupper(map.overlay[i][j]);
            /*If the map overlay character being parsed is an alpha character
              than create a guard, considering only guards can be alpha characters*/
            if (isalpha(mapChar)) {
                guard = createGuard(mapChar);
                guard->position = position;
                enqueue(guards, guard);
            }
        }
    }

    return guards;
}
