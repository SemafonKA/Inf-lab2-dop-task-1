#define OUTPUT

#include <iostream>
#include <string>
#include "Converters_machinery_double.h"
#include "Converters_machinery_float.h"

using namespace std;

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

void _toHex() {
   int type{ 0 };
   string num;
   double d_num;

   cout << "Input number:" << endl
      << "> ";
   cin >> num;
   cout << endl;
   d_num = accurate_double_parcer(num);

   cout << "Enter type of translation ([1] to float, [2] to double):" << endl
      << "> ";
   cin >> type;
   switch (type)
   {
   case 1:  // float case
   {
      Converters::computer_radix10_number<float> result(d_num);
      cout << "Number in radix2-system is: " << result.to_binary() << endl
         << "Number in radix16-system is: " << result.to_hex() << endl << endl;
   }
   break;

   case 2:  // Double case
   {
      Converters::computer_radix10_number<double> result(d_num);
      cout << "Number in radix2-system is: " << result.to_binary() << endl
         << "Number in radix16-system is: " << result.to_hex() << endl << endl;
   }
   break;

   default:
      cout << "Wrong input." << endl << endl;
      break;
   }

}

void _fromHex() {

   string inp;
   cout << "Input the value in computer form:" << endl
      << "> ";
   cin >> inp;

   Converters::computer_radix10_number<double> value(inp);

   cout << "Final value: " << std::scientific << value.to_decimal() << endl;
}

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
         _fromHex();
         stat = Stats::choose;
         break;
      }
   }

   return 0;
}

int main() {
   menu();

   return 0;
}