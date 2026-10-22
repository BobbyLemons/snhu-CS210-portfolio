/*
 * CS 210 - Project Two: Airgead Banking App
 * Author: Brian Beaudin
 *
 * BankingApp.h
 * Declares the BankingApp class, which handles everything the user sees:
 * collecting and validating input, displaying the two year-end reports,
 * and letting the user test different values as many times as they like.
 */

#ifndef AIRGEADBANKING_BANKINGAPP_H_
#define AIRGEADBANKING_BANKINGAPP_H_

#include <ostream>
#include <string>
#include <vector>

#include "InvestmentCalculator.h"

class BankingApp {
public:
   // Runs the input -> report -> "try again?" cycle until the user quits.
   void run();

private:
   // Screen sections
   void displayInputHeader() const;
   void displayEnteredValues(const InvestmentCalculator& t_calculator) const;
   void waitForEnter() const;
   bool askToTestAgain() const;

   // Prints one report to any output stream (the console, or a file).
   void printReport(std::ostream& t_out,
                    const std::string& t_title,
                    const std::vector<YearEndRecord>& t_records) const;

   // Validated input helpers: each keeps asking until the value is usable.
   double readDouble(const std::string& t_prompt, double t_minimum, bool t_allowMinimum) const;
   int readInt(const std::string& t_prompt, int t_minimum, int t_maximum) const;
   std::string readLine() const;

   // Formatting helpers
   static std::string formatCurrency(double t_amount);
   static std::string stripSymbols(const std::string& t_text);

   static const int MAX_YEARS = 100;
   static const int REPORT_WIDTH = 66;
};

#endif // AIRGEADBANKING_BANKINGAPP_H_
