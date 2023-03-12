#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator : public IOperatorCRTP<IMathObject, TestOperator, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  void throwExceptionPrefix() const {
    throw InvalidInputUnaryOpearatorException("!", "-10", InvalidInputUnaryOpearatorException::Type::Prefix);
  }

  void throwExceptionPostfix() const {
    throw InvalidInputUnaryOpearatorException("!", "-10", InvalidInputUnaryOpearatorException::Type::Postfix);
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override {
    return {};
  }
};

}

TEST(InvalidInputUnaryOpearatorExceptionTests, whatTests) {
  try {
    TestOperator().throwExceptionPrefix();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: !(-10)");
  }

  try {
    TestOperator().throwExceptionPostfix();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: (-10)!");
  }
}
