#include <time.h>
#include <ncurses.h>
#include "riotTesting.h"


int main(int argc, char **argv) {

    if (argc == 1) {
        testingHelp();
        printf("\nExiting.");
        exit(-1);
    }
    for (int i = 1; i < argc; i++) {

        if (argv[i][0] != '-')continue; //only process flags

//        if (!strcmp(argv[i], "-units")) unitsTest();
        else if (!strcmp(argv[i], "-map")) mapTest(argv[2] ? argv[2] : NULL);
        else if (!strcmp(argv[i], "-unitmove"))
            unitsMove(argv[2] ? argv[2] : NULL);
        else if (!strcmp(argv[i], "-color")) colorTest();
        else if (!strcmp(argv[i], "-guardtest"))guardTest();
//        else if (!strcmp(argv[i], "-logo")) logoTest();
        else if (!strcmp(argv[i], "-play")) unitsPlay(argv[2]);
        else printf("Unknown command (%s)\n", argv[i]);
    }

    printf("Testing done.\n");
    return 0;

}


void printPath(struct Path *path) {
    struct TileNode *nextNode;

    nextNode = path->first;
    printf("\n\n#### PRINTING PATH ####\n\n");
    for (int i = 0; i < path->count; i++) {
        printf("Location: %d :", nextNode->location);
        printf("Type: %c\n", nextNode->type);
        nextNode = nextNode->next;
    }
    printf("\n########################\n");
}


void printGuardList(struct UnitList *guardList) {
    struct UnitNode *nextNode;
    struct Guard *guard;

    nextNode = getHead(guardList);
    guard = (struct Guard *) nextNode->unit;
    printf("\nGuard List Size: %d\n", guardList->count);
    printf("\n\n#### PRINTING GUARDS ####\n\n");
    for (int i = 0; i < guardList->count; i++) {
        printf("Guard Type : %c\n", guard->type);
        printf("Location: %d\n", guard->position);
        printf("Damage: %d\n", guard->damage);
        printf("Range: %d\n", guard->range);
        printf("Cool Down: %d\n", guard->cooldown);
        printf("\n");
        if (nextNode->next != NULL) {
            nextNode = nextNode->next;
        }
        guard = (struct Guard *) nextNode->unit;
    }
    printf("\n########################\n");
}

void printInmateList(struct UnitList *inmateList) {
    struct UnitNode *nextNode;
    struct Inmate *inmate;

    nextNode = getHead(inmateList);
    inmate = (struct Inmate *) nextNode->unit;
    printf("\nInmate List Size: %d\n", inmateList->count);
    printf("\n\n#### PRINTING INMATES ####\n\n");
    for (int i = 0; i < inmateList->count; i++) {
        printf("Inmate Type : %c\n", inmate->type);
        printf("Location: %d\n", inmate->position);
        printf("\n");
        if (nextNode->next != NULL) {
            nextNode = nextNode->next;
        }
        inmate = (struct Inmate *) nextNode->unit;
    }
    printf("\n########################\n");
}


void colorTest() {
    initscr();
    start_color();
    init_pair(GREEN, GREEN, COLOR_BLACK);
    init_pair(YELLOW, YELLOW, COLOR_BLACK);
    init_pair(RED, RED, COLOR_BLACK);
    init_pair(PURPLE, PURPLE, COLOR_BLACK);
    init_pair(DAMAGED, COLOR_BLACK, DAMAGED);
    init_pair(20, GREEN, DAMAGED);
    init_pair(21, YELLOW, DAMAGED);
    init_pair(22, RED, DAMAGED);
    init_pair(23, PURPLE, DAMAGED);
    attron (COLOR_PAIR(GREEN));
    mvprintw(0, 0, "Green test Foreground: %d Background: %d", GREEN,
        COLOR_BLACK);
    attron (COLOR_PAIR(YELLOW));
    mvprintw(1, 0, "Yellow test");
    attron (COLOR_PAIR(RED));
    mvprintw(2, 0, "Red test");
    attron (COLOR_PAIR(PURPLE));
    mvprintw(3, 0, "Purple test");
    attron (COLOR_PAIR(DAMAGED));
    mvprintw(4, 0, "Damaged test Foreground: %d Background: %d\t", COLOR_BLACK,
        DAMAGED);
    attron (COLOR_PAIR(20));
    mvprintw(5, 0, "Damaged test Foreground: %d Background: %d\t", GREEN,
        DAMAGED);
    attron (COLOR_PAIR(21));
    mvprintw(6, 0, "Damaged test Foreground: %d Background: %d\t", YELLOW,
        DAMAGED);
    attron (COLOR_PAIR(22));
    mvprintw(7, 0, "Damaged test Foreground: %d Background: %d\t", RED,
        DAMAGED);
    attron (COLOR_PAIR(23));
    mvprintw(8, 0, "Damaged test Foreground: %d Background: %d\t", PURPLE,
        DAMAGED);
    refresh();
    getchar();
    endwin();
}

void guardTest(){
    struct UnitList guardList;

    /*Enqueue all avilable guards*/
    enqueue(&guardList,createGuard(LUNCH));
    enqueue(&guardList,createGuard(PSYCH));
    enqueue(&guardList,createGuard(GUARD));
    enqueue(&guardList,createGuard(DOGS));
    enqueue(&guardList,createGuard(SHARP));
    enqueue(&guardList,createGuard(WARDEN));
    enqueue(&guardList,createGuard(CYBORG));

    destroyList(&guardList);
}
void unitsMove(char *loadDir) {
    struct UnitList *inmates;
    //struct UnitList *guards;
    struct Inmate *inmateUnit;
    struct Dialog dialog[MAX_LEVELS];
    struct MapList *testList = malloc(sizeof(struct MapList));
    parseMap(loadDir, testList, dialog);
    struct Map current;
    struct Path path;
    printf("Riot Levels Found %d:\n\n", testList->count);

    inmates = malloc(sizeof(struct UnitList));

    inmates->count = 0;
    inmates->head = NULL;
    inmates->tail = NULL;

    //guards = createList();
    current = testList->level[3];
    getPath(&path, current);
    printf("LEVEL %d: \n\n", 3);
    for (int j = 0; j < MAP_ROWS; j++) {
        printf("%s\n", current.overlay[j]);
    }

    printPath(&path);

    // inmateUnit = createInmate(HOMEBOY);
    // inmateUnit->position = 693;
    // enqueue(inmates, inmateUnit);
    // printf("Adding an inmate to the list (%d)\n", inmates->count);
    // printf("Inmate position is: %f\n-----\n", inmateUnit->position);
    for (int i = 0; i < 10; i++) {
        inmateUnit = createInmate(HOMEBOY);
        inmateUnit->position = i * 20;
        enqueue(inmates, inmateUnit);
        printf("Enqueued!\n");
        printInmateList(inmates);

    }
    for (int i = 0; i < 4; i++) {
        removeUnit(inmates, 5);
        printf("Removed!\n");
        printInmateList(inmates);
    }
    /* for (int i = 0; i < 20; ++i) {
         inmateMove(inmates, path);
     }*/
    //simulate(&gameInterface,guards, inmates, path);
    putchar('\n');

    /* while (inmates->count) {
         //printf("Removing units (%d)\n", inmates->count);
         rmUnit(dequeue(inmates));
     }
     //putchar('\n');*/

    destroyList(inmates);
}


void unitsPlay(char *argument) {

//    enum GameMode gameMode;
//struct Windows windows;
    struct MapList mapList;
    struct Map *map;
    struct Dialog dialog[MAX_LEVELS];
//    struct UnitList inmates;
    struct UnitList guards;
//    struct UnitNode *unitNode;
    struct Path path;
    int level = 3;

    /* Parse map files */
    parseMap(argument, &mapList, dialog);

    /* Create nCurses WINDOWs */
    //uiInit(&windows);

    /* Present user with main menu */
    //gameMode = menuMain(&windows);

    // do{
    //     if(gameMode==EXIT){
    //         break;
    //     } else if (gameMode!=NEW){
    //        // level = levelSelect(&windows, &mapList, progress);
    //     }

    /* Select current map */
    map = &(mapList).level[level];

    getGuards(&guards, *map);
    getPath(&path, *map);
    //     inmates.count = 0;
    //     inmates.head = NULL;
    //     inmates.tail = NULL;

    //     /* Draw level */
    //     drawLevel(&windows, map, &guards);

    //     /* Prompt user for unit selection */
    //     drawInmateSelection(&windows, map, &inmates, &guards);

    //     unitNode = getHead(&inmates);
    //     for (int i = 0; i < inmates.count; i++) {
    //         ((struct Inmate *) unitNode->unit)->position = path.first->location;
    //         unitNode = unitNode->next;
    //     }

    //     /* Simulate unit interactions */
    //     progress[level] = simulate(&windows, &guards, &inmates, &path);
    //     if(progress[level]) gameMode=WIN;
    //     else gameMode=LOSE;

    //     /* Display outro text */
    //     drawText(&windows, dialog[level], gameMode);

//     } while (level!=EXIT);

    // uiFree(&windows);
    // quit("Thanks for playing.\n");
}


void mapTest(char *loadDir) {
    struct Dialog *dialog = calloc(MAX_LEVELS, sizeof(struct Dialog));
    struct MapList *testList = malloc(sizeof(struct MapList));
    parseMap(loadDir, testList, dialog);
    struct Map current;
    struct Path path;
    struct UnitList guardList;
    struct UnitList *inmates;
    struct Inmate *inmate;
    printf("Riot Levels Found %d:\n\n", testList->count);

    inmates = malloc(sizeof(struct UnitList));

    inmates->count = 0;
    inmates->head = NULL;
    inmates->tail = NULL;


    /*for (int i=0;i<30;i++){
        inmate = createInmate('f');
        inmate->position = rand() % (MAP_ROWS*MAP_COLS);
        enqueue(inmates,inmate);
        inmate = createInmate('s');
        inmate->position = rand() % (MAP_ROWS*MAP_COLS);
        enqueue(inmates,inmate);
    }*/
    /*inmate = createInmate('s');
    inmate->position = rand() % (MAP_ROWS*MAP_COLS);
    enqueue(inmates,inmate);*/
    for (int i = 4; i < 5; i++) {
        current = testList->level[i];
        getPath(&path, current);
        getGuards(&guardList, current);
        inmate = createInmate('s');
        inmate->position =
            ((struct Guard *) getHead(&guardList)->unit)->position + 2;
        enqueue(inmates, inmate);
        // printf("\n\nGuard list size after function %d\n\n");
        guardAttack(&guardList, inmates, path);
        printf("LEVEL %d: \n\n", i);

        printf("Name: %s\n", current.name);
        printf("\n");

        printf("Layout:\n");
        for (int j = 0; j < MAP_ROWS; j++) {
            printf("[%02d] %s\n", j, current.overlay[j]);
        }

//        printPath(path);
        //      printGuardList(guardList);
        printf("\n\n");

        //destroyList(&guardList);
    }

    return;

}


void printInmate(struct Inmate *inmate) {

    switch (inmate->type) {
        case PROTAGONIST:
            printf("unit:\t Protagonist\n");
            break;

        case HOMEBOY:
            printf("unit:\t Homeboy\n");
            break;

        case BRUISER:
            printf("unit:\t Bruiser\n");
            break;

        case LUNATIC:
            printf("unit:\t Lunatic\n");
            break;

        case FATTY:
            printf("unit:\t Fatty\n");
            break;

        case SPEEDY:
            printf("unit:\t Speedy\n");
            break;

        case CUTIE:
            printf("unit:\t Cutie\n");
            break;

        case ATTORNEY:
            printf("unit:\t Attorney\n");
            break;

        case DOCTOR:
            printf("unit:\t Doctor\n");
            break;

        default:
            break;
    }

    printf("pos:\t%d\n", inmate->position);
    printf("curHP:\t%d\n", inmate->currentHealth);
    printf("maxHP:\t%d\n", inmate->maxHealth);
    printf("speed:\t%d\n", inmate->speed);
    printf("rep:\t%d\n", inmate->rep);
    printf("panic:\t%d\n", inmate->panic);
    printf("\n");

    return;
}


void printGuard(struct Guard *guard) {

    int i = 0;

    printf("Guard #%d\n", i + 1);

    switch (guard->type) {
        case GUARD:
            printf("unit:\t\tGuard\n");
            break;

        case DOGS:
            printf("unit:\t\tDogs\n");
            break;

        case LUNCH:
            printf("unit:\t\tLunch Lady\n");
            break;

        case PSYCH:
            printf("unit:\t\tPsychiatrist\n");
            break;

        case SHARP:
            printf("unit:\t\tSharp Shooter\n");
            break;

        case WARDEN:
            printf("unit:\t\tWarden\n");
            break;

        case CYBORG:
            printf("unit:\t\tCyborg\n");
            break;

        default:
            break;
    }

    printf("pos: %d\n", guard->position);
    printf("damage: %d\n", guard->damage);
    printf("range: %d\n", guard->range);
    printf("cooldown: %d\n", guard->cooldown);
    printf("ai: %d\n", guard->ai);
    printf("\n");

    return;
}


void testingHelp() {
    printf(
        "Usage:\ttest [FLAG]... [OPTION]\n\n"
            "Flags:"
            "\t'-map' tests file parsing"
            "(defaults to cwd, optional absolute path as arg)\n"
            "\t'-unit' tests unit creation and deletion\n"
    );
}


void quit(char *message) {
    printf("ERROR: %s\n", message);
}
