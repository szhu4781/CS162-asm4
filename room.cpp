/*********************************************************************
** Program Filename: room.cpp
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Source file for defining Room class member functions
** Input: none
** Output: none
*********************************************************************/

#include "room.h"

using namespace std;

//Room Implementation

//Constructor
Room::Room(){
    event = nullptr;
    player_exist = false;
}

/*********************************************************************
** Function: set_event()
** Description: Clears room for any event first, then sets a new event to it
** Parameters: new_event - Pointer to the new event being set to room
** Pre-Conditions: none
** Post-Conditions: Room event is set to new event
*********************************************************************/
void Room::set_event(Event* new_event){
    //Check if new event is different or not
    //if (new_event != event){
        //clears the room for any events first, then set a new event to it
        clear_event();
        event = new_event;        
   // }
}

/*********************************************************************
** Function: get_event()
** Description: Gets the event that's being set in room
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns the event pointer in room
*********************************************************************/
Event* Room::get_event() const {
    return event;
}

/*********************************************************************
** Function: event_exist()
** Description: Checks if an event exists in a room
** Parameters: none
** Pre-Conditions: none 
** Post-Conditions: Returns a room that is not empty
*********************************************************************/
bool Room::event_exist() const {
    return event != nullptr;
}

/*********************************************************************
** Function: clear_event()
** Description: Deletes event from room after encounter and sets it to an empty room
** Parameters: none
** Pre-Conditions: There is an event in the room
** Post-Conditions: Room is empty after the event is removed
*********************************************************************/
void Room::clear_event(){
    //checks if there is an event going on or not, if condition is met, deletes it after encounter
    if (event != nullptr){
        delete event;
        event = nullptr; //room is empty after event is removed
    }
}

/*********************************************************************
** Function: set_player()
** Description: Sets the adventurer in a room
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Updates the player's presence in the room
*********************************************************************/
void Room::set_player(bool plr) {
    player_exist = plr;
}

/*********************************************************************
** Function: get_player()
** Description: Gets the adventurer
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns the player's presence
*********************************************************************/
bool Room::get_player() const {
    return player_exist;
}

//Destructor
Room::~Room(){
    clear_event();
}

//CC
Room::Room(const Room& other){
    if (other.event != nullptr){
        event = other.event->copy();
    }
    else {
        event = nullptr;
    }
    player_exist = other.player_exist;
}
//AOO
Room& Room::operator=(const Room& other){
    if(this != &other){
        clear_event();
    
        if(other.event != nullptr){
            event = other.event->copy();
        }
        else {
            event = nullptr;
        }

        player_exist = other.player_exist;
    }
    return *this;
}