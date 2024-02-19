#include <gtest/gtest.h>

#include "fintamath/core/MathObjectBoundTypes.hpp"

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/True.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;
using namespace detail;

TEST(MathObjectBoundTypesTests, bindTypesTest) {
  // TODO: implement
}

TEST(MathObjectBoundTypesTests, isBaseOfTest) {
  EXPECT_TRUE(isBaseOf(INumber::getTypeStatic(), Integer::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(INumber::getTypeStatic(), Rational::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(IArithmetic::getTypeStatic(), Integer::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(IMathObject::getTypeStatic(), Integer::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(IArithmetic::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(IMathObject::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(IMathObject::getTypeStatic(), IArithmetic::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(IConstant::getTypeStatic(), True::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(ILiteral::getTypeStatic(), Variable::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(ILiteral::getTypeStatic(), IConstant::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(ILiteral::getTypeStatic(), True::getTypeStatic()));
  EXPECT_TRUE(isBaseOf(ILiteral::getTypeStatic(), E::getTypeStatic()));

  EXPECT_FALSE(isBaseOf(Integer::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(Rational::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(Integer::getTypeStatic(), IArithmetic::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(Integer::getTypeStatic(), IMathObject::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(INumber::getTypeStatic(), IArithmetic::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(INumber::getTypeStatic(), IMathObject::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(IArithmetic::getTypeStatic(), IMathObject::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(True::getTypeStatic(), IConstant::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(Variable::getTypeStatic(), ILiteral::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(IConstant::getTypeStatic(), ILiteral::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(True::getTypeStatic(), ILiteral::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(E::getTypeStatic(), ILiteral::getTypeStatic()));

  EXPECT_FALSE(isBaseOf(ILiteral::getTypeStatic(), Integer::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(ILiteral::getTypeStatic(), Rational::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(ILiteral::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(IConstant::getTypeStatic(), INumber::getTypeStatic()));
  EXPECT_FALSE(isBaseOf(Boolean::getTypeStatic(), INumber::getTypeStatic()));
}
