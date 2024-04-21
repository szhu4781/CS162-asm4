/*********************************************************************
** Program Filename: armor.h
** Author: Shengwei Zhu
** Date: 11/19/2023
** Description: Header file containing Armor class, its member variables and functions
** Input: none
** Output: none
*********************************************************************/
#ifndef ARMOR_H
#define ARMOR_H

#include "event.h"

#include <iostream>
#include <string>

using namespace std;

//Armor interface

class Armor : public Event {
public:
  Armor(); //Armor constructor

  virtual void set_message(const string& msg) override; //sets message
  virtual string get_message() const override; //gets message for event
  virtual void print_message() const override; //prints the message

  virtual void set_symbol(char symbol) override; //sets the event symbol
  virtual char get_symbol() const override; //gets the symbol

  Armor* copy() const override{
    return new Armor();
  }
};

#endif