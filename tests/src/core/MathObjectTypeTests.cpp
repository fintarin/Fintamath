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

TEST(MathObjectTypesTests, constructorTest) {
  EXPECT_EQ(MathObjectType(MathObjectType::Integer), Integer::getTypeStatic());
  EXPECT_EQ(MathObjectType(static_cast<size_t>(MathObjectType::Integer)), Integer::getTypeStatic());
}

TEST(MathObjectTypesTests, equalsTest) {
  EXPECT_TRUE(Integer::getTypeStatic() == Integer::getTypeStatic());
  EXPECT_FALSE(Integer::getTypeStatic() == Rational::getTypeStatic());

  EXPECT_TRUE(Integer::getTypeStatic() == MathObjectType::Integer);
  EXPECT_FALSE(Integer::getTypeStatic() == MathObjectType::Rational);

  EXPECT_TRUE(Integer::getTypeStatic() == static_cast<size_t>(Integer::getTypeStatic()));
  EXPECT_FALSE(Integer::getTypeStatic() == static_cast<size_t>(Rational::getTypeStatic()));
}

TEST(MathObjectTypesTests, compareTest) {
  EXPECT_EQ(Integer::getTypeStatic() <=> Integer::getTypeStatic(), std::strong_ordering::equal);
  EXPECT_EQ(Integer::getTypeStatic() <=> Rational::getTypeStatic(), std::strong_ordering::greater);

  EXPECT_EQ(Integer::getTypeStatic() <=> MathObjectType::Integer, std::strong_ordering::equal);
  EXPECT_EQ(Integer::getTypeStatic() <=> MathObjectType::Rational, std::strong_ordering::greater);

  EXPECT_EQ(Integer::getTypeStatic() <=> static_cast<size_t>(Integer::getTypeStatic()), std::strong_ordering::equal);
  EXPECT_EQ(Integer::getTypeStatic() <=> static_cast<size_t>(Rational::getTypeStatic()), std::strong_ordering::greater);
}

TEST(MathObjectTypesTests, isBaseOfTest) {
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

TEST(MathObjectTypesTests, hashTest) {
  EXPECT_EQ(boost::hash<MathObjectType>{}(MathObjectType::IMathObject), static_cast<size_t>(MathObjectType::IMathObject));
  EXPECT_EQ(boost::hash<MathObjectType>{}(MathObjectType::INumber), static_cast<size_t>(MathObjectType::INumber));
  EXPECT_EQ(boost::hash<MathObjectType>{}(MathObjectType::Integer), static_cast<size_t>(MathObjectType::Integer));
  EXPECT_EQ(boost::hash<MathObjectType>{}(MathObjectType::ILiteral), static_cast<size_t>(MathObjectType::ILiteral));
  EXPECT_EQ(boost::hash<MathObjectType>{}(MathObjectType::IConstant), static_cast<size_t>(MathObjectType::IConstant));
  EXPECT_EQ(boost::hash<MathObjectType>{}(MathObjectType::Boolean), static_cast<size_t>(MathObjectType::Boolean));
  EXPECT_EQ(boost::hash<MathObjectType>{}(MathObjectType::None), static_cast<size_t>(MathObjectType::None));
}
