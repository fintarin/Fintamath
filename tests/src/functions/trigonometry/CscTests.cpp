#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/trigonometry/Csc.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Csc f;

TEST(CscTests, toStringTest) {
  EXPECT_EQ(f.toString(), "csc");
}

TEST(CscTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(CscTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), INumber::getClassStatic());
}

TEST(CscTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(CscTests, isEvaluatableTest) {
  EXPECT_TRUE(f.isEvaluatable());
}

TEST(CscTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(10))->toString(), "-1.8381639608896655887");
  EXPECT_EQ(f(Integer(5))->toString(), "-1.0428352127714058198");

  EXPECT_EQ(f(Rational(1, 10))->toString(), "10.016686131634776649");

  EXPECT_EQ(f(Real("1.123"))->toString(), "1.1093811703345135938");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "csc(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "csc(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CscTests, exprTest) {
  EXPECT_EQ(cscExpr(Integer(10))->toString(), "csc(10)");
}

TEST(CscTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Csc");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
