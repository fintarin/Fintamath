#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/calculus/Derivative.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Derivative f;

namespace {

class TestComparable : public IComparableCRTP<TestComparable> {
  FINTAMATH_CLASS_BODY(TestComparable, IComparable)

public:
  std::string toString() const override {
    return "testderivative";
  }

protected:
  std::strong_ordering compare(const TestComparable & /* rhs */) const override {
    return std::strong_ordering::less;
  }

  TestComparable &add(const TestComparable & /* rhs */) override {
    return *this;
  }

  TestComparable &substract(const TestComparable & /* rhs */) override {
    return *this;
  }

  TestComparable &multiply(const TestComparable & /* rhs */) override {
    return *this;
  }

  TestComparable &divide(const TestComparable & /* rhs */) override {
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

TEST(DerivativeTests, toStringTest) {
  EXPECT_EQ(f.toString(), "derivative");
}

TEST(DerivativeTests, getArgumentClassesTest) {
  EXPECT_THAT(f.getArgumentClasses(), testing::ElementsAre(IComparable::getClassStatic(), Variable::getClassStatic()));
}

TEST(DerivativeTests, getReturnClassTest) {
  EXPECT_EQ(f.getReturnClass(), IComparable::getClassStatic());
}

TEST(DerivativeTests, isVariadicTest) {
  EXPECT_FALSE(f.isVariadic());
}

TEST(DerivativeTests, isEvaluatableTest) {
  EXPECT_FALSE(f.isEvaluatable());
}

TEST(DerivativeTests, callTest) {
  EXPECT_EQ(f(Integer(5), Variable("a"))->toString(), "0");
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "1");
  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "0");
  EXPECT_EQ(f(Expression("a+a"), Variable("a"))->toString(), "2");

  EXPECT_EQ(f(TestComparable(), Variable("a"))->toString(), "derivative(testderivative, a)");

  EXPECT_THROW(f(Integer(5), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Expression("a+a")), InvalidInputException);

  EXPECT_THROW(f(), InvalidInputException);
  EXPECT_THROW(f(Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputException);
}

TEST(DerivativeTests, exprTest) {
  EXPECT_EQ(derivativeExpr(Variable("a"), Variable("a"))->toString(), "derivative(a, a)");
}

TEST(DerivativeTests, getClassTest) {
  EXPECT_EQ(f.getClass()->getName(), "Derivative");
  EXPECT_EQ(f.getClass()->getParent(), IFunction::getClassStatic());
}
