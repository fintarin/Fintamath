#include <gtest/gtest.h>

#include "fintamath/core/IIntegral.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestIntegral : public IIntegralCRTP<TestIntegral> {
  FINTAMATH_CONVERTIBLE()

public:
  std::string toString() const override {
    return "test";
  }

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

  TestIntegral &substract(const TestIntegral &rhs) override {
    return *this;
  }

  TestIntegral &multiply(const TestIntegral &rhs) override {
    return *this;
  }

  TestIntegral &divide(const TestIntegral &rhs) override {
    return *this;
  }

  TestIntegral &negate() override {
    return *this;
  }
};

class TestIntegralConvertible : public TestIntegral {
public:
  TestIntegralConvertible() : TestIntegral() {
  }

  TestIntegralConvertible(const Integer &rhs) : TestIntegralConvertible() {
  }
};

struct TestIntegralConvertableConfig {
  TestIntegralConvertableConfig() {
    Converter::add<TestIntegralConvertible, TestIntegralConvertible>(
        [](const TestIntegralConvertible & /*type*/, const TestIntegralConvertible &value) {
          return std::make_unique<TestIntegralConvertible>(value);
        });
    Converter::add<TestIntegralConvertible, Integer>(
        [](const TestIntegralConvertible & /*type*/, const Integer &value) {
          return std::make_unique<TestIntegralConvertible>(value);
        });
  }
};

const TestIntegralConvertableConfig config;

}

TEST(IIntegralTests, modTest) {
  std::unique_ptr<IIntegral> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IIntegral> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 % *m1)->toString(), "0");
  EXPECT_EQ((*m2 % *m2)->toString(), "0");
  EXPECT_EQ((*m1 % *m2)->toString(), "1");
  EXPECT_EQ((*m2 % *m1)->toString(), "3");

  EXPECT_TRUE(is<Integer>(*m1 % *m1));
  EXPECT_TRUE(is<Integer>(*m2 % *m2));
  EXPECT_TRUE(is<Integer>(*m1 % *m2));
  EXPECT_TRUE(is<Integer>(*m2 % *m1));

  EXPECT_TRUE(is<TestIntegral>(*m1 % TestIntegralConvertible()));
  EXPECT_TRUE(is<TestIntegral>(TestIntegralConvertible() % *m1));

  EXPECT_THROW(*m1 % TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() % *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a %= 3).toString(), "0");
}

TEST(IIntegralTests, bitAndTest) {
  std::unique_ptr<IIntegral> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IIntegral> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 & *m1)->toString(), "10");
  EXPECT_EQ((*m2 & *m2)->toString(), "3");
  EXPECT_EQ((*m1 & *m2)->toString(), "2");
  EXPECT_EQ((*m2 & *m1)->toString(), "2");

  EXPECT_TRUE(is<Integer>(*m1 & *m1));
  EXPECT_TRUE(is<Integer>(*m2 & *m2));
  EXPECT_TRUE(is<Integer>(*m1 & *m2));
  EXPECT_TRUE(is<Integer>(*m2 & *m1));

  EXPECT_TRUE(is<TestIntegral>(*m1 & TestIntegralConvertible()));
  EXPECT_TRUE(is<TestIntegral>(TestIntegralConvertible() & *m1));

  EXPECT_THROW(*m1 & TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() & *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a &= 3).toString(), "0");
}

TEST(IIntegralTests, bitOrTest) {
  std::unique_ptr<IIntegral> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IIntegral> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 | *m1)->toString(), "10");
  EXPECT_EQ((*m2 | *m2)->toString(), "3");
  EXPECT_EQ((*m1 | *m2)->toString(), "11");
  EXPECT_EQ((*m2 | *m1)->toString(), "11");

  EXPECT_TRUE(is<Integer>(*m1 | *m1));
  EXPECT_TRUE(is<Integer>(*m2 | *m2));
  EXPECT_TRUE(is<Integer>(*m1 | *m2));
  EXPECT_TRUE(is<Integer>(*m2 | *m1));

  EXPECT_TRUE(is<TestIntegral>(*m1 | TestIntegralConvertible()));
  EXPECT_TRUE(is<TestIntegral>(TestIntegralConvertible() | *m1));

  EXPECT_THROW(*m1 | TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() | *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a |= 3).toString(), "3");
}

TEST(IIntegralTests, bitXorTest) {
  std::unique_ptr<IIntegral> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IIntegral> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 ^ *m1)->toString(), "0");
  EXPECT_EQ((*m2 ^ *m2)->toString(), "0");
  EXPECT_EQ((*m1 ^ *m2)->toString(), "9");
  EXPECT_EQ((*m2 ^ *m1)->toString(), "9");

  EXPECT_TRUE(is<Integer>(*m1 ^ *m1));
  EXPECT_TRUE(is<Integer>(*m2 ^ *m2));
  EXPECT_TRUE(is<Integer>(*m1 ^ *m2));
  EXPECT_TRUE(is<Integer>(*m2 ^ *m1));

  EXPECT_TRUE(is<TestIntegral>(*m1 ^ TestIntegralConvertible()));
  EXPECT_TRUE(is<TestIntegral>(TestIntegralConvertible() ^ *m1));

  EXPECT_THROW(*m1 ^ TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() ^ *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a ^= 3).toString(), "3");
}

TEST(IIntegralTests, bitLeftShiftTest) {
  std::unique_ptr<IIntegral> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IIntegral> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 << *m1)->toString(), "10240");
  EXPECT_EQ((*m2 << *m2)->toString(), "24");
  EXPECT_EQ((*m1 << *m2)->toString(), "80");
  EXPECT_EQ((*m2 << *m1)->toString(), "3072");

  EXPECT_TRUE(is<Integer>(*m1 << *m1));
  EXPECT_TRUE(is<Integer>(*m2 << *m2));
  EXPECT_TRUE(is<Integer>(*m1 << *m2));
  EXPECT_TRUE(is<Integer>(*m2 << *m1));

  EXPECT_TRUE(is<TestIntegral>(*m1 << TestIntegralConvertible()));
  EXPECT_TRUE(is<TestIntegral>(TestIntegralConvertible() << *m1));

  EXPECT_THROW(*m1 << TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() << *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a <<= 3).toString(), "0");
}

TEST(IIntegralTests, bitRightShiftTest) {
  std::unique_ptr<IIntegral> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IIntegral> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 >> *m1)->toString(), "0");
  EXPECT_EQ((*m2 >> *m2)->toString(), "0");
  EXPECT_EQ((*m1 >> *m2)->toString(), "1");
  EXPECT_EQ((*m2 >> *m1)->toString(), "0");

  EXPECT_TRUE(is<Integer>(*m1 >> *m1));
  EXPECT_TRUE(is<Integer>(*m2 >> *m2));
  EXPECT_TRUE(is<Integer>(*m1 >> *m2));
  EXPECT_TRUE(is<Integer>(*m2 >> *m1));

  EXPECT_TRUE(is<TestIntegral>(*m1 >> TestIntegralConvertible()));
  EXPECT_TRUE(is<TestIntegral>(TestIntegralConvertible() >> *m1));

  EXPECT_THROW(*m1 >> TestIntegral(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestIntegral() >> *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a >>= 3).toString(), "0");
}

TEST(IIntegralTests, bitNotTest) {
  std::unique_ptr<IIntegral> m1 = std::make_unique<Integer>(44);
  EXPECT_EQ((~*m1)->toString(), "-45");

  EXPECT_EQ((~Integer(1)).toString(), "-2");
}
