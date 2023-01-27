#include <gtest/gtest.h>

#include "fintamath/core/IModular.hpp"

#include "fintamath/exceptions/InvalidInputBinaryOpearatorException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestModular : public IModularCRTP<TestModular> {
public:
protected:
  TestModular &mod(const TestModular & /* rhs */) override {
    return *this;
  }
};

}

TEST(ModularTests, modTest) {
  ModularPtr m1 = std::make_unique<Integer>(10);
  ModularPtr m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 % *m1)->toString(), "0");
  EXPECT_EQ((*m2 % *m2)->toString(), "0");
  EXPECT_EQ((*m1 % *m2)->toString(), "1");
  EXPECT_EQ((*m2 % *m1)->toString(), "3");

  EXPECT_TRUE(cast<Integer>(*m1 % *m1));
  EXPECT_TRUE(cast<Integer>(*m2 % *m2));
  EXPECT_TRUE(cast<Integer>(*m1 % *m2));
  EXPECT_TRUE(cast<Integer>(*m2 % *m1));

  EXPECT_THROW(*m1 % TestModular(), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(TestModular() % *m1, InvalidInputBinaryOpearatorException);

  Integer a;
  EXPECT_EQ((a %= 3).toString(), "0");
}
