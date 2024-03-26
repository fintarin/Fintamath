#include <gtest/gtest.h>

#include "fintamath/functions/IOperator.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/powers/Pow.hpp"

using namespace fintamath;

namespace {

class TestOperator final : public IOperatorCRTP<INumber, TestOperator, INumber> {
  FINTAMATH_CLASS_BODY(TestOperator)

public:
  static constexpr Priority getPriorityStatic() {
    return Priority::Addition;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

[[maybe_unused]] const auto config = [] {
  IOperator::registerType<TestOperator>();
  return 0;
}();

}

TEST(IOperatorTests, parseTest) {
  EXPECT_TRUE(is<TestOperator>(*IOperator::parseFirst("TestOperator")));
}

TEST(IOperatorTests, getPriorityTest) {
  EXPECT_EQ(Add().getPriority(), IOperator::Priority::Addition);
  EXPECT_EQ(Neg().getPriority(), IOperator::Priority::PrefixUnary);
  EXPECT_EQ(Factorial().getPriority(), IOperator::Priority::PostfixUnary);
  EXPECT_EQ(Or().getPriority(), IOperator::Priority::Disjunction);
}

TEST(IOperatorTests, isAssociativeTest) {
  EXPECT_TRUE(Add().isAssociative());
  EXPECT_FALSE(Neg().isAssociative());
  EXPECT_TRUE(Or().isAssociative());
  EXPECT_FALSE(Pow().isAssociative());
}

TEST(IOperatorTests, getClassTest) {
  EXPECT_EQ(IOperator::getClassStatic(), MathObjectClass("IOperator"));
  EXPECT_EQ(IOperator::getClassStatic().getParent(), IFunction::getClassStatic());
}
