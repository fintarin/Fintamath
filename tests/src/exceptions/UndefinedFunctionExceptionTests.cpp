#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedFunctionException.hpp"

#include "fintamath/functions/IFunction.hpp"

using namespace fintamath;

namespace {
  class TestFunction : public IFunctionCRTP<TestFunction, IMathObject> {
  public:
    std::string toString() const override {
      return {};
    }

    std::string getClassName() const override {
      return {};
    }

    void throwException() const {
      throw UndefinedFunctionException("sqrt", {"-10"});
    }

  protected:
    virtual Expression call(const ArgumentsVector &argsVect) const override {
      return {};
    }
  };
}

TEST(UndefinedFunctionExceptionTests, whatTests) {
  try {
    TestFunction().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: sqrt(-10)");
  }
}
