#pragma once

#include "fintamath/expressions/ExpressionBase.hpp"

namespace fintamath {

class Function : public ExpressionBase {
  FINTAMATH_CLASS_BODY(Function, ExpressionBase)

public:
  struct FunctionDeclaration : ExpressionBaseDeclaration {
    std::string functionName;
  };

protected:
  Function() = default;

  explicit Function(Children inChildren);

public:
  const FunctionDeclaration &getDeclaration() const noexcept override;

  std::string toString() const noexcept override;

  template <typename T>
  friend std::unique_ptr<Function> makeFunction(Function::Children children);

protected:
  virtual std::unique_ptr<Function> makeFunction(Children children) const;
};

template <typename T>
std::unique_ptr<Function> makeFunction(Function::Children children) {
  return T::getDefaultObjectStatic().makeFunction(std::move(children));
}

}
