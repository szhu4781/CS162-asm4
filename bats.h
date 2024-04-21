/*********************************************************************
** Program Filename: bats.h
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Header file containing Bat class, its member variables and functions
** Input: none
** Output: none
*********************************************************************/
#ifndef BATS_H
#define BATS_H 

#include "event.h"

#include <iostream>
#include <string>

using namespace std;

//Bats Interface

class Bats : public Event {
public:
    Bats(); //constructor

    virtual void set_message(const string& msg) override; //sets message
    virtual string get_message() const override; //gets message for event
    virtual void print_message() const override; //prints the message

    virtual void set_symbol(char symbol) override; //sets the event symbol
    virtual char get_symbol() const override; //gets the symbol
   
    //used for CC and AOO
    Bats* copy() const override{
        return new Bats();
    }
};

#endif