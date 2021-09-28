#define OUTPUT

#include <iostream>
#include "Converters_double_data.h"
#include "Converters_float_data.h"

using namespace std;

// Enumeration for state of menu
enum class Stats {
   complete,
   choose,
   toHex,
   fromHex,
};

Stats _menuChoose() {
   cout << "What you want to do:" << endl 
      << " float/double to computer hexadecimal (enter [1])" << endl
      << " or computer hexadecimal to float/double (enter [2])?" << endl
      << " (Enter [0] for exit)" << endl << "> ";
   int input = 0;
   cin >> input;
   cout << endl;

   switch (input) {
   case 0:
      return Stats::complete;
   case 1:
      return Stats::toHex;
   case 2:
      return Stats::fromHex;
   default:
      cout << "Incorrect input" << endl;
      return Stats::choose;
   }
}

void _toHex() {}

void _fromHex() {}

int menu() {
   auto stat = Stats::choose;

   while (stat != Stats::complete) {
      switch (stat) {
      case Stats::choose:
         stat = _menuChoose();
         break;
      case Stats::toHex:
         _toHex();
         stat = Stats::choose;
         break;
      case Stats::fromHex:
         //
         stat = Stats::choose;
         break;
      }
   }

   return 0;
}

double accurate_double_parcer(string input) {
   for (auto& elem : input) {
      if (elem == ',') {
         elem = '.';
      }
      else if (elem != '.' && elem != '-' && elem != '+' && elem != 'e' && (elem < '0' || elem > '9')) {
         return NAN;
      }
   }

   return atof(input.c_str());
}

int main() {
   //menu();
   string ee;
   cin >> ee;

   double eee = accurate_double_parcer(ee);

   radix10_computer_number<double> a(eee);
   cout << a.to_binary() << endl << a.to_hex() << endl;

   return 0;
}
