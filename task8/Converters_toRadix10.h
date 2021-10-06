#pragma once

#include <string>
#include <map>
#include "Converters_binary-hex.h"

namespace Converters
{
   template <typename T>
   class computer_radix10_number {
   private:
      std::string _hex_number = "";
      T _decimal_number = 0.0;
      bool _is_negative = false;

      static const std::string _inf_nan_exponent;
      static const std::string _zero_exponent;
      static const int exponent_size;
      static const int mantissa_size;

   public:
      computer_radix10_number(std::string computer_num) {
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
      }

      std::string to_binary() {
         return hex_to_binary(_hex_number);
      }

      T to_decimal() {
         return _decimal_number;
      }

      std::string to_hex() {
         return _hex_number;
      }

      bool is_negative() {
         return _is_negative;
      }
   };

}