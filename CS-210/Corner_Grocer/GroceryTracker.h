/*
 * GroceryTracker.h
 * CS-210 Project Three: Corner Grocer Item-Tracking Program
 * Author: Brian Beaudin
 *
 * Declares the GroceryTracker class, which reads the daily purchase log,
 * counts how often each item was purchased, backs the counts up to
 * frequency.dat, and reports the results in several formats.
 */

#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <map>
#include <string>

class GroceryTracker {
public:
   // Builds the tracker around the input and backup file names
   GroceryTracker(const std::string& inputFileName, const std::string& backupFileName);

   // Reads the input file and tallies each item; returns false if the file can't be opened
   bool LoadItems();

   // Writes every item and its count to the backup file; returns false on failure
   bool WriteBackupFile() const;

   // Returns how many times an item was purchased (case-insensitive); 0 if not found
   int GetItemFrequency(const std::string& itemName) const;

   // Prints every item paired with its purchase count (Menu Option Two)
   void PrintAllFrequencies() const;

   // Prints every item followed by one symbol per purchase (Menu Option Three)
   void PrintHistogram() const;

private:
   std::string inputFile;                 // name of the daily purchase log
   std::string backupFile;                // name of the backup data file
   std::map<std::string, int> itemCounts; // item name -> number of purchases
   size_t longestNameLength;              // used to line up columns in output

   // Returns a lowercase copy of text so searches ignore capitalization
   static std::string ToLower(const std::string& text);

   // Removes leading and trailing whitespace (spaces, tabs, stray \r characters)
   static std::string Trim(const std::string& text);
};

#endif // GROCERY_TRACKER_H
