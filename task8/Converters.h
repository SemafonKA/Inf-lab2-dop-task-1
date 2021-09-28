#pragma once

#include <string>
#include <map>

template<typename T = double>
class radix10_computer_number {
   T _decimal_number = 0.0;
   bool _is_negative = false;
   std::string _binary_number = "";

   static const std::map<std::string, std::string> radix2_to_radix16_map;

   static const std::string _plusInf;
   static const std::string _minusInf;
   static const std::string _plusZero;
   static const std::string _minusZero;
   static const std::string _NAN;

   static const int mantissa_size;
   static const int exponent_size;

public:
   radix10_computer_number(T num) : _decimal_number(num) {
      if (isinf(num)) {
         _is_negative = std::signbit(num);
         if (!_is_negative) {
            _binary_number = _plusInf;
         }
         else {
            _binary_number = _minusInf;
         }
      }
      else if (isnan(num)) {
         _binary_number = _NAN;
      }
      else if (num == 0.0) {
         _is_negative = std::signbit(num);
         if (!_is_negative) {
            _binary_number = _plusZero;
         }
         else {
            _binary_number = _minusZero;
         }
      }
      else {
         // Split the num to some parts
         _is_negative = std::signbit(num);
         num = std::abs(num);
         T first_part = std::floor(num);
         T second_part = num - first_part;
         std::string first_part_binary;
         std::string second_part_binary;

         // Get the first part of num in radix2
         int i = 0, j = 0;
         while (first_part != 0.0) {
            // If length is more than [mantissa_size], reduce the string
            if (i == mantissa_size) {
               ++j;
               first_part_binary = first_part_binary.substr(1);
            }
            if (i != mantissa_size) ++i;

            auto mod = std::fmod(first_part, 2.0);
            first_part = (first_part - mod) / 2.0;
            if (mod == 1.0) {
               first_part_binary += '1';
            }
            else {
               first_part_binary += '0';
            }
         }
         std::reverse(first_part_binary.begin(), first_part_binary.end());

         // Calc shift of number, and also move the second part, if first part is empty
         int shift = pow(2, exponent_size - 1) - 1;
         if (i == 0) {
            while (second_part < 1 && shift != 0) {
               --shift;
               second_part *= 2;
            }
            second_part_binary += '1';
            second_part -= 1;
            ++i;
         }
         else {
            shift += i - 1 + j;
         }

         // Translate shift part to binary code
         std::string shift_binary = "";
         for (int i = 0; i < exponent_size; ++i) {
            auto mod = shift % 2;
            shift /= 2;
            if (mod == 1) {
               shift_binary += '1';
            }
            else {
               shift_binary += '0';
            }
         }
         std::reverse(shift_binary.begin(), shift_binary.end());

         // Get the second part in radix2, while we got [mantissa_size]
         while (i++ < mantissa_size) {
            second_part *= 2.0;

            if (floor(second_part) == 1.0) {
               second_part_binary += '1';
               second_part -= 1;
            }
            else {
               second_part_binary += '0';
            }
         }

         // Finally, radix2 num
         _binary_number = (_is_negative ? '1' : '0') + shift_binary + (first_part_binary + second_part_binary).substr(1);
      }
   }

   T to_decimal() {
      return _decimal_number;
   }

   std::string to_binary() {
      return _binary_number;
   }

   std::string to_hex() {
      std::string final_number = "";
      for (int i = 0; i < _binary_number.length(); i += 4) {
         final_number += radix2_to_radix16_map.find(_binary_number.substr(i, 4))->second;
      }
      return final_number;
   }

   bool is_negative() {
      return _is_negative;
   }
};