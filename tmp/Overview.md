**1.	Overview**

**1.1.	Description**

RIOT! is a reverse tower defence game set in a prison theme.  RIOT! intends to switch the roles of a traditional tower defence game, placing the user in control of what would conventionally be the enemy horde.

The game’s objective is to escort the protagonist through each of correction facilities, with each one having progressive difficulty.  The player must send waves of inmates (ranging from the quick-moving Speedys to shot-absorbing Fatties) to clear the way for the protagonist.

Whether it’s trying to sober up from the Drunk Tank or escaping the clutches of the fabled Guantanamo, the difficulty only goes up as more guards arrive to bring your attempts to a halt.


**1.2.	Technical Features**


**2.	Instructions**

 In-order to play RIOT! you will have to do following...
1.	From the command line inside the root folder of the game, type and enter “make” in-order to compile the game.
2.	Afterwards, type “./bin/riot” to run the game
3.	Once the main menu is shown, you will be given the following options:
i.	[n]ew game
ii.	[c]ontinue
iii.	[e]xit
Choose the options with the following letter inside the bracket. 
New game sets the player inside the tutorial level so that they can learn how to play.
Continue allows the player to start wherever the left off or replay a level that’s been completed. They will not be able to choose a level that they haven’t unlocked.
Exit exits RIOT!
4.	Once a level is selected, the player will have to press any key continue to the game.
5.	Within the level, the available units will be displayed in the INMATES section below. The player can pick whom they’d want to use and that will be placed in the queue according to the letter picked. 
6.	To select the inmate the player must have enough ‘rep’ to purchase them. The higher the rep, the more inmates you can get.
7.	Once the player selects the inmates they want, they can either press enter to send them or fill up the queue and that will automatically send them through.
8.	With every inmate that escapes, the panic will increase, causing the towers to lose accuracy. The higher the panic, the easier it gets.
9.	If you complete the level, the player will be prompted with a message that continues the story, otherwise it will prompt them to start it again.


**3.	Design Changes**

- 8 levels instead of 9
- tentative tick time (is 1/6th of a second in design doc)
- because of terminal limitations, changes to colour have been made 
- riotIO is not explicitly used
- protagonist changes


**4.	Incomplete Features**




