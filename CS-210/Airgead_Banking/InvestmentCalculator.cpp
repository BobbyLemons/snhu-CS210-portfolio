/*
 * CS 210 - Project Two: Airgead Banking App
 * Author: Brian Beaudin
 *
 * InvestmentCalculator.cpp
 * Defines the InvestmentCalculator class. Interest is compounded monthly
 * using the formula from the Airgead Banking functional requirements:
 *    Interest = (Opening Amount + Deposited Amount) * ((Interest Rate / 100) / 12)
 */

#include "InvestmentCalculator.h"

#include <stdexcept>

// Stores the user's values after confirming each one is in a valid range.
// Invalid values throw an exception so the caller can report the problem
// and let the user try again instead of producing a meaningless report.
InvestmentCalculator::InvestmentCalculator(double t_initialInvestment,
                                           double t_monthlyDeposit,
                                           double t_annualInterest,
                                           int t_numberOfYears)
   : m_initialInvestment(t_initialInvestment),
     m_monthlyDeposit(t_monthlyDeposit),
     m_annualInterest(t_annualInterest),
     m_numberOfYears(t_numberOfYears) {
   if (m_initialInvestment <= 0.0) {
      throw std::invalid_argument("Initial investment must be greater than zero.");
   }
   if (m_monthlyDeposit < 0.0) {
      throw std::invalid_argument("Monthly deposit cannot be negative.");
   }
   if (m_annualInterest < 0.0) {
      throw std::invalid_argument("Annual interest cannot be negative.");
   }
   if (m_numberOfYears <= 0) {
      throw std::invalid_argument("Number of years must be at least 1.");
   }
}

// The first report: same calculation, but with no monthly deposits.
std::vector<YearEndRecord> InvestmentCalculator::calculateWithoutMonthlyDeposits() const {
   return calculateYearEndRecords(0.0);
}

// The second report: the user's monthly deposit is added every month.
std::vector<YearEndRecord> InvestmentCalculator::calculateWithMonthlyDeposits() const {
   return calculateYearEndRecords(m_monthlyDeposit);
}

// Walks through every month of every year, following the steps in the
// functional requirements: Opening Amount + Deposited Amount = Total,
// Total * monthly rate = Interest, Total + Interest = Closing Balance.
// The closing balance becomes next month's opening amount.
std::vector<YearEndRecord> InvestmentCalculator::calculateYearEndRecords(double t_monthlyDeposit) const {
   std::vector<YearEndRecord> records;
   records.reserve(static_cast<std::size_t>(m_numberOfYears));

   // Dividing by 100 converts the percent to a decimal; dividing by 12
   // spreads the annual rate across the months of the year.
   const double monthlyRate = (m_annualInterest / 100.0) / MONTHS_PER_YEAR;

   double openingAmount = m_initialInvestment;

   for (int year = 1; year <= m_numberOfYears; ++year) {
      double interestThisYear = 0.0;

      for (int month = 1; month <= MONTHS_PER_YEAR; ++month) {
         double total = openingAmount + t_monthlyDeposit;
         double interest = total * monthlyRate;
         double closingBalance = total + interest;

         interestThisYear += interest;
         openingAmount = closingBalance;   // Carry the balance into next month
      }

      // Values stay unrounded here; rounding to the cent happens only when
      // the report is displayed, so small rounding errors never accumulate.
      records.push_back({year, openingAmount, interestThisYear});
   }

   return records;
}

double InvestmentCalculator::getInitialInvestment() const {
   return m_initialInvestment;
}

double InvestmentCalculator::getMonthlyDeposit() const {
   return m_monthlyDeposit;
}

double InvestmentCalculator::getAnnualInterest() const {
   return m_annualInterest;
}

int InvestmentCalculator::getNumberOfYears() const {
   return m_numberOfYears;
}
