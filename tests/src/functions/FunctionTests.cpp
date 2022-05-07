#include <gtest/gtest.h>

#include "fintamath/functions/Function.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace fintamath::tests {
  class TestAdd : public FunctionImpl<TestAdd> {
  public:
    std::string toString() const override {
      return "+";
    }

    MathObjectPtr operator()(const MathObject &lhs, const MathObject &rhs) const {
      if (!lhs.instanceOf<Arithmetic>() || !rhs.instanceOf<Arithmetic>()) {
        throw std::invalid_argument("Types must be Arithmetic");
      }
      return lhs.to<Arithmetic>() + rhs.to<Arithmetic>();
    }

  protected:
    MathObjectPtr call(const std::vector<std::reference_wrapper<const MathObject>> &argsVect) const override {
      if (argsVect.size() != 2) {
        throw std::invalid_argument("The number of arguments must be 2");
      }
      return TestAdd::operator()(argsVect.at(0).get(), argsVect.at(1).get());
    }

    bool equals(const TestAdd & /*rhs*/) const override {
      return true;
    }
  };
}

TEST(FunctionTests, callTests) {
  FunctionPtr f = std::make_unique<tests::TestAdd>();
  Integer a = 3;
  Rational b(1, 2);

  EXPECT_EQ((*f)(a, a)->toString(), "6");
  EXPECT_EQ((*f)(b, b)->toString(), "1");
  EXPECT_EQ((*f)(a, b)->toString(), "7/2");
  EXPECT_EQ((*f)(b, a)->toString(), "7/2");

  EXPECT_THROW((*f)(a, Variable("a")), std::invalid_argument);

  EXPECT_THROW((*f)(), std::invalid_argument);
  EXPECT_THROW((*f)(a), std::invalid_argument);
  EXPECT_THROW((*f)(a, a, a), std::invalid_argument);
  EXPECT_THROW((*f)(a, a, a, a, a, a, a), std::invalid_argument);
}
