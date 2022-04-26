#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_5.1\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Numbers n[1] = { 3, 10, 4 };
			Assert::AreEqual(5, (int)Avg(n, 1).p1);
		}
	};
}
