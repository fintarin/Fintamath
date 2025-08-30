#pragma once

#include "fintamath/expressions/ExpressionBase.hpp"

namespace fintamath {

class Function : public ExpressionBase {
  FINTAMATH_INTERFACE_BODY(Function, ExpressionBase)

public:
  struct FunctionDeclaration : ExpressionBaseDeclaration {
    std::string functionName;
  };

protected:
  Function() = default;

  explicit Function(Children inChildren);

public:
  const FunctionDeclaration &getDeclaration() const noexcept override = 0;

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
