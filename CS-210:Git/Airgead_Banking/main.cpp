/*
 * CS 210 - Project Two: Airgead Banking App
 * Author: Brian Beaudin
 *
 * main.cpp
 * Program entry point. Following the Airgead Banking standards, main() is a
 * minimal driver: it creates the application object and starts it. All of
 * the program's logic lives in the BankingApp and InvestmentCalculator classes.
 */

#include <exception>
#include <iostream>
#include <memory>

#include "BankingApp.h"

int main() {
   try {
      // A smart pointer manages the object's memory automatically,
      // avoiding raw new/delete as the standards document requires.
      auto app = std::make_unique<BankingApp>();
      app->run();
   }
   catch (const std::exception& error) {
      // Any unexpected error ends the program gracefully with a message.
      std::cout << "\nThe program has ended: " << error.what() << std::endl;
      return 1;
   }

   return 0;
}
