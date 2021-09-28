#pragma once

#include "Converters.h"

const std::map<std::string, std::string> radix10_computer_number<double>::radix2_to_radix16_map = {
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

const std::string radix10_computer_number<double>::_plusInf  { "0111111111110000000000000000000000000000000000000000000000000000" };
const std::string radix10_computer_number<double>::_minusInf { "1111111111110000000000000000000011111111111111111111111111111111" };
const std::string radix10_computer_number<double>::_plusZero { "0000000000000000000000000000000000000000000000000000000000000000" };
const std::string radix10_computer_number<double>::_minusZero{ "1000000000000000000000000000000000000000000000000000000000000000" };
const std::string radix10_computer_number<double>::_NAN      { "0111111110000000000000000000000000000000000000000000000000000001" };

const int radix10_computer_number<double>::mantissa_size = 53;
const int radix10_computer_number<double>::exponent_size = 11;