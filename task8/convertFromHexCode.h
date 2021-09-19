#pragma once

#include <string>
#include <vector>
#include <map>
//#include <bitset>

std::map<std::string, std::string> radix16_to_radix2_map = {
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

std::string int_radix16_to_radix2(std::string radix16_number) {
   std::string final_number;

   for (auto elem : radix16_number) {
      final_number += radix16_to_radix2_map.find(std::to_string(elem))->second;
   }

   return final_number;
}