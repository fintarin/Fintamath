#pragma once

#include "fintamath/expressions/ExpressionBase.hpp"

namespace fintamath {

class Function : public ExpressionBase {
  FINTAMATH_INTERFACE_BODY(Function, ExpressionBase)

public:
  struct FunctionDeclaration {
    ExpressionDeclaration expressionDeclarion;
    std::string_view functionName;
  };

protected:
  Function() = default;

  explicit Function(Children inChildren);

public:
  constexpr ExpressionDeclaration getExpressionDeclaration() const noexcept final {
    return getFunctionDeclaration().expressionDeclarion;
  }

  virtual constexpr FunctionDeclaration getFunctionDeclaration() const noexcept = 0;

  std::string toString() const noexcept override;

  template <typename T>
  friend std::unique_ptr<Function> makeFunction(Function::Children children);

protected:
  virtual std::unique_ptr<Function> makeFunction(Children children) const = 0;
};

template <typename T>
std::unique_ptr<Function> makeFunction(Function::Children children) {
  return T::getDefaultObject().makeFunction(std::move(children));
}

}
