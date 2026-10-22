/*
 * GroceryTracker.cpp
 * CS-210 Project Three: Corner Grocer Item-Tracking Program
 * Author: Brian Beaudin
 *
 * Implements the GroceryTracker class declared in GroceryTracker.h.
 */

#include "GroceryTracker.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Constructor: stores the file names; counts are loaded later by LoadItems()
GroceryTracker::GroceryTracker(const string& inputFileName, const string& backupFileName)
   : inputFile(inputFileName), backupFile(backupFileName), longestNameLength(0) {
}

// Reads the purchase log one line at a time and tallies each item in the map
bool GroceryTracker::LoadItems() {
   ifstream inFS(inputFile);
   if (!inFS.is_open()) {
      return false;   // caller reports the error to the user
   }

   itemCounts.clear();
   longestNameLength = 0;

   string line;
   while (getline(inFS, line)) {
      string item = Trim(line);
      if (item.empty()) {
         continue;   // skip blank lines so they aren't counted as an item
      }

      // operator[] creates the entry at 0 the first time an item is seen,
      // so this single line handles both new and repeat items
      itemCounts[item]++;

      longestNameLength = max(longestNameLength, item.length());
   }

   inFS.close();
   return true;
}

// Writes "Item Count" pairs to the backup file, one per line
bool GroceryTracker::WriteBackupFile() const {
   ofstream outFS(backupFile);
   if (!outFS.is_open()) {
      return false;
   }

   // A map stores keys in sorted order, so the backup is alphabetical
   for (const auto& entry : itemCounts) {
      outFS << entry.first << " " << entry.second << endl;
   }

   outFS.close();
   return true;
}

// Looks up one item, ignoring capitalization ("apples" matches "Apples")
int GroceryTracker::GetItemFrequency(const string& itemName) const {
   string target = ToLower(Trim(itemName));

   for (const auto& entry : itemCounts) {
      if (ToLower(entry.first) == target) {
         return entry.second;
      }
   }

   return 0;   // item never appeared in the purchase log
}

// Menu Option Two: item names in a left-aligned column, counts beside them
void GroceryTracker::PrintAllFrequencies() const {
   for (const auto& entry : itemCounts) {
      cout << left << setw(static_cast<int>(longestNameLength) + 2) << entry.first
           << entry.second << endl;
   }
}

// Menu Option Three: one asterisk per purchase
void GroceryTracker::PrintHistogram() const {
   for (const auto& entry : itemCounts) {
      cout << left << setw(static_cast<int>(longestNameLength) + 2) << entry.first
           << string(entry.second, '*') << endl;   // string(n, c) repeats c n times
   }
}

// Helper: returns a lowercase copy of text
string GroceryTracker::ToLower(const string& text) {
   string result = text;
   for (char& ch : result) {
      ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
   }
   return result;
}

// Helper: strips whitespace from both ends, including Windows \r line endings
string GroceryTracker::Trim(const string& text) {
   const string whitespace = " \t\r\n";
   size_t start = text.find_first_not_of(whitespace);
   if (start == string::npos) {
      return "";   // line was entirely whitespace
   }
   size_t end = text.find_last_not_of(whitespace);
   return text.substr(start, end - start + 1);
}
