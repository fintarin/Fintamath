#include <gtest/gtest.h>

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"

#include "fintamath/functions/IOperator.hpp"

using namespace fintamath;

namespace {
  class TestOperator : public IOperatorCRTP<TestOperator, IMathObject> {
  public:
    TestOperator() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
    }

    std::string toString() const override {
      return {};
    }

    std::string getClassName() const override {
      return {};
    }

    void throwException() const {
      throw UndefinedUnaryOpearatorException("!", "-10", UndefinedUnaryOpearatorException::Type::Postfix);
    }

  protected:
    virtual Expression call(const ArgumentsVector &argsVect) const override {
      return {};
    }
  };
}

TEST(UndefinedUnaryOpearatorException, whatTests) {
  try {
    TestOperator().throwException();
    EXPECT_TRUE(false);
  } catch (const Exception &e) {
    EXPECT_EQ(std::string(e.what()), "Undefined: (-10)!");
  }
}
