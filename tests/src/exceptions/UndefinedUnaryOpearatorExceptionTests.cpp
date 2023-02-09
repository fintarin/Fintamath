#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator : public IOperatorCRTP<IMathObject, TestOperator, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  void throwExceptionPrefix() const {
    throw UndefinedUnaryOpearatorException("!", "-10", UndefinedUnaryOpearatorException::Type::Prefix);
  }

  void throwExceptionPostfix() const {
    throw UndefinedUnaryOpearatorException("!", "-10", UndefinedUnaryOpearatorException::Type::Postfix);
  }

protected:
  virtual MathObjectPtr call(const ArgumentsVector &argsVect) const override {
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
