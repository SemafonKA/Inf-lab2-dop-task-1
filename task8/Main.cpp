#include <iostream>
#include <string>
#include "Converters_machinery.h"

using namespace std;

double accurate_double_parcer(string input)
{
   for (auto& elem : input)
   {
      if (elem == ',')
      {
         elem = '.';
      }
      else if (elem != '.' && elem != '-' && elem != '+' && elem != 'e' && (elem < '0' || elem > '9'))
      {
         return NAN;
      }
   }

   return atof(input.c_str());
}

// Enumeration for state of menu
enum class stats
{
   complete,
   choose,
   to_hex,
   from_hex,
};

stats _menuChoose()
{
   cout << "What you want to do:" << endl
      << " float/double to computer hexadecimal (enter [1])" << endl
      << " or computer hexadecimal to float/double (enter [2])?" << endl
      << " (Enter [0] for exit)" << endl << "> ";
   int input = 0;
   cin >> input;
   cout << endl;

   switch (input)
   {
   case 0:
      return stats::complete;
   case 1:
      return stats::to_hex;
   case 2:
      return stats::from_hex;
   default:
      cout << "Incorrect input" << endl;
      return stats::choose;
   }
}

void _toHex()
{
   int type { 0 };
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
      converters::computer_radix10_number<float> result(d_num);
      cout << "Number in radix2-system is: " << result.to_binary() << endl
         << "Number in radix16-system is: " << result.to_hex() << endl << endl;
   }
   break;

   case 2:  // Double case
   {
      converters::computer_radix10_number<double> result(d_num);
      cout << "Number in radix2-system is: " << result.to_binary() << endl
         << "Number in radix16-system is: " << result.to_hex() << endl << endl;
   }
   break;

   default:
   {
      cout << "Wrong input." << endl << endl;
   }
   break;
   }

}

void _fromHex()
{

   string inp;
   cout << "Input the value in computer form:" << endl
      << "> ";
   cin >> inp;

   if (inp.length() == 16 /*Length of double*/)
   {
      converters::computer_radix10_number<double> value(inp);
      cout << "Final value: " << std::scientific << value.to_decimal() << endl;
   }
   else
   {
      converters::computer_radix10_number<float> value(inp);
      cout << "Final value: " << std::scientific << value.to_decimal() << endl;
   }
   cout << std::defaultfloat << endl;
}

int menu()
{
   auto stat = stats::choose;

   while (stat != stats::complete)
   {
      switch (stat)
      {
      case stats::choose:
         stat = _menuChoose();
         break;
      case stats::to_hex:
         _toHex();
         stat = stats::choose;
         break;
      case stats::from_hex:
         _fromHex();
         stat = stats::choose;
         break;
      }
   }

   return 0;
}

int main()
{
   try
   {
      menu();
   }
   catch (std::exception e)
   {
      cout << e.what() << endl;
   }
   return 0;
}