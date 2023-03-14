#include <gtest/gtest.h>

#include "fintamath/core/IComparable.hpp"

#include "fintamath/exceptions/InvalidInputBinaryOpearatorException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestComparable : public IComparableCRTP<TestComparable> {
protected:
  bool less(const TestComparable & /* rhs */) const override {
    return true;
  }

  bool more(const TestComparable & /* rhs */) const override {
    return true;
  }

  TestComparable &add(const TestComparable &rhs) override {
    return *this;
  }

  virtual TestComparable &substract(const TestComparable &rhs) override {
    return *this;
  }

  virtual TestComparable &multiply(const TestComparable &rhs) override {
    return *this;
  }

  virtual TestComparable &divide(const TestComparable &rhs) override {
    return *this;
  }

  virtual TestComparable &negate() override {
    return *this;
  }
};

}

TEST(ComparableTests, lessTest) {
  unique_ptr<IComparable> m1 = make_unique<Integer>(1);
  unique_ptr<IComparable> m2 = make_unique<Rational>(2);
  unique_ptr<IComparable> m3 = make_unique<Rational>(1, 2);

  EXPECT_FALSE(*m1 < *m1);
  EXPECT_FALSE(*m2 < *m2);
  EXPECT_TRUE(*m1 < *m2);
  EXPECT_FALSE(*m2 < *m1);

  EXPECT_FALSE(*m1 < *m3);
  EXPECT_FALSE(*m2 < *m3);
  EXPECT_TRUE(*m3 < *m1);
  EXPECT_TRUE(*m3 < *m2);

  EXPECT_THROW((void)(*m1 < TestComparable()), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(void(TestComparable() < *m1), InvalidInputBinaryOpearatorException);

  EXPECT_TRUE(Integer() < 1);
  EXPECT_TRUE(-1 < Integer());

  EXPECT_FALSE(Integer() < 0);
  EXPECT_FALSE(1 < Integer());
}

TEST(ComparableTests, moreTest) {
  unique_ptr<IComparable> m1 = make_unique<Integer>(1);
  unique_ptr<IComparable> m2 = make_unique<Rational>(2);
  unique_ptr<IComparable> m3 = make_unique<Rational>(1, 2);

  EXPECT_FALSE(*m1 > *m1);
  EXPECT_FALSE(*m2 > *m2);
  EXPECT_FALSE(*m1 > *m2);
  EXPECT_TRUE(*m2 > *m1);

  EXPECT_TRUE(*m1 > *m3);
  EXPECT_TRUE(*m2 > *m3);
  EXPECT_FALSE(*m3 > *m1);
  EXPECT_FALSE(*m3 > *m2);

  EXPECT_THROW(void(*m1 > TestComparable()), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(void(TestComparable() > *m1), InvalidInputBinaryOpearatorException);

  EXPECT_FALSE(Integer() > 1);
  EXPECT_FALSE(-1 > Integer());

  EXPECT_FALSE(Integer() > 0);
  EXPECT_TRUE(1 > Integer());
}

TEST(ComparableTests, lessEqualsTest) {
  unique_ptr<IComparable> m1 = make_unique<Integer>(1);
  unique_ptr<IComparable> m2 = make_unique<Rational>(2);
  unique_ptr<IComparable> m3 = make_unique<Rational>(1, 2);

  EXPECT_TRUE(*m1 <= *m1);
  EXPECT_TRUE(*m2 <= *m2);
  EXPECT_TRUE(*m1 <= *m2);
  EXPECT_FALSE(*m2 <= *m1);

  EXPECT_FALSE(*m1 <= *m3);
  EXPECT_FALSE(*m2 <= *m3);
  EXPECT_TRUE(*m3 <= *m1);
  EXPECT_TRUE(*m3 <= *m2);

  EXPECT_THROW(void(*m1 <= TestComparable()), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(void(TestComparable() <= *m1), InvalidInputBinaryOpearatorException);

  EXPECT_TRUE(Integer() <= 1);
  EXPECT_TRUE(-1 <= Integer());

  EXPECT_TRUE(Integer() <= 0);
  EXPECT_FALSE(1 <= Integer());
}

TEST(ComparableTests, moreEqualsTest) {
  unique_ptr<IComparable> m1 = make_unique<Integer>(1);
  unique_ptr<IComparable> m2 = make_unique<Rational>(2);
  unique_ptr<IComparable> m3 = make_unique<Rational>(1, 2);

  EXPECT_TRUE(*m1 >= *m1);
  EXPECT_TRUE(*m2 >= *m2);
  EXPECT_FALSE(*m1 >= *m2);
  EXPECT_TRUE(*m2 >= *m1);

  EXPECT_TRUE(*m1 >= *m3);
  EXPECT_TRUE(*m2 >= *m3);
  EXPECT_FALSE(*m3 >= *m1);
  EXPECT_FALSE(*m3 >= *m2);

  EXPECT_THROW(void(*m1 >= TestComparable()), InvalidInputBinaryOpearatorException);
  EXPECT_THROW(void(TestComparable() >= *m1), InvalidInputBinaryOpearatorException);

  EXPECT_FALSE(Integer() >= 1);
  EXPECT_FALSE(-1 >= Integer());

  EXPECT_TRUE(Integer() >= 0);
  EXPECT_TRUE(1 >= Integer());
}
