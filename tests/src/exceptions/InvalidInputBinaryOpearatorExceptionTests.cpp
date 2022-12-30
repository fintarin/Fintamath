#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputBinaryOpearatorException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator : public IOperatorCRTP<TestOperator, IMathObject, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(IOperator::Priority::Addition) {
  }

  void throwException() const {
    throw InvalidInputBinaryOpearatorException("^", "a", "0");
  }

protected:
  virtual Expression call(const ArgumentsVector &argsVect) const override {
    return {};
  }
};

}

TEST(InvalidInputBinaryOpearatorExceptionTests, whatTests) {
  try {
    TestOperator().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: (a)^(0)");
  }
}
