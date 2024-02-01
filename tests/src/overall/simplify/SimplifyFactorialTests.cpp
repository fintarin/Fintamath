#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyFactorialTests, simplifyTest) {
  EXPECT_EQ(Expression("9!").toString(),
            "362880");
  EXPECT_EQ(Expression("-1!").toString(),
            "-1");
  EXPECT_EQ(Expression("-100!").toString(),
            "-933262154439441526816992388562667004907159682643816214685929638952175999932299156089414639761565182862536"
            "97920827223758251185210916864000000000000000000000000");
  EXPECT_EQ(Expression("(5!)!").toString(),
            "6689502913449127057588118054090372586752746333138029810295671352301633557244962989366874165271984981308157"
            "637893214090552534408589408121859898481114389650005964960521256960000000000000000000000000000");
  EXPECT_EQ(Expression("(2)!").toString(),
            "2");

  EXPECT_EQ(Expression("5!").toString(),
            "120");
  EXPECT_EQ(Expression("5!!").toString(),
            "15");
  EXPECT_EQ(Expression("5!!!").toString(),
            "10");
  EXPECT_EQ(Expression("5!!!!").toString(),
            "5");
  EXPECT_EQ(Expression("5!!!!!").toString(),
            "5");
  EXPECT_EQ(Expression("5!!!!!!").toString(),
            "5");
  EXPECT_EQ(Expression("6!").toString(),
            "720");
  EXPECT_EQ(Expression("6!!").toString(),
            "48");
  EXPECT_EQ(Expression("6!!!").toString(),
            "18");
  EXPECT_EQ(Expression("6!!!!").toString(),
            "12");
  EXPECT_EQ(Expression("6!!!!!").toString(),
            "6");
  EXPECT_EQ(Expression("6!!!!!!").toString(),
            "6");
  EXPECT_EQ(Expression("15!!!!!!").toString(),
            "405");
  EXPECT_EQ(Expression("15!!!!!!!").toString(),
            "120");
  EXPECT_EQ(Expression("30!!!!!!").toString(),
            "933120");
  EXPECT_EQ(Expression("30!!!!!!!").toString(),
            "198720");

  EXPECT_EQ(Expression("(2/3)!").toString(),
            "(2/3)!");
  EXPECT_EQ(Expression("E!").toString(),
            "E!");
  EXPECT_EQ(Expression("(2/3)!!").toString(),
            "(2/3)!!");
  EXPECT_EQ(Expression("(-1)!!").toString(),
            "(-1)!!");
}
