#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IOperator;

class IFunctionVariadic : public IFunction {
  FINTAMATH_INTERFACE_BODY(IFunctionVariadic, IFunction)

public:
  using Args = ArgVector;

public:
  std::string toString() const noexcept override;

  ArgSpan getArgs() const noexcept override;

  Args getArgsVariadic() const noexcept;

protected:
  struct ArgumentStringData {
    std::string delimiter;
    std::string argumentString;

  public:
    std::string join() &&;
  };

  using ModifyFunction = std::function<SharedPtr<IMathObject>(const SharedRef<IMathObject> &, const SharedRef<IMathObject> &)>;

  using ModifyFunctions = std::vector<ModifyFunction>;

protected:
  IFunctionVariadic();

  explicit IFunctionVariadic(const Declaration &inDeclaration, Args inArgs);

  explicit IFunctionVariadic(const Declaration &inDeclaration, ArgSpan inArgs);

  virtual ArgumentStringData getArgumentStringData(const SharedRef<IMathObject> &arg, const SharedPtr<IMathObject> &prevArg) const;

  virtual ModifyFunctions getFunctionsForPreSimplify() const;

  virtual ModifyFunctions getFunctionsForSimplify() const;

  SharedPtr<IMathObject> preSimplifySelf() const override;

  SharedPtr<IMathObject> simplifySelf() const override;

  SharedPtr<IMathObject> unwrappSelf() const noexcept override;

  void registerDefaultObject() const override;

  // virtual bool isTermOrderInversed() const noexcept;

  // virtual bool isComparableOrderInversed() const noexcept;

  // virtual std::strong_ordering compare(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) const;

  std::optional<Args> compressArgs() const;

private:
  static void appendVariadicFunctionArgument(const SharedRef<IMathObject> &arg, const MathObjectClass &selfClass, Args &outArgs);

  static void appendVariadicFunctionArguments(const IFunction &func, const MathObjectClass &selfClass, Args &outArgs) noexcept;

  // void sort();

private:
  Args args;
};

}
