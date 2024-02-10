#include <gtest/gtest.h>

#include "fintamath/core/IComparable.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestComparable final : public IComparableCRTP<TestComparable> {
public:
  static constexpr MathObjectType getTypeStatic() {
    return static_cast<size_t>(MathObjectType::IComparable) + 998;
  }

protected:
  std::strong_ordering compare(const TestComparable & /* rhs */) const override {
    return 0 <=> 1;
  }

  TestComparable &add(const TestComparable &rhs) override {
    return *this;
  }

  TestComparable &substract(const TestComparable &rhs) override {
    return *this;
  }

  TestComparable &multiply(const TestComparable &rhs) override {
    return *this;
  }

  TestComparable &divide(const TestComparable &rhs) override {
    return *this;
  }

  TestComparable &negate() override {
    return *this;
  }
};

}

TEST(IComparableTests, lessTest) {
  std::unique_ptr<IComparable> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IComparable> m2 = std::make_unique<Rational>(2);
  std::unique_ptr<IComparable> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_FALSE(*m1 < *m1);
  EXPECT_FALSE(*m2 < *m2);
  EXPECT_TRUE(*m1 < *m2);
  EXPECT_FALSE(*m2 < *m1);

  EXPECT_FALSE(*m1 < *m3);
  EXPECT_FALSE(*m2 < *m3);
  EXPECT_TRUE(*m3 < *m1);
  EXPECT_TRUE(*m3 < *m2);

  EXPECT_THROW((void)(*m1 < TestComparable()), InvalidInputBinaryOperatorException);
  EXPECT_THROW(void(TestComparable() < *m1), InvalidInputBinaryOperatorException);

  EXPECT_TRUE(Integer() < 1);
  EXPECT_TRUE(-1 < Integer());

  EXPECT_FALSE(Integer() < 0);
  EXPECT_FALSE(1 < Integer());
}

TEST(IComparableTests, moreTest) {
  std::unique_ptr<IComparable> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IComparable> m2 = std::make_unique<Rational>(2);
  std::unique_ptr<IComparable> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_FALSE(*m1 > *m1);
  EXPECT_FALSE(*m2 > *m2);
  EXPECT_FALSE(*m1 > *m2);
  EXPECT_TRUE(*m2 > *m1);

  EXPECT_TRUE(*m1 > *m3);
  EXPECT_TRUE(*m2 > *m3);
  EXPECT_FALSE(*m3 > *m1);
  EXPECT_FALSE(*m3 > *m2);

  EXPECT_THROW(void(*m1 > TestComparable()), InvalidInputBinaryOperatorException);
  EXPECT_THROW(void(TestComparable() > *m1), InvalidInputBinaryOperatorException);

  EXPECT_FALSE(Integer() > 1);
  EXPECT_FALSE(-1 > Integer());

  EXPECT_FALSE(Integer() > 0);
  EXPECT_TRUE(1 > Integer());
}

TEST(IComparableTests, lessEqualsTest) {
  std::unique_ptr<IComparable> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IComparable> m2 = std::make_unique<Rational>(2);
  std::unique_ptr<IComparable> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_TRUE(*m1 <= *m1);
  EXPECT_TRUE(*m2 <= *m2);
  EXPECT_TRUE(*m1 <= *m2);
  EXPECT_FALSE(*m2 <= *m1);

  EXPECT_FALSE(*m1 <= *m3);
  EXPECT_FALSE(*m2 <= *m3);
  EXPECT_TRUE(*m3 <= *m1);
  EXPECT_TRUE(*m3 <= *m2);

  EXPECT_THROW(void(*m1 <= TestComparable()), InvalidInputBinaryOperatorException);
  EXPECT_THROW(void(TestComparable() <= *m1), InvalidInputBinaryOperatorException);

  EXPECT_TRUE(Integer() <= 1);
  EXPECT_TRUE(-1 <= Integer());

  EXPECT_TRUE(Integer() <= 0);
  EXPECT_FALSE(1 <= Integer());
}

TEST(IComparableTests, moreEqualsTest) {
  std::unique_ptr<IComparable> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IComparable> m2 = std::make_unique<Rational>(2);
  std::unique_ptr<IComparable> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_TRUE(*m1 >= *m1);
  EXPECT_TRUE(*m2 >= *m2);
  EXPECT_FALSE(*m1 >= *m2);
  EXPECT_TRUE(*m2 >= *m1);

  EXPECT_TRUE(*m1 >= *m3);
  EXPECT_TRUE(*m2 >= *m3);
  EXPECT_FALSE(*m3 >= *m1);
  EXPECT_FALSE(*m3 >= *m2);

  EXPECT_THROW(void(*m1 >= TestComparable()), InvalidInputBinaryOperatorException);
  EXPECT_THROW(void(TestComparable() >= *m1), InvalidInputBinaryOperatorException);

  EXPECT_FALSE(Integer() >= 1);
  EXPECT_FALSE(-1 >= Integer());

  EXPECT_TRUE(Integer() >= 0);
  EXPECT_TRUE(1 >= Integer());
}

TEST(IComparableTests, getTypeTest) {
  EXPECT_EQ(IComparable::getTypeStatic(), MathObjectType::IComparable);
}
