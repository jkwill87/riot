#ifndef RIOT_UI
#define RIOT_UI

#include "riotExec.h"
#include "riotMap.h"
#include "riotUnits.h"

/* Data Types */

struct MenuEntry {
    char key;
    char *text;
    struct MenuEntry *next;
};


/*DESCRIPTION: Initilizes the user interface / Windows struct members.
  ARGUMENTS: -The Windows struct containing the target ncurses WINDOWs (struct Windows *win).*/
void uiInit(struct Windows *win);


/*DESCRIPTION: Frees the windows once their use is no longer needed.
  ARGUMENTS: -The Windows struct containing the target ncurses WINDOWs (struct Windows *win).*/
void uiFree(struct Windows *win);


/*DESCRIPTION: Presents the user with the body menu.
  ARGUMENTS: -The Windows struct containing the targer ncurses WINDOWs (struct Windows *win).*/
enum GameMode menuMain(struct Windows *gameInterface);


/*DESCRIPTION: The menu that comes up when 'C' is pressed; it displays all the levels and lets
  the user select ones that are unlocked.
  ARGUMENTS: -The game interface (struct Windows *gameInterface).
             -The list of maps (struct MapList *mapList).
             -Value that represents how many levels the user has unlocked (int progress).*/
int levelSelect(struct Windows *gameInterface, struct MapList *mapList, int progress);


/*DESCRIPTION: Draws the window of all the inmates that the player an choose from.
  ARGUMENTS: -The interface window (struct Windows *win).
             -The current map loaded (struct Map *map).
             -List of Inmates (struct UnitList *inmates).
             -List of Guards (struct UnitList *guards).*/
void drawInmateSelection (struct Windows *win, struct Map *map, struct UnitList *inmates, struct UnitList *guards, enum GameMode gameMode);


/*DESCRIPTION: Updates the text in the header bar on the screen. 
  ARGUMENTS: -The header window being updated (WINDOW *header).
             -The map struct with different header description for each map (struct Map *map).*/
void updateHeader (WINDOW *header, struct Map *map);


/*DESCRIPTION: Updates the units in the box drawn by drawQueue function
  ARGUMENTS: -The body window being updated (WINDOW *body).
             -Unit list that will be displayed (struct UnitList *inmateList).
             -Number of units in the queue on the screen (int size).*/
void updateQueue (WINDOW *body, struct UnitList *inmateList, int size);


/*DESCRIPTION: A function that is called at the beginning of the game to
  create the map, path and all the obstacles.
  ARGUMENTS: -The window the map will be drawn on (WINDOW *body).
             -The map that will be loaded (struct Map *map).*/
void drawMap (WINDOW *body, struct Map *map);


/*DESCRIPTION: Calls drawMap and drawQueue and refreshes the body window
  ARGUMENTS: -Struct of all windows (struct Windows *windows).
             -The map that will be loaded (struct Map* map).
             -List of Guards that gets drawn onto the map (struct UnitList *guards).*/
void drawLevel(struct Windows *windows, struct Map* map, struct UnitList *guards); 


/*DESCRIPTION: Redraws the screen, this is for color functionality
  ARGUMENTS: -The body window that is drawn (WINDOW *body).
             -Map struct to know which level user is playing (struct Map *map).
             -List of Guards (struct UnitList *guardList).
             -List of Inmates (struct UnitList *inmateList).
             -Path struct to print units along the path (struct Path *path)*/
void gameplayRefresh (WINDOW *body, struct Map *map, struct UnitList *guardList, struct UnitList *inmateList, 
  struct Path *path);


/*DESCRIPTION: Updates the path as units move along it.
  ARGUMENTS: -The body window (WINDOW *body).
             -Path being redrawn (struct Path *path).
             -Current level user is on (int level).*/
void redrawPath (WINDOW *body, struct Path *path, int level);


/*DESCRIPTION: Gets the previous position that the unit moved from.
  ARGUMENTS: -Current Path user is on (struct Path *path) .
             -Previous position of this inmate (struct Inmate *inmate).*/
int getPrevPos (struct Path *path, struct Inmate *inmate);


/*DESCRIPTION: Sets the colour of the Guard based on its cooldown.
  ARGUMENTS: -Struct of single Guard (struct Guard *guard).*/
int guardColor (struct Guard *guard);


/*DESCRIPTION: Gets the color based on the units health.
  ARGUMENTS: -Struct of single Inmate (struct Inmate *inmate).*/
int getColor (struct Inmate *inmate);


/*DESCRIPTION: Erases a unit off the screen and restores tile.
  ARGUMENTS: -The body window being updated (WINDOW *body).
             -Path of the level (struct Path *path).
             -Position of the unit (float position).
             -Level the user is playing on (int level).*/
void eraseInmatePos(WINDOW *body, struct Path *path, float position, int level);


/*DESCRIPTION: Takes the position and returns it as 2 dimensional coordinate.
  ARGUMENTS: -A position of a unit as a single integer value (int position).*/
int *getCoordinate(int position);


/*DESCRIPTION: Prints the intro, outro, lose, win text when necessary.
  ARGUMENTS: -Struct of the Windows (struct Windows *windows
             -Dialog for each specified text (struct Dialog dialog)
             -GameMode for intro/outro, win/lose (enum GameMode gameMode).
             -Map level that user is playing (struct Map *map).*/
void drawText (struct Windows *windows, struct Dialog dialog,
    enum GameMode gameMode, struct Map *map);


/*DESCRIPTION: Return the name of the inmate.
  ARGUMENTS: The abbreviation of the inmate, for example 'H' for homeboy (char ch).*/
char *getInmateName(char ch); 


#endif //RIOT_UI
