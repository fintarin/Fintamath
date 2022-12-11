#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

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
      // TODO
      // throw UndefinedException("");
    }

  protected:
    virtual Expression call(const ArgumentsVector &argsVect) const override {
      return {};
    }
  };
}

TEST(UndefinedExceptionTests, whatTests) {
  try {
    TestFunction().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), ""); // TODO
  }
}
