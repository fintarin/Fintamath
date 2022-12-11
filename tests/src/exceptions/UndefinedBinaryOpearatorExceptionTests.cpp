#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {
  class TestOperator : public IOperatorCRTP<TestOperator, IMathObject, IMathObject> {
  public:
    TestOperator() : IOperatorCRTP(IOperator::Priority::Addition) {
    }

    std::string toString() const override {
      return {};
    }

    std::string getClassName() const override {
      return {};
    }

    void throwException() const {
      // TODO
      // throw UndefinedBinaryOpearatorException();
    }

  protected:
    virtual Expression call(const ArgumentsVector &argsVect) const override {
      return {};
    }
  };
}

TEST(UndefinedBinaryOpearatorExceptionTests, whatTests) {
  try {
    TestOperator().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), ""); // TODO
  }
}
