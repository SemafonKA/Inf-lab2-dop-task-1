#pragma once
#include "Converters_machinery.h"

namespace Converters
{
   const std::string computer_radix10_number<float>::_inf_nan_exponent = "11111111";
   const std::string computer_radix10_number<float>::_zero_exponent = "00000000";

   const std::string computer_radix10_number<float>::_plusInf{ "01111111100000000000000000000000" };
   const std::string computer_radix10_number<float>::_minusInf{ "11111111100000000000000000000000" };
   const std::string computer_radix10_number<float>::_NAN{ "10000000000000000000000000000000" };

   const int computer_radix10_number<float>::exponent_size = 8;
   const int computer_radix10_number<float>::mantissa_size = 23;
}