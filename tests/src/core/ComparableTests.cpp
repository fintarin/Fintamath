#include <gtest/gtest.h>

#include "fintamath/core/IComparable.hpp"

#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace fintamath::tests {
  class TestComparable : public ComparableCRTP<TestComparable> {
  public:
    std::string toString() const override {
      return {};
    }

  protected:
    bool equals(const TestComparable & /* rhs */) const override {
      return true;
    }

    bool less(const TestComparable & /* rhs */) const override {
      return true;
    }

    bool more(const TestComparable & /* rhs */) const override {
      return true;
    }
  };
}

TEST(ComparableTests, lessTest) {
  ComparablePtr m1 = std::make_unique<Integer>(1);
  ComparablePtr m2 = std::make_unique<Rational>(2);
  ComparablePtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_FALSE(*m1 < *m1);
  EXPECT_FALSE(*m2 < *m2);
  EXPECT_TRUE(*m1 < *m2);
  EXPECT_FALSE(*m2 < *m1);

  EXPECT_FALSE(*m1 < *m3);
  EXPECT_FALSE(*m2 < *m3);
  EXPECT_TRUE(*m3 < *m1);
  EXPECT_TRUE(*m3 < *m2);

  EXPECT_THROW((void)(*m1 < tests::TestComparable()), FunctionCallException);
  EXPECT_THROW(void(tests::TestComparable() < *m1), FunctionCallException);

  EXPECT_TRUE(Integer() < 1);
  EXPECT_TRUE(-1 < Integer());

  EXPECT_FALSE(Integer() < 0);
  EXPECT_FALSE(1 < Integer());
}

TEST(ComparableTests, moreTest) {
  ComparablePtr m1 = std::make_unique<Integer>(1);
  ComparablePtr m2 = std::make_unique<Rational>(2);
  ComparablePtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_FALSE(*m1 > *m1);
  EXPECT_FALSE(*m2 > *m2);
  EXPECT_FALSE(*m1 > *m2);
  EXPECT_TRUE(*m2 > *m1);

  EXPECT_TRUE(*m1 > *m3);
  EXPECT_TRUE(*m2 > *m3);
  EXPECT_FALSE(*m3 > *m1);
  EXPECT_FALSE(*m3 > *m2);

  EXPECT_THROW(void(*m1 > tests::TestComparable()), FunctionCallException);
  EXPECT_THROW(void(tests::TestComparable() > *m1), FunctionCallException);

  EXPECT_FALSE(Integer() > 1);
  EXPECT_FALSE(-1 > Integer());

  EXPECT_FALSE(Integer() > 0);
  EXPECT_TRUE(1 > Integer());
}

TEST(ComparableTests, lessEqualsTest) {
  ComparablePtr m1 = std::make_unique<Integer>(1);
  ComparablePtr m2 = std::make_unique<Rational>(2);
  ComparablePtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_TRUE(*m1 <= *m1);
  EXPECT_TRUE(*m2 <= *m2);
  EXPECT_TRUE(*m1 <= *m2);
  EXPECT_FALSE(*m2 <= *m1);

  EXPECT_FALSE(*m1 <= *m3);
  EXPECT_FALSE(*m2 <= *m3);
  EXPECT_TRUE(*m3 <= *m1);
  EXPECT_TRUE(*m3 <= *m2);

  EXPECT_THROW(void(*m1 <= tests::TestComparable()), FunctionCallException);
  EXPECT_THROW(void(tests::TestComparable() <= *m1), FunctionCallException);

  EXPECT_TRUE(Integer() <= 1);
  EXPECT_TRUE(-1 <= Integer());

  EXPECT_TRUE(Integer() <= 0);
  EXPECT_FALSE(1 <= Integer());
}

TEST(ComparableTests, moreEqualsTest) {
  ComparablePtr m1 = std::make_unique<Integer>(1);
  ComparablePtr m2 = std::make_unique<Rational>(2);
  ComparablePtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_TRUE(*m1 >= *m1);
  EXPECT_TRUE(*m2 >= *m2);
  EXPECT_FALSE(*m1 >= *m2);
  EXPECT_TRUE(*m2 >= *m1);

  EXPECT_TRUE(*m1 >= *m3);
  EXPECT_TRUE(*m2 >= *m3);
  EXPECT_FALSE(*m3 >= *m1);
  EXPECT_FALSE(*m3 >= *m2);

  EXPECT_THROW(void(*m1 >= tests::TestComparable()), FunctionCallException);
  EXPECT_THROW(void(tests::TestComparable() >= *m1), FunctionCallException);

  EXPECT_FALSE(Integer() >= 1);
  EXPECT_FALSE(-1 >= Integer());

  EXPECT_TRUE(Integer() >= 0);
  EXPECT_TRUE(1 >= Integer());
}
