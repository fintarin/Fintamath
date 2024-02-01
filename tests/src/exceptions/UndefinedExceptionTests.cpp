#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedException.hpp"

#include "fintamath/functions/IFunction.hpp"

using namespace fintamath;

namespace {

class TestFunction final : public IFunctionCRTP<IMathObject, TestFunction, IMathObject> {
public:
  static void throwException1() {
    throw UndefinedException();
  }

  static void throwException2() {
    throw UndefinedException("undefined");
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

}

TEST(UndefinedExceptionTests, whatTest) {
  try {
    TestFunction::throwException1();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined");
  }

  try {
    TestFunction::throwException2();
    EXPECT_TRUE(false);
  }
  catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: undefined");
  }
}
