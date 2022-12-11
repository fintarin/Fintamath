#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"

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
      // TODO
      // throw InvalidInputException();
    }

  protected:
    bool equals(const TestMathObject & /* rhs */) const override {
      return true;
    }
  };
}

TEST(InvalidInputExceptionTests, whatTests) {
  try {
    TestMathObject().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), ""); // TODO
  }
}
