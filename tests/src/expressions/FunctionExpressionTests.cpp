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

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IOperator) + 1'234'567;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override {
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

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IOperator) + 1'234'568;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override {
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

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IOperator) + 1'234'569;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override {
    return std::make_unique<Integer>(1);
  }
};

class TestOperatorConfig {
public:
  TestOperatorConfig() {
    IOperator::registerType<TestBinaryOperator>();
    IOperator::registerType<TestUnaryPrefixOperator>();
    IOperator::registerType<TestUnaryPostfixOperator>();
  }
};

const TestOperatorConfig testOperatorConfig;

}

TEST(FunctionExpressionTests, toStringTest) {
  EXPECT_EQ(Expression("a$a").toString(), "a$a");
  EXPECT_EQ(Expression("(a+1)$(b+1)").toString(), "(a + 1)$(b + 1)");

  EXPECT_EQ(Expression("$a").toString(), "$a");
  EXPECT_EQ(Expression("$(a+1)").toString(), "$(a + 1)");

  EXPECT_EQ(Expression("a$").toString(), "a$");
  EXPECT_EQ(Expression("(a+1)$").toString(), "(a + 1)$");
}

TEST(FunctionExpressionTests, getTypeIdTest) {
  EXPECT_EQ(makeExpr(TestBinaryOperator(), Integer(0).clone(), Integer(0).clone())->getTypeId(),
            MathObjectTypeId(MathObjectType::FunctionExpression));
}
