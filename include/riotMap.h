#ifndef RIOT_MAP
#define RIOT_MAP

#include "riotExec.h"

#define PATH_MAX 4096
#define MAP_SIZE 1545
#define MAX_LEVELS 10
#define REGEX_EXT "(\\.)?[0-9](.riot)$"
#define BONUS_LEVEL 8


/* Data Types */

struct MapList {
    struct Map level[MAX_LEVELS];
    int count;
};


struct Path {
    /* Path stores the game path as a list of TileNodes. */

    struct TileNode *first;
    struct TileNode *last;
    unsigned int count;
};


/* TileNode contains the location of the map on the board, along with a the
 * character representation of the tile. */
struct TileNode {

    int location;
    char type;
    int durability;
    struct TileNode *next;
};


/* DESCRIPTION: Parse level files and store their contents into
 *              the structures used by the rest of the system.
 * ARGUMENTS:   - The directory where the maps are found (char *loadDir).
 *              - List of maps being added (struct MapList* mapList)
 *              - Sets the dialog for each map (struct Dialog dialog[]).
 * POSTCONDITIONS: A Map struct is returned containing the map elements and
 * tower placements.*/
void parseMap(char *loadDir, struct MapList *mapList, struct Dialog dialog[]);


/* DESCRIPTION: Retrieves information from the given map and stores this data
 *              into a path structure.
 * ARGUMENTS: - The path to be populated (struct Path *path).
 *            - Map being parsed (struct Map map).*/
void getPath(struct Path *path, struct Map map);


/* DESCRIPTION: Recursive function which creates an ordered path struct.
 * ARGUMENTS:   - Map struct to be searched (struct Map map).
 *              - Path struct to be created(struct Path *path).
 *              - Previously checked positions(int prevChecked[]).
 *              - Number of the tile that has been added to the path(int count).
 *              - Current position being searched in the map struct(int
 *                currentPosition). */
struct Path *pathSolve(struct Map map, struct Path *path, int prevChecked[],
    int count, int currentPosition);


/* DESCRIPTION: Pushes a tile node to the back of the path list.
 * ARGUMENTS:   - Tile Node to be pushed (struct TileNode* insertNode).
 *              - Path that the tile node is pushed into (struct Path* path).*/
void pushToPath(struct TileNode *insertNode, struct Path *path);


/* DESCRIPTION: Checks whether the position exists in the previously checked
 *              array.
 * ARGUMENTS:   - Array of all positions previously checked (int prevChecked[]).
 *              - Position to be compared against the previously checked positions (int position).*/
bool beenChecked(int prevChecked[], int position);


/* DESCRIPTION: Returns a boolean based on whether the character is a path
 *              character.
 * ARGUMENTS:   - Character to be checked (char tileChar). */
bool isPathCharacter(char tileChar);


/* DESCRIPTION: Creates a tile node and initializes it.
 * ARGUMENTS:   - Location of the tile node (int location).
 *              - Character type of the tile node (char type). */
struct TileNode *createTileNode(int location, char type);


/* DESCRIPTION: Destroys the path and all the contents of the path.
 * ARGUMENTS:   - Path to be destroyed (struct Path *path).*/
void destroyPath(struct Path *path);


/* DESCRIPTION: Copies the elements from the initalMap to the dupeMap
 * ARGUMENTS:   - Initial Map Pointer, Map pointer for the duplicate to be used
 *                during gameplay (struct Map *initialMap).
 *              - Duplicate map being created (struct Map *dupeMap).*/
void copyMap(struct Map *initialMap, struct Map *dupeMap);


#endif //RIOT_MAP
