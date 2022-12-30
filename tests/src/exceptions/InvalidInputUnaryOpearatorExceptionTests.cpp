#include <gtest/gtest.h>

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {
  class TestOperator : public IOperatorCRTP<TestOperator, IMathObject> {
  public:
    TestOperator() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
    }

    void throwException() const {
      throw InvalidInputUnaryOpearatorException("!", "-10", InvalidInputUnaryOpearatorException::Type::Postfix);
    }

  protected:
    virtual Expression call(const ArgumentsVector &argsVect) const override {
      return {};
    }
  };
}

TEST(InvalidInputUnaryOpearatorException, whatTests) {
  try {
    TestOperator().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Invalid input: (-10)!");
  }
}
