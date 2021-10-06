#pragma once
#include "Converters_toRadix10.h"

namespace Converters
{
   const std::string computer_radix10_number<double>::_inf_nan_exponent = "11111111111";
   const std::string computer_radix10_number<double>::_zero_exponent = "00000000000";
   const int computer_radix10_number<double>::exponent_size = 11;
   const int computer_radix10_number<double>::mantissa_size = 52;
}