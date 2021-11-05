#include "CppUnitTest.h"
#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Standartunittests
{
	TEST_CLASS(Standartunittests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			converters::computer_radix10_number<double> var(-187.25);
			Assert::AreEqual(var.to_hex().c_str(), "C067680000000000");
		}
	};
}
