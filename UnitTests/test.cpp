#include "pch.h"

namespace StandartTests
{
   // RandomNumbersTest1
   TEST(RandomNumbersTest1, DoubleTest1)
   {
      converters::computer_radix10_number<double> doubleVar(-187.25);
      EXPECT_TRUE(strcmp(doubleVar.to_hex().c_str(), "C067680000000000") == 0);
   }
   TEST(RandomNumbersTest1, FloatTest1)
   {
      converters::computer_radix10_number<float> floatVar(-146.836f);
      EXPECT_TRUE(strcmp(floatVar.to_hex().c_str(), "C312D604") == 0);
   }
   TEST(RandomNumbersTest1, DoubleTest2)
   {
      converters::computer_radix10_number<double> doubleVar("C067680000000000");
      EXPECT_EQ(doubleVar.to_decimal(), -1.872500E+02);
   }
   TEST(RandomNumbersTest1, FloatTest2)
   {
      converters::computer_radix10_number<float>floatVar("C312D604");
      EXPECT_EQ(floatVar.to_decimal(), -1.468360E+02f);
   }
   // RandomNumbersTest1

   // RandomNumbersTest2
   TEST(RandomNumbersTest2, DoubleTest1)
   {
      converters::computer_radix10_number<double> doubleVar(465.625);
      EXPECT_TRUE(strcmp(doubleVar.to_hex().c_str(), "407D1A0000000000") == 0);

   }
   TEST(RandomNumbersTest2, FloatTest1)
   {
      converters::computer_radix10_number<float> floatVar(407.555f);
      EXPECT_TRUE(strcmp(floatVar.to_hex().c_str(), "43CBC70A") == 0);
   }
   TEST(RandomNumbersTest2, DoubleTest2)
   {
      converters::computer_radix10_number<double> doubleVar("407D1A0000000000");
      EXPECT_EQ(doubleVar.to_decimal(), 4.656250E+02);
   }
   TEST(RandomNumbersTest2, FloatTest2)
   {
      converters::computer_radix10_number<float>floatVar("43CBC70A");
      EXPECT_EQ(floatVar.to_decimal(), 4.075550E+02f);
   }
   // RandomNumbersTest2

   // RandomNumbersTest3
   TEST(RandomNumbersTest3, DoubleTest1)
   {
      converters::computer_radix10_number<double> doubleVar(-310.375);
      EXPECT_TRUE(strcmp(doubleVar.to_hex().c_str(), "C073660000000000") == 0);
   }
   TEST(RandomNumbersTest3, FloatTest1)
   {
      converters::computer_radix10_number<float> floatVar(-169.3125f);
      EXPECT_TRUE(strcmp(floatVar.to_hex().c_str(), "C3295000") == 0);
   }
   TEST(RandomNumbersTest3, DoubleTest2)
   {
      converters::computer_radix10_number<double> doubleVar("C073660000000000");
      EXPECT_EQ(doubleVar.to_decimal(), -3.103750e+02);
   }
   TEST(RandomNumbersTest3, FloatTest2)
   {
      converters::computer_radix10_number<float>floatVar("C3295000");
      EXPECT_EQ(floatVar.to_decimal(), -1.693125e+02f);
   }
   // RandomNumbersTest3

   // RandomNumbersTest4
   TEST(RandomNumbersTest4, DoubleTest1)
   {
      converters::computer_radix10_number<double> doubleVar(126.609375);
		EXPECT_TRUE(strcmp(doubleVar.to_hex().c_str(), "405FA70000000000") == 0);
   }
   TEST(RandomNumbersTest4, FloatTest1)
   {
      converters::computer_radix10_number<float> floatVar(29.6875f);
      EXPECT_TRUE(strcmp(floatVar.to_hex().c_str(), "41ED8000") == 0);
   }
   TEST(RandomNumbersTest4, DoubleTest2)
   {
      converters::computer_radix10_number<double> doubleVar("405FA70000000000");
      EXPECT_EQ(doubleVar.to_decimal(), 126.609375);
   }
   TEST(RandomNumbersTest4, FloatTest2)
   {
      converters::computer_radix10_number<float>floatVar("41ED8000");
      EXPECT_EQ(floatVar.to_decimal(), 2.968750e+01f);
   }
   // RandomNumbersTest4


   // FloatEdges
	TEST(FloatEdges, MinusNanHigher)
	{
		converters::computer_radix10_number<float> num("FFFFFFFF");
		EXPECT_TRUE(isnan(num.to_decimal()));
	}

	TEST(FloatEdges, MinusNanLower)
	{
		converters::computer_radix10_number<float> num("FF800001");
		EXPECT_TRUE(isnan(num.to_decimal()));
	}

	TEST(FloatEdges, MinusInf)
	{
		converters::computer_radix10_number<float> num("FF800000");
		EXPECT_EQ(num.to_decimal(), -INFINITY);
	}

	TEST(FloatEdges, NegativeHigherNum)
	{
		converters::computer_radix10_number<float> num("FF7FFFFF");
		EXPECT_EQ(num.to_decimal(), -3.40282347e+38f);
	}

	TEST(FloatEdges, NegativeMinimalNormalizedNum)
	{
		converters::computer_radix10_number<float> num("80800000");
		EXPECT_EQ(num.to_decimal(), -1.17549435e-38f);
	}

	TEST(FloatEdges, NegativeMaximalDenormalizedNum)
	{
		converters::computer_radix10_number<float> num("807FFFFF");
		EXPECT_EQ(num.to_decimal(), -1.17549421e-38f);
	}

	TEST(FloatEdges, NegativeMinimalDenormalizedNum)
	{
		converters::computer_radix10_number<float> num("80000001");
		EXPECT_EQ(num.to_decimal(), -1.40129846e-45f);
	}

	TEST(FloatEdges, NegativeZero)
	{
		converters::computer_radix10_number<float> num("80000000");
		EXPECT_EQ(num.to_decimal(), -0.000000e+00f);
	}

	TEST(FloatEdges, PositiveZero)
	{
		converters::computer_radix10_number<float> num("00000000");
		EXPECT_EQ(num.to_decimal(), 0.000000e+00f);
	}

	TEST(FloatEdges, PositiveMinimalDenormalizedNum)
	{
		converters::computer_radix10_number<float> num("00000001");
		EXPECT_EQ(num.to_decimal(), 1.40129846e-45f);
	}

	TEST(FloatEdges, PositiveMaximalDenormalizedNum)
	{
		converters::computer_radix10_number<float> num("007FFFFF");
		EXPECT_EQ(num.to_decimal(), 1.17549421e-38f);
	}

	TEST(FloatEdges, PositiveMinimalNormalizedNum)
	{
		converters::computer_radix10_number<float> num("00800000");
		EXPECT_EQ(num.to_decimal(), 1.17549435e-38f);
	}

	TEST(FloatEdges, PositiveMaximalNormalizedNum)
	{
		converters::computer_radix10_number<float> num("7F7FFFFF");
		EXPECT_EQ(num.to_decimal(), 3.40282347e+38f);
	}

	TEST(FloatEdges, PositiveInf)
	{
		converters::computer_radix10_number<float> num("7F800000");
		EXPECT_EQ(num.to_decimal(), INFINITY);
	}

	TEST(FloatEdges, PositiveNanLower)
	{
		converters::computer_radix10_number<float> num("7F800001");
		EXPECT_TRUE(isnan(num.to_decimal()));
	}

	TEST(FloatEdges, PositiveNanHigher)
	{
		converters::computer_radix10_number<float> num("7FFFFFFF");
		EXPECT_TRUE(isnan(num.to_decimal()));
	}
   // FloatEdges

   // DoubleEdges
	TEST(DoubleEdges, MinusNanHigher)
	{
		converters::computer_radix10_number<double> num("FFFFFFFFFFFFFFFF");
		EXPECT_TRUE(isnan(num.to_decimal()));
	}

	TEST(DoubleEdges, MinusNanLower)
	{
		converters::computer_radix10_number<double> num("FFF0000000000001");
		EXPECT_TRUE(isnan(num.to_decimal()));
	}

	TEST(DoubleEdges, MinusInf)
	{
		converters::computer_radix10_number<double> num("FFF0000000000000");
		EXPECT_EQ(num.to_decimal(), (double)-INFINITY);
	}

	TEST(DoubleEdges, NegativeHigherNum)
	{
		converters::computer_radix10_number<double> num("FFEFFFFFFFFFFFFF");
		EXPECT_EQ(num.to_decimal(), -1.79769313486231570814527423732E308);
	}

	TEST(DoubleEdges, NegativeMinimalNormalizedNum)
	{
		converters::computer_radix10_number<double> num("8010000000000000");
		EXPECT_EQ(num.to_decimal(), -2.22507385850720138309023271733E-308);
	}

	TEST(DoubleEdges, NegativeMaximalDenormalizedNum)
	{
		converters::computer_radix10_number<double> num("800FFFFFFFFFFFFF");
		EXPECT_EQ(num.to_decimal(), -2.22507385850720088902458687609E-308);
	}

	TEST(DoubleEdges, NegativeMinimalDenormalizedNum)
	{
		converters::computer_radix10_number<double> num("8000000000000001");
		EXPECT_EQ(num.to_decimal(), -4.94065645841246544176568792868E-324);
	}

	TEST(DoubleEdges, NegativeZero)
	{
		converters::computer_radix10_number<double> num("8000000000000000");
		EXPECT_EQ(num.to_decimal(), -0.0);
	}

	TEST(DoubleEdges, PositiveZero)
	{
		converters::computer_radix10_number<double> num("0000000000000000");
		EXPECT_EQ(num.to_decimal(), 0.0);
	}

	TEST(DoubleEdges, PositiveMinimalDenormalizedNum)
	{
		converters::computer_radix10_number<double> num("0000000000000001");
		EXPECT_EQ(num.to_decimal(), 4.94065645841246544176568792868E-324);
	}

	TEST(DoubleEdges, PositiveMaximalDenormalizedNum)
	{
		converters::computer_radix10_number<double> num("000FFFFFFFFFFFFF");
		EXPECT_EQ(num.to_decimal(), 2.22507385850720088902458687609E-308);
	}

	TEST(DoubleEdges, PositiveMinimalNormalizedNum)
	{
		converters::computer_radix10_number<double> num("0010000000000000");
		EXPECT_EQ(num.to_decimal(), 2.22507385850720138309023271733E-308);
	}

	TEST(DoubleEdges, PositiveMaximalNormalizedNum)
	{
		converters::computer_radix10_number<double> num("7FEFFFFFFFFFFFFF");
		EXPECT_EQ(num.to_decimal(), 1.79769313486231570814527423732E308);
	}

	TEST(DoubleEdges, PositiveInf)
	{
		converters::computer_radix10_number<double> num("7FF0000000000000");
		EXPECT_EQ(num.to_decimal(), (double)INFINITY);
	}

	TEST(DoubleEdges, PositiveNanLower)
	{
		converters::computer_radix10_number<double> num("7FF0000000000001");
		EXPECT_TRUE(isnan(num.to_decimal()));
	}

	TEST(DoubleEdges, PositiveNanHigher)
	{
		converters::computer_radix10_number<double> num("7FFFFFFFFFFFFFFF");
		EXPECT_TRUE(isnan(num.to_decimal()));
	}
   // DoubleEdges
}