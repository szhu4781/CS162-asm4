/*********************************************************************
** Program Filename: wumpus.h
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Header file containing Wumpus class, its member variables and functions
** Input: none
** Output: none
*********************************************************************/

#ifndef WUMPUS_H
#define WUMPUS_H 

#include "event.h"

#include <iostream>
#include <string>

using namespace std;

//Wumpus Interface
class Wumpus : public Event {
protected:
    bool alive;

public:
    Wumpus(); //constructor

    void set_status(bool status); //set status of Wumpus - alive or dead
    bool get_status() const; //gets status of Wumpus - alive or dead

    virtual void set_message(const string& msg) override; //sets message
    virtual string get_message() const override; //gets message for event
    virtual void print_message() const override; //prints the message

    virtual void set_symbol(char symbol) override; //sets the event symbol
    virtual char get_symbol() const override; //gets the symbol

    Wumpus* copy() const override{
        return new Wumpus();
    }
};

#endif