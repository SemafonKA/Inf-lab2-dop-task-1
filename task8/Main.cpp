#define OUTPUT

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <map>

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

template<typename T = double>
class radix10_computer_number {
   T _decimal_number = 0.0;
   bool _is_negative = false;
   string _binary_number = "";

   map<string, string> radix2_to_radix16_map = {
   {"0000", "0"},
   {"0001", "1"},
   {"0010", "2"},
   {"0011", "3"},
   {"0100", "4"},
   {"0101", "5"},
   {"0110", "6"},
   {"0111", "7"},
   {"1000", "8"},
   {"1001", "9"},
   {"1010", "A"},
   {"1011", "B"},
   {"1100", "C"},
   {"1101", "D"},
   {"1110", "E"},
   {"1111", "F"},
   };

public:
   radix10_computer_number(T num) : _decimal_number(num) {
      int mantissa_size = 53;
      int exponent_size = 11;

      // Choosing the size of constants by the choosed type
      if (typeid(T) == typeid(float)) {
         mantissa_size = 24;
         exponent_size = 8;
      }
      else if (typeid(T) != typeid(double)) throw exception("Wrong data type!");

      // Split the num to some parts
      _is_negative = num >= 0 ? false : true;
      T first_part = floor(num);
      T second_part = num - first_part;
      string first_part_binary;
      string second_part_binary;

      // Get the first part of num in radix2
      int i = 0;
      while (first_part != 0.0) {
         // If length is more than [mantissa_size], reduce the string
         if (i == mantissa_size) {
            first_part_binary = first_part_binary.substr(1);
         }
         if (i != mantissa_size) ++i;

         auto mod = fmod(first_part, 2.0);
         first_part = (first_part - mod) / 2.0;
         if (mod == 1.0) {
            first_part_binary += '1';
         }
         else {
            first_part_binary += '0';
         }
      }
      reverse(first_part_binary.begin(), first_part_binary.end());

      // Calc shift of number, and also move the second part, if first part is empty
      int shift = 0;
      if (i == 0) {
         while (second_part < 1) {
            --shift;
            second_part *= 2;
         }
         second_part_binary += '1';
         second_part -= 1;
         ++i;
      }
      else {
         shift = i - 1;
      }
      shift += pow(2, exponent_size - 1) - 1;

      // Translate shift part to binary code
      string shift_binary = "";
      for (int i = 0; i < exponent_size; ++i) {
         auto mod = shift % 2;
         shift /= 2.0;
         if (mod == 1) {
            shift_binary += '1';
         }
         else {
            shift_binary += '0';
         }
      }
      reverse(shift_binary.begin(), shift_binary.end());

      // Get the second part in radix2, while we got [mantissa_size]
      while (i++ < mantissa_size) {
         second_part *= 2.0;

         if (floor(second_part) == 1.0) {
            second_part_binary += '1';
            second_part -= 1;
         }
         else {
            second_part_binary += '0';
         }
      }

      // Finally, radix2 num
      _binary_number = (_is_negative ? '1' : '0') + shift_binary + (first_part_binary + second_part_binary).substr(1);
   }

   T to_decimal() {
      return _decimal_number;
   }

   string to_binary() {
      return _binary_number;
   }

   string to_hex() {
      string final_number = "";
      for (int i = 0; i < _binary_number.length(); i += 4) {
         final_number += radix2_to_radix16_map.find(_binary_number.substr(i, 4))->second;
      }
      return final_number;
   }

   bool is_negative() {
      return _is_negative;
   }
};

int main() {
   //menu();
   double eee;
   cin >> eee;

   radix10_computer_number<double> a(eee);
   cout << a.to_decimal() << endl << a.to_hex() << endl;

   return 0;
}
