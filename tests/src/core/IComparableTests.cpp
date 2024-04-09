#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/core/IComparable.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestComparable : public IComparableCRTP<TestComparable> {
  FINTAMATH_CLASS_BODY(TestComparable, IComparable)

protected:
  std::strong_ordering compare(const TestComparable & /* rhs */) const override {
    return std::strong_ordering::less;
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

FINTAMATH_CLASS_IMPLEMENTATION(TestComparable)

[[maybe_unused]] const auto config = [] {
  IComparable::registerType<TestComparable>();
  return 0;
}();

}

TEST(IComparableTests, parseTest) {
  EXPECT_TRUE(is<TestComparable>(*IComparable::parseFirst("TestComparable")));
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

  EXPECT_THAT(
      [&] { *m1 < TestComparable(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid arguments of the comparison operator (Integer "1" and TestComparable "TestComparable" are unconvertible to each other))")));
  EXPECT_THAT(
      [&] { TestComparable() < *m1; },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid arguments of the comparison operator (TestComparable "TestComparable" and Integer "1" are unconvertible to each other))")));

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

  EXPECT_THAT(
      [&] { *m1 < TestComparable(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid arguments of the comparison operator (Integer "1" and TestComparable "TestComparable" are unconvertible to each other))")));
  EXPECT_THAT(
      [&] { TestComparable() < *m1; },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid arguments of the comparison operator (TestComparable "TestComparable" and Integer "1" are unconvertible to each other))")));

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

  EXPECT_THAT(
      [&] { *m1 <= TestComparable(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid arguments of the comparison operator (Integer "1" and TestComparable "TestComparable" are unconvertible to each other))")));
  EXPECT_THAT(
      [&] { TestComparable() <= *m1; },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid arguments of the comparison operator (TestComparable "TestComparable" and Integer "1" are unconvertible to each other))")));

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

  EXPECT_THAT(
      [&] { *m1 >= TestComparable(); },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid arguments of the comparison operator (Integer "1" and TestComparable "TestComparable" are unconvertible to each other))")));
  EXPECT_THAT(
      [&] { TestComparable() >= *m1; },
      testing::ThrowsMessage<InvalidInputException>(
          testing::StrEq(R"(Invalid arguments of the comparison operator (TestComparable "TestComparable" and Integer "1" are unconvertible to each other))")));

  EXPECT_FALSE(Integer() >= 1);
  EXPECT_FALSE(-1 >= Integer());

  EXPECT_TRUE(Integer() >= 0);
  EXPECT_TRUE(1 >= Integer());
}

TEST(IComparableTests, getClassTest) {
  EXPECT_EQ(IComparable::getClassStatic()->getName(), "IComparable");
  EXPECT_EQ(IComparable::getClassStatic()->getParent(), IArithmetic::getClassStatic());
}
