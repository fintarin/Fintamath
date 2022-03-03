#include <gtest/gtest.h>

#include "fintamath/math_objects/nodes/expressions/Expression.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Integer.hpp"


using namespace fintamath;

TEST(ExpressionTests, stringConstructorTest) {
  EXPECT_THROW(Expression("(1+2"), std::invalid_argument);

  EXPECT_EQ(Expression("5").toString(), "5");
  EXPECT_EQ(Expression("(((56+(25/10))))").toString(), "56+25/10");
  EXPECT_EQ(Expression("(10+20)-(10+40)").toString(), "10+20-(10+40)");
}

TEST(ExpressionTests, toStringTest) {
  EXPECT_EQ(Expression("5").toString(), "5");

  EXPECT_EQ(Expression("-1").toString(), "-1");
  EXPECT_EQ(Expression("+-+-+1").toString(), "+(-(+(-(+1))))");

  EXPECT_EQ(Expression("-(1+2)").toString(), "-(1+2)");
  EXPECT_EQ(Expression("-(1-2)").toString(), "-(1-2)");
  EXPECT_EQ(Expression("+(1+2)").toString(), "+1+2");
  EXPECT_EQ(Expression("5--4").toString(), "5-(-4)");

  EXPECT_EQ(Expression("(10+20)*(20/15)").toString(), "(10+20)*20/15");
  EXPECT_EQ(Expression("(10+20)-(10+40)").toString(), "10+20-(10+40)");
  EXPECT_EQ(Expression("(10+20)*(10+40)").toString(), "(10+20)*(10+40)");
}

TEST(ExpressionTests, getSetTest){
  EXPECT_EQ(Expression("10").getSet(), Set{std::make_shared<Integer>(10)});
}
