#include <gtest/gtest.h>

#include "fintamath/literals/Constant.hpp"

using namespace fintamath;

TEST(ConstantTests, stringConstructorTest){
  EXPECT_EQ(Constant("e").toString(), "e");
  EXPECT_EQ(Constant("pi").toString(), "pi");

  EXPECT_THROW(Constant("3.14"), std::invalid_argument);
  EXPECT_THROW(Constant("const"), std::invalid_argument);
  EXPECT_THROW(Constant(""), std::invalid_argument);
}

TEST(ConstantTest, toRationalTest){
  EXPECT_EQ(Constant("e").toRational(1), Rational("2.71828182845904523536028747135266249775724709369995957496696762772407663035354759"));
  EXPECT_EQ(Constant("pi").toRational(1), Rational("3.14159265358979323846264338327950288419716939937510582097494459230781640628620899"));
  EXPECT_EQ(Constant("e").toRational(100), Rational("2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274"));
  EXPECT_EQ(Constant("pi").toRational(100), Rational("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170674"));
}

TEST(ConstantTest, toStringTest){
  EXPECT_EQ(Constant("e").toString(), "e");
  EXPECT_EQ(Constant("pi").toString(), "pi");
}

TEST(ConstantTests, cloneTests){
  auto a = Constant("e");
  EXPECT_TRUE(&a != &(*a.clone()) && a==(*a.clone()).to<Constant>());
}

TEST(ConstantTests, equalsTests){
  EXPECT_TRUE(Constant("e") == Constant("e"));
  EXPECT_FALSE(Constant("e") == Constant("pi"));
}