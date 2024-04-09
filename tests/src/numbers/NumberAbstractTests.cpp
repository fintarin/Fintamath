#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(NumberAbstractIntegerTests, multiplyTest) {
  EXPECT_EQ((Integer(0) * cast<IComparable>(Real(2)))->toString(), "0");
  EXPECT_EQ((Integer(1) * cast<IComparable>(Real(2)))->toString(), "2.0");
}

TEST(NumberAbstractIntegerTests, divideTest) {
  EXPECT_EQ((Integer(4) / cast<IComparable>(Integer(2)))->toString(), "2");
  EXPECT_EQ((Integer(1) / cast<IComparable>(Integer(2)))->toString(), "1/2");

  EXPECT_EQ((Integer(0) / cast<IComparable>(Real(2)))->toString(), "0");
  EXPECT_EQ((Integer(1) / cast<IComparable>(Real(2)))->toString(), "0.5");

  EXPECT_THAT(
      [] { Integer(0) / cast<IComparable>(Integer(0)); },
      testing::ThrowsMessage<UndefinedException>(
          testing::StrEq(R"(div(0, 0) is undefined (division by zero))")));
  EXPECT_THAT(
      [] { Integer(0) / cast<IComparable>(Real(0)); },
      testing::ThrowsMessage<UndefinedException>(
          testing::StrEq(R"(div(0.0, 0.0) is undefined (division by zero))")));
}

//-------------------------------------------------------------------------------------//

TEST(NumberAbstractRationalTests, multiplyTest) {
  EXPECT_EQ((Rational(0) * cast<IComparable>(Real(2)))->toString(), "0");
  EXPECT_EQ((Rational(1) * cast<IComparable>(Real(2)))->toString(), "2.0");
}

TEST(NumberAbstractRationalTests, divideTest) {
  EXPECT_EQ((Rational(0) / cast<IComparable>(Real(2)))->toString(), "0");
  EXPECT_EQ((Rational(1) / cast<IComparable>(Real(2)))->toString(), "0.5");

  EXPECT_THAT(
      [] { Rational(0) / cast<IComparable>(Integer(0)); },
      testing::ThrowsMessage<UndefinedException>(
          testing::StrEq(R"(div(0, 0) is undefined (division by zero))")));
  EXPECT_THAT(
      [] { Rational(0) / cast<IComparable>(Real(0)); },
      testing::ThrowsMessage<UndefinedException>(
          testing::StrEq(R"(div(0.0, 0.0) is undefined (division by zero))")));
}

//-------------------------------------------------------------------------------------//

TEST(NumberAbstractRealTests, equalsTest) {
  const Real a;
  const Integer b;
  const Rational c;

  EXPECT_NE(a, cast<IMathObject>(b));
  EXPECT_NE(cast<IMathObject>(b), a);
  EXPECT_NE(a, cast<IMathObject>(c));
  EXPECT_NE(cast<IMathObject>(c), a);
}

TEST(NumberAbstractRealTests, compareTest) {
  Real a;
  Integer b;
  Rational c;

  EXPECT_GT(a, cast<IComparable>(b));
  EXPECT_LT(cast<IComparable>(b), a);
  EXPECT_GE(a, cast<IComparable>(b));
  EXPECT_LE(cast<IComparable>(b), a);

  EXPECT_GT(a, cast<IComparable>(c));
  EXPECT_LT(cast<IComparable>(c), a);
  EXPECT_GE(a, cast<IComparable>(c));
  EXPECT_LE(cast<IComparable>(c), a);

  a = 10;
  b = 10;
  c = 10;

  EXPECT_GT(a, cast<IComparable>(b));
  EXPECT_LT(cast<IComparable>(b), a);
  EXPECT_GE(a, cast<IComparable>(b));
  EXPECT_LE(cast<IComparable>(b), a);

  EXPECT_GT(a, cast<IComparable>(c));
  EXPECT_LT(cast<IComparable>(c), a);
  EXPECT_GE(a, cast<IComparable>(c));
  EXPECT_LE(cast<IComparable>(c), a);

  a = -10;
  b = -10;
  c = -10;

  EXPECT_LT(a, cast<IComparable>(b));
  EXPECT_GT(cast<IComparable>(b), a);
  EXPECT_LE(a, cast<IComparable>(b));
  EXPECT_GE(cast<IComparable>(b), a);

  EXPECT_LT(a, cast<IComparable>(c));
  EXPECT_GT(cast<IComparable>(c), a);
  EXPECT_LE(a, cast<IComparable>(c));
  EXPECT_GE(cast<IComparable>(c), a);
}

TEST(NumberAbstractRealTests, multiplyTest) {
  EXPECT_EQ((Real(2) * cast<IComparable>(Integer(0)))->toString(), "0");
  EXPECT_EQ((Real(2) * cast<IComparable>(Integer(2)))->toString(), "4.0");
}
