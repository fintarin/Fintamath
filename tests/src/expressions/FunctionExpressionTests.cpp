#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"

using namespace fintamath;

namespace {

class TestBinaryOperator : public IOperatorCRTP<INumber, TestBinaryOperator, INumber, INumber> {
public:
  TestBinaryOperator() : IOperatorCRTP(IOperator::Priority::Exponentiation) {
  }

  std::string toString() const override {
    return "$";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectBoundTypes::get().at(IOperator::getTypeStatic()) - 1;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestUnaryPrefixOperator : public IOperatorCRTP<INumber, TestUnaryPrefixOperator, INumber> {
public:
  TestUnaryPrefixOperator() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "$";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectBoundTypes::get().at(IOperator::getTypeStatic()) - 2;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestUnaryPostfixOperator : public IOperatorCRTP<INumber, TestUnaryPostfixOperator, INumber> {
public:
  TestUnaryPostfixOperator() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "$";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectBoundTypes::get().at(IOperator::getTypeStatic()) - 3;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestUnaryFunction : public IFunctionCRTP<INumber, TestUnaryFunction, INumber> {
public:
  TestUnaryFunction() : IFunctionCRTP() {
  }

  std::string toString() const override {
    return "testfunction";
  }

  static MathObjectType getTypeStatic() {
    return size_t(IOperator::getTypeStatic()) - 1;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestBinaryFunction : public IFunctionCRTP<INumber, TestBinaryFunction, INumber, INumber> {
public:
  TestBinaryFunction() : IFunctionCRTP() {
  }

  std::string toString() const override {
    return "testfunction";
  }

  static MathObjectType getTypeStatic() {
    return size_t(IOperator::getTypeStatic()) - 2;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class FunctionExpressionConfig {
public:
  FunctionExpressionConfig() {
    IOperator::registerType<TestBinaryOperator>();
    IOperator::registerType<TestUnaryPrefixOperator>();
    IOperator::registerType<TestUnaryPostfixOperator>();

    IFunction::registerType<TestUnaryFunction>();
    IFunction::registerType<TestBinaryFunction>();
  }
};

const FunctionExpressionConfig testOperatorConfig;

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
