#include <gtest/gtest.h>

#include "fintamath/core/IIntegral.hpp"

#include "fintamath/exceptions/InvalidInputBinaryOperatorException.hpp"
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

  TestIntegral &bitAnd(const TestIntegral &rhs) override {
    return *this;
  }

  TestIntegral &bitOr(const TestIntegral &rhs) override {
    return *this;
  }

  TestIntegral &bitXor(const TestIntegral &rhs) override {
    return *this;
  }

  TestIntegral &bitLeftShift(const TestIntegral &rhs) override {
    return *this;
  }

  TestIntegral &bitRightShift(const TestIntegral &rhs) override {
    return *this;
  }

  TestIntegral &bitNot() override {
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
  unique_ptr<IIntegral> m1 = make_unique<Integer>(10);
  unique_ptr<IIntegral> m2 = make_unique<Integer>(3);

  EXPECT_EQ((*m1 % *m1)->toString(), "0");
  EXPECT_EQ((*m2 % *m2)->toString(), "0");
  EXPECT_EQ((*m1 % *m2)->toString(), "1");
  EXPECT_EQ((*m2 % *m1)->toString(), "3");

  EXPECT_TRUE(is<Integer>(*m1 % *m1));
  EXPECT_TRUE(is<Integer>(*m2 % *m2));
  EXPECT_TRUE(is<Integer>(*m1 % *m2));
  EXPECT_TRUE(is<Integer>(*m2 % *m1));

  EXPECT_THROW(*m1 % TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() % *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a %= 3).toString(), "0");
}

TEST(IntegralTests, bitAndTest) {
  unique_ptr<IIntegral> m1 = make_unique<Integer>(10);
  unique_ptr<IIntegral> m2 = make_unique<Integer>(3);

  EXPECT_EQ((*m1 & *m1)->toString(), "10");
  EXPECT_EQ((*m2 & *m2)->toString(), "3");
  EXPECT_EQ((*m1 & *m2)->toString(), "2");
  EXPECT_EQ((*m2 & *m1)->toString(), "2");

  EXPECT_TRUE(is<Integer>(*m1 & *m1));
  EXPECT_TRUE(is<Integer>(*m2 & *m2));
  EXPECT_TRUE(is<Integer>(*m1 & *m2));
  EXPECT_TRUE(is<Integer>(*m2 & *m1));

  EXPECT_THROW(*m1 & TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() & *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a &= 3).toString(), "0");
}

TEST(IntegralTests, bitOrTest) {
  unique_ptr<IIntegral> m1 = make_unique<Integer>(10);
  unique_ptr<IIntegral> m2 = make_unique<Integer>(3);

  EXPECT_EQ((*m1 | *m1)->toString(), "10");
  EXPECT_EQ((*m2 | *m2)->toString(), "3");
  EXPECT_EQ((*m1 | *m2)->toString(), "11");
  EXPECT_EQ((*m2 | *m1)->toString(), "11");

  EXPECT_TRUE(is<Integer>(*m1 | *m1));
  EXPECT_TRUE(is<Integer>(*m2 | *m2));
  EXPECT_TRUE(is<Integer>(*m1 | *m2));
  EXPECT_TRUE(is<Integer>(*m2 | *m1));

  EXPECT_THROW(*m1 | TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() | *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a |= 3).toString(), "3");
}

TEST(IntegralTests, bitXorTest) {
  unique_ptr<IIntegral> m1 = make_unique<Integer>(10);
  unique_ptr<IIntegral> m2 = make_unique<Integer>(3);

  EXPECT_EQ((*m1 ^ *m1)->toString(), "0");
  EXPECT_EQ((*m2 ^ *m2)->toString(), "0");
  EXPECT_EQ((*m1 ^ *m2)->toString(), "9");
  EXPECT_EQ((*m2 ^ *m1)->toString(), "9");

  EXPECT_TRUE(is<Integer>(*m1 ^ *m1));
  EXPECT_TRUE(is<Integer>(*m2 ^ *m2));
  EXPECT_TRUE(is<Integer>(*m1 ^ *m2));
  EXPECT_TRUE(is<Integer>(*m2 ^ *m1));

  EXPECT_THROW(*m1 ^ TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() ^ *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a ^= 3).toString(), "3");
}

TEST(IntegralTests, bitLeftShiftTest) {
  unique_ptr<IIntegral> m1 = make_unique<Integer>(10);
  unique_ptr<IIntegral> m2 = make_unique<Integer>(3);

  EXPECT_EQ((*m1 << *m1)->toString(), "10240");
  EXPECT_EQ((*m2 << *m2)->toString(), "24");
  EXPECT_EQ((*m1 << *m2)->toString(), "80");
  EXPECT_EQ((*m2 << *m1)->toString(), "3072");

  EXPECT_TRUE(is<Integer>(*m1 << *m1));
  EXPECT_TRUE(is<Integer>(*m2 << *m2));
  EXPECT_TRUE(is<Integer>(*m1 << *m2));
  EXPECT_TRUE(is<Integer>(*m2 << *m1));

  EXPECT_THROW(*m1 << TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() << *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a <<= 3).toString(), "0");
}

TEST(IntegralTests, bitRightShiftTest) {
  unique_ptr<IIntegral> m1 = make_unique<Integer>(10);
  unique_ptr<IIntegral> m2 = make_unique<Integer>(3);

  EXPECT_EQ((*m1 >> *m1)->toString(), "0");
  EXPECT_EQ((*m2 >> *m2)->toString(), "0");
  EXPECT_EQ((*m1 >> *m2)->toString(), "1");
  EXPECT_EQ((*m2 >> *m1)->toString(), "0");

  EXPECT_TRUE(is<Integer>(*m1 >> *m1));
  EXPECT_TRUE(is<Integer>(*m2 >> *m2));
  EXPECT_TRUE(is<Integer>(*m1 >> *m2));
  EXPECT_TRUE(is<Integer>(*m2 >> *m1));

  EXPECT_THROW(*m1 >> TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() >> *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a >>= 3).toString(), "0");
}

TEST(IntegralTests, bitNotTest) {
  unique_ptr<IIntegral> m1 = make_unique<Integer>(44);
  EXPECT_EQ((~*m1)->toString(), "-45");

  EXPECT_EQ((~Integer(1)).toString(), "-2");
}
