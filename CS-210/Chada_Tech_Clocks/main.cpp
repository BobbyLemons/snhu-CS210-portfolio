//============================================================
// File: main.cpp
// Author: Brian Beaudin
// Course: CS-210 - Programming Languages
// Project: Project One - Chada Tech Clocks
// Description: Displays a 12-hour and a 24-hour clock
//              simultaneously (per ISO 8601) and lets the user
//              add hours, minutes, or seconds to both clocks
//              via a menu, or exit the program.
//============================================================

#include <iostream>
#include "ClockFunctions.h"
using namespace std;

int main() {
    int hours, minutes, seconds;
    int choice;

    // Get the starting time from the user and display both clocks
    GetInitialTime(hours, minutes, seconds);
    DisplayClocks(hours, minutes, seconds);

    // Loop the menu until the user chooses to exit (option 4)
    do {
        choice = DisplayMenu();

        switch (choice) {
            case 1:
                AddHour(hours, minutes, seconds);
                DisplayClocks(hours, minutes, seconds);
                break;
            case 2:
                AddMinute(hours, minutes, seconds);
                DisplayClocks(hours, minutes, seconds);
                break;
            case 3:
                AddSecond(hours, minutes, seconds);
                DisplayClocks(hours, minutes, seconds);
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid selection. Please choose 1-4." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
