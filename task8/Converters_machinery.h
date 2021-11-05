#pragma once

#include <string>
#include <map>
#include "Converters_binary-hex.h"

namespace converters
{

   template <typename T = double>
   class computer_radix10_number
   {
   private:
      std::string hex_number_;
      T decimal_number_ = 0.0;
      bool is_negative_ = false;

      static const std::string inf_nan_exponent;
      static const std::string zero_exponent;

      static const std::string plus_inf;
      static const std::string minus_inf;
      static const std::string nan;

      static const int exponent_size;
      static const int mantissa_size;

      T _translate_to_decimal(std::string hex_number)
      {
         if (hex_number.size() != sizeof(T) * 2)
         {
            throw std::exception((std::string("Error: wrong length of computer number: length is ") + std::to_string(hex_number.size())).c_str());
         }

         std::string binary_number = hex_to_binary(hex_number);

         is_negative_ = binary_number[0] == '1' ? true : false;
         binary_number = binary_number.substr(1);

         std::string str_exponent = binary_number.substr(0, exponent_size);
         if (str_exponent == inf_nan_exponent)
         {
            if (binary_number.substr(exponent_size + 1).find('1') != std::string::npos)
            {
               decimal_number_ = is_negative_ ? NAN : -NAN;
            }
            else
            {
               decimal_number_ = is_negative_ ? -INFINITY : INFINITY;
            }
         }
         else
         {
            // Translate exponent from binary to decimal
            int shifted_int_exp = 0;
            for (int i = exponent_size - 1; i >= 0; --i)
            {
               if (str_exponent[i] == '1')
               {
                  shifted_int_exp += pow(2, exponent_size - i - 1);
               }
            }
            // Substract shift (2^(exp_size-1) + 1)
            int int_exp = shifted_int_exp - pow(2, exponent_size - 1) + 1;

            // Get binary mantissa with hidden bit and normalized to number without fraction part
            std::string str_mantissa = (shifted_int_exp == 0 ? "0" : "1") + binary_number.substr(exponent_size);
            for (int i = mantissa_size - 1; i >= 0; --i)
            {
               if (str_mantissa[i] == '1')
               {
                  decimal_number_ += pow(2, str_mantissa.size() - i - 1);
               }
            }
            // Because min exp is not in shifted_int_exp == 0, but 1
            if (shifted_int_exp == 0) int_exp++;
            decimal_number_ *= pow(2, int_exp - mantissa_size + 1) * (is_negative_ ? -1 : 1);
         }

         return decimal_number_;
      }

      std::string _translate_to_hex(T num)
      {
         std::string binary_number;
         if (isnan(num))
         {
            binary_number = nan;
         }
         else
         {
            is_negative_ = std::signbit(num);

            if (isinf(num))
            {
               if (!is_negative_)
               {
                  binary_number = plus_inf;
               }
               else
               {
                  binary_number = minus_inf;
               }
            }
            else
            {
               // Split the num to some parts
               num = std::abs(num);
               T first_part = std::floor(num);
               T second_part = num - first_part;
               std::string first_part_binary;
               std::string second_part_binary;

               // Get the first part of num in radix2
               int i = 0, j = 0;
               while (first_part != 0.0)
               {
                  // If length is more than [mantissa_size], reduce the string
                  if (i == mantissa_size)
                  {
                     ++j;
                     first_part_binary = first_part_binary.substr(1);
                  }
                  if (i != mantissa_size) ++i;

                  double mod = std::fmod(first_part, 2.0);
                  first_part = (first_part - mod) / 2.0;
                  if (mod == 1.0)
                  {
                     first_part_binary += '1';
                  }
                  else
                  {
                     first_part_binary += '0';
                  }
               }
               std::reverse(first_part_binary.begin(), first_part_binary.end());

               // Calc shift of number, and also move the second part, if first part is empty
               int shift = pow(2, exponent_size - 1) - 1;
               if (i == 0)
               {
                  while (second_part < 1 && shift != 0)
                  {
                     --shift;
                     second_part *= 2;
                  }
                  second_part_binary += '1';
                  second_part -= 1;
                  ++i;
               }
               // If first part isn't empty, calc it by i (size of first part) and j (shift of first part)
               else
               {
                  shift += i - 1 + j;
               }

               // Translate shift part to binary code
               std::string shift_binary = "";
               for (int i = 0; i < exponent_size; ++i)
               {
                  int mod = shift % 2;
                  shift /= 2;
                  if (mod == 1)
                  {
                     shift_binary += '1';
                  }
                  else
                  {
                     shift_binary += '0';
                  }
               }
               std::reverse(shift_binary.begin(), shift_binary.end());

               // Get the second part in radix2, while we got [mantissa_size]
               while (i++ < mantissa_size)
               {
                  second_part *= 2.0;

                  if (floor(second_part) == 1.0)
                  {
                     second_part_binary += '1';
                     second_part -= 1;
                  }
                  else
                  {
                     second_part_binary += '0';
                  }
               }

               // Finally, radix2 num (and don't forget to delete hidden bit)
               binary_number = (is_negative_ ? '1' : '0') + shift_binary + (first_part_binary + second_part_binary).substr(1);
            }
         }
         hex_number_ = binary_to_hex(binary_number);
         return hex_number_;
      }

   public:

      /// <summary>
      /// Default constructor
      /// </summary>
      computer_radix10_number(void)
      {}

      /// <summary>
      /// Constructor for machinery num from computer format
      /// </summary>
      /// <param name="computer_num"> - string with hex or binary formatted number</param>
      computer_radix10_number(const std::string& computer_num)
      {
         *this = computer_num;
      }

      /// <summary>
      /// Constructor for machinery num from decimal format
      /// </summary>
      /// <param name="decimal_num"> - number in decimal format</param>
      computer_radix10_number(const T decimal_num)
      {
         *this = decimal_num;
      }

      /// <summary>
      /// Operator for initialise new number from hex or binary format
      /// </summary>
      /// <param name="computer_num"> - string with hex or binary formatted number</param>
      computer_radix10_number<T>& operator= (const std::string& computer_num)
      {
         if (is_float_double_hex(computer_num))
         {
            hex_number_ = computer_num;
         }
         else
         {
            hex_number_ = binary_to_hex(computer_num);
         }

         decimal_number_ = _translate_to_decimal(computer_num);

         return *this;
      }

      /// <summary>
      /// Operator for initialise new number from decimal format
      /// </summary>
      /// <param name="decimal_num"> - string in decimal format</param>
      computer_radix10_number<T>& operator= (const T decimal_num)
      {
         decimal_number_ = decimal_num;
         _translate_to_hex(decimal_num);

         return *this;
      }

      computer_radix10_number<T>& operator= (const computer_radix10_number<T>& _right)
      {
         computer_radix10_number<T> new_num;
         new_num.hex_number_ = _right.hex_number_;
         new_num.decimal_number_ = _right.decimal_number_;
         new_num.is_negative_ = _right.is_negative_;

         return _right;
      }

      bool operator== (const computer_radix10_number<T>& _right) const
      {
         return decimal_number_ == _right.decimal_number_;
      }

      bool operator< (const computer_radix10_number<T>& _right) const
      {
         return decimal_number_ < _right.decimal_number_;
      }

      bool operator> (const computer_radix10_number<T>& _right) const
      {
         return decimal_number_ > _right.decimal_number_;
      }

      bool operator<= (const computer_radix10_number<T>& _right) const
      {
         return decimal_number_ <= _right.decimal_number_;
      }

      bool operator>= (const computer_radix10_number<T>& _right) const
      {
         return decimal_number_ >= _right.decimal_number_;
      }

      computer_radix10_number<T> operator+ (const computer_radix10_number<T>& _right) const
      {
         return computer_radix10_number<T>(this->decimal_number_ + _right.decimal_number_);
      }

      computer_radix10_number<T> operator- (const computer_radix10_number<T>& _right) const
      {
         return computer_radix10_number<T>(this->decimal_number_ - _right.decimal_number_);
      }

      computer_radix10_number<T> operator* (const computer_radix10_number<T>& _right) const
      {
         return computer_radix10_number<T>(this->decimal_number_ * _right.decimal_number_);
      }

      computer_radix10_number<T> operator/ (const computer_radix10_number<T>& _right) const
      {
         return computer_radix10_number<T>(this->decimal_number_ / _right.decimal_number_);
      }

      /// <summary>
      /// Get the binary-formatted number in [std::string]
      /// </summary>
      std::string to_binary() const
      {
         return hex_to_binary(hex_number_);
      }

      /// <summary>
      /// Get the hex-formatted number in [std::string]
      /// </summary>
      std::string to_hex() const
      {
         return hex_number_;
      }

      /// <summary>
      /// Get the decimal-formatted number in [T]
      /// </summary>
      T to_decimal() const
      {
         return decimal_number_;
      }

      /// <summary>
      /// Get the sign of number in [bool]
      /// </summary>
      bool is_negative() const
      {
         return is_negative_;
      }

      ~computer_radix10_number() = default;
   };

   // Float static constants
   const std::string computer_radix10_number<float>::inf_nan_exponent = "11111111";
   const std::string computer_radix10_number<float>::zero_exponent = "00000000";

   const std::string computer_radix10_number<float>::plus_inf { "01111111100000000000000000000000" };
   const std::string computer_radix10_number<float>::minus_inf { "11111111100000000000000000000000" };
   const std::string computer_radix10_number<float>::nan { "10000000000000000000000000000000" };

   constexpr int computer_radix10_number<float>::exponent_size = 8;
   constexpr int computer_radix10_number<float>::mantissa_size = 24;
   // end Float static constants

   // Double static constants
   const std::string computer_radix10_number<double>::inf_nan_exponent = "11111111111";
   const std::string computer_radix10_number<double>::zero_exponent = "00000000000";

   const std::string computer_radix10_number<double>::plus_inf { "0111111111110000000000000000000000000000000000000000000000000000" };
   const std::string computer_radix10_number<double>::minus_inf { "1111111111110000000000000000000011111111111111111111111111111111" };
   const std::string computer_radix10_number<double>::nan { "0111111110000000000000000000000000000000000000000000000000000001" };

   constexpr int computer_radix10_number<double>::exponent_size = 11;
   constexpr int computer_radix10_number<double>::mantissa_size = 53;
   //end Double static constants

} // namespace Converters