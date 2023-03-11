#include <gtest/gtest.h>

#include "fintamath/literals/constants/IConstant.hpp"

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

TEST(ConstantTests, callTests) {
  std::unique_ptr<IConstant> c1 = std::make_unique<E>();
  std::unique_ptr<IConstant> c2 = std::make_unique<Pi>();

  EXPECT_EQ((*c1)()->toString(), "2.7182818284590452353602874713526624977572470936999595749669676277240766303535476");
  EXPECT_EQ((*c2)()->toString(), "3.141592653589793238462643383279502884197169399375105820974944592307816406286209");
}
