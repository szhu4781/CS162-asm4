/*********************************************************************
** Program Filename: event.h
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Header file containing Event class, its member variables and functions
** Input: none
** Output: none
*********************************************************************/

#ifndef EVENT_H
#define EVENT_H 

#include <iostream>
#include <string>

using namespace std;

//Event Interface
//Note: this must be an abstract class!

class Event {
protected:
	string message;
    char letter;
public:
	Event(); //constructor
    virtual ~Event(); //destructor if needed
    
    virtual void set_message(const string& msg) = 0; //sets the message
    virtual string get_message() const = 0; //gets the message
    virtual void print_message() const = 0; //prints the message of event

    virtual void set_symbol(char symbol) = 0; //sets the event symbol
    virtual char get_symbol() const = 0; //gets the symbol

    virtual Event* copy() const = 0; //used for CC and AOO

};
#endif