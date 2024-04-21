/*********************************************************************
** Program Filename: stalactites.h
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Header file containing Stalactites class, its member variables and functions
** Input: none
** Output: none
*********************************************************************/

#ifndef STALACTITES_H
#define STALACTITES_H 

#include "event.h"

#include <iostream>
#include <string>

using namespace std;

//Stalactites Interface
class Stalactites : public Event {
public:
    Stalactites(); //constructor

    virtual void set_message(const string& msg) override; //sets message
    virtual string get_message() const override; //gets message for event
    virtual void print_message() const override; //prints the message

    virtual void set_symbol(char symbol) override; //sets the event symbol
    virtual char get_symbol() const override; //gets the symbol

    Stalactites* copy() const override{
        return new Stalactites();
    }
};

#endif
