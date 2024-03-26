#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"

using namespace fintamath;
using namespace detail;

namespace {

class TestUnaryFunction final : public IFunctionCRTP<INumber, TestUnaryFunction, INumber> {
  FINTAMATH_CLASS_BODY(TestUnaryFunction)

public:
  std::string toString() const override {
    return "testfunction";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestBinaryFunction final : public IFunctionCRTP<INumber, TestBinaryFunction, INumber, INumber> {
  FINTAMATH_CLASS_BODY(TestBinaryFunction)

public:
  std::string toString() const override {
    return "testfunction";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestBinaryOperator final : public IOperatorCRTP<INumber, TestBinaryOperator, INumber, INumber> {
  FINTAMATH_CLASS_BODY(TestBinaryOperator)

public:
  std::string toString() const override {
    return "$";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::Exponentiation;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestUnaryPrefixOperator final : public IOperatorCRTP<INumber, TestUnaryPrefixOperator, INumber> {
  FINTAMATH_CLASS_BODY(TestUnaryPrefixOperator)

public:
  std::string toString() const override {
    return "$";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PrefixUnary;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestUnaryPostfixOperator final : public IOperatorCRTP<INumber, TestUnaryPostfixOperator, INumber> {
  FINTAMATH_CLASS_BODY(TestUnaryPostfixOperator)

public:
  std::string toString() const override {
    return "$";
  }

  static constexpr Priority getPriorityStatic() {
    return Priority::PostfixUnary;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

[[maybe_unused]] const auto config = [] {
  IFunction::registerType<TestUnaryFunction>();
  IFunction::registerType<TestBinaryFunction>();

  IOperator::registerType<TestBinaryOperator>();
  IOperator::registerType<TestUnaryPrefixOperator>();
  IOperator::registerType<TestUnaryPostfixOperator>();

  return 0;
}();

}

TEST(FunctionExpressionTests, stringConstructorTest) {
  EXPECT_EQ(Expression("a$a").toString(), "a$a");
  EXPECT_EQ(Expression("(a+1)$(b+1)").toString(), "(a + 1)$(b + 1)");

  EXPECT_EQ(Expression("$a").toString(), "$a");
  EXPECT_EQ(Expression("$(a+1)").toString(), "$(a + 1)");
  EXPECT_EQ(Expression("($a)").toString(), "$a");
  EXPECT_EQ(Expression("($(a+1))").toString(), "$(a + 1)");

  EXPECT_EQ(Expression("a$").toString(), "a$");
  EXPECT_EQ(Expression("(a+1)$").toString(), "(a + 1)$");
  EXPECT_EQ(Expression("(a$)").toString(), "a$");
  EXPECT_EQ(Expression("((a+1)$)").toString(), "(a + 1)$");

  EXPECT_EQ(Expression("testfunction(a)").toString(), "testfunction(a)");
  EXPECT_EQ(Expression("testfunction(a+1)").toString(), "testfunction(a + 1)");

  EXPECT_EQ(Expression("testfunction(a,b)").toString(), "testfunction(a, b)");
  EXPECT_EQ(Expression("testfunction(a+1,b+1)").toString(), "testfunction(a + 1, b + 1)");
}

TEST(FunctionExpressionTests, getClassTest) {
  EXPECT_EQ(makeExpr(TestBinaryOperator(), Integer(0), Integer(0))->getClass(), MathObjectClass("FunctionExpression"));
}
