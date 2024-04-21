/*********************************************************************
** Program Filename: event.cpp
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Source file for defining Event class member functions
** Input: none
** Output: none
*********************************************************************/

#include "event.h"

using namespace std;

//Event Implementation

//constructor
Event::Event(){
    message = " ";
    letter = ' ';
}

//destructor
Event::~Event(){

}

/*********************************************************************
** Function: set_message()
** Description: Sets the message for the specific event
** Parameters: const string& msg - Used to set the message
** Pre-Conditions: none
** Post-Conditions: Event message is set to the string
*********************************************************************/
void Event::set_message(const string& msg) {
    message = msg;
}

/*********************************************************************
** Function: get_message()
** Description: Gets the message for the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns the message of the event
*********************************************************************/
string Event::get_message() const {
    return message;
}

/*********************************************************************
** Function: print_message()
** Description: Prints out the event message corresponding to the specific event
** Parameters: none
** Pre-Conditions: none 
** Post-Conditions: Message of the event is printed
*********************************************************************/
void Event::print_message() const {
    cout << message << endl;
}

/*********************************************************************
** Function: set_symbol()
** Description: Sets the symbol for the event
** Parameters: char symbol - The symbol used to represent a event
** Pre-Conditions: none
** Post-Conditions: The event letter is set to the symbol
*********************************************************************/
void Event::set_symbol(char symbol){
    letter = symbol;
}

/*********************************************************************
** Function: get_symbol()
** Description: Gets the symbol for the event
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns the symbol of the event
*********************************************************************/
char Event::get_symbol() const {
    return letter;
}