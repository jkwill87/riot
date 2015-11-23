# Testing

RiotUnits.c Testing

riotUnits.c is made up of three primary componenets. These being inmateMove(),guardAttack(), and simulate(). The majority of testing for these functions was performed inside the riotTesting.c file where test cases were used to improve code robustness and functionality.

Inmates moving was tested by creating an arbitrary path and inmate list. Debug statements were printed to the screen to ensure that inmate positions changed as they were supposed to. Inmates were added with adjacent positions to ensure a unit is not moving to the next tile when it is occupied.

Special abilities were tested by ensuring that they were triggered and not triggered, given certain conditions. Doctors were placed in a position before another unit to test for healing. Several inmates were placed within the range of a lunch lady and their speed was tested to make sure it decreased. The psychiatrist special ability was tested by moving inmates being placed within its range, and than by making sure that the closest inmate is frozen.

Guard attack testing was done by creating a list of inmates with random positions alongside a list of guards that were read from a map overlay. Several types of guard attack types were used (aoe,proximity,end) to check for proper inmate selection by the guard. 

Running the program is tested by running the game without an assets or maps folder. In the case of a missing folder, the program will fail to run and an error message will be shown. Also,
if the game is run with an optional parameter for the assets folder and the given folder does not exist the program will not run and an error message will prompt.

Valgrind was used to test for memory leaks.

