#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedUnaryOperatorException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator : public IOperatorCRTP<IMathObject, TestOperator, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  void throwExceptionPrefix() const {
    throw UndefinedUnaryOperatorException("!", "-10", UndefinedUnaryOperatorException::Type::Prefix);
  }

  void throwExceptionPostfix() const {
    throw UndefinedUnaryOperatorException("!", "-10", UndefinedUnaryOperatorException::Type::Postfix);
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override {
    return {};
  }
};

}

TEST(UndefinedUnaryOpearatorExceptionTests, whatTests) {
  try {
    TestOperator().throwExceptionPrefix();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: !(-10)");
  }

  try {
    TestOperator().throwExceptionPostfix();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: (-10)!");
  }
}
