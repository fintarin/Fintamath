#pragma once

#include <functional>
#include <unordered_map>

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IFunction : public IExpression {
  FINTAMATH_INTERFACE_BODY(IFunction, IExpression)

public:
  struct FunctionDeclaration {
    ExpressionDeclaration expressionDeclarion;
    std::string functionName;
  };

  struct FunctionMaker {
    std::function<std::shared_ptr<const IFunction>(Children children)> maker;
    std::reference_wrapper<const IFunction> defaultObject;
  };

  using FunctionMakers = std::vector<FunctionMaker>;
  using NameToFunctionMakersMap = std::unordered_map<std::string, FunctionMakers>;

protected:
  IFunction() = default;

  explicit IFunction(Children inChildren);

public:
  const ExpressionDeclaration &getExpressionDeclaration() const noexcept final;

  virtual const FunctionDeclaration &getFunctionDeclaration() const noexcept = 0;

  std::string toString() const noexcept override;

  static const FunctionMakers* parseFunctionMakers(const std::string& str);

  template <typename T>
  friend std::unique_ptr<IFunction> makeFunction(IFunction::Children children);

protected:
  virtual std::unique_ptr<IFunction> makeFunctionSelf(Children children) const = 0;

  void registerDefaultObject() const override;

private:
  static NameToFunctionMakersMap &getNameToFunctionMakersMap();
};

template <typename T>
std::unique_ptr<IFunction> makeFunction(IFunction::Children children) {
  return T::getDefaultObjectStatic().makeFunctionSelf(std::move(children));
}

}
