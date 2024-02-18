#include <gtest/gtest.h>

#include "fintamath/literals/constants/IConstant.hpp"

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

TEST(IConstantTests, callTest) {
  const std::unique_ptr<IConstant> c1 = std::make_unique<E>();
  const std::unique_ptr<IConstant> c2 = std::make_unique<Pi>();

  EXPECT_EQ((*c1)()->toString(), "2.7182818284590452354");
  EXPECT_EQ((*c2)()->toString(), "3.1415926535897932385");
}

TEST(IConstantTests, getTypeTest) {
  EXPECT_EQ(IConstant::getTypeStatic(), MathObjectType(MathObjectType::IConstant, "IConstant"));
}
