#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StandartUnitTests
{
	TEST_CLASS(RandomNumbersTest1)
	{
	public:		
		TEST_METHOD(DoubleTest1)
		{
			converters::computer_radix10_number<double> doubleVar(-187.25);
			Assert::AreEqual(doubleVar.to_hex().c_str(), "C067680000000000");

		}
		TEST_METHOD(FloatTest1)
		{
         converters::computer_radix10_number<float> floatVar(-146.836f);
         Assert::AreEqual(floatVar.to_hex().c_str(), "C312D604");
		}
		TEST_METHOD(DoubleTest2)
		{
			converters::computer_radix10_number<double> doubleVar("C067680000000000");
			Assert::AreEqual(doubleVar.to_decimal(), -1.872500E+02);
		}
		TEST_METHOD(FloatTest2)
		{
			converters::computer_radix10_number<float>floatVar("C312D604");
			Assert::AreEqual(floatVar.to_decimal(), -1.468360E+02f);
		}
	};

	TEST_CLASS(RandomNumbersTest2)
	{
	public:		
		TEST_METHOD(DoubleTest1)
		{
			converters::computer_radix10_number<double> doubleVar(465.625);
			Assert::AreEqual(doubleVar.to_hex().c_str(), "407D1A0000000000");

		}
		TEST_METHOD(FloatTest1)
		{
         converters::computer_radix10_number<float> floatVar(407.555f);
         Assert::AreEqual(floatVar.to_hex().c_str(), "43CBC70A");
		}
		TEST_METHOD(DoubleTest2)
		{
			converters::computer_radix10_number<double> doubleVar("407D1A0000000000");
			Assert::AreEqual(doubleVar.to_decimal(), 4.656250E+02);
		}
		TEST_METHOD(FloatTest2)
		{
			converters::computer_radix10_number<float>floatVar("43CBC70A");
			Assert::AreEqual(floatVar.to_decimal(), 4.075550E+02f);
		}
	};

	TEST_CLASS(RandomNumbersTest3)
	{
	public:		
		TEST_METHOD(DoubleTest1)
		{
			converters::computer_radix10_number<double> doubleVar(-310.375);
			Assert::AreEqual(doubleVar.to_hex().c_str(), "C073660000000000");

		}
		TEST_METHOD(FloatTest1)
		{
         converters::computer_radix10_number<float> floatVar(-169.3125f);
         Assert::AreEqual(floatVar.to_hex().c_str(), "C3295000");
		}
		TEST_METHOD(DoubleTest2)
		{
			converters::computer_radix10_number<double> doubleVar("C073660000000000");
			Assert::AreEqual(doubleVar.to_decimal(), -3.103750e+02);
		}
		TEST_METHOD(FloatTest2)
		{
			converters::computer_radix10_number<float>floatVar("C3295000");
			Assert::AreEqual(floatVar.to_decimal(), -1.693125e+02f);
		}
	};

	TEST_CLASS(RandomNumbersTest4)
	{
	public:		
		TEST_METHOD(DoubleTest1)
		{
			converters::computer_radix10_number<double> doubleVar(126.609375);
			Assert::AreEqual(doubleVar.to_hex().c_str(), "405FA70000000000");

		}
		TEST_METHOD(FloatTest1)
		{
         converters::computer_radix10_number<float> floatVar(29.6875f);
         Assert::AreEqual(floatVar.to_hex().c_str(), "41ED8000");
		}
		TEST_METHOD(DoubleTest2)
		{
			converters::computer_radix10_number<double> doubleVar("405FA70000000000");
			Assert::AreEqual(doubleVar.to_decimal(), 126.609375);
		}
		TEST_METHOD(FloatTest2)
		{
			converters::computer_radix10_number<float>floatVar("41ED8000");
			Assert::AreEqual(floatVar.to_decimal(), 2.968750e+01f);
		}
	};

	TEST_CLASS(FloatEdges)
	{
		TEST_METHOD(MinusNanHigher)
		{
			converters::computer_radix10_number<float> num("FFFFFFFF");
			Assert::IsTrue(isnan(num.to_decimal()));
		}

		TEST_METHOD(MinusNanLower)
		{
			converters::computer_radix10_number<float> num("FF800001");
			Assert::IsTrue(isnan(num.to_decimal()));
		}

		TEST_METHOD(MinusInf)
		{
			converters::computer_radix10_number<float> num("FF800000");
			Assert::AreEqual(num.to_decimal(), -INFINITY);
		}
		
		TEST_METHOD(NegativeHigherNum)
		{
			converters::computer_radix10_number<float> num("FF7FFFFF");
			Assert::AreEqual(num.to_decimal(), -3.40282347e+38f);
		}
		
		TEST_METHOD(NegativeMinimalNormalizedNum)
		{
			converters::computer_radix10_number<float> num("80800000");
			Assert::AreEqual(num.to_decimal(), -1.17549435e-38f);
		}
		
		TEST_METHOD(NegativeMaximalDenormalizedNum)
		{
			converters::computer_radix10_number<float> num("807FFFFF");
			Assert::AreEqual(num.to_decimal(), -1.17549421e-38f);
		}
		
		TEST_METHOD(NegativeMinimalDenormalizedNum)
		{
			converters::computer_radix10_number<float> num("80000001");
			Assert::AreEqual(num.to_decimal(), -1.40129846e-45f);
		}
		
		TEST_METHOD(NegativeZero)
		{
			converters::computer_radix10_number<float> num("80000000");
			Assert::AreEqual(num.to_decimal(), -0.000000e+00f);
		}
				
		TEST_METHOD(PositiveZero)
		{
			converters::computer_radix10_number<float> num("00000000");
			Assert::AreEqual(num.to_decimal(), 0.000000e+00f);
		}
						
		TEST_METHOD(PositiveMinimalDenormalizedNum)
		{
			converters::computer_radix10_number<float> num("00000001");
			Assert::AreEqual(num.to_decimal(), 1.40129846e-45f);
		}
						
		TEST_METHOD(PositiveMaximalDenormalizedNum)
		{
			converters::computer_radix10_number<float> num("007FFFFF");
			Assert::AreEqual(num.to_decimal(), 1.17549421e-38f);
		}
						
		TEST_METHOD(PositiveMinimalNormalizedNum)
		{
			converters::computer_radix10_number<float> num("00800000");
			Assert::AreEqual(num.to_decimal(), 1.17549435e-38f);
		}
						
		TEST_METHOD(PositiveMaximalNormalizedNum)
		{
			converters::computer_radix10_number<float> num("7F7FFFFF");
			Assert::AreEqual(num.to_decimal(), 3.40282347e+38f);
		}
						
		TEST_METHOD(PositiveInf)
		{
			converters::computer_radix10_number<float> num("7F800000");
			Assert::AreEqual(num.to_decimal(), INFINITY);
		}
						
		TEST_METHOD(PositiveNanLower)
		{
			converters::computer_radix10_number<float> num("7F800001");
			Assert::IsTrue(isnan(num.to_decimal()));
		}
					
		TEST_METHOD(PositiveNanHigher)
		{
			converters::computer_radix10_number<float> num("7FFFFFFF");
			Assert::IsTrue(isnan(num.to_decimal()));
		}

	};
	
	TEST_CLASS(DoubleEdges)
	{
		TEST_METHOD(MinusNanHigher)
		{
			converters::computer_radix10_number<double> num("FFFFFFFFFFFFFFFF");
			Assert::IsTrue(isnan(num.to_decimal()));
		}

		TEST_METHOD(MinusNanLower)
		{
			converters::computer_radix10_number<double> num("FFF0000000000001");
			Assert::IsTrue(isnan(num.to_decimal()));
		}

		TEST_METHOD(MinusInf)
		{
			converters::computer_radix10_number<double> num("FFF0000000000000");
			Assert::AreEqual(num.to_decimal(), (double) -INFINITY);
		}
		
		TEST_METHOD(NegativeHigherNum)
		{
			converters::computer_radix10_number<double> num("FFEFFFFFFFFFFFFF");
			Assert::AreEqual(num.to_decimal(), -1.79769313486231570814527423732E308);
		}
		
		TEST_METHOD(NegativeMinimalNormalizedNum)
		{
			converters::computer_radix10_number<double> num("8010000000000000");
			Assert::AreEqual(num.to_decimal(), -2.22507385850720138309023271733E-308);
		}
		
		TEST_METHOD(NegativeMaximalDenormalizedNum)
		{
			converters::computer_radix10_number<double> num("800FFFFFFFFFFFFF");
			Assert::AreEqual(num.to_decimal(), -2.22507385850720088902458687609E-308);
		}
		
		TEST_METHOD(NegativeMinimalDenormalizedNum)
		{
			converters::computer_radix10_number<double> num("8000000000000001");
			Assert::AreEqual(num.to_decimal(), -4.94065645841246544176568792868E-324);
		}
		
		TEST_METHOD(NegativeZero)
		{
			converters::computer_radix10_number<double> num("8000000000000000");
			Assert::AreEqual(num.to_decimal(), -0.0);
		}
				
		TEST_METHOD(PositiveZero)
		{
			converters::computer_radix10_number<double> num("0000000000000000");
			Assert::AreEqual(num.to_decimal(), 0.0);
		}
						
		TEST_METHOD(PositiveMinimalDenormalizedNum)
		{
			converters::computer_radix10_number<double> num("0000000000000001");
			Assert::AreEqual(num.to_decimal(), 4.94065645841246544176568792868E-324);
		}
						
		TEST_METHOD(PositiveMaximalDenormalizedNum)
		{
			converters::computer_radix10_number<double> num("000FFFFFFFFFFFFF");
			Assert::AreEqual(num.to_decimal(), 2.22507385850720088902458687609E-308);
		}
						
		TEST_METHOD(PositiveMinimalNormalizedNum)
		{
			converters::computer_radix10_number<double> num("0010000000000000");
			Assert::AreEqual(num.to_decimal(), 2.22507385850720138309023271733E-308);
		}
						
		TEST_METHOD(PositiveMaximalNormalizedNum)
		{
			converters::computer_radix10_number<double> num("7FEFFFFFFFFFFFFF");
			Assert::AreEqual(num.to_decimal(), 1.79769313486231570814527423732E308);
		}
						
		TEST_METHOD(PositiveInf)
		{
			converters::computer_radix10_number<double> num("7FF0000000000000");
			Assert::AreEqual(num.to_decimal(), (double)INFINITY);
		}
						
		TEST_METHOD(PositiveNanLower)
		{
			converters::computer_radix10_number<double> num("7FF0000000000001");
			Assert::IsTrue(isnan(num.to_decimal()));
		}
					
		TEST_METHOD(PositiveNanHigher)
		{
			converters::computer_radix10_number<double> num("7FFFFFFFFFFFFFFF");
			Assert::IsTrue(isnan(num.to_decimal()));
		}

	};

}