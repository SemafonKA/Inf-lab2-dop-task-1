#pragma once

//#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

const int accuracy = 54;

std::map<std::string, std::string> radix2_to_radix16_map = {
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

struct normalized {
   std::string number;
   int exponent;

   normalized(std::string _number, int _exp) : number(_number), exponent(_exp) {}
};

// Split the [inp] in vector<string> by default divider (point or comma)
std::vector<std::string> split(std::string inp) {
   std::vector<std::string> splitted;
   size_t begin{ 0 }, end{ 0 };
   while (end < inp.length()) {
      if (inp[end] == '.' || inp[end] == ',') {
         if (begin != end - 1 && begin != end) {
            splitted.push_back(inp.substr(begin, end - begin));
         }
         begin = end + 1;
      }
      ++end;
   }
   splitted.push_back(inp.substr(begin, end));

   return splitted;
}

// Translate positive radix10 number to positive radix2 number
std::string radix10_to_radix2(std::string radix10_number) {
   auto parsed = split(radix10_number);   // Split the string by dot
   std::string first = std::bitset<accuracy>(atoll(parsed[0].c_str())).to_string();  // get the first part of number
   std::string second = ".";     // Variable to second part of number

   // Remove trash (left) zeros from first part of number (if all is zero, str is zero)
   int i;
   for (i = 0; i < first.size() && first[i] != '1'; ++i);
   if (first.size() == i) first = "0";
   else first = first.substr(i);

   // If number has only int part, then second part is zero
   if (parsed.size() == 1) {
      second = "";
   }
   else {
      // Work with second part like int number, add a power of second part
      long long power = 10;
      long long num = atoi(parsed[1].c_str());
      while (num % power != num) power *= 10;

      for (int i = 0; i < accuracy - first.length() && num != 0; ++i) {
         num *= 2;
         if (num / power == 1) {
            second += "1";
            num = num - power;
         }
         else {
            second += "0";
         }
      }
   }
   return first + second;
}

// Get the normalized radix2 number and exponent of number
normalized radix2_get_normalized_form(std::string radix2_number) {
   int start_pos = radix2_number.find('1');
   int point_pos = radix2_number.find('.');

   if (point_pos == std::string::npos) {
      radix2_number += ".0";
      point_pos = radix2_number.length() - 2;
   }

   if (start_pos == std::string::npos) {
      return normalized("0.0", 0);
   }

   int exponent = start_pos == 0 ? point_pos - 1 : point_pos - start_pos;

   std::string normalized_number = "1.";
   std::string tmp = "";

   for (int i = start_pos + 1; i < radix2_number.length(); ++i) {
      if (radix2_number[i] != '.') {
         tmp += radix2_number[i];
         if (radix2_number[i] == '1') {
            normalized_number += tmp;
            tmp = "";
         }
      }
   }
   if (normalized_number == "1.") {
      normalized_number += '0';
   }
   return normalized(normalized_number, exponent);
}

// Translate positive int radix2 number to positive int radix16 number
std::string int_radix2_to_radix16(std::string radix2_number) {
   while (radix2_number.length() % 4 != 0) radix2_number = "0" + radix2_number;

   std::string final_number = "";
   for (int i = 0; i < radix2_number.length(); i += 4) {
      final_number += radix2_to_radix16_map.find(radix2_number.substr(i, 4))->second;
   }
   return final_number;
}