#include <gtest/gtest.h>

#include "fintamath/literals/constants/Constant.hpp"

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

TEST(ConstantTests, parseTest) {
  EXPECT_TRUE(Constant::parse("e")->is<E>());
  EXPECT_TRUE(Constant::parse("pi")->is<Pi>());

  EXPECT_EQ(Constant::parse("a"), nullptr);
  EXPECT_EQ(Constant::parse("z"), nullptr);
  EXPECT_EQ(Constant::parse("1"), nullptr);
  EXPECT_EQ(Constant::parse("a_"), nullptr);
  EXPECT_EQ(Constant::parse("a1"), nullptr);
  EXPECT_EQ(Constant::parse("aa"), nullptr);
}
