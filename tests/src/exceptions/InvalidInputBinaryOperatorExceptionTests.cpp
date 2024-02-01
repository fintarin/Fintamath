#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator final : public IOperatorCRTP<IMathObject, TestOperator, IMathObject, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(Priority::Addition) {
  }

  static void throwException() {
    throw InvalidInputBinaryOperatorException("^", "a", "0");
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

}

TEST(InvalidInputBinaryOpearatorExceptionTests, whatTest) {
  try {
    TestOperator::throwException();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: (a)^(0)");
  }
}
