# Information

* **Name**: RIOT!
* **Class**: CIS3250
* **Instructor**: David McCaughan
* **Version**: 0.1
* **Date**: November 20, 2015


## Game Overview

:hammer:RIOT! is a reverse tower defence game set in a prison theme.

It is a turn-based strategy game where the player is tasked with breaking out of correctional facilities by recruiting and deploying waves of inmates against statically positioned guards with the intention of generating panic and making their escape.

RIOT! intends to switch the roles of a traditional tower defence game, placing the user in control of what would conventionally be the enemy horde.


## Guidelines Followed & Limitations

* implemented in C
* ran in a terminal window with a keyboard-based psuedo-gui
* Curses library used to graphically draw the game
* to be run in an 80x24 character window (both menu and main screen will be contained here)
* map files contained in plain-text encoded with 1148 UTF-8 characters


## Features

* Reverse tower defence puzzle game!
* Distinct prison-break-esque theme!
* Exponentially increasing difficulty!
* Various amounts of levels with different mechanics!
* Unlock inmates as you progress!
* Escape from dangerous guards from dogs to cyborgs!


## Installation and Running

In order to play RIOT! You will have to do following...
    1.	From the command line inside the root folder of the game, type and enter “make” in-order to compile the game.
    2.	Afterwards, type “./bin/riot” to run the game

To use a different assets folder, you can run the game with an additional argument (./bin/riot [arg]) to run it with a different map file.

The map files must start at 0 and continue progressively, and have a .riot extension.  These map files must follow the exact format as the default map files.

If the assets is missing, an error will occur without running the game.


## Changelog

* (11/18/2015) Unit speeds changed from random values to powers of 2 (1,2,4,8..)
* (11/20/2015) Breaking down doors reduced from 5 ticks to 4 ticks
* (11/22/2015) Nerfed Level 7
* (11/22/2015) Attorney HP lowered (30->26)
* (11/22/2015) Lunatic panic generation lowered (8->6)
* (11/22/2015) Speedy and Cutie HP buffed
* (11/22/2015) Bruiser speed increased(4->3)
* (11/22/2015) Sharpshooter damage and cooldown increased
* (11/22/2015) Dog damage decreased and cooldown decreased
* (11/22/2015) Nerfed Level 3

## Contributors

* Jessy Williams
* Daniel Miller
* Filip Hasson
* Marc Santos
* Karol Zdebel
* Sanchitt Dhir
* Antonio Jajou
* Conner Keating
* Justin Galvez
