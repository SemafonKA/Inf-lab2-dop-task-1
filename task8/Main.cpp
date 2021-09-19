#define OUTPUT

#include <iostream>
#include "convertToHexCode.h"

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

void _toHex() {
   cout <<"You want to convert float number (enter [1]) or double number (enter [2])? : ";
   int stat = 0;
   cin >> stat;

   string input_num;
   cout << "Input the number: ";
   cin >> input_num;

   // Get the sign of number
   bool is_negative = false;
   if (input_num[0] == '-') {
      is_negative = true;
      input_num = input_num.substr(1);
   }

#ifdef OUTPUT
   cout << "Module of input number is: " << input_num << endl;
   cout << "In radix2 system number is: " << radix10_to_radix2(input_num) << endl;
#endif // OUTPUT

   // Get normalized number with his exponent value (in int type)
   auto normalize = radix2_get_normalized_form(radix10_to_radix2(input_num)); // Get the normalized number
   string shifted_exponent = "";
   string formatted_mantissa = normalize.number.substr(2);  // Remove the "1." part of normalized num
   int exponent_length{};
   int mantissa_length{};

#ifdef OUTPUT
   cout << "Normalized part is: " << normalize.number << endl;
   cout << "exponent is: " << normalize.exponent << endl;
#endif // OUTPUT

   switch (stat) {
   case 1:  // Float numbers
      exponent_length = 8;
      mantissa_length = 23;
      break;

   case 2:  // double numbers
      exponent_length = 11;
      mantissa_length = 52;
      break;

   default:
      cout << "Wrong number. Choosed the float number" << endl;
      exponent_length = 8;
      mantissa_length = 23;
      break;
   }

   // If number is 0.0, then shifted_exponent is full-zero.
   if (normalize.number != "0.0") {
      shifted_exponent = radix10_to_radix2(to_string(normalize.exponent + ((int)pow(2, exponent_length - 1) - 1)));
   }
   // add a missing bits
   for (int i = shifted_exponent.length(); i < exponent_length; ++i) shifted_exponent = "0" + shifted_exponent; 

#ifdef OUTPUT
   cout << "Final shifted exponent of num is: " << shifted_exponent << endl;
#endif // OUTPUT

   // if length more than [mantissa_length], trim the string
   if (formatted_mantissa.length() > mantissa_length) {
      formatted_mantissa = formatted_mantissa.substr(0, mantissa_length);
   }
   // add a missing bits
   for (int i = formatted_mantissa.length(); i < mantissa_length; ++i) formatted_mantissa += "0";

#ifdef OUTPUT
   cout << "Final formatted mantissa of num is: " << formatted_mantissa << endl;
#endif // OUTPUT

   string result_number = is_negative ? "1" : "0";
   result_number += shifted_exponent + formatted_mantissa;
   
#ifdef OUTPUT
   cout << "Result number in radix2 is: " << result_number << endl;
#endif // OUTPUT

   cout << "Result number is: " << int_radix2_to_radix16(result_number) << endl << endl;
}

void _fromHex() {
   string input_num;
   cout << "Input the number: ";
   cin >> input_num;

   int exponent_length{};
   int mantissa_length{};
   bool is_negative = false;

   switch (input_num.length()) {
   case 32:
      exponent_length = 8;
      mantissa_length = 23;
      break;

   case 64:
      exponent_length = 11;
      mantissa_length = 52;
      break;
      
   default:
      cout << "Wrong length of number." << endl << endl;
      return;
   }

   is_negative = input_num[0] == '1';
   string shifted_exponent = input_num.substr(1, exponent_length);
   string 
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
         //
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