#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {
  class IExpression;
  using ExpressionPtr = std::unique_ptr<IExpression>;

  class IExpression : virtual public IMathObject { // TODO replace IMathObject to IArithmetic
  protected:
    using TokenVector = std::vector<std::string>;

  protected:
    static TokenVector tokenize(const std::string &str);
  };

  template <typename Derived>
  class IExpressionCRTP : virtual public IExpression,
                          virtual public IMathObjectCRTP<Derived> { // TODO replace IMathObjectCRTP to IArithmeticCRTP
  protected:
    bool equals(const Derived &rhs) const final {
      return toString() == rhs.toString();
    }
  };
}
