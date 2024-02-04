#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Csc.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Csc f;

TEST(CscTests, toStringTest) {
  EXPECT_EQ(f.toString(), "csc");
}

TEST(CscTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CscTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(10))->toString(),
            "-1.8381639608896655887052365237649145973889020018834973862573493747201515058875292");
  EXPECT_EQ(f(Integer(5))->toString(),
            "-1.0428352127714058197831198559077598439723517523645461744044708582222288573346961");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "10.016686131634776648706352542080683736894622464520060956623269457319144620943524");

  EXPECT_EQ(f(Real("1.123"))->toString(),
            "1.1093811703345135937778706061052839025764741627310001533337188696539698252609898");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "csc(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "csc(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CscTests, exprTest) {
  EXPECT_EQ(cscExpr(Integer(10))->toString(), "csc(10)");
}

TEST(CscTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(CscTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Csc());
  EXPECT_EQ(Csc(), f);
  EXPECT_EQ(f, cast<IMathObject>(Csc()));
  EXPECT_EQ(cast<IMathObject>(Csc()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(CscTests, getTypeTest) {
  EXPECT_EQ(Csc::getTypeStatic(), MathObjectType::Csc);
  EXPECT_EQ(Csc().getType(), MathObjectType::Csc);
}
