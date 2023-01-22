#include <gtest/gtest.h>

#include "fintamath/core/IMathObject.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(MathObjectTests, isTest) {
  MathObjectPtr m1 = std::make_unique<Integer>();

  EXPECT_TRUE(m1->instanceof<Integer>());

  EXPECT_FALSE(m1->instanceof<Rational>());
  EXPECT_FALSE(m1->instanceof<Variable>());
}

TEST(MathObjectTests, instanceofTest) {
  MathObjectPtr m1 = std::make_unique<Integer>();

  EXPECT_TRUE(m1->instanceof<Integer>());
  EXPECT_TRUE(m1->instanceof<INumber>());
  EXPECT_TRUE(m1->instanceof<IArithmetic>());
  EXPECT_TRUE(m1->instanceof<IMathObject>());

  EXPECT_FALSE(m1->instanceof<Rational>());
  EXPECT_FALSE(m1->instanceof<Variable>());
}

TEST(MathObjectTests, toTest) {
  MathObjectPtr m1 = std::make_unique<Integer>();

  EXPECT_TRUE(m1->to<Integer>().instanceof<Integer>());
  EXPECT_TRUE(m1->to<INumber>().instanceof<INumber>());
  EXPECT_TRUE(m1->to<IArithmetic>().instanceof<IArithmetic>());
  EXPECT_TRUE(m1->to<IMathObject>().instanceof<IMathObject>());

  EXPECT_TRUE(m1->to<IMathObject>().instanceof<Integer>());

  EXPECT_THROW(m1->to<Rational>(), std::bad_cast);
  EXPECT_THROW(m1->to<Variable>(), std::bad_cast);
}

TEST(MathObjectTests, cloneTest) {
  MathObjectPtr m1 = std::make_unique<Integer>();
  MathObjectPtr m2 = std::make_unique<Integer>(1);
  MathObjectPtr m3 = m1->clone();

  EXPECT_EQ(*m3, *m1);

  EXPECT_NE(*m3, *m2);

  EXPECT_NE(m3, m1);
}

TEST(MathObjectTests, equalsTest) {
  MathObjectPtr m1 = std::make_unique<Integer>(1);
  MathObjectPtr m2 = std::make_unique<Rational>(1);
  MathObjectPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_TRUE(*m1 == *m1);
  EXPECT_TRUE(*m2 == *m2);
  EXPECT_TRUE(*m1 == *m2);
  EXPECT_TRUE(*m2 == *m1);

  EXPECT_FALSE(*m1 == *m3);
  EXPECT_FALSE(*m2 == *m3);
  EXPECT_FALSE(*m3 == *m1);
  EXPECT_FALSE(*m3 == *m2);

  EXPECT_FALSE(*m1 == Variable("a"));
  EXPECT_FALSE(Variable("a") == *m1);

  EXPECT_TRUE(Integer() == 0);
  EXPECT_TRUE(0 == Integer());

  EXPECT_FALSE(Integer() == 1);
  EXPECT_FALSE(1 == Integer());
}

TEST(MathObjectTests, nequalsTest) {
  MathObjectPtr m1 = std::make_unique<Integer>(1);
  MathObjectPtr m2 = std::make_unique<Rational>(1);
  MathObjectPtr m3 = std::make_unique<Rational>(1, 2);

  EXPECT_FALSE(*m1 != *m1);
  EXPECT_FALSE(*m2 != *m2);
  EXPECT_FALSE(*m1 != *m2);
  EXPECT_FALSE(*m2 != *m1);

  EXPECT_TRUE(*m1 != *m3);
  EXPECT_TRUE(*m2 != *m3);
  EXPECT_TRUE(*m3 != *m1);
  EXPECT_TRUE(*m3 != *m2);

  EXPECT_TRUE(*m1 != Variable("a"));
  EXPECT_TRUE(Variable("a") != *m1);

  EXPECT_FALSE(Integer() != 0);
  EXPECT_FALSE(0 != Integer());

  EXPECT_TRUE(Integer() != 1);
  EXPECT_TRUE(1 != Integer());
}

TEST(MathObjectTests, outputTest) {
  MathObjectPtr m1 = std::make_unique<Integer>(123);
  std::stringstream out;
  out << *m1;
  EXPECT_EQ(out.str(), "123");
}
