#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedFunctionException.hpp"

#include "fintamath/functions/IFunction.hpp"

using namespace fintamath;

namespace {

class TestFunction : public IFunctionCRTP<IMathObject, TestFunction, IMathObject> {
public:
  void throwException() const {
    throw UndefinedFunctionException("sqrt", {"-10", "a", "b"});
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override {
    return {};
  }
};

}

TEST(UndefinedFunctionExceptionTests, whatTests) {
  try {
    TestFunction().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: sqrt(-10,a,b)");
  }
}
