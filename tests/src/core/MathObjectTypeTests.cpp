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

TEST(MathObjectTypesTests, isBaseOfTest) {
  EXPECT_TRUE(isBaseOf(INumber::getTypeIdStatic(), Integer::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(INumber::getTypeIdStatic(), Rational::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(IArithmetic::getTypeIdStatic(), Integer::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(IMathObject::getTypeIdStatic(), Integer::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(IArithmetic::getTypeIdStatic(), INumber::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(IMathObject::getTypeIdStatic(), INumber::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(IMathObject::getTypeIdStatic(), IArithmetic::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(IConstant::getTypeIdStatic(), True::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(ILiteral::getTypeIdStatic(), Variable::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(ILiteral::getTypeIdStatic(), IConstant::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(ILiteral::getTypeIdStatic(), True::getTypeIdStatic()));
  EXPECT_TRUE(isBaseOf(ILiteral::getTypeIdStatic(), E::getTypeIdStatic()));

  EXPECT_FALSE(isBaseOf(Integer::getTypeIdStatic(), INumber::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(Rational::getTypeIdStatic(), INumber::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(Integer::getTypeIdStatic(), IArithmetic::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(Integer::getTypeIdStatic(), IMathObject::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(INumber::getTypeIdStatic(), IArithmetic::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(INumber::getTypeIdStatic(), IMathObject::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(IArithmetic::getTypeIdStatic(), IMathObject::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(True::getTypeIdStatic(), IConstant::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(Variable::getTypeIdStatic(), ILiteral::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(IConstant::getTypeIdStatic(), ILiteral::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(True::getTypeIdStatic(), ILiteral::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(E::getTypeIdStatic(), ILiteral::getTypeIdStatic()));

  EXPECT_FALSE(isBaseOf(ILiteral::getTypeIdStatic(), Integer::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(ILiteral::getTypeIdStatic(), Rational::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(ILiteral::getTypeIdStatic(), INumber::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(IConstant::getTypeIdStatic(), INumber::getTypeIdStatic()));
  EXPECT_FALSE(isBaseOf(Boolean::getTypeIdStatic(), INumber::getTypeIdStatic()));
}
