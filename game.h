/*********************************************************************
** Program Filename: game.h
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Header file containing Game class, its member variables and functions
** Input: none
** Output: none
*********************************************************************/

#ifndef GAME_H
#define GAME_H 

#include <vector>
#include <iostream> 
#include "room.h"

using namespace std;

//Game interface 
class Game
{
private:
	//declare a 2D vector of Room objects:
	vector<vector<Room> > grid; //vector declaration

	//other member variables:
	int length; 			//length of the board
	int width;  			//width of the board
	int num_arrows; 		//keep track of number of errors remaining
	bool debug_view;		//debug mode or not

	int p_row; //row for the player position
	int p_col; //col for the player position

	int s_row; //row of the room where the player is initially set
	int s_col; //col of the room where the player is initially set

	int bat_turns; //number of turns for reversed controls
	char movement; //stores last move due to reverse controls

	bool gold; //gold has been found or not

	int armor_turns; //number of turns the armor last for

	bool endgame; //variable for ending the game

	//variables for wumpus position
	int w_row;
	int w_col;

public:
	//constructor
	Game();

	//destructor
	~Game();

	//CC
	Game(const Game& other);

	//AOO
	Game& operator=(const Game& other);

	void set_up(int, int); //setting grid

	bool debug_input(bool &debug); //asks user inputs for debug mode
	int grid_input(int &l, int &w); //asks user inputs for setting up grid size

	bool position(int row, int col) const; //checks if event is adjacent to the player position

	void display_game() const; //displaying the grid

	bool check_win() const; //check win condition

	//void end_game(const string& cause);



	char get_dir(); //get directions
	void wumpus_move(); //wumpus move

	void shuffle(int moves[][2], int size); //Shuffles moves for Wumpus each turn
	void fire_arrow(); //fire arrow

	//direction functions
	void move_up();
	void move_left();
	void move_right();
	void move_down();

	void move(char dir);

	//event encounters
	void bats_encounter();
	void reversed_controls();

	void stalactites_encounter();
	void wumpus_encounter();
	void gold_encounter();

	void armor_encounter(); //armor event for extra credit
	void passage_encounter(); //hidden passage event for extra credit

	void event_encounter(); //checks for what event the adventurer may encounter
	char get_input(); //get user input

	void play_game(int, int, bool); //playing the game

	void same_game(); //Same cave configurations
	void new_game(); //New cave configurations
	void replay_game(); //replay menu

};
#endif