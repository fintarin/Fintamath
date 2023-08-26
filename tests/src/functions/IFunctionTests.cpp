#include <gtest/gtest.h>

#include "fintamath/functions/IFunction.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(IFunctionTests, callTest) {
  std::unique_ptr<IFunction> f = std::make_unique<Add>();
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_EQ((*f)(a, a)->toString(), "6");
  EXPECT_EQ((*f)(b, b)->toString(), "1");
  EXPECT_EQ((*f)(a, b)->toString(), "7/2");
  EXPECT_EQ((*f)(b, a)->toString(), "7/2");

  EXPECT_EQ((*f)(a, c)->toString(), "c + 3");

  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a, a, a), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a, a, a, a, a, a, a), InvalidInputFunctionException);
}

TEST(IFunctionTests, calVectTest) {
  std::unique_ptr<IFunction> f = std::make_unique<Add>();
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_EQ((*f)({a, a})->toString(), "6");
  EXPECT_EQ((*f)({b, b})->toString(), "1");
  EXPECT_EQ((*f)({a, b})->toString(), "7/2");
  EXPECT_EQ((*f)({b, a})->toString(), "7/2");

  EXPECT_EQ((*f)({a, c})->toString(), "c + 3");

  EXPECT_THROW((*f)({}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a, a, a}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a, a, a, a, a, a, a}), InvalidInputFunctionException);
}

TEST(IFunctionTests, equalsTest) {
  EXPECT_EQ(Add(), Add());
  EXPECT_NE(Add(), Sub());
  EXPECT_NE(Sub(), Add());
  EXPECT_NE(Add(), UnaryPlus());
  EXPECT_NE(UnaryPlus(), Add());
  EXPECT_NE(Add(), Sin());
  EXPECT_NE(Sin(), Add());
}

TEST(IFunctionTests, getFunctionTypeTest) {
  EXPECT_EQ(Add().getFunctionType(), IFunction::Type::Binary);
  EXPECT_EQ(Neg().getFunctionType(), IFunction::Type::Unary);
  EXPECT_EQ(Sin().getFunctionType(), IFunction::Type::Unary);
}

TEST(IFunctionTests, getReturnTypeIdTest) {
  EXPECT_EQ(Add().getReturnTypeId(), IArithmetic::getTypeIdStatic());
  EXPECT_EQ(Neg().getReturnTypeId(), IArithmetic::getTypeIdStatic());
  EXPECT_EQ(Sin().getReturnTypeId(), INumber::getTypeIdStatic());
}

TEST(IFunctionTests, getArgTypeIdsTest) {
  EXPECT_EQ(Add().getArgTypeIds()[0], IArithmetic::getTypeIdStatic());
  EXPECT_EQ(Add().getArgTypeIds()[1], IArithmetic::getTypeIdStatic());
  EXPECT_EQ(Neg().getArgTypeIds()[0], IArithmetic::getTypeIdStatic());
  EXPECT_EQ(Sin().getArgTypeIds()[0], INumber::getTypeIdStatic());
}

TEST(IFunctionTests, doArgsMatchTest) {
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_TRUE(Add().doArgsMatch({a, b}));
  EXPECT_FALSE(Add().doArgsMatch({c, c}));
  EXPECT_FALSE(Add().doArgsMatch({a, c}));
  EXPECT_FALSE(Add().doArgsMatch({c, a}));
  EXPECT_FALSE(Add().doArgsMatch({a}));
  EXPECT_FALSE(Add().doArgsMatch({a, a, a}));
  EXPECT_FALSE(Add().doArgsMatch({a, b, a, b}));
}

TEST(IFunctionTests, getTypeIdTest) {
  EXPECT_EQ(IFunction::getTypeIdStatic(), MathObjectTypeId(MathObjectType::IFunction));
}
