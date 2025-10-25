#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IFunctionUnary : public IFunction {
  FINTAMATH_INTERFACE_BODY(IFunctionUnary, IFunction)

public:
  using Args = std::array<SharedRef<IMathObject>, 1>;

protected:
  std::string toString() const noexcept override;

  ArgSpan getArgs() const noexcept override;

  const SharedRef<IMathObject> &getArg() const;

protected:
  using ModifyFunction = std::function<SharedPtr<IMathObject>(const SharedRef<IMathObject> &)>;

  using ModifyFunctions = std::vector<ModifyFunction>;

protected:
  IFunctionUnary();

  explicit IFunctionUnary(const Declaration &inDeclaration, Args inArgs);

  explicit IFunctionUnary(const Declaration &inDeclaration, ArgSpan inArgs);

  virtual ModifyFunctions getFunctionsForPreSimplify() const;

  virtual ModifyFunctions getFunctionsForSimplify() const;

  SharedPtr<IMathObject> preSimplifySelf() const override;

  SharedPtr<IMathObject> simplifySelf() const override;

  void registerDefaultObject() const override;

private:
  Args args;
};

}
