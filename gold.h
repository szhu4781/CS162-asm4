/*********************************************************************
** Program Filename: gold.h
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Header file containing Gold class, its member variables and functions
** Input: none
** Output: none
*********************************************************************/

#ifndef GOLD_H
#define GOLD_H 

#include "event.h"

#include <iostream>
#include <string>

using namespace std;

//Gold Interface
class Gold : public Event {
public:
    Gold(); //constructor

    virtual void set_message(const string& msg) override; //sets message
    virtual string get_message() const override; //gets message for event
    virtual void print_message() const override; //prints the message

    virtual void set_symbol(char symbol) override; //sets the event symbol
    virtual char get_symbol() const override; //gets the symbol

     Gold* copy() const override{
        return new Gold();
    }
};

#endif