#pragma once

#include "Converters.h"

const std::string radix10_computer_number<double>::_plusInf  { "0111111111110000000000000000000000000000000000000000000000000000" };
const std::string radix10_computer_number<double>::_minusInf { "1111111111110000000000000000000011111111111111111111111111111111" };
const std::string radix10_computer_number<double>::_NAN      { "0111111110000000000000000000000000000000000000000000000000000001" };

const int radix10_computer_number<double>::mantissa_size = 53;
const int radix10_computer_number<double>::exponent_size = 11;