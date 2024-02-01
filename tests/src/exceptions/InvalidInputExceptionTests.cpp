#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"

#include "fintamath/core/IMathObject.hpp"

using namespace fintamath;

namespace {

class TestMathObject final : public IMathObjectCRTP<TestMathObject> {
public:
  static void throwException() {
    throw InvalidInputException("123");
  }
};

}

TEST(InvalidInputExceptionTests, whatTest) {
  try {
    TestMathObject::throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: 123");
  }
}