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
using namespace detail;

TEST(MathObjectTypeTests, constructorTest) {
  {
    constexpr MathObjectType t(MathObjectType::Integer, "Int");
    EXPECT_EQ(t.getId(), static_cast<size_t>(MathObjectType::Integer));
    EXPECT_EQ(t.getName(), "Int");
  }
  {
    constexpr MathObjectType t(123, "NotInt");
    EXPECT_EQ(t.getId(), 123);
    EXPECT_EQ(t.getName(), "NotInt");
  }
}

TEST(MathObjectTypeTests, equalsTest) {
  EXPECT_TRUE(Integer::getTypeStatic() == Integer::getTypeStatic());
  EXPECT_FALSE(Integer::getTypeStatic() == Rational::getTypeStatic());
}

TEST(MathObjectTypeTests, compareTest) {
  EXPECT_EQ(Integer::getTypeStatic() <=> Integer::getTypeStatic(), std::strong_ordering::equal);
  EXPECT_EQ(Rational::getTypeStatic() <=> Integer::getTypeStatic(), std::strong_ordering::less);
  EXPECT_EQ(Integer::getTypeStatic() <=> Rational::getTypeStatic(), std::strong_ordering::greater);
}

TEST(MathObjectTypeTests, getIdTest) {
  EXPECT_EQ(Integer::getTypeStatic().getId(), static_cast<size_t>(MathObjectType::Integer));
}

TEST(MathObjectTypeTests, getNameTest) {
  EXPECT_EQ(Integer::getTypeStatic().getName(), "Integer");
}

TEST(MathObjectTypeTests, hashTest) {
  EXPECT_EQ(boost::hash<MathObjectType>{}(IMathObject::getTypeStatic()), static_cast<size_t>(MathObjectType::IMathObject));
  EXPECT_EQ(boost::hash<MathObjectType>{}(INumber::getTypeStatic()), static_cast<size_t>(MathObjectType::INumber));
  EXPECT_EQ(boost::hash<MathObjectType>{}(Integer::getTypeStatic()), static_cast<size_t>(MathObjectType::Integer));
  EXPECT_EQ(boost::hash<MathObjectType>{}(ILiteral::getTypeStatic()), static_cast<size_t>(MathObjectType::ILiteral));
  EXPECT_EQ(boost::hash<MathObjectType>{}(IConstant::getTypeStatic()), static_cast<size_t>(MathObjectType::IConstant));
  EXPECT_EQ(boost::hash<MathObjectType>{}(Boolean::getTypeStatic()), static_cast<size_t>(MathObjectType::Boolean));
}

TEST(MathObjectbindTypes, bindTypesTest) {
  // TODO: implement
}

TEST(MathObjectbindTypes, isBaseOfTest) {
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
