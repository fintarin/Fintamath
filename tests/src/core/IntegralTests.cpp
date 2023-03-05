#include <gtest/gtest.h>

#include "fintamath/core/IIntegral.hpp"

#include "fintamath/exceptions/InvalidInputBinaryOpearatorException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestIntegral : public IIntegralCRTP<TestIntegral> {
public:
protected:
  TestIntegral &mod(const TestIntegral & /* rhs */) override {
    return *this;
  }

  TestIntegral &add(const TestIntegral &rhs) override {
    return *this;
  }

  virtual TestIntegral &substract(const TestIntegral &rhs) override {
    return *this;
  }

  virtual TestIntegral &multiply(const TestIntegral &rhs) override {
    return *this;
  }

  virtual TestIntegral &divide(const TestIntegral &rhs) override {
    return *this;
  }

  virtual TestIntegral &negate() override {
    return *this;
  }
};

}

TEST(IntegralTests, modTest) {
  IntegralPtr m1 = std::make_unique<Integer>(10);
  IntegralPtr m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 % *m1)->toString(), "0");
  EXPECT_EQ((*m2 % *m2)->toString(), "0");
  EXPECT_EQ((*m1 % *m2)->toString(), "1");
  EXPECT_EQ((*m2 % *m1)->toString(), "3");

  EXPECT_TRUE(is<Integer>(*m1 % *m1));
  EXPECT_TRUE(is<Integer>(*m2 % *m2));
  EXPECT_TRUE(is<Integer>(*m1 % *m2));
  EXPECT_TRUE(is<Integer>(*m2 % *m1));

  EXPECT_THROW(*m1 % TestIntegral(), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(TestIntegral() % *m1, InvalidInputBinaryOpearatorException);

  Integer a;
  EXPECT_EQ((a %= 3).toString(), "0");
}
