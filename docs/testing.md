# Testing

RiotUnits.c Testing

riotUnits.c is made up of three primary componenets. These being inmateMove(),guardAttack(), and simulate(). The majority of testing for these functions was performed inside the riotTesting.c file where test cases were used to improve code robustness and functionality.

Inmates moving was tested by creating an arbitrary path and inmate list. Debug statements were printed to the screen to ensure that inmate positions changed as they were supposed to. Inmates were added with adjacent positions to ensure a unit is not moving to the next tile when it is occupied.

Special abilities were tested by ensuring that they were triggered and not triggered, given certain conditions. Doctors were placed in a position before another unit to test for healing. Several inmates were placed within the range of a lunch lady and their speed was tested to make sure it decreased. The psychiatrist special ability was tested by moving inmates being placed within its range, and than by making sure that the closest inmate is frozen.

Guard attack testing was done by creating a list of inmates with random positions alongside a list of guards that were read from a map overlay. Several types of guard attack types were used (aoe,proximity,end) to check for proper inmate selection by the guard. 

Running the program is tested by running the game without an assets or maps folder. In the case of a missing folder, the program will fail to run and an error message will be shown. Also,
if the game is run with an optional parameter for the assets folder and the given folder does not exist the program will not run and an error message will prompt.

Valgrind was used to test for memory leaks.

<<<<<<< HEAD

=======
<<<<<<< HEAD
Valgrind was used to test for memory leaks.

RiotUI.c Testing

A majority of testing on for the UI was verifying that certain characters and colors work.

Finding colors to use:
running './bin/test -colorDump', gets the max dimensions of the current terminal window and prints all foreground/background color combinations that will fit in the current specifications. Color beyond 15 for foreground created sporatic results. A similar effect was observed for background colors beyond 7. Also colors beyond this range varied drastically between machines and terminals. This forced us to limit our colors to the more narror range of colors we used. This also impacted earlier design descisions such as the colors we used to display health. The color dump test showed that there was no orange color, and thus health colors were changed from Green->Yellow->Orange->Red to Green->Yellow->Red->Purple. 

running './bin/test -color', is a more targeted test of colors intended to be used in the program. This was less for functionality but more for gameplay purposes to make sure all color combinations were both legible and not overly distracting. 

int * getCoordinate(int position):
 "getCoordinate" is used to convert a single value integer to a pair of coordinates. This function is tested using the "printCoordinate" function. the test integer is passed in and is run through the "getCoordinate" function. The output x and y value of the function are then printed to the command line
=======
>>>>>>> 9c8e58936b78371e95f9dd354f77352e4539589d
>>>>>>> b726855fd60eadb0ae901a753d27fabeff1111db
