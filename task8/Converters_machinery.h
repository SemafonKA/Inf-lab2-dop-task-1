#pragma once

#include <string>
#include <map>
#include "Converters_binary-hex.h"

namespace Converters {

   template <typename T = double>
   class computer_radix10_number {
   private:
      std::string _hex_number = "";
      T _decimal_number = 0.0;
      bool _is_negative = false;

      static const std::string _inf_nan_exponent;
      static const std::string _zero_exponent;

      static const std::string _plusInf;
      static const std::string _minusInf;
      static const std::string _NAN;

      static const int exponent_size;
      static const int mantissa_size;

      T _translate_to_decimal(std::string computer_num) {
         if ((computer_num.size() != sizeof(T) * 2) && (computer_num.size() != sizeof(T) * 8)) {
            std::string err = std::string("Error: wrong length of computer number: length is ") + std::to_string(computer_num.size());
            throw std::exception(err.c_str());
         }

         std::string binary_number = "";
         if (computer_num.size() == sizeof(T) * 8) {
            binary_number = computer_num;
            _hex_number = binary_to_hex(binary_number);
         }
         else {
            _hex_number = computer_num;
            binary_number = hex_to_binary(_hex_number);
         }

         _is_negative = binary_number[0] == '1' ? true : false;
         binary_number = binary_number.substr(1);

         std::string str_exponent = binary_number.substr(0, 11);
         if (str_exponent == _inf_nan_exponent) {
            if (binary_number.substr(12).find('1') != std::string::npos) {
               _decimal_number = NAN;
            }
            else {
               _decimal_number = _is_negative ? -INFINITY : INFINITY;
            }
         }
         else {
            // Translate exponent from binary to decimal
            int shifted_int_exp = 0;
            for (int i = str_exponent.size() - 1; i >= 0; --i) {
               if (str_exponent[i] == '1') {
                  shifted_int_exp += pow(2, str_exponent.size() - i - 1);
               }
            }
            // Substract shift (2^(exp_size-1) + 1)
            int int_exp = shifted_int_exp - pow(2, str_exponent.size() - 1) + 1;

            // Get binary mantissa with hidden bit and normalized to number without fraction part
            std::string str_mantissa = (/*-int_exp == (pow(2, str_exponent.size() - 1) - 1)*/shifted_int_exp == 0 ? "0" : "1") + binary_number.substr(exponent_size);
            for (int i = str_mantissa.size() - 1; i >= 0; --i) {
               if (str_mantissa[i] == '1') {
                  _decimal_number += pow(2, str_mantissa.size() - i - 1);
               }
            }
            _decimal_number *= pow(2, int_exp - 52) * (_is_negative ? -1 : 1);
         }

         return _decimal_number;
      }

      std::string _translate_to_hex(T num) {
         std::string _binary_number = "";
         if (isnan(num)) {
            _binary_number = _NAN;
         }
         else {
            _is_negative = std::signbit(num);

            if (isinf(num)) {
               if (!_is_negative) {
                  _binary_number = _plusInf;
               }
               else {
                  _binary_number = _minusInf;
               }
            }
            else {
               // Split the num to some parts
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
         _hex_number = binary_to_hex(_binary_number);
         return _hex_number;
      }

   public:
      /// <summary>
      /// Constructor for machinery num from computer format
      /// </summary>
      /// <param name="computer_num"> - string with hex or binary formatted number</param>
      computer_radix10_number(std::string computer_num) {
         _translate_to_decimal(computer_num);
      }

      /// <summary>
      /// Default constructor
      /// </summary>
      computer_radix10_number(void) {}

      /// <summary>
      /// Constructor for machinery num from decimal format
      /// </summary>
      /// <param name="decimal_num"> - number in decimal format</param>
      computer_radix10_number(T decimal_num) {
         _decimal_number = decimal_num;
         _translate_to_hex(decimal_num);
      }

      /// <summary>
      /// Get the binary-formatted number in [std::string]
      /// </summary>
      std::string to_binary() {
         return hex_to_binary(_hex_number);
      }

      /// <summary>
      /// Get the decimal-formatted number in [T]
      /// </summary>
      T to_decimal() {
         return _decimal_number;
      }

      /// <summary>
      /// Get the hex-formatted number in [std::string]
      /// </summary>
      std::string to_hex() {
         return _hex_number;
      }

      /// <summary>
      /// Get the sign of number in [bool]
      /// </summary>
      bool is_negative() {
         return _is_negative;
      }
   };


} // namespace Converters