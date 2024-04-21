/*********************************************************************
** Program Filename: main.cpp
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Source file containing the main function
** Input: Inputs are set up in game.cpp and called in the main function
** Output: Outputs are set up in game.cpp
*********************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

/*********************************************************************
** Function: int main()
** Description: The main function calling functions set up in game.cpp
** Parameters: none
** Pre-Conditions: game.cpp has functions set up
** Post-Conditions: Accesses functions set up in Game and returns whatever
** output is set corresponding to those functions. 
*********************************************************************/
int main()
{
	//set the random seed
	srand(time(NULL));
	
	int wid, len;
	bool debug;
	
	Game g;

	g.grid_input(wid, len); //gets inputs for dimension sizes and debug view inputs after

	//Play game
	g.play_game(wid, len, debug);

	return 0;
}