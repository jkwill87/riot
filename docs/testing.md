# Testing

RiotUnits.c Testing

riotUnits.c is made up of three primary componenets. These being inmateMove(),guardAttack(), and simulate(). The majority of testing for these functions was performed inside the riotTesting.c file where test cases were used to improve code robustness and functionality.

inmateMove() was tested by creating an arbitrary path and inmate list. InmateMove() was than called with that inmate list and path as the arguments. Debug statements were printed to the screen to ensure that inmate positions changed as they were supposed to. Further testing had to be done when multiple units moving through a path was implemented. Many debug statements were printed ensuring that all neccessary conditions were met, such as a unit not moving to the next tile when it is occupied.


GuardAttack() testing was done by creating a list of inmates with random positions alongside a list of guards that were read from a map overlay. Several helper functions were tested for functionality using print statements, one example being inRange() which returns a boolean based on if an inmate is within a guards range.


Valgrind was used to test for memory leaks.

RiotUI.c Testing

A majority of testing on for the UI was verifying that certain characters and colors work.

Finding colors to use:
running './bin/test -colorDump', gets the max dimensions of the current terminal window and prints all foreground/background color combinations that will fit in the current specifications. Color beyond 15 for foreground created sporatic results. A similar effect was observed for background colors beyond 7. Also colors beyond this range varied drastically between machines and terminals. This forced us to limit our colors to the more narror range of colors we used. This also impacted earlier design descisions such as the colors we used to display health. The color dump test showed that there was no orange color, and thus health colors were changed from Green->Yellow->Orange->Red to Green->Yellow->Red->Purple. 

running './bin/test -color', is a more targeted test of colors intended to be used in the program. This was less for functionality but more for gameplay purposes to make sure all color combinations were both legible and not overly distracting. 