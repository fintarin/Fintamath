#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"

using namespace fintamath;

TEST(ExpressionTests, stringConstructorTest) {
  EXPECT_EQ(simplify(Expression("2 + 2")).toString(), "(add 2 2)");
  EXPECT_EQ(simplify(Expression("2 + 3 + 4 + 5")).toString(), "(add 2 3 4 5)");
  EXPECT_EQ(simplify(Expression("2 + 3 * 4 + 2")).toString(), "(add 2 (mul 3 4) 2)");
  EXPECT_EQ(simplify(Expression("add(2, 3, 4, 5)")).toString(), "(add 2 3 4 5)");
  EXPECT_EQ(simplify(Expression("mul(2, 3, 4, 5)")).toString(), "(mul 2 3 4 5)");
  EXPECT_EQ(simplify(Expression("sin(sin(x + x))")).toString(), "(sin (sin (add x x)))");

  EXPECT_THAT(
    [] { Expression("True + False"); },
    testing::ThrowsMessage<InvalidInputException>(
      testing::StrEq(R"(Unable to parse an expression from "True + False" (operator args are invalid))")
    )
  );
}
