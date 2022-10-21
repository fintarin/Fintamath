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

  public:
    ~IExpression() override = default;

  protected:
    static TokenVector tokenize(const std::string &str);
  };

  template <typename Derived>
  class IExpressionCRTP : virtual public IExpression,
                          virtual public IMathObjectCRTP<Derived> { // TODO replace IMathObjectCRTP to IArithmeticCRTP
  public:
    ~IExpressionCRTP() override = default;

  protected:
    bool equals(const Derived &rhs) const final {
      return toString() == rhs.toString();
    }
  };
}
