#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IFunctionBinary : public IFunction {
  FINTAMATH_INTERFACE_BODY(IFunctionBinary, IFunction)

protected:
  using SimplifyFunction = std::function<SharedPtr<IMathObject>(const SharedRef<IMathObject> &, const SharedRef<IMathObject> &)>;

  using SimplifyFunctions = std::vector<SimplifyFunction>;

public:
  using IFunction::IFunction;

  std::string toString() const noexcept override;

  const SharedRef<IMathObject> &getLeftArgument() const;

  const SharedRef<IMathObject> &getRightArgument() const;

protected:
  virtual SimplifyFunctions getFunctionsForPreSimplify() const;

  virtual SimplifyFunctions getFunctionsForSimplify() const;

  SharedPtr<IMathObject> preSimplifySelf() const override;

  SharedPtr<IMathObject> simplifySelf() const override;

  void registerDefaultObject() const override;
};

}
