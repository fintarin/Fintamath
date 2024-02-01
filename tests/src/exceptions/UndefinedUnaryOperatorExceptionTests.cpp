#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator final : public IOperatorCRTP<IMathObject, TestOperator, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(Priority::PrefixUnary) {
  }

  static void throwExceptionPrefix() {
    throw UndefinedUnaryOperatorException("!", "-10", UndefinedUnaryOperatorException::Type::Prefix);
  }

  static void throwExceptionPostfix() {
    throw UndefinedUnaryOperatorException("!", "-10", UndefinedUnaryOperatorException::Type::Postfix);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

}

TEST(UndefinedUnaryOpearatorExceptionTests, whatTest) {
  try {
    TestOperator::throwExceptionPrefix();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: !(-10)");
  }

  try {
    TestOperator::throwExceptionPostfix();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: (-10)!");
  }
}
