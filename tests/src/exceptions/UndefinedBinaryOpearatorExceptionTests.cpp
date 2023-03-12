#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {

class TestOperator : public IOperatorCRTP<IMathObject, TestOperator, IMathObject, IMathObject> {
public:
  TestOperator() : IOperatorCRTP(IOperator::Priority::Addition) {
  }

  void throwException() const {
    throw UndefinedBinaryOpearatorException("^", "0", "0");
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override {
    return {};
  }
};

}

TEST(UndefinedBinaryOpearatorExceptionTests, whatTests) {
  try {
    TestOperator().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: (0)^(0)");
  }
}
