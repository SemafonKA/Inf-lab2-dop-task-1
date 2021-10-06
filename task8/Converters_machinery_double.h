#pragma once
#include "Converters_machinery.h"

namespace Converters
{
   const std::string computer_radix10_number<double>::_inf_nan_exponent = "11111111111";
   const std::string computer_radix10_number<double>::_zero_exponent = "00000000000";

   const std::string computer_radix10_number<double>::_plusInf{ "0111111111110000000000000000000000000000000000000000000000000000" };
   const std::string computer_radix10_number<double>::_minusInf{ "1111111111110000000000000000000011111111111111111111111111111111" };
   const std::string computer_radix10_number<double>::_NAN{ "0111111110000000000000000000000000000000000000000000000000000001" };

   const int computer_radix10_number<double>::exponent_size = 11;
   const int computer_radix10_number<double>::mantissa_size = 52;
}