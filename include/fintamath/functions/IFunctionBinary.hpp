#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IFunctionBinary : public IFunction {
  FINTAMATH_INTERFACE_BODY(IFunctionBinary, IFunction)

public:
  using Args = std::array<SharedRef<IMathObject>, 2>;

public:
  std::string toString() const noexcept override;

  ArgSpan getArgs() const noexcept override;

  const SharedRef<IMathObject> &getArgLeft() const;

  const SharedRef<IMathObject> &getArgRight() const;

protected:
  using ModifyFunction = std::function<SharedPtr<IMathObject>(const SharedRef<IMathObject> &, const SharedRef<IMathObject> &)>;

  using ModifyFunctions = std::vector<ModifyFunction>;

protected:
  IFunctionBinary();

  explicit IFunctionBinary(const Declaration &inDeclaration, Args inArgs);

  explicit IFunctionBinary(const Declaration &inDeclaration, ArgSpan inArgs);

  virtual ModifyFunctions getFunctionsForPreSimplify() const;

  virtual ModifyFunctions getFunctionsForSimplify() const;

  SharedPtr<IMathObject> preSimplifySelf() const override;

  SharedPtr<IMathObject> simplifySelf() const override;

  void registerDefaultObject() const override;

private:
  Args args;
};

}
