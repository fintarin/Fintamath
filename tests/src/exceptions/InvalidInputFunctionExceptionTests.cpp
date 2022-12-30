#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputFunctionException.hpp"

#include "fintamath/functions/IFunction.hpp"

using namespace fintamath;

namespace {

class TestFunction : public IFunctionCRTP<TestFunction, IMathObject> {
public:
  void throwException() const {
    throw InvalidInputFunctionException("sqrt", {"-10", "a", "b"});
  }

protected:
  virtual Expression call(const ArgumentsVector &argsVect) const override {
    return {};
  }
};

}

TEST(InvalidInputFunctionExceptionTests, whatTests) {
  try {
    TestFunction().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: sqrt(-10,a,b)");
  }
}
