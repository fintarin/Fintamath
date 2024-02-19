#include <gtest/gtest.h>

#include "fintamath/core/MathObjectType.hpp"

#include "fintamath/literals/ILiteral.hpp"
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

  {
    const MathObjectType t(MathObjectType::Integer, "Int");
    EXPECT_EQ(t.getId(), static_cast<size_t>(MathObjectType::Integer));
    EXPECT_EQ(t.getName(), "Int");
  }
  {
    const MathObjectType t(123, "NotInt");
    EXPECT_EQ(t.getId(), 123);
    EXPECT_EQ(t.getName(), "NotInt");
  }
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
