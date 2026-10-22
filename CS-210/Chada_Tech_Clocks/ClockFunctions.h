//============================================================
// File: ClockFunctions.h
// Author: Brian Beaudin
// Course: CS-210 - Programming Languages
// Description: Function prototypes for the Chada Tech dual
//              clock application (12-hour and 24-hour display).
//============================================================

#ifndef CLOCKFUNCTIONS_H
#define CLOCKFUNCTIONS_H

// Prompts the user for the starting time (24-hour format) and
// stores the values in the hours, minutes, and seconds parameters
void GetInitialTime(int &hours, int &minutes, int &seconds);

// Displays the user menu and returns the user's selected option
int DisplayMenu();

// Adds one hour to the current time, rolling over at 24 hours
void AddHour(int &hours, int &minutes, int &seconds);

// Adds one minute to the current time, rolling into the hour as needed
void AddMinute(int &hours, int &minutes, int &seconds);

// Adds one second to the current time, rolling into the minute as needed
void AddSecond(int &hours, int &minutes, int &seconds);

// Displays the 12-hour and 24-hour clocks side by side in the
// format specified by the Chada Tech functional requirements
void DisplayClocks(int hours, int minutes, int seconds);

#endif
