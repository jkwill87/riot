# Testing

## Testing Overview

The *RIOT* Makefile produces two targets, `riot` and `test`. As its name suggests, `test` performs automated test cases that where used to guide development. Not to be confused with testing, the `riot` executable also allows for debug mode when compiled with the `make -D_DEBUG`, which allows the user or developer to unlock all levels from the game's start.


## Units Testing

Riot Units is made up of three primary components: inmateMove(), guardAttack(), and simulate(). Testing of these functions is performed inside the riotTesting.c file where test cases were used to improve code robustness and functionality.

Inmates moving was tested by creating an arbitrary path and inmate list. Debug statements were printed to the screen to ensure that inmate positions changed as they were supposed to. Inmates were added with adjacent positions to ensure a unit is not moving to the next tile when it is occupied.

Special abilities were tested by ensuring that they were triggered and not triggered, given certain conditions. Doctors were placed in a position before another unit to test for healing. Several inmates were placed within the range of a lunch lady and their speed was tested to make sure it decreased. The psychiatrist special ability was tested by moving inmates being placed within its range, and than by making sure that the closest inmate is frozen.

Guard attack testing was done by creating a list of inmates with random positions alongside a list of guards that were read from a map overlay. Several types of guard attack types were used (aoe,proximity,end) to check for proper inmate selection by the guard. 

Running the program is tested by running the game without an assets or maps folder. In the case of a missing folder, the program will fail to run and an error message will be shown. Also,
if the game is run with an optional parameter for the assets folder and the given folder does not exist the program will not run and an error message will prompt.

Valgrind was used to test for memory leaks.


## UI Testing

A majority of testing on for the UI was verifying that certain characters and colours work.

Finding colours to use:
running './bin/test -colourDump', gets the max dimensions of the current terminal window and prints all foreground/background colour combinations that will fit in the current specifications. colour beyond 15 for foreground created sporadic results. A similar effect was observed for background colours beyond 7. Also colours beyond this range varied drastically between machines and terminals. This forced us to limit our colours to the more narrower range of colours we used. This also impacted earlier design decisions such as the colours we used to display health. The colour dump test showed that there was no orange colour, and thus health colours were changed from Green->Yellow->Orange->Red to Green->Yellow->Red->Purple. 

running './bin/test -color', is a more targeted test of colours intended to be used in the program. This was less for functionality but more for game play purposes to make sure all colour combinations were both legible and not overly distracting. colours tested here were also for features that never made it to the final game, such as damaged units and further colour effects like visualizing slows and freezing. These were cut as the screen would appear confusing and cluttered with so many different colours displaying

additional testing for UI was done in during game execution. This was for simpler issues such as adding and removing units to the game queue, selecting and unlocking levels, adding too many units, getting proper charges and refunds for rep used when preforming various add/remove functions. going back and forth between level and the main menu, and replaying levels in odd or peculiar orders.

int * getCoordinate(int position):
"getCoordinate" is used to convert a single value integer to a pair of coordinates. This function is tested using the "printCoordinate" function. the test integer is passed in and is run through the "getCoordinate" function. The output x and y value of the function are then printed to the command line


 "getCoordinate" is used to convert a single value integer to a pair of coordinates. This function is tested using the "printCoordinate" function. the test integer is passed in and is run through the "getCoordinate" function. The output x and y value of the function are then printed to the command line and the user compares expected value to the one printed. use the "-printCr" flag and an integer value to run this test


## Map Testing

Map testing can be activated by passing the `-map` flag to the `test` binary target. This parameter will print map layouts in the same way that the game will interpret them, line by line. This allows for the detection of any formatting inconsistencies which can result in undefined behaviour during game execution.