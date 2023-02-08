#include <gtest/gtest.h>

#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/True.hpp"
#include "fintamath/meta/InheritanceTable.hpp"

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(InheritanceTableTests, isBaseOfTest) {
  EXPECT_TRUE(InheritanceTable::isBaseOf(typeid(INumber), typeid(Integer)));
  EXPECT_TRUE(InheritanceTable::isBaseOf(typeid(INumber), typeid(Rational)));
  EXPECT_TRUE(InheritanceTable::isBaseOf(typeid(IConstant), typeid(True)));
  EXPECT_TRUE(InheritanceTable::isBaseOf(typeid(ILiteral), typeid(Variable)));
  EXPECT_TRUE(InheritanceTable::isBaseOf(typeid(ILiteral), typeid(IConstant)));
  EXPECT_TRUE(InheritanceTable::isBaseOf(typeid(ILiteral), typeid(True)));
  EXPECT_TRUE(InheritanceTable::isBaseOf(typeid(ILiteral), typeid(E)));

  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(Integer), typeid(INumber)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(Rational), typeid(INumber)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(True), typeid(IConstant)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(Variable), typeid(ILiteral)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(IConstant), typeid(ILiteral)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(True), typeid(ILiteral)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(E), typeid(ILiteral)));

  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(ILiteral), typeid(Integer)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(ILiteral), typeid(Rational)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(ILiteral), typeid(INumber)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(IConstant), typeid(INumber)));
  EXPECT_FALSE(InheritanceTable::isBaseOf(typeid(Boolean), typeid(INumber)));
}
