#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IFunctionUnary : public IFunction {
  FINTAMATH_INTERFACE_BODY(IFunctionUnary, IFunction)

public:
  using IFunction::IFunction;

  std::string toString() const noexcept override;

  const SharedRef<IMathObject> &getArgument() const;

protected:
  using SimplifyFunction = std::function<SharedPtr<IMathObject>(const SharedRef<IMathObject> &)>;

  using SimplifyFunctions = std::vector<SimplifyFunction>;

protected:
  virtual SimplifyFunctions getFunctionsForPreSimplify() const;

  virtual SimplifyFunctions getFunctionsForSimplify() const;

  SharedPtr<IMathObject> preSimplifySelf() const override;

  SharedPtr<IMathObject> simplifySelf() const override;

  void registerDefaultObject() const override;
};

}
