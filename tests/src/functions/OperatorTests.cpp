#include <gtest/gtest.h>

#include "fintamath/functions/IOperator.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/factorials/DoubleFactorial.hpp"
#include "fintamath/functions/factorials/Factorial.hpp"
#include "fintamath/functions/other/Percent.hpp"
#include "fintamath/functions/powers/Pow.hpp"

using namespace fintamath;

TEST(OperatorTests, parseTest) {
  EXPECT_TRUE(IOperator::parse("+", IOperator::Priority::Addition)->is<Add>());
  EXPECT_TRUE(IOperator::parse("+", IOperator::Priority::PrefixUnary)->is<UnaryPlus>());
  EXPECT_TRUE(IOperator::parse("-", IOperator::Priority::Addition)->is<Sub>());
  EXPECT_TRUE(IOperator::parse("-", IOperator::Priority::PrefixUnary)->is<Neg>());
  EXPECT_TRUE(IOperator::parse("*")->is<Mul>());
  EXPECT_TRUE(IOperator::parse("/")->is<Div>());
  EXPECT_TRUE(IOperator::parse("^")->is<Pow>());
  EXPECT_TRUE(IOperator::parse("%")->is<Percent>());
  EXPECT_TRUE(IOperator::parse("!")->is<Factorial>());
  EXPECT_TRUE(IOperator::parse("!!")->is<DoubleFactorial>());

  EXPECT_EQ(IOperator::parse("asdgewfe"), nullptr);
  EXPECT_EQ(IOperator::parse("1224"), nullptr);
}
