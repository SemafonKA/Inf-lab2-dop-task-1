#pragma once

#include <string>
#include <map>

namespace converters
{
   const std::map<std::string, std::string> radix2_to_radix16_map = {
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

   const std::map<std::string, std::string> radix16_to_radix2_map = {
      {"0", "0000"},
      {"1", "0001"},
      {"2", "0010"},
      {"3", "0011"},
      {"4", "0100"},
      {"5", "0101"},
      {"6", "0110"},
      {"7", "0111"},
      {"8", "1000"},
      {"9", "1001"},
      {"A", "1010"},
      {"B", "1011"},
      {"C", "1100"},
      {"D", "1101"},
      {"E", "1110"},
      {"F", "1111"},
   };

   inline std::string binary_to_hex(std::string binary_number)
   {
      if (binary_number.size() % 4 != 0)
         binary_number = std::string(4 - binary_number.size() % 4, '0') + binary_number;

      std::string hex_number;
      for (int i = 0; i < binary_number.size(); i += 4)
      {
         hex_number += radix2_to_radix16_map.find(binary_number.substr(i, 4))->second;
      }
      return hex_number;
   }

   inline std::string hex_to_binary(const std::string& hex_number)
   {
      std::string binary_number;
      for (const auto elem : hex_number)
      {
         binary_number += radix16_to_radix2_map.find(std::string(1, toupper(elem)))->second;
      }

      return binary_number;
   }

   inline bool is_float_double_hex(const std::string& number)
   {
      if (number.size() % 8 <= 1)
      {
         return true;
      }
      return false;
   }

}