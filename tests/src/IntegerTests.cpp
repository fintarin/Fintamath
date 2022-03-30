#include <gtest/gtest.h>

#include "fintamath/nodes/numbers/Integer.hpp"

using namespace fintamath;

TEST(IntegerTests, plusAssignmentOperatorsTest) {
  Integer val;
  EXPECT_EQ(val += 2, 2);
}

TEST(IntegerTests, plusOperatorsTest) {
  Integer val;
  EXPECT_EQ(val + 2, 2);
  EXPECT_EQ(2 + val, 2);
}

TEST(IntegerTests, minusAssignmentOperatorsTest) {
  Integer val;
  EXPECT_EQ(val -= 2, -2);
}

TEST(IntegerTests, minusOperatorsTest) {
  Integer val;
  EXPECT_EQ(val - 2, -2);
  EXPECT_EQ(2 - val, 2);
}

TEST(IntegerTests, multiplyAssignmentOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val *= Integer(2), 4);
  EXPECT_EQ(val *= 2, 8);
}

TEST(IntegerTests, multiplyOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val * 2, 4);
  EXPECT_EQ(2 * val, 4);
}

TEST(IntegerTests, divideAssignmentOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val /= Integer(2), 1);
  EXPECT_EQ(val /= 2, 0);
}

TEST(IntegerTests, divideOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val / 2, 1);
  EXPECT_EQ(2 / val, 1);
}

TEST(IntegerTests, moduloAssignmentOperatorsTest) {
  Integer val(3);
  EXPECT_EQ(val %= Integer(2), 1);
  EXPECT_EQ(val %= 2, 1);
}

TEST(IntegerTests, moduloOperatorsTest) {
  Integer val(3);
  EXPECT_EQ(val % 2, 1);
  EXPECT_EQ(2 % val, 2);
}

TEST(IntegerTests, incrementDecrementOperatorsTest) {
  Integer val;
  EXPECT_EQ(++val, 1);
  EXPECT_EQ(val++, 1);
  EXPECT_EQ(val, 2);
  EXPECT_EQ(--val, 1);
  EXPECT_EQ(val--, 1);
  EXPECT_EQ(val, 0);
}

TEST(IntegerTests, unaryMinusPlusOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(+val, 2);
  EXPECT_EQ(-val, -2);
}

TEST(IntegerTests, equalOperatorsTest) {
  Integer val(2);
  Integer intVal(2);
  EXPECT_EQ(val == intVal, true);
  EXPECT_EQ(intVal == val, true);
  EXPECT_EQ(val == 2, true);
  EXPECT_EQ(2 == val, true);
}

TEST(IntegerTests, notEqualOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val != 1, true);
  EXPECT_EQ(1 != val, true);
}

TEST(IntegerTests, lessOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val < 1, false);
  EXPECT_EQ(1 < val, true);
  EXPECT_EQ(val < -1, false);
  EXPECT_EQ(-val < 1, true);
  EXPECT_EQ(-val < -1, true);
  EXPECT_EQ(Integer("10000000000000000000000000000000000") < Integer("1"), false);
  EXPECT_EQ(Integer("1") < Integer("10000000000000000000000000000000000"), true);
}

TEST(IntegerTests, moreOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val > 1, true);
  EXPECT_EQ(1 > val, false);
  EXPECT_EQ(val > -1, true);
  EXPECT_EQ(-val > 1, false);
  EXPECT_EQ(-val > -1, false);
  EXPECT_EQ(Integer("10000000000000000000000000000000000") > Integer("1"), true);
  EXPECT_EQ(Integer("1") > Integer("10000000000000000000000000000000000"), false);
}

TEST(IntegerTests, lessEqualOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val <= 1, false);
  EXPECT_EQ(1 <= val, true);
  EXPECT_EQ(val <= -1, false);
  EXPECT_EQ(-val <= 1, true);
  EXPECT_EQ(-val <= -1, true);
  EXPECT_EQ(Integer("10000000000000000000000000000000000") <= Integer("1"), false);
  EXPECT_EQ(Integer("1") <= Integer("10000000000000000000000000000000000"), true);
}

TEST(IntegerTests, moreEqualOperatorsTest) {
  Integer val(2);
  EXPECT_EQ(val >= 1, true);
  EXPECT_EQ(1 >= val, false);
  EXPECT_EQ(val >= -1, true);
  EXPECT_EQ(-val >= 1, false);
  EXPECT_EQ(-val >= -1, false);
  EXPECT_EQ(Integer("10000000000000000000000000000000000") >= Integer("1"), true);
  EXPECT_EQ(Integer("1") >= Integer("10000000000000000000000000000000000"), false);
}

TEST(IntegerTests, inOperatorsTest) {
  Integer val;
  std::stringstream in;
  in << 2;
  in >> val;
  EXPECT_EQ(val, 2);
}

TEST(IntegerTests, outOperatorsTest) {
  Integer val(2);
  std::stringstream out;
  out << val;
  EXPECT_EQ(out.str(), "2");
}

TEST(IntegerTests, divisionModuloNegativeTest) {
  Integer val(2);
  EXPECT_EQ(0 / val, 0);
  EXPECT_EQ(0 % val, 0);
  EXPECT_THROW(val / 0, std::domain_error);
  EXPECT_THROW(val % 0, std::domain_error);
}

TEST(IntegerTests, sqrtNegativeTest) {
  EXPECT_THROW(sqrt(Integer(-2)), std::domain_error);
}

TEST(IntegerTests, negativeToStringTest) {
  EXPECT_EQ(Integer(-1).toString(), "-1");
}
