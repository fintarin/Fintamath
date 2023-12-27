#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator : public IOperatorCRTP<IMathObject, TestOperator, IMathObject, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(IOperator::Priority::Addition) {
  }

  void throwException() const {
    throw UndefinedBinaryOperatorException("^", "0", "0");
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override {
    return {};
  }
};

}

TEST(UndefinedBinaryOpearatorExceptionTests, whatTest) {
  try {
    TestOperator().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: (0)^(0)");
  }
}
