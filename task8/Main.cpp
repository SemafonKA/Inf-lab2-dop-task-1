#define OUTPUT

#include <iostream>
#include <string>
#include "Converters_double_data.h"
#include "Converters_float_data.h"

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
      radix10_computer_number<float> result(d_num);
      cout << "Number in radix2-system is: " << result.to_binary() << endl
         << "Number in radix16-system is: " << result.to_hex() << endl << endl;
   }
   break;

   case 2:  // Double case
   {
      radix10_computer_number<double> result(d_num);
      cout << "Number in radix2-system is: " << result.to_binary() << endl
         << "Number in radix16-system is: " << result.to_hex() << endl << endl;

   }
   break;

   default:
      cout << "Wrong input." << endl << endl;
      break;
   }

}

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

string hex_to_binary(string input) {
   string output = "";
   for (auto elem : input) {
      output += radix16_to_radix2_map.find(string(1, toupper(elem)))->second;
   }

   return output;
}

int main() {
   //menu();
   string inp;
   cin >> inp;

   string double_inf_nan_exponent = "11111111111";
   string double_zero_exponent    = "00000000000";

   string str_binary_input = hex_to_binary(inp);
   double final_value = 0;

   bool is_negative = str_binary_input[0] == '1' ? true : false;
   str_binary_input = str_binary_input.substr(1);
   
   string str_exponent = str_binary_input.substr(0, 11);
   if (str_exponent == double_inf_nan_exponent) {
      if (str_binary_input.substr(12).find('1') != string::npos) {
         final_value = NAN;
      }
      else {
         final_value = is_negative ? -INFINITY : INFINITY;
      }
   }
   else {
      int shifted_int_exp = 0;
      for (int i = str_exponent.size() - 1; i >= 0; --i) {
         if (str_exponent[i] == '1') {
            shifted_int_exp += pow(2, str_exponent.size() - i - 1);
         }
      }
      //cout << "Shifted exponent: " << shifted_int_exp << endl;
      int int_exp = shifted_int_exp - pow(2, str_exponent.size() - 1) + 1;

      //cout << "Exponent: " << int_exp << endl;

      string str_mantissa = (-int_exp == (pow(2, str_exponent.size() - 1) - 1) ? "0" : "1") + str_binary_input.substr(11);
      for (int i = str_mantissa.size() - 1; i >= 0; --i) {
         if (str_mantissa[i] == '1') {
            final_value += pow(2, str_mantissa.size() - i - 1);
         }
      }
      final_value *= pow(2, int_exp - 52) * (is_negative ? -1 : 1);
   }

   cout << "Final value: " << std::scientific << final_value << endl;

   return 0;
}