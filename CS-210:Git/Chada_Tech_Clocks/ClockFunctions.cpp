//============================================================
// File: ClockFunctions.cpp
// Author: Brian Beaudin
// Course: CS-210 - Programming Languages
// Description: Function implementations for the Chada Tech
//              dual clock application. Time is tracked
//              internally in 24-hour format as the single
//              source of truth; the 12-hour clock is derived
//              from it whenever the clocks are displayed.
//============================================================

#include <iostream>
#include <iomanip>
#include <sstream>
#include "ClockFunctions.h"
using namespace std;

void GetInitialTime(int &hours, int &minutes, int &seconds) {
    // Read the starting time in 24-hour format as HH:MM:SS, e.g.: 15:22:01
    // The colon characters are read into throwaway variables so the
    // integer extraction can continue past them
    char colon1, colon2;

    cout << "Enter the starting time in 24-hour format (HH:MM:SS): ";
    cin >> hours >> colon1 >> minutes >> colon2 >> seconds;
}

int DisplayMenu() {
    int choice;

    cout << endl;
    cout << "****************************" << endl;
    cout << "* 1 - Add One Hour         *" << endl;
    cout << "* 2 - Add One Minute       *" << endl;
    cout << "* 3 - Add One Second       *" << endl;
    cout << "* 4 - Exit Program         *" << endl;
    cout << "****************************" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    return choice;
}

void AddHour(int &hours, int &minutes, int &seconds) {
    // Increment the hour, rolling over from 23 back to 0
    hours++;
    if (hours > 23) {
        hours = 0;
    }
}

void AddMinute(int &hours, int &minutes, int &seconds) {
    // Increment the minute; roll into the hour when minutes exceed 59
    minutes++;
    if (minutes > 59) {
        minutes = 0;
        AddHour(hours, minutes, seconds);
    }
}

void AddSecond(int &hours, int &minutes, int &seconds) {
    // Increment the second; roll into the minute when seconds exceed 59
    seconds++;
    if (seconds > 59) {
        seconds = 0;
        AddMinute(hours, minutes, seconds);
    }
}

void DisplayClocks(int hours, int minutes, int seconds) {
    // Derive the 12-hour equivalent from the 24-hour source of truth
    int hours12 = hours % 12;
    if (hours12 == 0) {
        hours12 = 12;
    }
    string period = (hours < 12) ? "A M" : "P M";

    // Build the 12-hour time string with leading zeros
    ostringstream clock12Stream;
    clock12Stream << setw(2) << setfill('0') << hours12 << ":"
                  << setw(2) << setfill('0') << minutes << ":"
                  << setw(2) << setfill('0') << seconds << " " << period;
    string clock12Str = clock12Stream.str();

    // Build the 24-hour time string with leading zeros
    ostringstream clock24Stream;
    clock24Stream << setw(2) << setfill('0') << hours << ":"
                  << setw(2) << setfill('0') << minutes << ":"
                  << setw(2) << setfill('0') << seconds;
    string clock24Str = clock24Stream.str();

    // Display both clocks side by side, per the functional requirements
    cout << endl;
    cout << "*************************** " << "***************************" << endl;
    cout << "*      12-Hour Clock      * " << "*      24-Hour Clock      *" << endl;
    cout << "*      " << clock12Str << "      * " << "*        " << clock24Str << "         *" << endl;
    cout << "*************************** " << "***************************" << endl;
}
