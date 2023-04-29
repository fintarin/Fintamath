#include <gtest/gtest.h>

#include "fintamath/literals/ILiteral.hpp"

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

TEST(LiteralTests, equalsTests) {
  std::unique_ptr<ILiteral> c1 = std::make_unique<E>();
  std::unique_ptr<ILiteral> c2 = std::make_unique<Pi>();
  std::unique_ptr<ILiteral> v1 = std::make_unique<Variable>("a");
  std::unique_ptr<ILiteral> v2 = std::make_unique<Variable>("b");

  EXPECT_EQ(*c1, *c1);
  EXPECT_EQ(*c2, *c2);
  EXPECT_NE(*c1, *c2);
  EXPECT_NE(*c2, *c1);

  EXPECT_EQ(*v1, *v1);
  EXPECT_EQ(*v2, *v2);
  EXPECT_NE(*v1, *v2);
  EXPECT_NE(*v2, *v1);

  EXPECT_NE(*c1, *v1);
  EXPECT_NE(*c1, *v1);
}
