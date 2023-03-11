#ifndef ROTARY_H_
#define ROTARY_H_

#include <iostream>
#include <cstring>
#include "config.h"
using namespace std;

// Global Variables
// Rotary
extern int counterRotary;
extern char currentDirection[4]; // "_ _ _ null" for a c-string
extern int currentStateCLK;
extern int currentStateDT;
extern int lastStateCLK;
extern int currentStateSW;
extern int counterSW; // Switches counter
// extern int counterDelaySW; // delayed counter for switch to monitor when a change happens for rotary.cpp
extern unsigned long lastButtonPress;

bool rotary__update_state();
void rotary__update_LCD();

#endif
