#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"

using namespace fintamath;

namespace {

class TestBinaryOperator final : public IOperatorCRTP<INumber, TestBinaryOperator, INumber, INumber> {
public:
  TestBinaryOperator() : IOperatorCRTP(Priority::Exponentiation) {
  }

  std::string toString() const override {
    return "$";
  }

  static constexpr MathObjectType getTypeStatic() {
    return static_cast<size_t>(MathObjectType::IOperator) + 999;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestUnaryPrefixOperator final : public IOperatorCRTP<INumber, TestUnaryPrefixOperator, INumber> {
public:
  TestUnaryPrefixOperator() : IOperatorCRTP(Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "$";
  }

  static constexpr MathObjectType getTypeStatic() {
    return static_cast<size_t>(MathObjectType::IOperator) + 998;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestUnaryPostfixOperator final : public IOperatorCRTP<INumber, TestUnaryPostfixOperator, INumber> {
public:
  TestUnaryPostfixOperator() : IOperatorCRTP(Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "$";
  }

  static constexpr MathObjectType getTypeStatic() {
    return static_cast<size_t>(MathObjectType::IOperator) + 997;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestUnaryFunction final : public IFunctionCRTP<INumber, TestUnaryFunction, INumber> {
public:
  TestUnaryFunction() {
  }

  std::string toString() const override {
    return "testfunction";
  }

  static constexpr MathObjectType getTypeStatic() {
    return static_cast<size_t>(MathObjectType::IFunction) + 996;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestBinaryFunction final : public IFunctionCRTP<INumber, TestBinaryFunction, INumber, INumber> {
public:
  TestBinaryFunction() {
  }

  std::string toString() const override {
    return "testfunction";
  }

  static constexpr MathObjectType getTypeStatic() {
    return static_cast<size_t>(MathObjectType::IFunction) + 995;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class FunctionExpressionConfig final {
public:
  FunctionExpressionConfig() {
    IOperator::registerType<TestBinaryOperator>();
    IOperator::registerType<TestUnaryPrefixOperator>();
    IOperator::registerType<TestUnaryPostfixOperator>();

    IFunction::registerType<TestUnaryFunction>();
    IFunction::registerType<TestBinaryFunction>();
  }
};

[[maybe_unused]] const FunctionExpressionConfig testOperatorConfig;

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

TEST(FunctionExpressionTests, getTypeTest) {
  EXPECT_EQ(makeExpr(TestBinaryOperator(), Integer(0), Integer(0))->getType(), MathObjectType::FunctionExpression);
}
