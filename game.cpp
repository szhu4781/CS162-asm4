/*********************************************************************
** Program Filename: game.cpp
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Source file for defining Game class member functions
** Input: 'w', 'a', 's', 'd' to move up, left, down, right. 
**				'f' to fire arrows
** Output: Prints messages each time the adventurer moves to a room
** to keep track of their movements. (The adventurer moves into another room.)
** Messages are printed when the adventurer encounters an event (Events varies)
** Messages are printed when the adventurer fires an arrow to a specific 
** direction. (An arrow is fired and travels through 3 rooms or hits something.)
** Messages are printed whenever the adventurer wins or loses.
** (Adventurer picks up gold and escapes, adventurer shoots and kills Wumpus, 
** adventurer dies from stalactites, or adventurer encounters Wumpus)
** Extra Credit: The adventurer encounters armor and they are protected
** from Wumpus and Stalactites 
*********************************************************************/

#include "game.h"
#include "gold.h"
#include "stalactites.h"
#include "bats.h"
#include "wumpus.h"
#include "armor.h"

using namespace std;

//Game Implementation

Game::Game(){
	//Game constructor
	this->length = 0;
	this->width = 0;
	this->num_arrows = 0;
	this->debug_view = false;
	grid = vector<vector<Room> >(length, vector<Room>(width));
	bat_turns = 0;
	movement = ' ';
	gold = false;
	armor_turns = 0;
	endgame = false;
}

Game::~Game(){
	//destructor
	grid.clear();
}

/*********************************************************************
** Function: set_up()
** Description: Sets up the game and its rooms with random events
** Parameters: int l - length of game board
** 						 int w - width of game board
** Pre-Conditions: none
** Post-Conditions: Initializes game with a 2D vector of Room objects along with
**									random events placed in a random room
*********************************************************************/
void Game::set_up(int l, int w){
	//set up the game
	this->length = l;
	this->width = w;

	this->num_arrows = 3; 	//start with 3 arrows
	
	// Create the game board: 2D vector of Room objects
	grid = vector<vector<Room> >(length, vector<Room>(width));

	//Events are defined here
	//This line is slightly long due to some of the extra credit events
	//Not sure if I will get marked down for this or not
	Event* event[] = {new Bats(), new Bats(), new Stalactites(), new Stalactites(), new Wumpus(), new Gold(), new Armor()};

	//iterate through list of events and place them randomly
	for (Event* event : event){
		int row, col;

		do {
			//randomizes the coordinates
			row = rand() % this->length;
			col = rand() % this->width;
		}
		while (grid[row][col].event_exist());

		grid[row][col].set_event(event); //sets event in the chosen room

	}

	//Set the adventurer in a random room with no events
	do {
		p_row = rand() % this->length;
		p_col = rand() % this->width;
	}
	while (grid[p_row][p_col].event_exist());

	//Starting position variables for the adventurer
	s_row = p_row;
	s_col = p_col;

	grid[p_row][p_col].set_player(true); //the adventurer is placed in a selected room
}

/*********************************************************************
** Function: debug_input()
** Description: Asks for user inputs if user wants to enable debugging mode or not
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Takes in the user inputs to enable or not enable debugging mode
*********************************************************************/
bool Game::debug_input(bool &debug){
	//bool debug;


	cout << "Would you like to enter debug mode? (1 - yes, 0 - no)" << endl;
	cin >> debug;

	//Error handling
	while (!(cin >> debug) || (debug != 0 && debug != 1)){
		cout << "Please enter a value between 1 or 0." << endl;
		//Clear buffer
	}
	this->debug_view = debug;
	return debug;
}

/*********************************************************************
** Function: grid_input()
** Description: Asks for user inputs for length and width size
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Takes in the user inputs for the entered length and width
*********************************************************************/
int Game::grid_input(int &l, int &w){

	//checks for valid dimension size (minimum of 4 rooms on one side, maximum of 50 rooms on one side)
	do {
		//ask for width
		cout << "Enter a width for the grid: " << endl;
		cin >> w;

		if (w < 4 || w > 50){
			cout << "Invalid dimension size." << endl;
		}
	} while (w < 4 || w > 50);

	do {
		//ask for length
		cout << "Enter a length for the grid: " << endl;
		cin >> l;

		//error handling if user enters invalid size
		if (l < 4 || l > 50){
			cout << "Invalid dimension size." << endl;
		}
	} while (l < 4 || l > 50);

	this->width = w;
	this->length = l;

	//set_up(l, w); //sets up game after taking in inputs

	debug_input(this->debug_view); //asks if user wants to enable debugging mode or not

	//Check if debugging mode is enabled or not
	if(this->debug_view){
		cout << "Debugging enabled." << endl;
	}
	else {
		cout << "Debugging disabled. Running normally..." << endl;
	}
	return l, w;
}
/*********************************************************************
** Function: display_game()
** Description: Displays the game board once set up along with symbols in debug mode
** Parameters: none
** Pre-Conditions: The user has to input the grid size and enable or not enable debug mode.
** Post-Conditions: Displays the game interface with game board, list of controls,
**									number of arrows.
*********************************************************************/
void Game::display_game() const{
	cout << debug_view << endl;
	cout << endl << endl;
	cout << "Arrows remaining: " << this->num_arrows << endl;
	
	string line = "";
	for (int i = 0; i < this->width; ++i)
		line += "-----";

	for (int i = 0; i < this->length; ++i)
	{
		cout << line << endl;
		for (int j = 0; j < this->width; ++j)
		{
			//The first char indicates whether there is a player in that room or not
			//if the room does not have the player, print space " "
			if (!grid[i][j].get_player()){
				cout << " ";
			}
			//else, print "*"
			else {
				cout << "*";
			}
			
			//The next two chars indicate the event in the room
			//if the room does not have an event, print "  ||" (2 spaces + ||)
			if (!grid[i][j].event_exist()){
				cout << "  ||";
			}
			//else, 
				//if debug_view is true
					//print the corresponding char of the event
				//else
					//print " " (1 space)
				// print " ||" (1 space + ||)
			else {
				if (grid[i][j].get_event() != nullptr){
					if (this->debug_view){
					cout << grid[i][j].get_event()->get_symbol();
					}
					else {
						cout << " ";
					}
				}
				cout << " ||";				
			}
		}
		cout << endl;
	}
	cout << line << endl;

	bool nearby_event = position(p_row, p_col);
}

/*********************************************************************
** Function: check_win()
** Description: Checks the winning condition(s) and see if its being met
** Parameters: none
** Pre-Conditions: The adventurer meets the requirements for the winning condition(s)
** Post-Conditions: If the condition(s) is met, return true and the adventurer can win. 
** If not, return false and the player cannot win yet.
*********************************************************************/
bool Game::check_win() const{
    // Check if the player is at the starting position with the gold
    if (p_row == s_row && p_col == s_col && gold){
			return true;
		}
		else {
			return false;
		}
}

/*********************************************************************
** Function: position()
** Description: Checks if the adventurer is in a room adjacent 
**							to a room containing an event
** Parameters: none
** Pre-Conditions: The player is in a room adjacent to a room with an event
** Post-Conditions: A percept message is printed if the player is in a room
** adjacent to a room with a event
*********************************************************************/
bool Game::position(int row, int col) const {
	int r = grid.size();
	int c = grid[0].size();

	bool nearby_event = false;

	//Note: The rows and columns are never equal to 0 since it would be
	//out of bounds of the game grid. 

	//checks the north direction
	if (row > 0 && grid[row - 1][col].event_exist()){
		nearby_event = true;
		grid[row - 1][col].get_event()->print_message();
	}
	//checks south direction
	if (row < r - 1 && grid[row + 1][col].event_exist()) {
		nearby_event = true;
		grid[row + 1][col].get_event()->print_message();
	}
	//checks west direction
	if (col > 0 && grid[row][col - 1].event_exist()) {
		nearby_event = true;
		grid[row][col - 1].get_event()->print_message();
	}
	//checks east direction
	if (col < c - 1 && grid[row][col + 1].event_exist()) {
		nearby_event = true;
		grid[row][col + 1].get_event()->print_message();
	}
	return nearby_event;
}

/*********************************************************************
** Function: bat_encounter()
** Description: The adventurer encounters bats
** Parameters: none
** Pre-Conditions: The adventurer enters a room with super bats
** Post-Conditions: The adventurer's controls are reversed for 5 turns.
** This function is called and the reverse controls are handled in move()
*********************************************************************/
void Game::bats_encounter(){

	Event* bat_event = grid[p_row][p_col].get_event(); //checks for events in a room

	//checks if the event encounter is Bats or not and if the event symbol matches
	if (bat_event && bat_event->get_symbol() == 'B'){
		cout << "You entered a room filled with bats. They screech at you." << endl;
		cout << "You are confused. (Reversed controls for 5 turns.)" << endl;
		bat_turns = 5; //number of turns this effect last for
	}
}

/*********************************************************************
** Function: stalactites_encounter()
** Description: The adventurer encounters falling stalactites
** Parameters: none
** Pre-Conditions: The adventurer is inside of a room with stalactites
** Post-Conditions: The adventurer either lives or dies from the stalactites
*********************************************************************/
void Game::stalactites_encounter(){
	cout << "You entered a room with falling stalactites. Be careful!" << endl;

	if (rand() % 2 == 0){
		cout << "You just barely survived. You feel somewhat traumatized." << endl;
	}
	else {
		cout << "A stalactite landed on you..." << endl;
		endgame = true;
	}
}

/*********************************************************************
** Function: wumpus_encounter()
** Description: The adventurer stumbles upon Wumpus when entering a room
** Parameters: none
** Pre-Conditions: The adventurer is inside of a room containing Wumpus
** Post-Conditions: The adventurer is eaten by Wumpus and they die
*********************************************************************/
void Game::wumpus_encounter(){
	cout << "You entered a room with a sleeping Wumpus. It woke up." << endl;
	cout << "You have been devoured by the Wumpus." << endl;
	endgame = true;
}

/*********************************************************************
** Function: gold_encounter()
** Description: The adventurer stumbles upon gold
** Parameters: none
** Pre-Conditions: The adventurer is inside the room containing the gold
** Post-Conditions: A message is printed out telling the adventurer to
** escape with the gold without dying
*********************************************************************/
void Game::gold_encounter(){
		cout << "You found gold! Retrace your steps back to where you started." << endl;

		gold = true; //The gold is found and set to true

		grid[p_row][p_col].set_event(nullptr); //gold symbol is removed after taking the gold

	//check_win();
}

/*********************************************************************
** Function: armor_encounter()
** Description: The adventurer stumbles upon armor
** Parameters: none
** Pre-Conditions: The adventurer is inside the room containing the armor
** Post-Conditions: The adventurer gains armor, protecting them from either
** Wumpus or falling Stalactites for two turns.
*********************************************************************/
void Game::armor_encounter(){
	Event* armor_event = grid[p_row][p_col].get_event();

	//Checks if the adventurer encounters the armor event
	//in a room or not and if the symbol of the event matches
	if (armor_event && armor_event->get_symbol() == 'A'){
		cout << "You found an old suit of armor." << endl;
		cout << "You put on the armor, and you feel protected." << endl;
		armor_turns = 2; //Armor last for
	}
}

/*********************************************************************
** Function: event_encounter
** Description: Calls each individual event encounter functions
** Parameters: none
** Pre-Conditions: All the event encounter functions are set up properly
** Post-Conditions: Outputs the corresponding event encounter based on
** the specific event that was encountered
*********************************************************************/
void Game::event_encounter(){
	Event* rand_event = grid[p_row][p_col].get_event();

	if (rand_event){
		//Event is happening in a room
		char type = rand_event->get_symbol();

		//For armor event encounter
		//Checks if event encounter is armor or not
		if (armor_turns > 0){
			cout << "You feel strong to hold off anything." << endl;
			armor_turns--;
			return;
		}
		
		//Switches through events to check the specific event that's being encountered
		switch (type){
			case 'B':
				//Bats event
				bats_encounter();
				break;
			case 'S':
				//Stalactites event
				stalactites_encounter();
				break;
			case 'W':
				//Wumpus event
				wumpus_encounter();
				break;
			case 'G':
				//Gold event
				gold_encounter();
				break;
			case 'A':
				//Armor event
				armor_encounter();
				break;
		}
	}
}

/*********************************************************************
** Function: move_up()
** Description: Let's the user move the adventurer up
** Parameters: none
** Pre-Conditions: The game has been set up
** Post-Conditions: The adventurer moves into a room facing up
*********************************************************************/
void Game::move_up() {
	//move player up
	//Your code here:
	if (p_row > 0){
		grid[p_row][p_col].set_player(false); //Current room does not contain player
		p_row--; //Player position is updated
		grid[p_row][p_col].set_player(true); //Player is set in the new room

		//checks if player is confused or not
		if (bat_turns <= 0){
			event_encounter(); //Check for event and handle events if player encounters one
		}

		cout << "You moved up." << endl;
	}
	else {
		cout << "Can't move. Out of bounds." << endl;
	}
}

/*********************************************************************
** Function: move_down()
** Description: Let's the user move the adventurer down
** Parameters: none
** Pre-Conditions: The game has been set up
** Post-Conditions: The adventurer moves into a room facing down
*********************************************************************/
void Game::move_down() {
	//move player down
	//Your code here:
	if (p_row < length - 1){
		grid[p_row][p_col].set_player(false); //Current room does not contain player
		p_row++; //Player position is updated
		grid[p_row][p_col].set_player(true); //Player is set in the new room

		if (bat_turns <= 0){
			event_encounter(); //Check for event and handle events if player encounters one
		}

		cout << "You moved down." << endl;	
	}
	else {
		cout << "Can't move. Out of bounds." << endl;
	}
}

/*********************************************************************
** Function: move_left
** Description: Let's the user move the adventurer left
** Parameters: none
** Pre-Conditions: The game has been set up
** Post-Conditions: The adventurer moves into a room facing left
*********************************************************************/
void Game::move_left() {
	//move player left
	//Your code here:
	if (p_col > 0){
		grid[p_row][p_col].set_player(false); //Current room does not contain player
		p_col--; //Player position is updated
		grid[p_row][p_col].set_player(true); //Player is set in the new room
		if (bat_turns <= 0){
			event_encounter(); //Check for event and handle events if player encounters one
		}
		cout << "You moved left." << endl;	
	}
	else {
		cout << "Can't move. Out of bounds." << endl;
	}
}

/*********************************************************************
** Function: move_right()
** Description: Let's the user move the adventurer right
** Parameters: none
** Pre-Conditions: The game has been set up
** Post-Conditions: The adventurer moves into a room facing right
*********************************************************************/
void Game::move_right() {
	//move player right
	//Your code here:
	if (p_col < width - 1){
		grid[p_row][p_col].set_player(false); //Current room does not contain player
		p_col++; //Player position is updated
		grid[p_row][p_col].set_player(true); //Player is set in the new room
		if (bat_turns <= 0){
			event_encounter(); //Check for event and handle events if player encounters one
		}
		cout << "You moved right." << endl;	
	}
	else {
		cout << "Can't move. Out of bounds." << endl;
	}
}

/*********************************************************************
** Function: get_dir()
** Description: Prompts the user to input a direction for firing an arrow
** Parameters: none
** Pre-Conditions: The user inputs the key for firing an arrow
** Post-Conditions: The input direction corresponds to the direction of fire
*********************************************************************/
char Game::get_dir(){
	//get direction of arrow:
	char dir;
	//Note: error checking is needed!! 
	//Your code here:
	cout << "Fire an arrow...." << endl;
	cout << "W-up" << endl;
	cout << "A-left" << endl;
	cout << "S-down" << endl;
	cout << "D-right" << endl;
	

	cout << "Enter direction: " << endl;
	cin >> dir;
	cin.ignore(256, '\n');
	
	//Error handling is added in fire_arrow()

	return dir;
}

//Ignore this....
// void Game::shuffle(int moves[][2], int size){
// 	for (int i = size - 1; i > 0; i--){
// 		int move = rand() % (i + 1);

// 		//Swaps moves between i and move
// 		int m1 = moves[i][0];
// 		int m2 = moves[i][1];
// 		moves[i][0] = moves[move][0];
// 		moves[i][1] = moves[move][0];
// 		moves[move][0] = m1;
// 		moves[move][1] = m2;
// 	}
// }

/*********************************************************************
** Function: wumpus_move
** Description: Wumpus can move to an empty room when the user fires
** and misses their arrow shot
** Parameters: none
** Pre-Conditions: An arrow has been fired and it didn't hit Wumpus
** Post-Conditions: Wumpus has a 75% chance to move to an empty room
*********************************************************************/
void Game::wumpus_move(){
	//after a missed arrow, 75% chance that the wumpus is moved to a different room

	//How to get 75%? 
	//Hint: generate a random number from 0-3, if the number is not 0, then move

	//Your code here:
	if (rand() % 4 != 0){
		int w_row, w_col;

		//Get current position of Wumpus
		int row = -1, col = -1;		
		for (int i = 0; i < length; i++){
			for (int j = 0; j < width; j++){
				if (grid[i][j].event_exist() && grid[i][j].get_event()->get_symbol() == 'W'){
					row = i;
					col = j;
					break;
				}
			}
			if (row != -1){
				break;
			}
		}
		//If Wumpus is found
		if (row != -1){
			grid[row][col].get_event()->set_symbol(' '); //set symbol to empty
			grid[row][col].clear_event(); //delete any leftover memory	
		}

		//Ignore this...
		//Moves for Wumpus
		// int w_moves[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

		// //Shuffle orders of moves
		// shuffle(w_moves, 4);

		//Tries different moves till an empty room
		// for (int i = 0; i < 4; i++){
		// 	w_row = row + w_moves[i][0];
		// 	w_col = col + w_moves[i][1];

		// 	//Check if moves are within bounds and if rooms are empty
		// 	if (w_row >= 0 && w_row < length && w_col >= 0 && w_col < width && !grid[w_row][w_col].event_exist() && !grid[w_row][w_col].get_player()){
		// 		break;
		// 	}
		// }

		//randomizes wumpus position
		do {
			w_row = rand() % this->length;
			w_col = rand() % this->width;
		}
		//Checks if room has no events or adventurer in it.
		while (grid[w_row][w_col].event_exist() || grid[w_row][w_col].get_player());

		grid[w_row][w_col].set_event(new Wumpus()); //set Wumpus in a new room

		cout << "Something happened... or did it?" << endl;
	}
}

/*********************************************************************
** Function: fire_arrow()
** Description: Allows the user to have the adventurer fire arrows
**						  in a specific direction.
** Parameters: none
** Pre-Conditions: The game has been set up and the user pressed 'f'
** Post-Conditions: The adventurer fires an arrow to a specific direction
** 									based on the user's inputs. If the adventurer misses
** their shot, Wumpus may move to a random empty room.
*********************************************************************/
void Game::fire_arrow(){
	// The player may fire arrow...
	//If the adventurer runs out of arrows
	if (num_arrows == 0){
		cout << "Out of arrows." << endl;
		return;
	}
	char dir = get_dir();

	//Error handling for firing direction
	//If the the user enters an invalid direction
	if (!(dir == 'w' || dir == 's' || dir == 'a' || dir == 'd')){
		cout << "Invalid direction. Please try again." << endl;
		return;
	}

	//Your code here:
	//Logic for firing arrows go here
	int target_r = p_row;
	int target_c = p_col;
	int range = 3;

	num_arrows--;

	//Logic for max distance an arrow can travel
	//An arrow can only go through 3 rooms
	while (range > 0){
		range--;
		switch(dir){
			case 'w':
				if (target_r > 0){
					target_r--;
				}
				break;
			case 's':
				if (target_r < length - 1){
					target_r++;
				}
				break;
			case 'a':
				if (target_c > 0){
					target_c--;
				}
				break;
			case 'd':
				if (target_c < width - 1){
					target_c++;
				}
				break;
		}

		//Checks if an arrow hits Wumpus or not.
		if (grid[target_r][target_c].event_exist() && grid [target_r][target_c].get_event()->get_symbol() == 'W'){
			cout << "You hear a loud thud in the distance... You feel somewhat relieved." << endl;
			cout << "Congratulations! You successfully killed Wumpus and won!" << endl;
			endgame = true;
			grid.clear(); //Clears the vector grid before exiting program
			break;
		}

	}

	//Tells which direction the arrow has been fired
	switch(dir){
		case 'w':
			cout << "The arrow fired north." << endl;
			break;
		case 's':
			cout << "The arrow fired south." << endl;
			break;
		case 'a':
			cout << "The arrow fired west." << endl;
			break;
		case 'd':
			cout << "The arrow fired east." << endl;
			break;
	}

	//If the arrow didn't hit anything
	if (range == 0){
		wumpus_move();
		cout << "You feel as if you've missed..." << endl;
	}

}

/*********************************************************************
** Function: move()
** Description: Handles the inputs for moving and firing arrows
** Parameters: char c - The user input that the program takes in
** Pre-Conditions: The game has been set up
** Post-Conditions: The inputs are taken in by the program and handled properly.
** If the player encounters Bats, their controls are reversed for 5 turns.
** This effect does not stack.
*********************************************************************/
void Game::move(char c) {
	// Handle player's action: move or fire an arrow
	if (c == 'f'){
		Game::fire_arrow();
		return;
	}
	bats_encounter(); //call bats_encounter to print out the prompts

	//checks if the adventurer is confused for 5 turns
	//their controls are reversed over while having this effect
	if (bat_turns > 0) {
		switch(c){
			case 'w':
				move_down();
				break;
			case 'a':
				move_right();
				break;
			case 's':
				move_up();
				break;
			case 'd':
				move_left();
				break;
		}	
		bat_turns--;
	}
	//else, their controls are normal
	else {
		switch(c){
		case 'w':
			Game::move_up();
			break;
		case 'a':
			Game::move_left();
			break;
		case 's':
			Game::move_down();
			break;
		case 'd':
			Game::move_right();
			break;
		}
	}

	//Check whether if armor effect is still active while moving
	if (armor_turns > 0){
		cout << "You feel strong to hold off anything." << endl;
		armor_turns--;
		return;
	}
}

/*********************************************************************
** Function: get_input()
** Description: Gets the inputs for movement and firing arrows
** Parameters: none
** Pre-Conditions: The game has been set up
** Post-Conditions: Prompts the user of what inputs are valid and
**									what action the adventurer can perform
*********************************************************************/
char Game::get_input(){
	//get action, move direction or firing an arrow

	//Note: error checking is needed!!
	//Your code here:
	char c;

	cout << endl << endl << "Player move..." << endl << endl;
	cout << "W-up" << endl;
	cout << "A-left" << endl;
	cout << "S-down" << endl;
	cout << "D-right" << endl;
	cout << "f-fire an arrow" << endl;

	cout << "Enter input: " << endl;
	cin >> c;
	cin.ignore(256, '\n');

	//Error handling for entering an invalid input
	if (!(c == 'w' || c == 's' || c == 'a' || c == 'd' || c == 'f')){
		cout << "Invalid input. Try again." << endl;
	}
	else {
		movement = c;
	}
	return c;
}

/*********************************************************************
** Function: play_game()
** Description: 
** Parameters: int l - grid length
**						 int w - grid width
**						 bool d - variable intialized for debugging
** Pre-Conditions: All the functions called within this function are set up properly
** Post-Conditions: Calls the function for setting the game up, display the game, user
** inputs, player movement, and checking the win conditions.
*********************************************************************/
void Game::play_game(int l, int w, bool d){

	set_up(w, l);
	//this->debug_view = d;

	char input, arrow_input;
	
	while (true){
		//check if winning conditions are true or not
    if (check_win() == true){
        // Display win message and exits successfully
        cout << "Congratulations! You won!" << endl;
				grid.clear();
				replay_game();
        break;
    }

		//print game board
		display_game();

		//display percepts around player's location
		//Your code here:

		//Player move...
		//1. get input
		input = get_input();

		//2. move player
		move(input);

		//3. may or may not encounter events
		//Your code here:

		//player death
		if (endgame == true){
			cout << "You died. Game over." << endl;
			replay_game();
			break;
		}
	}
}

/*********************************************************************
** Function: same_game()
** Description: 
** Parameters: none
** Pre-Conditions: The user chose to start the game again with same configurations
** Post-Conditions: The game restarts with the same cave configurations
*********************************************************************/
void Game::same_game(){
	gold = false;
	endgame = false;
	grid.clear();
	set_up(width, length);
	play_game(length, width, debug_view);
}

/*********************************************************************
** Function: new_game()
** Description: 
** Parameters: none
** Pre-Conditions: The user chose to start the game with new configurations
** Post-Conditions: The game starts the
*********************************************************************/
void Game::new_game(){
	gold = false;
	endgame = false;
	grid.clear();

	//Calls the starting input functions again.
	int num_input = grid_input(length, width);

	//display_game();
	play_game(length, width, debug_view);
}

/*********************************************************************
** Function: replay_game()
** Description: 
** Parameters: none
** Pre-Conditions: The adventurer dies from some hazard
** Post-Conditions: Prompts the user how they want to restart the game or quit
*********************************************************************/
void Game::replay_game(){
	//Menu prompts
	int choice;
	cout << "Would you like to: " << endl;
	cout << "1. Play again with the same cave configurations?" << endl;
	cout << "2. Play again with new cave configurations?" << endl;
	cout << "3. Quit the game." << endl;
	cin >> choice;

	cin.clear();
	cin.ignore(256, '\n');

	switch (choice) {
		case 1:
			//Same cave config
			same_game();
			break;
		case 2:
			//New cave config
			new_game();
			play_game(width, length, debug_view);
			break;
		case 3:
			//Quit game
			cout << "L + Ratio. Skill issue lol." << endl;
			grid.clear();
			exit(0);
		default:
			//Error checking
			cout << "Invalid choice. Please try again." << endl;
			replay_game();
	}
}

