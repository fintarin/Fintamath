#include <gtest/gtest.h>

#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"

using namespace fintamath;

namespace {

class TestIExpression : public IExpressionCRTP<TestIExpression> {
public:
  std::shared_ptr<IFunction> getFunction() const override {
    return std::make_shared<Add>();
  }

  ArgumentsPtrVector getChildren() const override {
    return {};
  }

  void setChildren(const ArgumentsPtrVector &childVect) override {
  }

protected:
  ArgumentPtr simplify() const override {
    if (auto res = preSimplify()) {
      return res;
    }

    if (auto res = postSimplify()) {
      return res;
    }

    return clone();
  }
};

}

TEST(IExpressionTests, getFunctionTest) {
  // TODO: implement
}

TEST(IExpressionTests, getChildrenTest) {
  // TODO: implement
}

TEST(IExpressionTests, setChildrenTest) {
  // TODO: implement
}

TEST(IExpressionTests, getVariablesUnsortedTest) {
  // TODO: implement
}

TEST(IExpressionTests, getVariablesTest) {
  // TODO: implement
}

TEST(IExpressionTests, setValuesOfVariablesTest) {
  // TODO: implement
}

TEST(IExpressionTests, toMinimalObjectTest) {
  TestIExpression a;
  EXPECT_EQ(*a.toMinimalObject(), a);
  // TODO: implement more tests
}

TEST(IExpressionTests, equalsTest) {
  // TODO: implement
}
