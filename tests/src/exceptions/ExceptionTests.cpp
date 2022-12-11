#include <gtest/gtest.h>

#include "fintamath/exceptions/Exception.hpp"

#include "fintamath/core/IMathObject.hpp"

using namespace fintamath;

namespace {
  class TestMathObject : public IMathObjectCRTP<TestMathObject> {
  public:
    std::string toString() const override {
      return {};
    }

    std::string getClassName() const override {
      return {};
    }

    void throwException() const {
      throw Exception();
    }

  protected:
    bool equals(const TestMathObject & /* rhs */) const override {
      return true;
    }
  };
}

TEST(ExceptionTests, whatTests) {
  try {
    TestMathObject().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Something went wrong...");
  }
}
