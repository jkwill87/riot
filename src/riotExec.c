#include "riotExec.h"
#include "riotUI.h"


int main(int argc, char **argv) {

    enum GameMode gameMode = MENU;
    struct Windows windows;
    struct MapList mapList;
    struct Map currentMap, mapCopy;
    struct Dialog dialog[MAX_LEVELS];
    struct UnitList inmates, guards;
    struct UnitNode *unitNode;
    struct Path path;
    int progress = 0;
    int level;

    /* Parse map files */
    parseMap(argv[1], &mapList, dialog);

    /* Create nCurses WINDOWs */
    uiInit(&windows);

    while (gameMode != EXIT) {


        /* Start with main menu */
        gameMode = menuMain(&windows);
        if (gameMode == EXIT) { break; }

        /* Determine level to be loaded */
        if (gameMode == NEW) level = 0;
        else {

            level = levelSelect(&windows, &mapList, progress);

            /* Check if user picked the [b]ack button; return to main menu */
            if (level == -1) gameMode = MENU;
        }

        /*checks if the menu is current gamemode to skip back to the top of the loop*/
        if (gameMode != MENU) {

            /*checks if new level or if */
            if (gameMode != UNDECIDED) {
                /* Select current map */
                currentMap = mapList.level[level];
                currentMap.panicCur = 0;

                /* Display intro text */
                drawText(&windows, dialog[level], NEW, &currentMap);

                /* Initialize game elements */
                getGuards(&guards, currentMap);
                getPath(&path, currentMap);

                /* Draw level */
                drawLevel(&windows, &currentMap, &guards);

                /* Set origin to path origin */
                unitNode = getHead(&inmates);
                for (int i = 0; i < inmates.count; i++) {
                    ((struct Inmate *) unitNode->unit)->position = path.first->location;
                    unitNode = unitNode->next;
                }

                /* Create snapshot of current map (deep copy) */
                copyMap(&currentMap, &mapCopy);
            }

            do {
                /* Prompt user for unit selection */
                drawInmateSelection(&windows, &mapCopy, &inmates, &guards,
                    gameMode);

                /* Simulate unit interactions */
                gameMode = simulate(&windows, &guards, &inmates, &path,
                    &mapCopy);
                if (gameMode == WIN) {
                    if (level == progress)
                        progress++;
                    drawText(&windows, dialog[level], WIN, &mapCopy);
                } else if (gameMode == LOSE) {
                    drawText(&windows, dialog[level], LOSE, &mapCopy);
                }

            }while (gameMode==UNDECIDED);
            getchar();
            gameMode=CONTINUE;
        }
    }

    /* Free memory, exit */
    uiFree(&windows);
    destroyPath(&path);
    destroyList(&inmates);
    destroyList(&guards);
    quit("Thanks for playing");
    return 0;
}


void quit(char *message) {
    if (stdscr) endwin();
    printf("%s. Exiting.\n", message);
    exit(1);
}
