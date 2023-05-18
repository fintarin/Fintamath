#include <gtest/gtest.h>

#include "fintamath/numbers/IInteger.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestInteger : public IIntegerCRTP<TestInteger> {
  FINTAMATH_CONVERTIBLE()

public:
  std::string toString() const override {
    return "test";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return size_t(getBoundTypeIds().at(MathObjectTypeId(MathObjectType::IInteger))) - 1;
  }

protected:
  TestInteger &mod(const TestInteger & /* rhs */) override {
    return *this;
  }

  TestInteger &bitAnd(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &bitOr(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &bitXor(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &bitLeftShift(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &bitRightShift(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &bitNot() override {
    return *this;
  }

  TestInteger &add(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &substract(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &multiply(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &divide(const TestInteger &rhs) override {
    return *this;
  }

  TestInteger &negate() override {
    return *this;
  }

  bool less(const TestInteger &rhs) const override {
    return false;
  }

  bool more(const TestInteger &rhs) const override {
    return false;
  }

  TestInteger &increase() override {
    return *this;
  }

  TestInteger &decrease() override {
    return *this;
  }
};

class TestIntegerConvertible : public TestInteger {
public:
  TestIntegerConvertible() : TestInteger() {
  }

  TestIntegerConvertible(const Integer &rhs) : TestIntegerConvertible() {
  }
};

struct TestIntegerConvertableConfig {
  TestIntegerConvertableConfig() {
    Converter::add<TestIntegerConvertible, TestIntegerConvertible>(
        [](const TestIntegerConvertible & /*type*/, const TestIntegerConvertible &value) {
          return std::make_unique<TestIntegerConvertible>(value);
        });
    Converter::add<TestIntegerConvertible, Integer>([](const TestIntegerConvertible & /*type*/, const Integer &value) {
      return std::make_unique<TestIntegerConvertible>(value);
    });
  }
};

const TestIntegerConvertableConfig config;

}

TEST(IIntegerTests, modTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IInteger> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 % *m1)->toString(), "0");
  EXPECT_EQ((*m2 % *m2)->toString(), "0");
  EXPECT_EQ((*m1 % *m2)->toString(), "1");
  EXPECT_EQ((*m2 % *m1)->toString(), "3");

  EXPECT_TRUE(is<Integer>(*m1 % *m1));
  EXPECT_TRUE(is<Integer>(*m2 % *m2));
  EXPECT_TRUE(is<Integer>(*m1 % *m2));
  EXPECT_TRUE(is<Integer>(*m2 % *m1));

  EXPECT_TRUE(is<TestInteger>(*m1 % TestIntegerConvertible()));
  EXPECT_TRUE(is<TestInteger>(TestIntegerConvertible() % *m1));

  EXPECT_THROW(*m1 % TestInteger(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestInteger() % *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a %= 3).toString(), "0");
}

TEST(IIntegerTests, bitAndTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IInteger> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 & *m1)->toString(), "10");
  EXPECT_EQ((*m2 & *m2)->toString(), "3");
  EXPECT_EQ((*m1 & *m2)->toString(), "2");
  EXPECT_EQ((*m2 & *m1)->toString(), "2");

  EXPECT_TRUE(is<Integer>(*m1 & *m1));
  EXPECT_TRUE(is<Integer>(*m2 & *m2));
  EXPECT_TRUE(is<Integer>(*m1 & *m2));
  EXPECT_TRUE(is<Integer>(*m2 & *m1));

  EXPECT_TRUE(is<TestInteger>(*m1 & TestIntegerConvertible()));
  EXPECT_TRUE(is<TestInteger>(TestIntegerConvertible() & *m1));

  EXPECT_THROW(*m1 & TestInteger(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestInteger() & *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a &= 3).toString(), "0");
}

TEST(IIntegerTests, bitOrTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IInteger> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 | *m1)->toString(), "10");
  EXPECT_EQ((*m2 | *m2)->toString(), "3");
  EXPECT_EQ((*m1 | *m2)->toString(), "11");
  EXPECT_EQ((*m2 | *m1)->toString(), "11");

  EXPECT_TRUE(is<Integer>(*m1 | *m1));
  EXPECT_TRUE(is<Integer>(*m2 | *m2));
  EXPECT_TRUE(is<Integer>(*m1 | *m2));
  EXPECT_TRUE(is<Integer>(*m2 | *m1));

  EXPECT_TRUE(is<TestInteger>(*m1 | TestIntegerConvertible()));
  EXPECT_TRUE(is<TestInteger>(TestIntegerConvertible() | *m1));

  EXPECT_THROW(*m1 | TestInteger(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestInteger() | *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a |= 3).toString(), "3");
}

TEST(IIntegerTests, bitXorTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IInteger> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 ^ *m1)->toString(), "0");
  EXPECT_EQ((*m2 ^ *m2)->toString(), "0");
  EXPECT_EQ((*m1 ^ *m2)->toString(), "9");
  EXPECT_EQ((*m2 ^ *m1)->toString(), "9");

  EXPECT_TRUE(is<Integer>(*m1 ^ *m1));
  EXPECT_TRUE(is<Integer>(*m2 ^ *m2));
  EXPECT_TRUE(is<Integer>(*m1 ^ *m2));
  EXPECT_TRUE(is<Integer>(*m2 ^ *m1));

  EXPECT_TRUE(is<TestInteger>(*m1 ^ TestIntegerConvertible()));
  EXPECT_TRUE(is<TestInteger>(TestIntegerConvertible() ^ *m1));

  EXPECT_THROW(*m1 ^ TestInteger(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestInteger() ^ *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a ^= 3).toString(), "3");
}

TEST(IIntegerTests, bitLeftShiftTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IInteger> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 << *m1)->toString(), "10240");
  EXPECT_EQ((*m2 << *m2)->toString(), "24");
  EXPECT_EQ((*m1 << *m2)->toString(), "80");
  EXPECT_EQ((*m2 << *m1)->toString(), "3072");

  EXPECT_TRUE(is<Integer>(*m1 << *m1));
  EXPECT_TRUE(is<Integer>(*m2 << *m2));
  EXPECT_TRUE(is<Integer>(*m1 << *m2));
  EXPECT_TRUE(is<Integer>(*m2 << *m1));

  EXPECT_TRUE(is<TestInteger>(*m1 << TestIntegerConvertible()));
  EXPECT_TRUE(is<TestInteger>(TestIntegerConvertible() << *m1));

  EXPECT_THROW(*m1 << TestInteger(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestInteger() << *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a <<= 3).toString(), "0");
}

TEST(IIntegerTests, bitRightShiftTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(10);
  std::unique_ptr<IInteger> m2 = std::make_unique<Integer>(3);

  EXPECT_EQ((*m1 >> *m1)->toString(), "0");
  EXPECT_EQ((*m2 >> *m2)->toString(), "0");
  EXPECT_EQ((*m1 >> *m2)->toString(), "1");
  EXPECT_EQ((*m2 >> *m1)->toString(), "0");

  EXPECT_TRUE(is<Integer>(*m1 >> *m1));
  EXPECT_TRUE(is<Integer>(*m2 >> *m2));
  EXPECT_TRUE(is<Integer>(*m1 >> *m2));
  EXPECT_TRUE(is<Integer>(*m2 >> *m1));

  EXPECT_TRUE(is<TestInteger>(*m1 >> TestIntegerConvertible()));
  EXPECT_TRUE(is<TestInteger>(TestIntegerConvertible() >> *m1));

  EXPECT_THROW(*m1 >> TestInteger(), InvalidInputBinaryOperatorException);
  EXPECT_THROW(TestInteger() >> *m1, InvalidInputBinaryOperatorException);

  Integer a;
  EXPECT_EQ((a >>= 3).toString(), "0");
}

TEST(IIntegerTests, bitNotTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(44);
  EXPECT_EQ((~*m1)->toString(), "-45");

  EXPECT_EQ((~Integer(1)).toString(), "-2");
}

TEST(IIntegerTests, incTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(1);
  EXPECT_EQ((++*m1).toString(), "2");
  EXPECT_EQ(((*m1)++)->toString(), "2");
  EXPECT_EQ(m1->toString(), "3");

  EXPECT_EQ((++Integer(1)).toString(), "2");
  EXPECT_EQ((Integer(1)++).toString(), "1");
}

TEST(IIntegerTests, decTest) {
  std::unique_ptr<IInteger> m1 = std::make_unique<Integer>(1);
  EXPECT_EQ((--*m1).toString(), "0");
  EXPECT_EQ(((*m1)--)->toString(), "0");
  EXPECT_EQ(m1->toString(), "-1");

  EXPECT_EQ((--Integer(1)).toString(), "0");
  EXPECT_EQ((Integer(1)--).toString(), "1");
}
