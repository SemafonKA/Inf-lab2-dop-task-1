#pragma once

#include "Converters_fromRadix10.h"

namespace Converters
{
   const std::string radix10_computer_number<float>::_plusInf{ "01111111100000000000000000000000" };
   const std::string radix10_computer_number<float>::_minusInf{ "11111111100000000000000000000000" };
   const std::string radix10_computer_number<float>::_NAN{ "10000000000000000000000000000000" };

   const int radix10_computer_number<float>::mantissa_size = 24;
   const int radix10_computer_number<float>::exponent_size = 8;
}