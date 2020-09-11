#include <gtest/gtest.h>
#include <numeric/Integer.hpp>
#include <string>

class IntegerTest: public ::testing::Test {
protected:
	const Integer iOne              { 1 };
	const Integer iMinusOne         { -1 };
	const Integer llTrillion        { 1'000'000'000'000LL };
	const Integer llMinusTrillion   { -1'000'000'000'000LL };
	const Integer dOnePointTwo      { 1.2 };
	const Integer dMinusOnePointTwo { -1.2 };
	const Integer sOne              { "1" };
	const Integer sMinusOne         { "-1" };

protected:
	void SetUp() override {
	}

	void TearDown() override {
	}
};

TEST_F(IntegerTest, constructFromNumber) {
	EXPECT_EQ(iOne, 1);
	EXPECT_EQ(1, iOne);
	EXPECT_EQ(iMinusOne, -1);
	EXPECT_EQ(-1, iMinusOne);
	EXPECT_NE(iOne, iMinusOne);

	EXPECT_EQ(llTrillion, 1'000'000'000'000LL);
	EXPECT_EQ(llMinusTrillion, -1'000'000'000'000LL);

	EXPECT_LT(iOne, llTrillion);
	EXPECT_LT(llMinusTrillion, llTrillion);
	EXPECT_LT(iMinusOne, iOne);
	EXPECT_LT(llMinusTrillion, llTrillion);

	EXPECT_GT(llTrillion, iOne);
	EXPECT_GT(llTrillion, llMinusTrillion);
	EXPECT_GT(iOne, iMinusOne);

	EXPECT_EQ(iOne, dOnePointTwo);
	EXPECT_EQ(iMinusOne, dMinusOnePointTwo);
}

TEST_F(IntegerTest, constructFromString) {
	EXPECT_EQ(sOne, 1);
	EXPECT_EQ(1, sOne);
	EXPECT_EQ(sMinusOne, -1);
	EXPECT_EQ(-1, sMinusOne);
	EXPECT_EQ(sOne, iOne);
	EXPECT_EQ(sMinusOne, iMinusOne);
	EXPECT_NE(sOne, sMinusOne);

	char big1[]         { "1000000000000000000000000000" };
	const char *big2    { "1000000000000000000000000000" };
	std::string big3    { "1000000000000000000000000000" };
	std::string big4    { "1000000000000000000000000001" };
	Integer b1  { big1 };
	Integer b2  { big2 };
	Integer b3  { big3 };
	Integer b4  { big4 };

	EXPECT_EQ(b1, b2);
	EXPECT_EQ(b2, b3);
	EXPECT_EQ(b1, b3);
	EXPECT_NE(b1, b4);

	EXPECT_NE(b1, iOne);
	EXPECT_NE(b2, iOne);
	EXPECT_NE(b3, iOne);
	EXPECT_NE(b4, iOne);
}
