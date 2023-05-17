#include <gtest/gtest.h>

#include "fintamath/core/MathObjectTypes.hpp"

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/True.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(MathObjectTypesTests, isTest) {
  EXPECT_TRUE(is(INumber::getTypeStatic(), Integer::getTypeStatic()));
  EXPECT_TRUE(is(INumber::getTypeStatic(), Rational::getTypeStatic()));
  EXPECT_TRUE(is(IArithmetic::getTypeStatic(), Integer::getTypeStatic()));
  EXPECT_TRUE(is(IMathObject::getTypeStatic(), Integer::getTypeStatic()));
  EXPECT_TRUE(is(IArithmetic::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_TRUE(is(IMathObject::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_TRUE(is(IMathObject::getTypeStatic(), IArithmetic::getTypeStatic()));
  EXPECT_TRUE(is(IConstant::getTypeStatic(), True::getTypeStatic()));
  EXPECT_TRUE(is(ILiteral::getTypeStatic(), Variable::getTypeStatic()));
  EXPECT_TRUE(is(ILiteral::getTypeStatic(), IConstant::getTypeStatic()));
  EXPECT_TRUE(is(ILiteral::getTypeStatic(), True::getTypeStatic()));
  EXPECT_TRUE(is(ILiteral::getTypeStatic(), E::getTypeStatic()));

  EXPECT_FALSE(is(Integer::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_FALSE(is(Rational::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_FALSE(is(Integer::getTypeStatic(), IArithmetic::getTypeStatic()));
  EXPECT_FALSE(is(Integer::getTypeStatic(), IMathObject::getTypeStatic()));
  EXPECT_FALSE(is(INumber::getTypeStatic(), IArithmetic::getTypeStatic()));
  EXPECT_FALSE(is(INumber::getTypeStatic(), IMathObject::getTypeStatic()));
  EXPECT_FALSE(is(IArithmetic::getTypeStatic(), IMathObject::getTypeStatic()));
  EXPECT_FALSE(is(True::getTypeStatic(), IConstant::getTypeStatic()));
  EXPECT_FALSE(is(Variable::getTypeStatic(), ILiteral::getTypeStatic()));
  EXPECT_FALSE(is(IConstant::getTypeStatic(), ILiteral::getTypeStatic()));
  EXPECT_FALSE(is(True::getTypeStatic(), ILiteral::getTypeStatic()));
  EXPECT_FALSE(is(E::getTypeStatic(), ILiteral::getTypeStatic()));

  EXPECT_FALSE(is(ILiteral::getTypeStatic(), Integer::getTypeStatic()));
  EXPECT_FALSE(is(ILiteral::getTypeStatic(), Rational::getTypeStatic()));
  EXPECT_FALSE(is(ILiteral::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_FALSE(is(IConstant::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_FALSE(is(Boolean::getTypeStatic(), INumber::getTypeStatic()));
}
