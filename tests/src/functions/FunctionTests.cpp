#include <gtest/gtest.h>

#include "fintamath/functions/Function.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/other/Abs.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(FunctionTests, callTests) {
  FunctionPtr f = std::make_unique<Add>();
  Integer a = 3;
  Rational b(1, 2);

  EXPECT_EQ((*f)(a, a)->toString(), "6");
  EXPECT_EQ((*f)(b, b)->toString(), "1");
  EXPECT_EQ((*f)(a, b)->toString(), "7/2");
  EXPECT_EQ((*f)(b, a)->toString(), "7/2");

  EXPECT_THROW((*f)(a, Variable("a")), std::invalid_argument);

  EXPECT_THROW((*f)(), std::invalid_argument);
  EXPECT_THROW((*f)(a), std::invalid_argument);
  EXPECT_THROW((*f)(a, a, a), std::invalid_argument);
  EXPECT_THROW((*f)(a, a, a, a, a, a, a), std::invalid_argument);
}

TEST(FunctionTests, equalsTests) {
  EXPECT_TRUE(Add() == Add());

  EXPECT_FALSE(Add() == Sub());
  EXPECT_FALSE(Sub() == Add());
}

TEST(FunctionTests, parseTest) {
  EXPECT_TRUE(Function::parse("+")->is<Add>());
  EXPECT_TRUE(Function::parse("-")->is<Sub>());
  EXPECT_TRUE(Function::parse("-", true)->is<Neg>());
  EXPECT_TRUE(Function::parse("*")->is<Mul>());
  EXPECT_TRUE(Function::parse("/")->is<Div>());
  EXPECT_TRUE(Function::parse("^")->is<Pow>());
  EXPECT_TRUE(Function::parse("pow")->is<Pow>());
  EXPECT_TRUE(Function::parse("%")->is<Percent>());
  EXPECT_TRUE(Function::parse("!")->is<Factorial>());
  EXPECT_TRUE(Function::parse("!!")->is<DoubleFactorial>());
  EXPECT_TRUE(Function::parse("sqrt")->is<Sqrt>());
  EXPECT_TRUE(Function::parse("exp")->is<Exp>());
  EXPECT_TRUE(Function::parse("log")->is<Log>());
  EXPECT_TRUE(Function::parse("ln")->is<Ln>());
  EXPECT_TRUE(Function::parse("lb")->is<Lb>());
  EXPECT_TRUE(Function::parse("lg")->is<Lg>());
  EXPECT_TRUE(Function::parse("sin")->is<Sin>());
  EXPECT_TRUE(Function::parse("cos")->is<Cos>());
  EXPECT_TRUE(Function::parse("tan")->is<Tan>());
  EXPECT_TRUE(Function::parse("cot")->is<Cot>());
  EXPECT_TRUE(Function::parse("asin")->is<Asin>());
  EXPECT_TRUE(Function::parse("acos")->is<Acos>());
  EXPECT_TRUE(Function::parse("atan")->is<Atan>());
  EXPECT_TRUE(Function::parse("acot")->is<Acot>());
  EXPECT_TRUE(Function::parse("abs")->is<Abs>());

  EXPECT_EQ(Function::parse("asdgewfe"), nullptr);
  EXPECT_EQ(Function::parse("1224"), nullptr);
}
