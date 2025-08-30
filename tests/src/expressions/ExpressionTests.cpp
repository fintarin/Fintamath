#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(ExpressionTests, stringConstructorTest) {
  EXPECT_EQ(Expression("2 + 2").toString(), "(add 2 2)");
  EXPECT_EQ(Expression("2 + 3 + 4 + 5").toString(), "(add 2 3 4 5)");
  EXPECT_EQ(Expression("2 + 3 * 4 + 2").toString(), "(add 2 (mul 3 4) 2)");
  EXPECT_EQ(Expression("add(2, 3, 4, 5)").toString(), "(add 2 3 4 5)");
  EXPECT_EQ(Expression("mul(2, 3, 4, 5)").toString(), "(mul 2 3 4 5)");

  EXPECT_THAT(
    [] { Expression("true + false"); },
    testing::ThrowsMessage<InvalidInputException>(
      testing::StrEq(R"(Unable to parse an expression from "true + false" (operator args are invalid))")
    )
  );
}
