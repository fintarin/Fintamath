#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyHyperbolicTests, simplifyTest) {
  EXPECT_EQ(Expression("sinh(-x)").toString(),
            "-sinh(x)");
  EXPECT_EQ(Expression("cosh(-x)").toString(),
            "cosh(x)");
  EXPECT_EQ(Expression("tanh(-x)").toString(),
            "-tanh(x)");
  EXPECT_EQ(Expression("coth(-x)").toString(),
            "-coth(x)");
  EXPECT_EQ(Expression("sech(-x)").toString(),
            "sech(x)");
  EXPECT_EQ(Expression("csch(-x)").toString(),
            "-csch(x)");

  EXPECT_EQ(Expression("sinh(asinh(x))").toString(),
            "x");
  EXPECT_EQ(Expression("cosh(acosh(x))").toString(),
            "x");
  EXPECT_EQ(Expression("tanh(atanh(x))").toString(),
            "x");
  EXPECT_EQ(Expression("coth(acoth(x))").toString(),
            "x");
  EXPECT_EQ(Expression("sech(asech(x))").toString(),
            "x");
  EXPECT_EQ(Expression("csch(acsch(x))").toString(),
            "x");
  EXPECT_EQ(Expression("asinh(sinh(x))").toString(),
            "asinh(sinh(x))");
  EXPECT_EQ(Expression("acosh(cosh(x))").toString(),
            "acosh(cosh(x))");
  EXPECT_EQ(Expression("atanh(tanh(x))").toString(),
            "atanh(tanh(x))");
  EXPECT_EQ(Expression("acoth(coth(x))").toString(),
            "acoth(coth(x))");
  EXPECT_EQ(Expression("asech(sech(x))").toString(),
            "asech(sech(x))");
  EXPECT_EQ(Expression("acsch(csch(x))").toString(),
            "acsch(csch(x))");

  EXPECT_EQ(Expression("sinh(x)/cosh(x)").toString(),
            "tanh(x)");
  EXPECT_EQ(Expression("(-2sinh(x))/cosh(x)").toString(),
            "-2 tanh(x)");
  EXPECT_EQ(Expression("(2sinh(x))/(3cosh(x))").toString(),
            "(2 tanh(x))/3");
  EXPECT_EQ(Expression("sinh(x)^2/cosh(x)").toString(),
            "sinh(x)^2 sech(x)");
  EXPECT_EQ(Expression("sinh(x)/cosh(x)^2").toString(),
            "sech(x)^2 sinh(x)");
  EXPECT_EQ(Expression("sinh(x)^2/cosh(x)^2").toString(),
            "tanh(x)^2");
  EXPECT_EQ(Expression("(2sinh(x))^2/cosh(x)^2").toString(),
            "4 tanh(x)^2");
  EXPECT_EQ(Expression("(2sinh(x))^2/(3cosh(x))^2").toString(),
            "(4 tanh(x)^2)/9");

  EXPECT_EQ(Expression("cosh(x)/sinh(x)").toString(),
            "coth(x)");
  EXPECT_EQ(Expression("(-2cosh(x))/sinh(x)").toString(),
            "-2 coth(x)");
  EXPECT_EQ(Expression("(2cosh(x))/(3sinh(x))").toString(),
            "(2 coth(x))/3");
  EXPECT_EQ(Expression("cosh(x)^2/sinh(x)").toString(),
            "cosh(x)^2 csch(x)");
  EXPECT_EQ(Expression("cosh(x)/sinh(x)^2").toString(),
            "csch(x)^2 cosh(x)");
  EXPECT_EQ(Expression("cosh(x)^2/sinh(x)^2").toString(),
            "coth(x)^2");
  EXPECT_EQ(Expression("(2cosh(x))^2/sinh(x)^2").toString(),
            "4 coth(x)^2");
  EXPECT_EQ(Expression("(2cosh(x))^2/(3sinh(x))^2").toString(),
            "(4 coth(x)^2)/9");

  EXPECT_EQ(Expression("sech(x)/csch(x)").toString(),
            "tanh(x)");
  EXPECT_EQ(Expression("csch(x)/sech(x)").toString(),
            "coth(x)");
  EXPECT_EQ(Expression("sech(x)*coth(x)").toString(),
            "csch(x)");
  EXPECT_EQ(Expression("csch(x)*tanh(x)").toString(),
            "sech(x)");

  EXPECT_EQ(Expression("tanh(x) * coth(x)").toString(),
            "1");
  EXPECT_EQ(Expression("coth(x) * tanh(x)").toString(),
            "1");
  // TODO: implement
  // EXPECT_EQ(Expression("cosh(x)^2 - sinh(x)^2").toString(),
  //           "1");
}
