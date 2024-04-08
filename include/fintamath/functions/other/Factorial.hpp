#pragma once

#include <cassert>
#include <cstddef>
#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Integer;
class Rational;
class Real;

class Factorial : public IOperatorCRTP<INumber, Factorial, INumber> {
  FINTAMATH_CLASS_BODY(Factorial, IOperator)

public:
  Factorial() = default;

  explicit Factorial(const size_t inOrder) : Factorial() {
    setOrder(inOrder);
  }

  std::string toString() const override {
    return std::string(order, '!');
  }

  static constexpr Priority getPriorityStatic() noexcept {
    return Priority::PostfixUnary;
  }

  size_t getOrder() const {
    return order;
  }

  void setOrder(const size_t inOrder) {
    assert(inOrder > 0);
    order = inOrder;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiFactorialSimplify(const INumber &lhs, size_t order);

  static std::unique_ptr<IMathObject> factorialSimplify(const Integer &rhs, size_t order);

  static std::unique_ptr<IMathObject> factorialSimplify(const Rational &rhs, size_t order);

  static std::unique_ptr<IMathObject> factorialSimplify(const Real &rhs, size_t order);

private:
  size_t order = 1;
};

FINTAMATH_FUNCTION_EXPRESSION(Factorial, factorialExpr);

}
