/*
 * CS 210 - Project Two: Airgead Banking App
 * Author: Brian Beaudin
 *
 * InvestmentCalculator.h
 * Declares the InvestmentCalculator class, which holds the user's investment
 * values and calculates year-end balances and earned interest, both with and
 * without additional monthly deposits.
 */

#ifndef AIRGEADBANKING_INVESTMENTCALCULATOR_H_
#define AIRGEADBANKING_INVESTMENTCALCULATOR_H_

#include <vector>

// One row of a year-end report: the year number, the balance at the end
// of that year, and the interest earned during that year.
struct YearEndRecord {
   int year;
   double yearEndBalance;
   double yearEndEarnedInterest;
};

class InvestmentCalculator {
public:
   // Builds a calculator from the user's four input values.
   // Throws std::invalid_argument if any value is outside its allowed range.
   InvestmentCalculator(double t_initialInvestment,
                        double t_monthlyDeposit,
                        double t_annualInterest,
                        int t_numberOfYears);

   // Year-end results if the user never adds a monthly deposit.
   std::vector<YearEndRecord> calculateWithoutMonthlyDeposits() const;

   // Year-end results using the user's monthly deposit every month.
   std::vector<YearEndRecord> calculateWithMonthlyDeposits() const;

   // Read-only access to the stored input values.
   double getInitialInvestment() const;
   double getMonthlyDeposit() const;
   double getAnnualInterest() const;
   int getNumberOfYears() const;

private:
   // Shared month-by-month compounding logic used by both public reports.
   std::vector<YearEndRecord> calculateYearEndRecords(double t_monthlyDeposit) const;

   static const int MONTHS_PER_YEAR = 12;

   double m_initialInvestment;   // Starting amount of the investment
   double m_monthlyDeposit;      // Amount added at the start of every month
   double m_annualInterest;      // Annual interest rate as a percent (5 means 5%)
   int m_numberOfYears;          // How many years the investment grows
};

#endif // AIRGEADBANKING_INVESTMENTCALCULATOR_H_
