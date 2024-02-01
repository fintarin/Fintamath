#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator final : public IOperatorCRTP<IMathObject, TestOperator, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(Priority::PrefixUnary) {
  }

  static void throwExceptionPrefix() {
    throw InvalidInputUnaryOperatorException("!", "-10", InvalidInputUnaryOperatorException::Type::Prefix);
  }

  static void throwExceptionPostfix() {
    throw InvalidInputUnaryOperatorException("!", "-10", InvalidInputUnaryOperatorException::Type::Postfix);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

}

TEST(InvalidInputUnaryOpearatorExceptionTests, whatTest) {
  try {
    TestOperator::throwExceptionPrefix();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: !(-10)");
  }

  try {
    TestOperator::throwExceptionPostfix();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: (-10)!");
  }
}
