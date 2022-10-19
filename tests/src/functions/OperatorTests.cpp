#include <gtest/gtest.h>

#include "fintamath/functions/Operator.hpp"

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
  EXPECT_TRUE(Operator::parse("+", Operator::Priority::Addition)->is<Add>());
  EXPECT_TRUE(Operator::parse("+", Operator::Priority::PrefixUnary)->is<UnaryPlus>());
  EXPECT_TRUE(Operator::parse("-", Operator::Priority::Addition)->is<Sub>());
  EXPECT_TRUE(Operator::parse("-", Operator::Priority::PrefixUnary)->is<Neg>());
  EXPECT_TRUE(Operator::parse("*")->is<Mul>());
  EXPECT_TRUE(Operator::parse("/")->is<Div>());
  EXPECT_TRUE(Operator::parse("^")->is<Pow>());
  EXPECT_TRUE(Operator::parse("%")->is<Percent>());
  EXPECT_TRUE(Operator::parse("!")->is<Factorial>());
  EXPECT_TRUE(Operator::parse("!!")->is<DoubleFactorial>());

  EXPECT_EQ(Operator::parse("asdgewfe"), nullptr);
  EXPECT_EQ(Operator::parse("1224"), nullptr);
}
