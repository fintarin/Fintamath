#include <gtest/gtest.h>

#include "fintamath/exceptions/FunctionCallException.hpp"

#include "fintamath/functions/IFunction.hpp"

using namespace fintamath;

namespace {
  class TestFunction : public IFunctionCRTP<TestFunction, IMathObject> {
  public:
    void throwException() const {
      throw FunctionCallException("func", {"a", "b", "c"});
    }

  protected:
    virtual Expression call(const ArgumentsVector &argsVect) const override {
      return {};
    }
  };
}

TEST(FunctionCallExceptionTests, whatTests) {
  try {
    TestFunction().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Unable to call func for arguments (a, b, c)");
  }
}
