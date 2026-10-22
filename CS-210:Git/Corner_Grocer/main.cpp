/*
 * main.cpp
 * CS-210 Project Three: Corner Grocer Item-Tracking Program
 * Author: Brian Beaudin
 *
 * Loads the day's purchase records, backs up the item counts to
 * frequency.dat, and runs a menu that lets the user search for one item,
 * list every item's count, view a histogram, or exit.
 */

#include <iostream>
#include <limits>
#include <string>

#include "GroceryTracker.h"

using namespace std;

// File names used by the program
const string INPUT_FILE_NAME  = "CS210_Project_Three_Input_File.txt";
const string BACKUP_FILE_NAME = "frequency.dat";

// Displays the main menu
void DisplayMenu() {
   cout << endl;
   cout << "========== Corner Grocer ==========" << endl;
   cout << "1. Look up how often an item was purchased" << endl;
   cout << "2. Print purchase counts for all items" << endl;
   cout << "3. Print purchase histogram" << endl;
   cout << "4. Exit" << endl;
   cout << "===================================" << endl;
   cout << "Enter your choice (1-4): ";
}

// Reads a menu choice, rejecting non-numbers and values outside 1-4
int GetMenuChoice() {
   int choice;

   while (true) {
      if (cin >> choice && choice >= 1 && choice <= 4) {
         // Clear the rest of the line so a later getline() starts fresh
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         return choice;
      }

      if (cin.eof()) {
         return 4;   // input stream closed; exit cleanly
      }

      // Recover from bad input (e.g., letters) and ask again
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid choice. Please enter a number from 1 to 4: ";
   }
}

int main() {
   GroceryTracker tracker(INPUT_FILE_NAME, BACKUP_FILE_NAME);

   // Load the purchase records; nothing else works without them
   if (!tracker.LoadItems()) {
      cout << "Error: could not open " << INPUT_FILE_NAME << "." << endl;
      cout << "Make sure the file is in the same folder as the program." << endl;
      return 1;
   }

   // Back up the counts automatically at startup, with no user action needed
   if (!tracker.WriteBackupFile()) {
      cout << "Warning: could not create " << BACKUP_FILE_NAME
           << ". Continuing without a backup." << endl;
   }

   int choice = 0;
   while (choice != 4) {
      DisplayMenu();
      choice = GetMenuChoice();

      switch (choice) {
         case 1: {
            // Option 1: search for a single item
            string itemName;
            cout << "Enter the item to look up: ";
            getline(cin, itemName);

            int frequency = tracker.GetItemFrequency(itemName);
            if (frequency > 0) {
               cout << itemName << " was purchased " << frequency
                    << (frequency == 1 ? " time." : " times.") << endl;
            }
            else {
               cout << itemName << " was not purchased today." << endl;
            }
            break;
         }

         case 2:
            // Option 2: list every item with its count
            cout << endl;
            tracker.PrintAllFrequencies();
            break;

         case 3:
            // Option 3: text histogram
            cout << endl;
            tracker.PrintHistogram();
            break;

         case 4:
            // Option 4: exit the loop
            cout << "Goodbye!" << endl;
            break;
      }
   }

   return 0;
}
