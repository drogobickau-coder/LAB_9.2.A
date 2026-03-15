#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_9.2.A/lab.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestA
{
	TEST_CLASS(UnitTestA)
	{
	public:

		TEST_METHOD(TestAvg)
		{
			Student s;

			s.physics = 5;
			s.math = 4;
			s.informatics = 3;

			double avg = Avg(s);

			Assert::AreEqual(4.0, avg);
		}

		TEST_METHOD(TestBinarySearch)
		{
			const int N = 2;
			Student p[N];

			p[0].surname = "Ivanov";
			p[0].physics = 5;
			p[0].math = 5;
			p[0].informatics = 5;

			p[1].surname = "Petrov";
			p[1].physics = 3;
			p[1].math = 3;
			p[1].informatics = 3;

			int k = BinarySearch(p, N, "Ivanov", 5.0, 5);

			Assert::IsTrue(k >= 0);
		}
	};
}