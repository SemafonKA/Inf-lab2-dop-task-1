#pragma once

#include "Converters.h"

const std::map<std::string, std::string> radix10_computer_number<float>::radix2_to_radix16_map = {
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

const std::string radix10_computer_number<float>::_plusInf  { "01111111100000000000000000000000" };
const std::string radix10_computer_number<float>::_minusInf { "11111111100000000000000000000000" };
const std::string radix10_computer_number<float>::_plusZero { "00000000000000000000000000000000" };
const std::string radix10_computer_number<float>::_minusZero{ "10000000000000000000000000000000" };
const std::string radix10_computer_number<float>::_NAN{ "10000000000000000000000000000000" };

const int radix10_computer_number<float>::mantissa_size = 24;
const int radix10_computer_number<float>::exponent_size = 8;