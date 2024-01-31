#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

#include "fintamath/functions/IFunction.hpp"

using namespace fintamath;

namespace {

class TestFunction : public IFunctionCRTP<IMathObject, TestFunction, IMathObject> {
public:
  void throwException1() const {
    throw UndefinedFunctionException("sqrt", {"-10", "a", "b"});
  }

  void throwException2() const {
    throw UndefinedFunctionException("sqrt", {});
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

}

TEST(UndefinedFunctionExceptionTests, whatTest) {
  try {
    TestFunction().throwException1();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: sqrt(-10,a,b)");
  }

  try {
    TestFunction().throwException2();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: sqrt()");
  }
}
