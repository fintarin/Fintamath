#include <gtest/gtest.h>

#include "fintamath/literals/constants/IConstant.hpp"

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"

using namespace fintamath;

namespace {

class TestConstant : public IConstantCRTP<Integer, TestConstant> {
  FINTAMATH_CLASS_BODY(TestConstant, IConstant)

protected:
  std::unique_ptr<IMathObject> call() const override {
    return {};
  }
};

[[maybe_unused]] const auto config = [] {
  IConstant::registerType<TestConstant>();
  return 0;
}();

}

TEST(IConstantTests, parseTest) {
  EXPECT_TRUE(is<TestConstant>(*IConstant::parseFirst("TestConstant")));
}

TEST(IConstantTests, callTest) {
  const std::unique_ptr<IConstant> c1 = std::make_unique<E>();
  const std::unique_ptr<IConstant> c2 = std::make_unique<Pi>();

  EXPECT_EQ((*c1)()->toString(), "2.7182818284590452354");
  EXPECT_EQ((*c2)()->toString(), "3.1415926535897932385");
}

TEST(IConstantTests, getClassTest) {
  EXPECT_EQ(IConstant::getClassStatic()->getName(), "IConstant");
  EXPECT_EQ(IConstant::getClassStatic()->getParent(), ILiteral::getClassStatic());
}
