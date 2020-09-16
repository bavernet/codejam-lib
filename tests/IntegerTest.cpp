#include <gtest/gtest.h>
#include <numeric/Integer.hpp>
#include <string>
#include <limits>

class IntegerTest: public ::testing::Test {
protected:
	const Integer iOne              { 1 };
	const Integer iMinusOne         { -1 };
	const Integer llTrillion        { 1'000'000'000'000LL };
	const Integer llMinusTrillion   { -1'000'000'000'000LL };
	const Integer dOnePointTwo      { 1.2 };
	const Integer dMinusOnePointTwo { -1.2 };
	const Integer sZero             { "0" };
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

TEST_F(IntegerTest, fromString10) {
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
	std::string big5    { "-1000000000000000000000000001" };
	Integer b1  { big1 };
	Integer b2  { big2 };
	Integer b3  { big3 };
	Integer b4  { big4 };
	Integer b5  { big5 };

	EXPECT_EQ(b1, b2);
	EXPECT_EQ(b2, b3);
	EXPECT_EQ(b1, b3);
	EXPECT_NE(b1, b4);
	EXPECT_NE(b4, b5);

	EXPECT_LT(b3, b4);
	EXPECT_GT(b4, b5);
	EXPECT_LE(b3, b4);
	EXPECT_LE(b2, b3);
	EXPECT_GE(b4, b3);
	EXPECT_GE(b2, b3);

	EXPECT_NE(b1, iOne);
	EXPECT_NE(b2, iOne);
	EXPECT_NE(b3, iOne);
	EXPECT_NE(b4, iOne);
}

TEST_F(IntegerTest, fromString2) {
	EXPECT_EQ(Integer("1", 2),     Integer(1));
	EXPECT_EQ(Integer("10", 2),    Integer(2));
	EXPECT_EQ(Integer("11", 2),    Integer(3));
	EXPECT_EQ(Integer("100", 2),   Integer(4));
	EXPECT_EQ(Integer("101", 2),   Integer(5));
	EXPECT_EQ(Integer("110", 2),   Integer(6));
	EXPECT_EQ(Integer("111", 2),   Integer(7));
	EXPECT_EQ(Integer("1000", 2),  Integer(8));
	EXPECT_EQ(Integer("1001", 2),  Integer(9));
	EXPECT_EQ(Integer("1010", 2),  Integer(10));
	EXPECT_EQ(Integer("1001111110010000011011001100100100011010111110110010011011000101101110001110011000000100010101", 2),
			  Integer("12345678901234567890123456789"));

	EXPECT_EQ(Integer("-1", 2),    Integer(-1));
	EXPECT_EQ(Integer("-10", 2),   Integer(-2));
	EXPECT_EQ(Integer("-11", 2),   Integer(-3));
	EXPECT_EQ(Integer("-100", 2),  Integer(-4));
	EXPECT_EQ(Integer("-101", 2),  Integer(-5));
	EXPECT_EQ(Integer("-110", 2),  Integer(-6));
	EXPECT_EQ(Integer("-111", 2),  Integer(-7));
	EXPECT_EQ(Integer("-1000", 2), Integer(-8));
	EXPECT_EQ(Integer("-1001", 2), Integer(-9));
	EXPECT_EQ(Integer("-1010", 2), Integer(-10));
	EXPECT_EQ(Integer("-1001111110010000011011001100100100011010111110110010011011000101101110001110011000000100010101", 2),
			  Integer("-12345678901234567890123456789"));
}


TEST_F(IntegerTest, fromString8) {
	EXPECT_EQ(Integer("1", 8),   Integer(1));
	EXPECT_EQ(Integer("2", 8),   Integer(2));
	EXPECT_EQ(Integer("3", 8),   Integer(3));
	EXPECT_EQ(Integer("4", 8),   Integer(4));
	EXPECT_EQ(Integer("5", 8),   Integer(5));
	EXPECT_EQ(Integer("6", 8),   Integer(6));
	EXPECT_EQ(Integer("7", 8),   Integer(7));
	EXPECT_EQ(Integer("10", 8),  Integer(8));
	EXPECT_EQ(Integer("11", 8),  Integer(9));
	EXPECT_EQ(Integer("12", 8),  Integer(10));
	EXPECT_EQ(Integer("11762033144432766233055616300425", 8),
			  Integer("12345678901234567890123456789"));

	EXPECT_EQ(Integer("-1", 8),   Integer(-1));
	EXPECT_EQ(Integer("-2", 8),   Integer(-2));
	EXPECT_EQ(Integer("-3", 8),   Integer(-3));
	EXPECT_EQ(Integer("-4", 8),   Integer(-4));
	EXPECT_EQ(Integer("-5", 8),   Integer(-5));
	EXPECT_EQ(Integer("-6", 8),   Integer(-6));
	EXPECT_EQ(Integer("-7", 8),   Integer(-7));
	EXPECT_EQ(Integer("-10", 8),  Integer(-8));
	EXPECT_EQ(Integer("-11", 8),  Integer(-9));
	EXPECT_EQ(Integer("-12", 8),  Integer(-10));
	EXPECT_EQ(Integer("-11762033144432766233055616300425", 8),
			  Integer("-12345678901234567890123456789"));

	EXPECT_EQ(Integer("-1", 16),   Integer(-1));
	EXPECT_EQ(Integer("-2", 16),   Integer(-2));
	EXPECT_EQ(Integer("-3", 16),   Integer(-3));
	EXPECT_EQ(Integer("-4", 16),   Integer(-4));
	EXPECT_EQ(Integer("-5", 16),   Integer(-5));
	EXPECT_EQ(Integer("-6", 16),   Integer(-6));
	EXPECT_EQ(Integer("-7", 16),   Integer(-7));
	EXPECT_EQ(Integer("-8", 16),   Integer(-8));
	EXPECT_EQ(Integer("-9", 16),   Integer(-9));
	EXPECT_EQ(Integer("-A", 16),   Integer(-10));
	EXPECT_EQ(Integer("-B", 16),   Integer(-11));
	EXPECT_EQ(Integer("-C", 16),   Integer(-12));
	EXPECT_EQ(Integer("-D", 16),   Integer(-13));
	EXPECT_EQ(Integer("-E", 16),   Integer(-14));
	EXPECT_EQ(Integer("-F", 16),   Integer(-15));
	EXPECT_EQ(Integer("-10", 16),  Integer(-16));
	EXPECT_EQ(Integer("-11", 16),  Integer(-17));
	EXPECT_EQ(Integer("-12", 16),  Integer(-18));
	EXPECT_EQ(Integer("-13", 16),  Integer(-19));
	EXPECT_EQ(Integer("-14", 16),  Integer(-20));
	EXPECT_EQ(Integer("-27E41B3246BEC9B16E398115", 16),
			  Integer("-12345678901234567890123456789"));

	EXPECT_EQ(Integer("-1", 16),   Integer(-1));
	EXPECT_EQ(Integer("-2", 16),   Integer(-2));
	EXPECT_EQ(Integer("-3", 16),   Integer(-3));
	EXPECT_EQ(Integer("-4", 16),   Integer(-4));
	EXPECT_EQ(Integer("-5", 16),   Integer(-5));
	EXPECT_EQ(Integer("-6", 16),   Integer(-6));
	EXPECT_EQ(Integer("-7", 16),   Integer(-7));
	EXPECT_EQ(Integer("-8", 16),   Integer(-8));
	EXPECT_EQ(Integer("-9", 16),   Integer(-9));
	EXPECT_EQ(Integer("-a", 16),   Integer(-10));
	EXPECT_EQ(Integer("-b", 16),   Integer(-11));
	EXPECT_EQ(Integer("-c", 16),   Integer(-12));
	EXPECT_EQ(Integer("-d", 16),   Integer(-13));
	EXPECT_EQ(Integer("-e", 16),   Integer(-14));
	EXPECT_EQ(Integer("-f", 16),   Integer(-15));
	EXPECT_EQ(Integer("-10", 16),  Integer(-16));
	EXPECT_EQ(Integer("-11", 16),  Integer(-17));
	EXPECT_EQ(Integer("-12", 16),  Integer(-18));
	EXPECT_EQ(Integer("-13", 16),  Integer(-19));
	EXPECT_EQ(Integer("-14", 16),  Integer(-20));
	EXPECT_EQ(Integer("-27e41b3246bec9b16e398115", 16),
			  Integer("-12345678901234567890123456789"));
}

TEST_F(IntegerTest, fromString16) {
	EXPECT_EQ(Integer("1", 16),   Integer(1));
	EXPECT_EQ(Integer("2", 16),   Integer(2));
	EXPECT_EQ(Integer("3", 16),   Integer(3));
	EXPECT_EQ(Integer("4", 16),   Integer(4));
	EXPECT_EQ(Integer("5", 16),   Integer(5));
	EXPECT_EQ(Integer("6", 16),   Integer(6));
	EXPECT_EQ(Integer("7", 16),   Integer(7));
	EXPECT_EQ(Integer("8", 16),   Integer(8));
	EXPECT_EQ(Integer("9", 16),   Integer(9));
	EXPECT_EQ(Integer("A", 16),   Integer(10));
	EXPECT_EQ(Integer("B", 16),   Integer(11));
	EXPECT_EQ(Integer("C", 16),   Integer(12));
	EXPECT_EQ(Integer("D", 16),   Integer(13));
	EXPECT_EQ(Integer("E", 16),   Integer(14));
	EXPECT_EQ(Integer("F", 16),   Integer(15));
	EXPECT_EQ(Integer("10", 16),  Integer(16));
	EXPECT_EQ(Integer("11", 16),  Integer(17));
	EXPECT_EQ(Integer("12", 16),  Integer(18));
	EXPECT_EQ(Integer("13", 16),  Integer(19));
	EXPECT_EQ(Integer("14", 16),  Integer(20));
	EXPECT_EQ(Integer("27E41B3246BEC9B16E398115", 16),
			  Integer("12345678901234567890123456789"));

	EXPECT_EQ(Integer("1", 16),   Integer(1));
	EXPECT_EQ(Integer("2", 16),   Integer(2));
	EXPECT_EQ(Integer("3", 16),   Integer(3));
	EXPECT_EQ(Integer("4", 16),   Integer(4));
	EXPECT_EQ(Integer("5", 16),   Integer(5));
	EXPECT_EQ(Integer("6", 16),   Integer(6));
	EXPECT_EQ(Integer("7", 16),   Integer(7));
	EXPECT_EQ(Integer("8", 16),   Integer(8));
	EXPECT_EQ(Integer("9", 16),   Integer(9));
	EXPECT_EQ(Integer("a", 16),   Integer(10));
	EXPECT_EQ(Integer("b", 16),   Integer(11));
	EXPECT_EQ(Integer("c", 16),   Integer(12));
	EXPECT_EQ(Integer("d", 16),   Integer(13));
	EXPECT_EQ(Integer("e", 16),   Integer(14));
	EXPECT_EQ(Integer("f", 16),   Integer(15));
	EXPECT_EQ(Integer("10", 16),  Integer(16));
	EXPECT_EQ(Integer("11", 16),  Integer(17));
	EXPECT_EQ(Integer("12", 16),  Integer(18));
	EXPECT_EQ(Integer("13", 16),  Integer(19));
	EXPECT_EQ(Integer("14", 16),  Integer(20));
	EXPECT_EQ(Integer("27e41b3246bec9b16e398115", 16),
			  Integer("12345678901234567890123456789"));
}

TEST_F(IntegerTest, toString10) {
	EXPECT_EQ(std::string(Integer("-0")), "0");
	EXPECT_EQ(std::string(sZero), "0");
	EXPECT_EQ(std::string(iOne), "1");
	EXPECT_EQ(std::string(iMinusOne), "-1");
	EXPECT_EQ(std::string(llTrillion), "1000000000000");
	EXPECT_EQ(std::string(llMinusTrillion), "-1000000000000");

	int64_t n1 = std::numeric_limits<uint32_t>::max();
	std::string big1    { std::to_string(n1 + 1) };
	Integer b1  { big1 };
	EXPECT_EQ(std::string(b1), big1);

	uint64_t n2 = std::numeric_limits<uint64_t>::max();
	std::string big2    { "-" };
	big2 += std::to_string(n2);
	++big2.back();
	Integer b2  { big2 };
	EXPECT_EQ(std::string(b2), big2);

	std::string big3    { "-12345678901234567890123456789" };
	Integer b3  { big3 };
	EXPECT_EQ(std::string(b3), big3);
}

TEST_F(IntegerTest, toString2) {
	EXPECT_EQ(Integer(1).toString(2), "1");
	EXPECT_EQ(Integer(2).toString(2), "10");
	EXPECT_EQ(Integer(3).toString(2), "11");
	EXPECT_EQ(Integer(4).toString(2), "100");
	EXPECT_EQ(Integer(5).toString(2), "101");
	EXPECT_EQ(Integer(6).toString(2), "110");
	EXPECT_EQ(Integer(7).toString(2), "111");
	EXPECT_EQ(Integer(8).toString(2), "1000");
	EXPECT_EQ(Integer(9).toString(2), "1001");
	EXPECT_EQ(Integer(10).toString(2), "1010");
	EXPECT_EQ(Integer("12345678901234567890123456789").toString(2),
			  "1001111110010000011011001100100100011010111110110010011011000101101110001110011000000100010101");

	EXPECT_EQ(Integer(-1).toString(2), "-1");
	EXPECT_EQ(Integer(-2).toString(2), "-10");
	EXPECT_EQ(Integer(-3).toString(2), "-11");
	EXPECT_EQ(Integer(-4).toString(2), "-100");
	EXPECT_EQ(Integer(-5).toString(2), "-101");
	EXPECT_EQ(Integer(-6).toString(2), "-110");
	EXPECT_EQ(Integer(-7).toString(2), "-111");
	EXPECT_EQ(Integer(-8).toString(2), "-1000");
	EXPECT_EQ(Integer(-9).toString(2), "-1001");
	EXPECT_EQ(Integer(-10).toString(2), "-1010");
	EXPECT_EQ(Integer("-12345678901234567890123456789").toString(2),
			  "-1001111110010000011011001100100100011010111110110010011011000101101110001110011000000100010101");
}

TEST_F(IntegerTest, toString8) {
	EXPECT_EQ(Integer(1).toString(8), "1");
	EXPECT_EQ(Integer(2).toString(8), "2");
	EXPECT_EQ(Integer(3).toString(8), "3");
	EXPECT_EQ(Integer(4).toString(8), "4");
	EXPECT_EQ(Integer(5).toString(8), "5");
	EXPECT_EQ(Integer(6).toString(8), "6");
	EXPECT_EQ(Integer(7).toString(8), "7");
	EXPECT_EQ(Integer(8).toString(8), "10");
	EXPECT_EQ(Integer(9).toString(8), "11");
	EXPECT_EQ(Integer(10).toString(8), "12");
	EXPECT_EQ(Integer("12345678901234567890123456789").toString(8),
			  "11762033144432766233055616300425");

	EXPECT_EQ(Integer(-1).toString(8), "-1");
	EXPECT_EQ(Integer(-2).toString(8), "-2");
	EXPECT_EQ(Integer(-3).toString(8), "-3");
	EXPECT_EQ(Integer(-4).toString(8), "-4");
	EXPECT_EQ(Integer(-5).toString(8), "-5");
	EXPECT_EQ(Integer(-6).toString(8), "-6");
	EXPECT_EQ(Integer(-7).toString(8), "-7");
	EXPECT_EQ(Integer(-8).toString(8), "-10");
	EXPECT_EQ(Integer(-9).toString(8), "-11");
	EXPECT_EQ(Integer(-10).toString(8), "-12");
	EXPECT_EQ(Integer("-12345678901234567890123456789").toString(8),
			  "-11762033144432766233055616300425");
}

TEST_F(IntegerTest, toString16) {
	EXPECT_EQ(Integer(1).toString(16), "1");
	EXPECT_EQ(Integer(2).toString(16), "2");
	EXPECT_EQ(Integer(3).toString(16), "3");
	EXPECT_EQ(Integer(4).toString(16), "4");
	EXPECT_EQ(Integer(5).toString(16), "5");
	EXPECT_EQ(Integer(6).toString(16), "6");
	EXPECT_EQ(Integer(7).toString(16), "7");
	EXPECT_EQ(Integer(8).toString(16), "8");
	EXPECT_EQ(Integer(9).toString(16), "9");
	EXPECT_EQ(Integer(10).toString(16), "A");
	EXPECT_EQ(Integer(11).toString(16), "B");
	EXPECT_EQ(Integer(12).toString(16), "C");
	EXPECT_EQ(Integer(13).toString(16), "D");
	EXPECT_EQ(Integer(14).toString(16), "E");
	EXPECT_EQ(Integer(15).toString(16), "F");
	EXPECT_EQ(Integer(16).toString(16), "10");
	EXPECT_EQ(Integer(17).toString(16), "11");
	EXPECT_EQ(Integer(18).toString(16), "12");
	EXPECT_EQ(Integer(19).toString(16), "13");
	EXPECT_EQ(Integer(20).toString(16), "14");
	EXPECT_EQ(Integer("12345678901234567890123456789").toString(16),
			  "27E41B3246BEC9B16E398115");

	EXPECT_EQ(Integer(-1).toString(16), "-1");
	EXPECT_EQ(Integer(-2).toString(16), "-2");
	EXPECT_EQ(Integer(-3).toString(16), "-3");
	EXPECT_EQ(Integer(-4).toString(16), "-4");
	EXPECT_EQ(Integer(-5).toString(16), "-5");
	EXPECT_EQ(Integer(-6).toString(16), "-6");
	EXPECT_EQ(Integer(-7).toString(16), "-7");
	EXPECT_EQ(Integer(-8).toString(16), "-8");
	EXPECT_EQ(Integer(-9).toString(16), "-9");
	EXPECT_EQ(Integer(-10).toString(16), "-A");
	EXPECT_EQ(Integer(-11).toString(16), "-B");
	EXPECT_EQ(Integer(-12).toString(16), "-C");
	EXPECT_EQ(Integer(-13).toString(16), "-D");
	EXPECT_EQ(Integer(-14).toString(16), "-E");
	EXPECT_EQ(Integer(-15).toString(16), "-F");
	EXPECT_EQ(Integer(-16).toString(16), "-10");
	EXPECT_EQ(Integer(-17).toString(16), "-11");
	EXPECT_EQ(Integer(-18).toString(16), "-12");
	EXPECT_EQ(Integer(-19).toString(16), "-13");
	EXPECT_EQ(Integer(-20).toString(16), "-14");
	EXPECT_EQ(Integer("-12345678901234567890123456789").toString(16),
			  "-27E41B3246BEC9B16E398115");
}

TEST_F(IntegerTest, add) {
	EXPECT_EQ(Integer(1) + Integer(2), Integer(3));
	EXPECT_EQ(Integer(2) + Integer(1), Integer(3));
	EXPECT_EQ(Integer(-1) + Integer(-2), Integer(-3));
	EXPECT_EQ(Integer(-2) + Integer(-1), Integer(-3));
	EXPECT_EQ(Integer(-1) + Integer(2), Integer(1));
	EXPECT_EQ(Integer(2) + Integer(-1), Integer(1));
	EXPECT_EQ(Integer(1) + Integer(-2), Integer(-1));
	EXPECT_EQ(Integer(-2) + Integer(1), Integer(-1));
	EXPECT_EQ(Integer(10) + Integer(-10), Integer(0));
	EXPECT_EQ(Integer("9123456789012345678901234567890") + Integer("-9123456789012345678901234567888"), Integer(2));
	EXPECT_EQ(Integer("-9123456789012345678901234567890") + Integer("9123456789012345678901234567888"), Integer(-2));
	EXPECT_EQ(std::string(Integer("9123456789012345678901234567890") + Integer("9123456789012345678901234567888")),
			  "18246913578024691357802469135778");
	EXPECT_EQ(std::string(Integer("-9123456789012345678901234567890") + Integer("-9123456789012345678901234567888")),
			  "-18246913578024691357802469135778");
	EXPECT_EQ(Integer("36893488147419103232") + Integer("36893488147419103232"), Integer("73786976294838206464"));
	EXPECT_EQ(Integer("-36893488147419103232") + Integer("-36893488147419103232"), Integer("-73786976294838206464"));
}

TEST_F(IntegerTest, subtract) {
	EXPECT_EQ(Integer(1) - Integer(2), Integer(-1));
	EXPECT_EQ(Integer(2) - Integer(1), Integer(1));
	EXPECT_EQ(Integer(-1) - Integer(-2), Integer(1));
	EXPECT_EQ(Integer(-2) - Integer(-1), Integer(-1));
	EXPECT_EQ(Integer(-1) - Integer(2), Integer(-3));
	EXPECT_EQ(Integer(2) - Integer(-1), Integer(3));
	EXPECT_EQ(Integer(1) - Integer(-2), Integer(3));
	EXPECT_EQ(Integer(-2) - Integer(1), Integer(-3));
	EXPECT_EQ(Integer(10) - Integer(10), Integer(0));
	EXPECT_EQ(Integer(-10) - Integer(-10), Integer(0));
	EXPECT_EQ(Integer("9123456789012345678901234567890") - Integer("9123456789012345678901234567888"), Integer(2));
	EXPECT_EQ(Integer("-9123456789012345678901234567890") - Integer("-9123456789012345678901234567888"), Integer(-2));
	EXPECT_EQ(std::string(Integer("9123456789012345678901234567890") - Integer("-9123456789012345678901234567888")),
			  "18246913578024691357802469135778");
	EXPECT_EQ(std::string(Integer("-9123456789012345678901234567890") - Integer("9123456789012345678901234567888")),
			  "-18246913578024691357802469135778");
	EXPECT_EQ(Integer("36893488147419103232") - Integer("-36893488147419103232"), Integer("73786976294838206464"));
	EXPECT_EQ(Integer("-36893488147419103232") - Integer("36893488147419103232"), Integer("-73786976294838206464"));
	EXPECT_EQ(Integer("-36893488147419103232") - Integer("36893488147419103232"), Integer("-73786976294838206464"));
	EXPECT_EQ(Integer("36893488147419103232") - Integer("-36893488147419103232"), Integer("73786976294838206464"));
}
