/*
 * CS 210 - Project Two: Airgead Banking App
 * Author: Brian Beaudin
 *
 * BankingApp.cpp
 * Defines the BankingApp class: the interactive console experience for the
 * Airgead Banking investment calculator.
 */

#include "BankingApp.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Main loop. Each pass collects a full set of values, shows both reports,
// and then asks whether the user wants to test different numbers.
void BankingApp::run() {
   bool testAgain = true;

   while (testAgain) {
      displayInputHeader();

      // Each read repeats until the user enters a valid value.
      double initialInvestment = readDouble("Initial Investment Amount: $", 0.0, false);
      double monthlyDeposit    = readDouble("Monthly Deposit:           $", 0.0, true);
      double annualInterest    = readDouble("Annual Interest:           %", 0.0, true);
      int numberOfYears        = readInt("Number of Years:            ", 1, MAX_YEARS);

      try {
         InvestmentCalculator calculator(initialInvestment, monthlyDeposit,
                                         annualInterest, numberOfYears);

         displayEnteredValues(calculator);
         waitForEnter();

         printReport(std::cout,
                     "Balance and Interest Without Additional Monthly Deposits",
                     calculator.calculateWithoutMonthlyDeposits());

         printReport(std::cout,
                     "Balance and Interest With Additional Monthly Deposits of "
                        + formatCurrency(calculator.getMonthlyDeposit()),
                     calculator.calculateWithMonthlyDeposits());
      }
      catch (const std::invalid_argument& error) {
         // The calculator rejected a value; explain why and start over.
         std::cout << "\nUnable to calculate: " << error.what() << "\n";
      }

      testAgain = askToTestAgain();
   }

   std::cout << "\nThank you for using the Airgead Banking investment calculator.\n";
}

void BankingApp::displayInputHeader() const {
   std::cout << "\n" << std::string(REPORT_WIDTH, '*') << "\n"
             << "Airgead Banking - Investment Calculator\n"
             << std::string(REPORT_WIDTH, '*') << "\n"
             << "Enter amounts as numbers only (for example: 1.00, 50, 5).\n\n";
}

// Echoes the values back so the user can confirm them before continuing.
void BankingApp::displayEnteredValues(const InvestmentCalculator& t_calculator) const {
   std::ostringstream interest;
   interest << std::fixed << std::setprecision(2) << t_calculator.getAnnualInterest() << "%";

   std::cout << "\n" << std::string(REPORT_WIDTH, '-') << "\n"
             << std::left
             << std::setw(30) << "Initial Investment Amount:" << formatCurrency(t_calculator.getInitialInvestment()) << "\n"
             << std::setw(30) << "Monthly Deposit:"           << formatCurrency(t_calculator.getMonthlyDeposit()) << "\n"
             << std::setw(30) << "Annual Interest:"           << interest.str() << "\n"
             << std::setw(30) << "Number of Years:"           << t_calculator.getNumberOfYears() << "\n"
             << std::right
             << std::string(REPORT_WIDTH, '-') << "\n";
}

// Standard C++ has no portable "any key" read, so Enter is used instead.
void BankingApp::waitForEnter() const {
   std::cout << "Press Enter to continue...";
   readLine();
}

// Accepts y/yes or n/no in any capitalization; anything else asks again.
bool BankingApp::askToTestAgain() const {
   while (true) {
      std::cout << "\nWould you like to test different values? (y/n): ";
      std::string answer = stripSymbols(readLine());

      if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes" || answer == "YES") {
         return true;
      }
      if (answer == "n" || answer == "N" || answer == "no" || answer == "No" || answer == "NO") {
         return false;
      }
      std::cout << "Please enter y or n.\n";
   }
}

// Prints a titled, column-aligned report. Taking an ostream& means the same
// function can write to std::cout or to an ofstream without any changes.
void BankingApp::printReport(std::ostream& t_out,
                             const std::string& t_title,
                             const std::vector<YearEndRecord>& t_records) const {
   t_out << "\n" << std::string(REPORT_WIDTH, '=') << "\n"
         << "  " << t_title << "\n"
         << std::string(REPORT_WIDTH, '=') << "\n"
         << std::left  << std::setw(8)  << "  Year"
         << std::right << std::setw(26) << "Year End Balance"
         << std::setw(32) << "Year End Earned Interest" << "\n"
         << std::string(REPORT_WIDTH, '-') << "\n";

   for (const YearEndRecord& record : t_records) {
      t_out << std::right << std::setw(6) << record.year << "  "
            << std::setw(26) << formatCurrency(record.yearEndBalance)
            << std::setw(32) << formatCurrency(record.yearEndEarnedInterest) << "\n";
   }

   t_out << std::string(REPORT_WIDTH, '=') << "\n";
}

// Reads a real number. Symbols like $, %, and commas are removed first, so
// "$1,000.00" and "5%" are accepted. Text, blank input, and out-of-range
// values produce a message and a new prompt instead of a crash.
double BankingApp::readDouble(const std::string& t_prompt, double t_minimum, bool t_allowMinimum) const {
   while (true) {
      std::cout << t_prompt;
      std::string input = stripSymbols(readLine());

      try {
         std::size_t charactersUsed = 0;
         double value = std::stod(input, &charactersUsed);

         // Reject entries like "50abc" where only part of the text is a number.
         if (charactersUsed != input.size()) {
            throw std::invalid_argument("extra characters");
         }

         bool tooSmall = t_allowMinimum ? (value < t_minimum) : (value <= t_minimum);
         if (tooSmall) {
            std::cout << (t_allowMinimum ? "  Please enter zero or a positive number.\n"
                                         : "  Please enter a number greater than zero.\n");
            continue;
         }
         return value;
      }
      catch (const std::invalid_argument&) {
         std::cout << "  That is not a valid number. Please try again.\n";
      }
      catch (const std::out_of_range&) {
         std::cout << "  That number is too large. Please try again.\n";
      }
   }
}

// Reads a whole number within [t_minimum, t_maximum].
int BankingApp::readInt(const std::string& t_prompt, int t_minimum, int t_maximum) const {
   while (true) {
      std::cout << t_prompt;
      std::string input = stripSymbols(readLine());

      try {
         std::size_t charactersUsed = 0;
         int value = std::stoi(input, &charactersUsed);

         if (charactersUsed != input.size()) {
            throw std::invalid_argument("extra characters");
         }
         if (value < t_minimum || value > t_maximum) {
            std::cout << "  Please enter a whole number from " << t_minimum
                      << " to " << t_maximum << ".\n";
            continue;
         }
         return value;
      }
      catch (const std::invalid_argument&) {
         std::cout << "  Please enter a whole number of years.\n";
      }
      catch (const std::out_of_range&) {
         std::cout << "  That number is too large. Please try again.\n";
      }
   }
}

// Reads one full line from the keyboard. If input has closed completely
// (for example, Ctrl+D), there is nothing left to read, so an exception
// lets main() end the program gracefully instead of looping forever.
std::string BankingApp::readLine() const {
   std::string line;
   if (!std::getline(std::cin, line)) {
      throw std::runtime_error("Input ended unexpectedly.");
   }
   return line;
}

// Formats a value as dollars and cents, for example $1265.65.
std::string BankingApp::formatCurrency(double t_amount) {
   std::ostringstream formatted;
   formatted << "$" << std::fixed << std::setprecision(2) << t_amount;
   return formatted.str();
}

// Removes spaces, tabs, carriage returns, $, %, and commas from user input.
std::string BankingApp::stripSymbols(const std::string& t_text) {
   std::string cleaned;
   for (char character : t_text) {
      if (character != ' ' && character != '\t' && character != '\r' &&
          character != '$' && character != '%' && character != ',') {
         cleaned += character;
      }
   }
   return cleaned;
}
