#include <gtest/gtest.h>

#include "fintamath/functions/IOperator.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/AddOper.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/logic/OrOper.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/powers/PowOper.hpp"

using namespace fintamath;

namespace {

class TestOperator : public IOperatorCRTP<INumber, TestOperator, INumber> {
  FINTAMATH_CLASS_BODY(TestOperator, IOperator)

public:
  static constexpr Priority getPriorityStatic() noexcept {
    return Priority::Addition;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

FINTAMATH_CLASS_IMPLEMENTATION(TestOperator)

[[maybe_unused]] const auto config = [] {
  IOperator::registerType<TestOperator>();
  return 0;
}();

}

TEST(IOperatorTests, parseTest) {
  EXPECT_TRUE(is<TestOperator>(*IOperator::parseFirst("TestOperator")));
}

TEST(IOperatorTests, getPriorityTest) {
  EXPECT_EQ(AddOper().getPriority(), IOperator::Priority::Addition);
  EXPECT_EQ(Neg().getPriority(), IOperator::Priority::PrefixUnary);
  EXPECT_EQ(Factorial().getPriority(), IOperator::Priority::PostfixUnary);
  EXPECT_EQ(OrOper().getPriority(), IOperator::Priority::Disjunction);
}

TEST(IOperatorTests, isAssociativeTest) {
  EXPECT_TRUE(AddOper().isAssociative());
  EXPECT_FALSE(Neg().isAssociative());
  EXPECT_TRUE(OrOper().isAssociative());
  EXPECT_FALSE(PowOper().isAssociative());
}

TEST(IOperatorTests, getClassTest) {
  EXPECT_EQ(IOperator::getClassStatic()->getName(), "IOperator");
  EXPECT_EQ(IOperator::getClassStatic()->getParent(), IFunction::getClassStatic());
}
