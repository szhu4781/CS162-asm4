/*********************************************************************
** Program Filename: room.h
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Header file containing Room class, its member variables and functions
** Input: none
** Output: none
*********************************************************************/

#ifndef ROOM_H
#define ROOM_H 

#include "event.h"

using namespace std;

//Room Interface
//Note: Each room may be empty or has an event (bat, gold, pit, or wumpus);
//		Use event polymorphically

class Room
{
private: 
    Event* event;
    bool player_exist;	
public:
    Room(); //constructor

    ~Room(); //destructor

    //CC
    Room(const Room& other);

    //AOO
    Room& operator=(const Room& other);

    void set_event(Event* event); //sets event in a room
    Event* get_event() const; //gets the event

    bool event_exist() const; //checks if there is an event or not
    void clear_event(); //clears an event after the adventurer encounters it
    
    void set_player(bool plr); //set player in a room
    bool get_player() const; //get the player


};

#endif