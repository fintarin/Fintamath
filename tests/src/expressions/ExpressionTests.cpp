#include <gtest/gtest.h>

#include <fintamath/numbers/Rational.hpp>
#include <fstream>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(ExpressionTests, toStringTest){

}

TEST(ExpressionTests, constructorTest){
  EXPECT_EQ(Expression().toString(), "");
}

TEST(ExpressionTests, moveTest){
  auto a = Expression("1+2-3");
  EXPECT_EQ(a.toString(),"0");
  auto b = std::move(a);
  EXPECT_TRUE(b.toString() == "0" && a.toString() == "");
  a = std::move(b);
  EXPECT_TRUE(a.toString() == "0" && b.toString() == "");

}

TEST(ExpressionTests, copyTest){
  auto a = Expression("1+2");
  auto b = a;
  EXPECT_TRUE(a == b && &a != &b);
}

TEST(ExpressionTests, simplifyTest){
    EXPECT_EQ(Expression("2").toString(), "2");
    EXPECT_EQ(Expression("2 + 2").toString(), "4");
    EXPECT_EQ(Expression("2 * 2").toString(), "4");
    EXPECT_EQ(Expression("2 ^ 2").toString(), "4");
    EXPECT_EQ(Expression("2 + 2 * 2").toString(), "6");
    EXPECT_EQ(Expression("(2 + 2) * 2").toString(), "8");
    EXPECT_EQ(Expression("(2 + 2) / (2 ^ 2 - 2) * 2").toString(), "4");
    EXPECT_EQ(Expression("((((2))))").toString(), "2");
    EXPECT_EQ(Expression("(((((2 + 2) + 2) + 2) + 2) + 2)").toString(), "12");
    EXPECT_EQ(Expression("(((2 ^ 2)^2))").toString(), "16");
    EXPECT_EQ(Expression("2^2^2^2").toString(), "65536");
    EXPECT_EQ(Expression("(2-2)").toString(), "0");
    EXPECT_EQ(Expression("0^1").toString(), "0");
    EXPECT_EQ(Expression("2^0").toString(), "1");
    EXPECT_EQ(Expression("0/3").toString(), "0");
    EXPECT_EQ(Expression("1/3").toString(), "1/3");
    EXPECT_EQ(Expression("-2+3").toString(), "1");


    EXPECT_EQ(Expression("-(-(-(-(-(-(-(-a)))))))").toString(), "a");
    EXPECT_EQ(Expression("a+a").toString(), "2*a");
    EXPECT_EQ(Expression("a-a").toString(), "0");
    EXPECT_EQ(Expression("(a+b)-b").toString(), "a");

    EXPECT_EQ(Expression("(a+b)*(a+b)+a*b*c-c*a*b+b*a").toString(), "b*b+a*a+3*a*b");
}