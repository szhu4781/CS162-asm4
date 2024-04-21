/*********************************************************************
** Program Filename: event.cpp
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Source file for defining Wumpus class member functions
** Input: none
** Output: none
*********************************************************************/

#include "wumpus.h"

using namespace std;

//Wumpus Implementation

//Wumpus constructor
Wumpus::Wumpus(){
    message = "You smell a terrible stench.";
    letter = 'W';
    alive = true;
}

/*********************************************************************
** Function: set_status
** Description: Sets Wumpus's status
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Status is set to alive
*********************************************************************/
void Wumpus::set_status(bool status){
    alive = status;
}

/*********************************************************************
** Function: get_status
** Description: Gets Wumpus's status
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns the status of Wumpus
*********************************************************************/
bool Wumpus::get_status() const {
    return alive;
}

/*********************************************************************
** Function: set_message()
** Description: Sets the message for the specific event
** Parameters: const string& msg - Used to set the message
** Pre-Conditions: none
** Post-Conditions: Event message is set to the string
*********************************************************************/
void Wumpus::set_message(const string& msg){
    message = msg;
}

/*********************************************************************
** Function: get_message()
** Description: Gets the message for the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns the message of the event
*********************************************************************/
string Wumpus::get_message() const {
    return message;
}

/*********************************************************************
** Function: print_message()
** Description: Prints out the event message corresponding to the specific event
** Parameters: none
** Pre-Conditions: none 
** Post-Conditions: Message of the event is printed
*********************************************************************/
void Wumpus::print_message() const {
    cout << message << endl;
}

/*********************************************************************
** Function: set_symbol()
** Description: Sets the symbol for the event
** Parameters: char symbol - The symbol used to represent a event
** Pre-Conditions: none
** Post-Conditions: The event letter is set to the symbol
*********************************************************************/
void Wumpus::set_symbol(char symbol){
    letter = symbol;
}

/*********************************************************************
** Function: get_symbol()
** Description: Gets the symbol for the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns the symbol of the event
*********************************************************************/
char Wumpus::get_symbol() const {
    return letter;
}