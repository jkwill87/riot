# Testing

RiotUnits.c Testing

riotUnits.c is made up of three primary componenets. These being inmateMove(),guardAttack(), and simulate(). The majority of testing for these functions was performed inside the riotTesting.c file where test cases were used to improve code robustness and functionality.

inmateMove() was tested by creating an arbitrary path and inmate list. InmateMove() was than called with that inmate list and path as the arguments. Debug statements were printed to the screen to ensure that inmate positions changed as they were supposed to. Further testing had to be done when multiple units moving through a path was implemented. Many debug statements were printed ensuring that all neccessary conditions were met, such as a unit not moving to the next tile when it is occupied.


GuardAttack() testing was done by creating a list of inmates with random positions alongside a list of guards that were read from a map overlay. Several helper functions were tested for functionality using print statements, one example being inRange() which returns a boolean based on if an inmate is within a guards range.


Valgrind was used to test for memory leaks.