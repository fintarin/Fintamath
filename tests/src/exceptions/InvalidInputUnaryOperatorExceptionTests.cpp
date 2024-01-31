#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator : public IOperatorCRTP<IMathObject, TestOperator, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  void throwExceptionPrefix() const {
    throw InvalidInputUnaryOperatorException("!", "-10", InvalidInputUnaryOperatorException::Type::Prefix);
  }

  void throwExceptionPostfix() const {
    throw InvalidInputUnaryOperatorException("!", "-10", InvalidInputUnaryOperatorException::Type::Postfix);
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

}

TEST(InvalidInputUnaryOpearatorExceptionTests, whatTest) {
  try {
    TestOperator().throwExceptionPrefix();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: !(-10)");
  }

  try {
    TestOperator().throwExceptionPostfix();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: (-10)!");
  }
}
