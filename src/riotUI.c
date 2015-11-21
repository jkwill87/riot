#include "riotUI.h"

void uiInit(struct Windows *win) {

    int y, x;

    initscr();
    start_color();
    init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);

    noecho(); // hide keypresses
    curs_set(FALSE); // hide cursor

    /* Verify terminal dimensions */
    getmaxyx(stdscr, y, x);
    if ((x < MAX_COLS) || (y < MAX_ROWS)) quit("Terminal size too small");

    /* Set window positions*/
    win->header = newwin(HEADER, MAX_COLS, 0, 0);
    win->body = newwin(MAIN, MAX_COLS, HEADER, 0);
    win->footer = newwin(FOOTER, MAX_COLS, HEADER + MAIN, 0);
    win->menu = newwin(MAX_ROWS, MAX_COLS, 0, 0);
}


void uiFree(struct Windows *win) {
    if (stdscr) {

        /* Free memory allocated for nCurses windows */
        if (win->header) delwin(win->header);
        if (win->body) delwin(win->body);
        if (win->footer) delwin(win->footer);
        if (win->menu) delwin(win->menu);
        endwin();
    }
}


enum GameMode menuMain(struct Windows *gameInterface) {

    enum GameMode gameMode = _GAME_MODE_LIMIT;
    WINDOW *menu = gameInterface->menu;

    int y = 3;

    /* Print banner */
    wclear(menu);
    box(menu, 0, 0);
    mvwaddstr(menu, y++, 21, "8888888b. 8888888 .d88888b.88888888888");
    mvwaddstr(menu, y++, 21, "888   Y88b  888  d88P   Y88b   888");
    mvwaddstr(menu, y++, 21, "888    888  888  888     888   888");
    mvwaddstr(menu, y++, 21, "888   d88P  888  888     888   888");
    mvwaddstr(menu, y++, 21, "8888888P    888  888     888   888");
    mvwaddstr(menu, y++, 21, "888 T88b    888  888     888   888");
    mvwaddstr(menu, y++, 21, "888  T88b   888  Y88b. .d88P   888");
    mvwaddstr(menu, y++, 21, "888   T88b8888888  Y88888P     888");

    /* Print seperating line */
    mvwhline(menu, y += 2, 21, ACS_HLINE, 37);

    /* Print gameplay options */
    mvwaddstr(menu, y += 3, 21, "GAME MENU");
    y += 2;
    mvwaddstr(menu, y++, 21, "[n]ew game");
    mvwaddstr(menu, y++, 21, "[c]ontinue");
    mvwaddstr(menu, y++, 21, "[e]xit");
    wrefresh(menu);

    /* Prompt for user input */
    while (gameMode != NEW
           && gameMode != CONTINUE
           && gameMode != EXIT)
        gameMode = wgetch(menu);

    return gameMode;
}


int levelSelect(struct Windows *gameInterface, struct MapList *mapList,
    int progress) {

    WINDOW *menu = gameInterface->menu;
    struct Map *current;
    int select;
    int y = 3;
    int x;

#ifdef _DEBUG
    progress = mapList->count - 1; //unlocks all levels
#endif

    /* Print box around menu WINDOW */
    wclear(menu);
    box(menu, 0, 0);

    /* Print header information */
    mvwaddstr(menu, y, 21, "LEVEL SELECT");
    mvwhline(menu, y += 2, 21, ACS_HLINE, 37);
    y += 2;

    /* Print level choices */
    for (x = 0; x < mapList->count; x++) {

        /* Print unlocked levels */
        if (x <= progress) {
            current = &mapList->level[x];
            mvwprintw(menu, y + x, 21, "[%d] %s", x, current->name);

        /* Hint at locked levels */
        } else {
            mvwprintw(menu, y + x, 21, "[/] LOCKED");
        }
    }
    wrefresh(menu);

    /* Prompt for user's level selection (until valid level selected) */
    do {
        select = wgetch(menu) - '0'; //get input from user (as number value)
        if (select >= 0 && select <= progress) return select;
        else if (select == 'b' - '0') return -1;
    } while (true);

    return select;
}


void drawInmateSelection(struct Windows *win, struct Map *map,
    struct UnitList *inmates, struct UnitList *guards) {

    struct Inmate *inmate;
    int input;
    int y;
    int i;
    int numAdded = 0;
    static bool ifProt = FALSE;
    do {
        updateHeader(win->header, map);
        wrefresh(win->header);
        input = wgetch(win->body);

        switch (input) {
            case PROTAGONIST:
                if (!ifProt) {
                    ifProt = TRUE;
                    mvwprintw(win->footer, 0, 40, "PROTAGONIST ADDED");
                    inmate = createInmate(input);
                    enqueue(inmates, inmate);
                    numAdded++;
                    updateQueue(win->body, inmates, numAdded);
                }
                else {
                    mvwprintw(win->footer, 0, 40, "PROTAGONIST ALREADY PRESENT");
                }
                break;
            case HOMEBOY:
                for (i = 0; i < strlen(map->inmates); i++){
                    if (map->inmates[i] == HOMEBOY){
                        i=strlen(map->inmates)+2;
                        if (map->repMax >= 10) {
                            mvwprintw(win->footer, 0, 40, "HOMEBOY ADDED");
                            map->repMax -= 10;
                            inmate = createInmate(input);
                            enqueue(inmates, inmate);
                            numAdded++;
                            updateQueue(win->body, inmates, numAdded);
                        }
                        else {
                            mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                        }
                    }
                }
                break;
            case BRUISER:
                for (i = 0; i < strlen(map->inmates); i++){
                    if (map->inmates[i] == BRUISER){
                        i=strlen(map->inmates)+2;
                        if (map->repMax >= 16) {
                            mvwprintw(win->footer, 0, 40, "BRUISER ADDED");
                            inmate = createInmate(input);
                            map->repMax -= 16;
                            enqueue(inmates, inmate);
                            numAdded++;
                            updateQueue(win->body, inmates, numAdded);
                        }
                        else {
                            mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                        }
                    }
                }
                break;
            case LUNATIC:
                for (i = 0; i < strlen(map->inmates); i++){
                    if (map->inmates[i] == LUNATIC){
                        i=strlen(map->inmates)+2;
                        if (map->repMax >= 16) {
                            mvwprintw(win->footer, 0, 40, "LUNATIC ADDED");
                            inmate = createInmate(input);
                            map->repMax -= 16;
                            enqueue(inmates, inmate);
                            numAdded++;
                            updateQueue(win->body, inmates, numAdded);
                        }
                        else {
                            mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                        }
                    }
                }
                break;
            case FATTY:
                for (i = 0; i < strlen(map->inmates); i++){
                    if (map->inmates[i] == FATTY){
                        i=strlen(map->inmates)+2;
                        if (map->repMax >= 60) {
                            mvwprintw(win->footer, 0, 40, "FATTY ADDED");
                            inmate = createInmate(input);
                            map->repMax -= 60;
                            enqueue(inmates, inmate);
                            numAdded++;
                            updateQueue(win->body, inmates, numAdded);
                        }
                        else {
                            mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                        }
                    }
                }
                break;
            case SPEEDY:
                for (i = 0; i < strlen(map->inmates); i++){
                    if (map->inmates[i] == SPEEDY){
                        i=strlen(map->inmates)+2;
                        if (map->repMax >= 10) {
                            mvwprintw(win->footer, 0, 40, "SPEEDY ADDED");
                            inmate = createInmate(input);
                            map->repMax -= 10;
                            enqueue(inmates, inmate);
                            numAdded++;
                            updateQueue(win->body, inmates, numAdded);
                        }
                    }
                }
                break;
            case CUTIE:
                for (i = 0; i < strlen(map->inmates); i++){
                    if (map->inmates[i] == CUTIE){
                        i=strlen(map->inmates)+2;
                        if (map->repMax >= 20) {
                            mvwprintw(win->footer, 0, 40, "CUTIE ADDED");
                            inmate = createInmate(input);
                            map->repMax -= 20;
                            enqueue(inmates, inmate);
                            numAdded++;
                            updateQueue(win->body, inmates, numAdded);
                        }
                        else {
                            mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                        }
                    }
                }
                break;
            case ATTORNEY:
                for (i = 0; i < strlen(map->inmates); i++){
                    if (map->inmates[i] == ATTORNEY){
                        i=strlen(map->inmates)+2;
                        if (map->repMax >= 30) {
                            mvwprintw(win->footer, 0, 40, "ATTORNEY ADDED");
                            inmate = createInmate(input);
                            map->repMax -= 30;
                            enqueue(inmates, inmate);
                            numAdded++;
                            updateQueue(win->body, inmates, numAdded);
                        }
                        else {
                            mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                        }
                    }
                }
                break;
            case DOCTOR:
                for (i = 0; i < strlen(map->inmates); i++){
                    if (map->inmates[i] == DOCTOR){
                        i=strlen(map->inmates)+2;
                        if (map->repMax >= 10) {
                            mvwprintw(win->footer, 0, 40, "DOCTOR ADDED");
                            inmate = createInmate(input);
                            map->repMax -= 10;
                            enqueue(inmates, inmate);
                            numAdded++;
                            updateQueue(win->body, inmates, numAdded);
                        }
                        else {
                            mvwprintw(win->footer, 0, 40, "INSUFICIENT FUNDS");
                        }
                    }
                }
                break;
        }
        if (map->repMax < 10) {
            mvwprintw(win->footer, 0, 20, "INSUFICIENT FUNDS");
            wrefresh(win->footer);
            wgetch(win->body);
            wgetch(win->body);
            break;
        }
        if (input == '\n' && numAdded == 0) {
            mvwprintw(win->footer, 0, 30, "Please select at least one unit");
            input = ' ';
        }
        else if (input == '\n') {
            break;
        }
        wrefresh(win->footer);
        for (y = 30; y < MAX_COLS - 5; y++) {
            mvwaddch(win->footer, 0, y, ACS_HLINE);
        }
    } while (input != '\n' && numAdded < 5);
    for (y = 1; y < MAX_COLS - 5; y++) {
        mvwaddch(win->footer, 0, y, ACS_HLINE);
    }
    for (y = 1; y < MAX_COLS - 5; y++) {
        mvwaddch(win->body, MAP_ROWS, y, ' ');
    }
    wrefresh(win->footer);
    wrefresh(win->body);
}


void updateHeader(WINDOW *header, struct Map *map) {
    wclear(header);
    box(header, 0, 0);
    mvwprintw(header, 1, 1, "Level %d: %s", map->levelNo,
        map->name); // Display Level
    mvwprintw(header, 1, MAX_COLS - 24, "Panic:%d%%",
        map->panicMax); // Display Panic
    mvwprintw(header, 1, MAX_COLS - 11, "Rep:%d",
        map->repMax); // Display Rep
    mvwaddstr(header, 0, 1, "riot");
    mvwaddch (header, 2, 0, ACS_LTEE);
    mvwaddch (header, 2, MAX_COLS - 1, ACS_RTEE);
}


void updateQueue(WINDOW *body, struct UnitList *inmateList, int size) {
    struct UnitNode *nextInmate;
    struct Inmate *temp;
    int i;
    nextInmate = getHead(inmateList);
    for (i=0; i<size; i++){
        temp = (struct Inmate*)nextInmate->unit;
        mvwaddch(body, 6+i, MAX_COLS - 3, temp->type);
    }
    if (size < 5){
        mvwaddch(body, 6+i, MAX_COLS - 3, '.');
    }
}


void drawMap(WINDOW *body, struct Map *map) {
    int y;
    int x;
    int n,s,e,w;
    for (y = 0; y < MAP_ROWS; y++){
        for (x = 0; x < MAP_COLS-1; x++){
            if (map->overlay[y][x] == '|')
                mvwaddch(body,y,x+1,ACS_VLINE);
            else if (map->overlay[y][x] == '-')
                mvwaddch(body,y,x+1,ACS_HLINE);
            else if (map->overlay[y][x]== '+'){
                n=0;
                s=0;
                e=0;
                w=0;
                if (y> 0 && (map->overlay[y-1][x]=='|' || map->overlay[y-1][x]=='-' || map->overlay[y-1][x]=='+' || map->overlay[y-1][x]=='#'))
                    n=1;
                if (map->overlay[y+1][x]=='|' || map->overlay[y+1][x]=='-' || map->overlay[y+1][x]=='+'|| map->overlay[y+1][x]=='#')
                    s=1;
                if (map->overlay[y][x+1]=='|' || map->overlay[y][x+1]=='-' || map->overlay[y][x+1]=='+'|| map->overlay[y][x+1]=='#')
                    e=1;
                if (x >0 && (map->overlay[y][x-1]=='|' || map->overlay[y][x-1]=='-' || map->overlay[y][x-1]=='+'|| map->overlay[y][x-1]=='#'))
                    w=1;

                if (n==1 && s == 1 && e == 1 && w == 1){
                    mvwaddch(body,y,x+1,ACS_PLUS);
                }
                else if (n == 1 && s == 1 && w == 1 && e ==0){
                    mvwaddch(body,y,x+1,ACS_RTEE);
                }
                else if (n == 1 && s == 1 && e == 1 && w ==0){
                    mvwaddch(body,y,x+1,ACS_LTEE);
                }
                else if (n == 1 && e == 1 && w == 1 && s ==0){
                    mvwaddch(body,y,x+1,ACS_BTEE);
                }
                else if (s == 1 && e == 1 && w == 1 && n ==0){
                    mvwaddch(body,y,x+1,ACS_TTEE);
                }
                else if (n == 1 && w == 1 && e == 0 && s ==0){
                    mvwaddch(body,y,x+1,ACS_LRCORNER);
                }
                else if (n == 1 && e == 1 && w == 0 && s ==0){
                    mvwaddch(body,y,x+1,ACS_LLCORNER);
                }
                else if (s == 1 && w == 1 && e == 0 && n ==0){
                    mvwaddch(body,y,x+1,ACS_URCORNER);
                }
                else if (s == 1 && e == 1 && w == 0 && n ==0){
                    mvwaddch(body,y,x+1,ACS_ULCORNER);
                }
            }
            else
                mvwaddch(body,y,x+1,map->overlay[y][x]);
        }
    }
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(body, y, 0, ACS_VLINE);
        mvwaddch(body, y, MAX_COLS - 1, ACS_VLINE);
    }
}


void drawLevel(struct Windows *windows, struct Map *map,
    struct UnitList *guards) {
    char protName[20];
    char output[100];
    int i;
    int y;
    int *coordinates;
    struct UnitNode *guardNode;
    struct Guard *guard;
    char type;

    wclear(windows->footer);

    drawMap(windows->body, map);

    guardNode = getHead(guards);
    guard = (struct Guard *) guardNode->unit;
    coordinates = getCoordinate(guard->position);
    type = guard->type;
    mvwaddch(windows->body, coordinates[0], coordinates[1], type);
    for (y = 1; y < getLength(guards) - 2; y++) {
        guardNode = guardNode->next;
        guard = (struct Guard *) guardNode->unit;
        coordinates = getCoordinate(guard->position);
        type = guard->type;
        mvwaddch(windows->body, coordinates[0], coordinates[1], type);
    }

    /* Draw Queue */
    mvwaddstr(windows->body, 4, MAX_COLS - 6, "QUEUE");
    mvwaddch(windows->body, 5, MAX_COLS - 6, ACS_ULCORNER);
    mvwaddch(windows->body, 5, MAX_COLS - 2, ACS_URCORNER);
    mvwaddch(windows->body, 11, MAX_COLS - 6, ACS_LLCORNER);
    mvwaddch(windows->body, 11, MAX_COLS - 2, ACS_LRCORNER);
    mvwaddch(windows->body, 6, MAX_COLS - 3, '.');

    for (y = 7; y < 11; y++)
        mvwaddch(windows->body, y, MAX_COLS - 3, ' ');
    for (y = 1; y < 6; y++)
        mvwprintw(windows->body, 5 + y, MAX_COLS - 5, "%d", y);
    for (y = 0; y < 3; y++) {
        mvwaddch(windows->body, 5, MAX_COLS - 5 + y, ACS_HLINE);
        mvwaddch(windows->body, 11, MAX_COLS - 5 + y, ACS_HLINE);
    }
    for (y = 0; y < 5; y++) {
        mvwaddch(windows->body, 6 + y, MAX_COLS - 6, ACS_VLINE);
        mvwaddch(windows->body, 6 + y, MAX_COLS - 2, ACS_VLINE);
    }

    /*Draws the header*/
    updateHeader(windows->header, map);

    /* Draw window borders around windows */
    box(windows->footer, 0, 0);
    mvwaddch(windows->footer, 0, 0, ACS_LTEE);
    mvwaddch(windows->footer, 0, MAX_COLS - 1, ACS_RTEE);
    mvwaddch(windows->header, 0, 0, ACS_ULCORNER);
    for (y = 0; y < MAX_ROWS; y++) {
        mvwaddch(windows->body, y, 0, ACS_VLINE);
        mvwaddch(windows->body, y, MAX_COLS - 1, ACS_VLINE);
    }

    /*Populates footer*/

    strcpy(output, "");
    for (i = 0; i < strlen(map->inmates); i++) {
        if (map->inmates[i]==PROTAGONIST){
            strcat(protName, getInmateName(map->inmates[i]));
            mvwaddstr(windows->footer, 2,1,protName);
        }
        else{
            strcat(output, getInmateName(map->inmates[i]));
            strcat(output, "\t");
        }
        if (i == 4) {
            mvwaddstr(windows->footer, 1, 15, output);
            strcpy(output, "");
        }
    }
    mvwprintw(windows->footer, 1, 1, "INMATES:");
    mvwaddstr(windows->footer, 2, 15, output);
    mvwaddch(windows->footer, 2, MAX_COLS-1, ACS_VLINE);
    mvwaddch(windows->footer, 1, MAX_COLS-1, ACS_VLINE);

    wrefresh(windows->body);
    wrefresh(windows->header);
    wrefresh(windows->footer);

    return;
}

void gameplayRefresh (WINDOW *body, struct Map *map, struct UnitList *guardList, struct UnitList *inmateList,
    struct Path *path){
    int i;
    struct UnitNode *nextInmate;
    struct UnitNode *nextGuard;
    struct Inmate *inmate;
    struct Guard *guard;
    int *coordinates = malloc(sizeof(int) * 2);

    //Initializes all colors
    init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN, GREEN, COLOR_BLACK);
    init_pair(YELLOW, YELLOW, COLOR_BLACK);
    init_pair(RED, RED, COLOR_BLACK);
    init_pair(PURPLE, PURPLE, COLOR_BLACK);
    init_pair(DAMAGED, COLOR_BLACK, DAMAGED);
    init_pair(20, GREEN, DAMAGED);
    init_pair(21, YELLOW, DAMAGED);
    init_pair(22, RED, DAMAGED);
    init_pair(23, PURPLE, DAMAGED);
    init_pair(24, COLOR_WHITE, GREEN);
    init_pair(25, COLOR_WHITE, YELLOW);
    init_pair(26, COLOR_WHITE, RED);
    //set color black/white
    wattron(body,COLOR_PAIR(DEFAULT));
    //redraw map
//    drawMap(body,map);
    //redraw queuebox
    nextGuard = getHead(guardList);
    for (i=0; i< getLength(guardList); i++){
        guard = (struct Guard*)nextGuard->unit;
        wattron(body,COLOR_PAIR(guardColor(guard)));
        coordinates = getCoordinate(guard->position);
        mvwaddch(body, coordinates[0], coordinates[1], guard->type);
        wattron(body, COLOR_PAIR(DEFAULT));
        nextGuard=nextGuard->next;
    }
    //redraw unitList //colors change here
    nextInmate = getHead(inmateList);
    for (i=0; i< getLength(inmateList); i++){
        inmate = (struct Inmate*)nextInmate->unit;
        wattron(body,COLOR_PAIR(getColor(inmate)));
        coordinates = getCoordinate(inmate->position);
        mvwaddch(body, coordinates[0], coordinates[1], inmate->type);
        wattron(body,COLOR_PAIR(DEFAULT));
        eraseInmatePos(body, path,getPrevPos(path,inmate));
        nextInmate=nextInmate->next;
    }
    //set color back to black and white
    wattron(body,COLOR_PAIR(DEFAULT));
    //refresh body
    wrefresh(body);
    //refresh();
    //return
    //free(coordinates);
    return;
}


int getPrevPos (struct Path *path, struct Inmate *inmate){
    struct TileNode *currentTile;
    struct TileNode *nextTile;

    currentTile = path->first;
    if (currentTile->next == NULL)
        quit("No Path Found When Getting Prev Pos");
    nextTile = currentTile->next;
    while (1){
        if(nextTile->next == NULL)
            return (currentTile->location);
            //quit("Position never found");
        if(nextTile->location == inmate->position)
            return (currentTile->location);
        currentTile= nextTile;
        nextTile= nextTile->next;
    }
}

int guardColor (struct Guard *guard){
    float cd, cdr, pcd;
    cd = (float) guard->cooldown;
    cdr = (float) guard->cooldownRemaining;
    pcd = (cdr/cd) *100;
    if (pcd > 20.0)
        return(26);
    else if (pcd > 1.0)
        return (25);
    else
        return (24);
}

int getColor (struct Inmate *inmate){
    float hp, mhp, php;
    int setColor = GREEN;
    hp = (float) inmate->currentHealth;
    mhp = (float) inmate->maxHealth;
    php = (hp / mhp) * 100;
    if (php >= 75.0) {
        setColor = GREEN;
        //if inmate->beingAttacked == true
            //setColor == 20
    } else if (php >= 50.0) {
        setColor = YELLOW;
        //if inmate->beingAttacked == true
            //setColor == 21
    } else if (php >= 25.0) {
        setColor = RED;
        //if inmate->beingAttacked == true
            //setColor == 22
    } else {
        setColor = PURPLE;
        //if inmate->beingAttacked == true
            //setColor == 23
    }
    return setColor;
}


void eraseInmatePos(WINDOW *body, struct Path * path, float position) {
    struct TileNode * nextTile;
    nextTile = path->first;
    char ch;
    int * coordinates;
    while (1){
        if(nextTile->next == NULL){
            break;
        }
        if(nextTile->location == position){
            if (nextTile->type =='#')
                nextTile->type='.';
            ch = nextTile->type;
            coordinates = getCoordinate(position);
            mvwaddch(body, coordinates[0], coordinates[1], ch);
            break;
        }
        nextTile = nextTile->next;
    }
}

void eraseInmate(WINDOW *body, struct Path *path,struct Inmate *inmate){
    eraseInmatePos(body, path, inmate->position);
}


int *getCoordinate(int position) {
    static int coordinates[2];

    coordinates[0] = ((position - 1) /
        MAP_COLS);    //Gives you the row, where the lowest row is 0
    coordinates[1] =
        (position - (coordinates[0] * MAP_COLS)) + 1;      //Gives you x

    return coordinates;
}


void drawText(struct Windows *windows, struct Dialog dialog,
    enum GameMode gameMode, struct Map *map) {
    char *target = NULL;
    char current;
    int height = 0;
    int i = 1;
    int yOff, xOff;

    /* Get dialogue text field */
    switch (gameMode) {
        case NEW:
            target = dialog.textIntro;
            break;
        case CONTINUE:
            target = dialog.textIntro;
            break;
        case WIN:
            target = dialog.textWin;
            break;
        case LOSE:
            target = dialog.textLose;
            break;
        default:
            quit("Simulation terminated with unknown condition");
    }

    xOff = MAX_COLS / 2 - MAP_COLS / 2;

    /* Print borders and static text */
    wclear(windows->menu);
    box(windows->menu, 0, 0);
    mvwprintw(windows->menu,2,xOff,"Level %d: %s",map->levelNo,map->name);
    mvwprintw(windows->menu,MAX_ROWS -3,4,"Press any key to continue...");


    wrefresh(windows->menu);

    /* Determine text height based on newline count */
    while ((current = target[i++]) != '\0')
        if (current == '\n')height++;
    if (height > MAX_ROWS) quit("Too much text in current dialogue entry");

    yOff = MAX_ROWS / 2 - height / 2;

    /* Resize window (temporarily)*/
    wresize(windows->menu, height, MAP_COLS + 1); // +1 for newline
    mvwin(windows->menu, yOff, xOff);
    wclear(windows->menu);


    /* Printout to screen */
    mvwaddstr(windows->menu,0,0, target);
    wrefresh(windows->menu);

    /* Wait for user input to continue */
    getchar();

    /* Restore window dimensions */
    wresize(windows->menu, MAX_ROWS, MAX_COLS);
    mvwin(windows->menu, 0, 0);
}


char *getInmateName(char ch) {
    switch (ch) {
        case PROTAGONIST:
            return "[p]rotagonist";
        case HOMEBOY:
            return "[h]omeboy(10)";
        case BRUISER:
            return "[b]ruiser(16)";
        case LUNATIC:
            return "[l]unatic(16)";
        case FATTY:
            return "[f]atty(60)";
        case SPEEDY:
            return "[s]peedy(10)";
        case CUTIE:
            return "[c]utie(20)";
        case ATTORNEY:
            return "[a]ttorney(30)";
        case DOCTOR:
            return "[d]octor(10)";
        default:
            return "FAIL";
    }
}
