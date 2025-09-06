#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IFunction : public IExpression {
  FINTAMATH_INTERFACE_BODY(Function, IExpression)

public:
  struct FunctionDeclaration {
    ExpressionDeclaration expressionDeclarion;
    std::string_view functionName;
  };

protected:
  IFunction() = default;

  explicit IFunction(Children inChildren);

public:
  constexpr ExpressionDeclaration getExpressionDeclaration() const noexcept final {
    return getFunctionDeclaration().expressionDeclarion;
  }

  virtual constexpr FunctionDeclaration getFunctionDeclaration() const noexcept = 0;

  std::string toString() const noexcept override;

  template <typename T>
  friend std::unique_ptr<IFunction> makeFunction(IFunction::Children children);

protected:
  virtual std::unique_ptr<IFunction> makeFunction(Children children) const = 0;
};

template <typename T>
std::unique_ptr<IFunction> makeFunction(IFunction::Children children) {
  return T::getDefaultObject().makeFunction(std::move(children));
}

}
