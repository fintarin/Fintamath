#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/numbers/IntegerFunctions.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

using namespace fintamath;

TEST(IntegerFunctionsTests, absTest) {
  EXPECT_EQ(abs(Integer("-210")).toString(), "210");
  EXPECT_EQ(abs(Integer("4545628562")).toString(), "4545628562");
  EXPECT_EQ(abs(Integer("0")).toString(), "0");
}

TEST(IntegerFunctionsTests, gcdTest) {
  EXPECT_EQ(gcd(Integer(12), Integer(18)), Integer(6));
  EXPECT_EQ(gcd(Integer(30), Integer(45)), Integer(15));
  EXPECT_EQ(gcd(Integer(25), Integer(35)), Integer(5));

  EXPECT_EQ(gcd(Integer(-12), Integer(-18)), Integer(6));
  EXPECT_EQ(gcd(Integer(-30), Integer(-45)), Integer(15));
  EXPECT_EQ(gcd(Integer(-25), Integer(-35)), Integer(5));

  EXPECT_EQ(gcd(Integer(0), Integer(10)), Integer(10));
  EXPECT_EQ(gcd(Integer(0), Integer(-15)), Integer(15));

  EXPECT_EQ(gcd(Integer(0), Integer(0)), Integer(0));

  EXPECT_EQ(
    gcd(Integer("1234567890123456789012345678901234567890123456789012345678901234567890"), Integer("9876543210987654321098765432109876543210987654321098765432109876543210")).toString(),
    "90000000009000000000900000000090000000009000000000900000000090"
  );
}

TEST(IntegerFunctionsTests, lcmTest) {
  EXPECT_EQ(lcm(Integer(12), Integer(18)), Integer(36));
  EXPECT_EQ(lcm(Integer(5), Integer(7)), Integer(35));
  EXPECT_EQ(lcm(Integer(8), Integer(12)), Integer(24));
  EXPECT_EQ(lcm(Integer(15), Integer(25)), Integer(75));
  EXPECT_EQ(lcm(Integer(4), Integer(9)), Integer(36));

  EXPECT_EQ(lcm(Integer(0), Integer(5)), Integer(0));
  EXPECT_EQ(lcm(Integer(5), Integer(0)), Integer(0));
  EXPECT_EQ(lcm(Integer(0), Integer(0)), Integer(0));

  EXPECT_GE(lcm(Integer(-4), Integer(7)), Integer(0));
  EXPECT_GE(lcm(Integer(3), Integer(-6)), Integer(0));
  EXPECT_EQ(lcm(Integer(-2), Integer(0)), Integer(0));

  EXPECT_EQ(
    lcm(Integer("1234567890123456789012345678901234567890123456789012345678901234567890"), Integer("9876543210987654321098765432109876543210987654321098765432109876543210")).toString(),
    "135480701249809480124980948012498094801249809480124980948012498094801236261410"
  );
}

TEST(IntegerFunctionsTests, sqrtTest) {
  EXPECT_EQ(sqrt(Integer(25)), 5);
  EXPECT_EQ(sqrt(Integer(100)), 10);
  EXPECT_EQ(sqrt(Integer(144)), 12);
  EXPECT_EQ(sqrt(Integer("10000000000000000000000000000000000000000000000000000")), Integer("100000000000000000000000000"));

  EXPECT_EQ(sqrt(Integer(35)), 5);
  EXPECT_EQ(sqrt(Integer(4212)), Integer(64));
  EXPECT_EQ(sqrt(Integer("992188888888")), Integer(996086));
  EXPECT_EQ(sqrt(Integer("68732648273642987365932706179432649827364")), Integer("262169121510606178721"));

  EXPECT_THAT(
    [] { sqrt(Integer(-9289)); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(sqrt(-9289) is undefined (expected argument >= 0))")
    )
  );
}

TEST(IntegerFunctionsTests, sqrtWithRemainderTest) {
  Integer remainder;

  EXPECT_EQ(sqrt(Integer(25), remainder), 5);
  EXPECT_EQ(remainder, 0);

  EXPECT_EQ(sqrt(Integer(100), remainder), 10);
  EXPECT_EQ(remainder, 0);

  EXPECT_EQ(sqrt(Integer(144), remainder), 12);
  EXPECT_EQ(remainder, 0);

  EXPECT_EQ(sqrt(Integer("10000000000000000000000000000000000000000000000000000"), remainder), Integer("100000000000000000000000000"));
  EXPECT_EQ(remainder, 0);

  EXPECT_EQ(sqrt(Integer(35), remainder), 5);
  EXPECT_EQ(remainder, 10);

  EXPECT_EQ(sqrt(Integer(4212), remainder), Integer(64));
  EXPECT_EQ(remainder, 116);

  EXPECT_EQ(sqrt(Integer("992188888888"), remainder), Integer(996086));
  EXPECT_EQ(remainder, 1569492);

  EXPECT_EQ(sqrt(Integer("68732648273642987365932706179432649827364"), remainder), Integer("262169121510606178721"));
  EXPECT_EQ(remainder.toString(), "307087949370856631523");

  EXPECT_THAT(
    [&] { sqrt(Integer(-9289), remainder); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(sqrt(-9289) is undefined (expected argument >= 0))")
    )
  );
}

TEST(IntegerFunctionsTests, powTest) {
  EXPECT_EQ(pow(Integer(5), Integer(2)), 25);
  EXPECT_EQ(pow(Integer(-5), Integer(5)), -3125);
  EXPECT_EQ(pow(Integer(6789), Integer(4)).toString(), "2124336126051441");
  EXPECT_EQ(pow(Integer(1), Integer("429837493286275623874628734628734")), 1);
  EXPECT_EQ(
    pow(Integer("135253468973498327423987498324729384"), Integer(3)).toString(),
    "2474259452251333810348988009462181048257185161014872437371075550103119323428971486869861741659206806895104"
  );
  EXPECT_EQ(pow(Integer(6789), Integer(-4)), 0);

  //   EXPECT_EQ(pow(Rational(5, 2), Integer(2)).toString(),
  //             "25/4");
  //   EXPECT_EQ(pow(Rational(-5, 2), Integer(5)).toString(),
  //             "-3125/32");
  //   EXPECT_EQ(pow(Rational(6789), Integer(4)).toString(),
  //             "2124336126051441");
  //   EXPECT_EQ(pow(Rational("135253468973498327423987498324729384.12987349823749832"), Integer(3)).toString(),
  //             "4832537992678386348337867205980822373798257851094432575433371642956047093945525418683507600681355491343220122262032882136893556623485326120689398001084489/1953125000000000000000000000000000000000000000000");
  //   EXPECT_EQ(pow(Rational(6789), Integer(-4)).toString(),
  //             "1/2124336126051441");

  //   EXPECT_EQ(pow(Real(5), Integer(2)).toString(),
  //             "25.0");
  //   EXPECT_EQ(pow(Real(-5), Integer(5)).toString(),
  //             "-3125.0");
  //   EXPECT_EQ(pow(Real(6789), Integer(4)).toString(),
  //             "2124336126051441.0");
  //   EXPECT_EQ(pow(Real("135253468973498327423987498324729384.12987349823749832"), Integer(3)).toString(),
  //             "2.4742594522513338103*10^105");
  //   EXPECT_EQ(pow(Real(6789), Integer(-4)).toString(),
  //             "4.7073529830645308412*10^-16");

  //   EXPECT_EQ(pow(Complex(5, 2), Integer(2)).toString(),
  //             "21 + 20 I");
  //   EXPECT_EQ(pow(Complex(Rational(1, 2), Rational(2, 3)), Integer(5)).toString(),
  //             "-79/2592 - 779/1944 I");
  //   EXPECT_EQ(pow(Complex(6789, 2345), Integer(4)).toString(),
  //             "633857838549916 + 2584899750306720 I");
  //   EXPECT_EQ(pow(Complex("135253468973498327423987498324729384.12987349823749832"), Integer(3)).toString(),
  //             "4832537992678386348337867205980822373798257851094432575433371642956047093945525418683507600681355491343220122262032882136893556623485326120689398001084489/1953125000000000000000000000000000000000000000000");
  //   EXPECT_EQ(pow(Complex(6789, 11), Integer(-4)).toString(),
  //             "531075666086959/1128212841481282934557153710724 - 860496245400/282053210370320733639288427681 I");

  //   EXPECT_THAT(
  //       [] { pow(Integer(0), Integer(0)); },
  //       testing::ThrowsMessage<UndefinedException>(
  //           testing::StrEq(R"(pow({}, {}) is undefined (zero to the power of zero))")));
  //   EXPECT_THAT(
  //       [] { pow(Rational(0), Integer(0)); },
  //       testing::ThrowsMessage<UndefinedException>(
  //           testing::StrEq(R"(pow({}, {}) is undefined (zero to the power of zero))")));
  //   EXPECT_THAT(
  //       [] { pow(Real(0), Integer(0)); },
  //       testing::ThrowsMessage<UndefinedException>(
  //           testing::StrEq(R"(pow({}, {}) is undefined (zero to the power of zero))")));
  //   EXPECT_THAT(
  //       [] { pow(Complex(0), Integer(0)); },
  //       testing::ThrowsMessage<UndefinedException>(
  //           testing::StrEq(R"(pow({}, {}) is undefined (zero to the power of zero))")));
}

TEST(IntegerFunctionsTests, factorialTest) {
  EXPECT_EQ(factorial(Integer(0)), 1);
  EXPECT_EQ(factorial(Integer(1)), 1);
  EXPECT_EQ(factorial(Integer(2)), 2);
  EXPECT_EQ(factorial(Integer(3)), 6);
  EXPECT_EQ(factorial(Integer(4)), 24);
  EXPECT_EQ(factorial(Integer(5)), 120);
  EXPECT_EQ(factorial(Integer(10)), 3628800);
  EXPECT_EQ(factorial(Integer(25)).toString(), "15511210043330985984000000");

  EXPECT_THAT(
    [] { factorial(Integer(-1)); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factorial(-1) is undefined (expected argument >= 0))")
    )
  );
  EXPECT_THAT(
    [] { factorial(Integer(-2)); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factorial(-2) is undefined (expected argument >= 0))")
    )
  );
}

TEST(IntegerFunctionsTests, nthFactorialTest) {
  EXPECT_EQ(factorial(Integer(0), 1), 1);
  EXPECT_EQ(factorial(Integer(1), 1), 1);
  EXPECT_EQ(factorial(Integer(2), 1), 2);
  EXPECT_EQ(factorial(Integer(3), 1), 6);
  EXPECT_EQ(factorial(Integer(4), 1), 24);
  EXPECT_EQ(factorial(Integer(5), 1), 120);
  EXPECT_EQ(factorial(Integer(10), 1), 3628800);
  EXPECT_EQ(factorial(Integer(25), 1).toString(), "15511210043330985984000000");

  EXPECT_EQ(factorial(Integer(0), 2), 1);
  EXPECT_EQ(factorial(Integer(1), 2), 1);
  EXPECT_EQ(factorial(Integer(2), 2), 2);
  EXPECT_EQ(factorial(Integer(3), 2), 3);
  EXPECT_EQ(factorial(Integer(4), 2), 8);
  EXPECT_EQ(factorial(Integer(5), 2), 15);
  EXPECT_EQ(factorial(Integer(10), 2), 3840);
  EXPECT_EQ(factorial(Integer(25), 2).toString(), "7905853580625");

  EXPECT_EQ(factorial(Integer(0), 3), 1);
  EXPECT_EQ(factorial(Integer(1), 3), 1);
  EXPECT_EQ(factorial(Integer(2), 3), 2);
  EXPECT_EQ(factorial(Integer(3), 3), 3);
  EXPECT_EQ(factorial(Integer(4), 3), 4);
  EXPECT_EQ(factorial(Integer(5), 3), 10);
  EXPECT_EQ(factorial(Integer(10), 3), 280);
  EXPECT_EQ(factorial(Integer(25), 3).toString(), "608608000");

  EXPECT_EQ(factorial(Integer(0), 10), 1);
  EXPECT_EQ(factorial(Integer(1), 10), 1);
  EXPECT_EQ(factorial(Integer(2), 10), 2);
  EXPECT_EQ(factorial(Integer(3), 10), 3);
  EXPECT_EQ(factorial(Integer(4), 10), 4);
  EXPECT_EQ(factorial(Integer(5), 10), 5);
  EXPECT_EQ(factorial(Integer(10), 10), 10);
  EXPECT_EQ(factorial(Integer(25), 10).toString(), "1875");

  EXPECT_THAT(
    [] { factorial(Integer(-1), 1); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factorial(-1, 1) is undefined (expected first argument >= 0))")
    )
  );
  EXPECT_THAT(
    [] { factorial(Integer(-1), 20); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factorial(-1, 20) is undefined (expected first argument >= 0))")
    )
  );
  EXPECT_THAT(
    [] { factorial(Integer(-2), 1); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factorial(-2, 1) is undefined (expected first argument >= 0))")
    )
  );
  EXPECT_THAT(
    [] { factorial(Integer(-2), 20); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factorial(-2, 20) is undefined (expected first argument >= 0))")
    )
  );
}

TEST(IntegerFunctionsTests, factorsTest) {
  FactorToCountMap factorToCountMap;

  factorToCountMap = factors(2);
  EXPECT_EQ(factorToCountMap.size(), 1);
  EXPECT_EQ(factorToCountMap[2], 1);

  factorToCountMap = factors(32);
  EXPECT_EQ(factorToCountMap.size(), 1);
  EXPECT_EQ(factorToCountMap[2], 5);

  factorToCountMap = factors(144);
  EXPECT_EQ(factorToCountMap.size(), 2);
  EXPECT_EQ(factorToCountMap[2], 4);
  EXPECT_EQ(factorToCountMap[3], 2);

  factorToCountMap = factors(123);
  EXPECT_EQ(factorToCountMap.size(), 2);
  EXPECT_EQ(factorToCountMap[3], 1);
  EXPECT_EQ(factorToCountMap[41], 1);

  factorToCountMap = factors(Integer("139826427468275632"), 1000);
  EXPECT_EQ(factorToCountMap.size(), 5);
  EXPECT_EQ(factorToCountMap[2], 4);
  EXPECT_EQ(factorToCountMap[7], 1);
  EXPECT_EQ(factorToCountMap[17], 1);
  EXPECT_EQ(factorToCountMap[31], 1);
  EXPECT_EQ(factorToCountMap[Integer("2368975797443")], 1);

  factorToCountMap = factors(Integer("139826427468275632"), 10000);
  EXPECT_EQ(factorToCountMap[2], 4);
  EXPECT_EQ(factorToCountMap[7], 1);
  EXPECT_EQ(factorToCountMap[17], 1);
  EXPECT_EQ(factorToCountMap[31], 1);
  EXPECT_EQ(factorToCountMap[1093], 1);
  EXPECT_EQ(factorToCountMap[Integer("2167406951")], 1);

  factorToCountMap = factors(Integer("13982642746827562949728"), 1000);
  EXPECT_EQ(factorToCountMap.size(), 3);
  EXPECT_EQ(factorToCountMap[2], 5);
  EXPECT_EQ(factorToCountMap[59], 1);
  EXPECT_EQ(factorToCountMap[Integer("7406060776921378681")], 1);

  EXPECT_THAT(
    [] { factors(-1); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factors(-1) is undefined (expected argument >= 2))")
    )
  );
  EXPECT_THAT(
    [] { factors(0); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factors(0) is undefined (expected argument >= 2))")
    )
  );
  EXPECT_THAT(
    [] { factors(1); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(factors(1) is undefined (expected argument >= 2))")
    )
  );
}

TEST(IntegerFunctionsTests, combinationsTest) {
  EXPECT_EQ(combinations(Integer(6), Integer(2)), 15);
  EXPECT_EQ(combinations(Integer(10), Integer(7)), 120);
  EXPECT_EQ(combinations(Integer(15), Integer(2)), 105);

  EXPECT_THAT(
    [] { combinations(Integer(20), Integer(40)); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(combinations(20, 40) is undefined (expected totalNumber > choosedNumber))")
    )
  );

  EXPECT_THAT(
    [] { combinations(Integer(-3), Integer(-8)); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(combinations(-3, -8) is undefined (expected totalNumber >= 0 and choosedNumber >= 0))")
    )
  );
  EXPECT_THAT(
    [] { combinations(Integer(5), Integer(-3)); },
    testing::ThrowsMessage<UndefinedException>(
      testing::StrEq(R"(combinations(5, -3) is undefined (expected totalNumber >= 0 and choosedNumber >= 0))")
    )
  );
}

TEST(IntegerFunctionsTests, multinomialCoefficientTest) {
  EXPECT_EQ(multinomialCoefficient({Integer(2), Integer(3), Integer(1)}), 60);
  EXPECT_EQ(multinomialCoefficient({Integer(8)}), 1);
  EXPECT_EQ(multinomialCoefficient({Integer(3), Integer(2)}), 10);
  EXPECT_EQ(multinomialCoefficient({Integer(3), Integer(9), Integer(0)}), 220);
}
