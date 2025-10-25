#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class IOperator;

class IFunctionVariadic : public IFunction {
  FINTAMATH_INTERFACE_BODY(IFunctionVariadic, IFunction)

public:
  using IFunction::IFunction;

  std::string toString() const noexcept override;

protected:
  struct ArgumentStringData {
    std::string delimiter;
    std::string argumentString;

  public:
    std::string join() &&;
  };

  using SimplifyFunction = std::function<SharedPtr<IMathObject>(const SharedRef<IMathObject> &, const SharedRef<IMathObject> &)>;

  using SimplifyFunctions = std::vector<SimplifyFunction>;

protected:
  virtual ArgumentStringData getArgumentStringData(const SharedRef<IMathObject> &arg, const SharedPtr<IMathObject> &prevArg) const;

  virtual SimplifyFunctions getFunctionsForPreSimplify() const;

  virtual SimplifyFunctions getFunctionsForSimplify() const;

  SharedPtr<IMathObject> compressSelf() const override;

  SharedPtr<IMathObject> preSimplifySelf() const override;

  SharedPtr<IMathObject> simplifySelf() const override;

  SharedPtr<IMathObject> unwrappSelf() const noexcept override;

  void registerDefaultObject() const override;

  // virtual bool isTermOrderInversed() const noexcept;

  // virtual bool isComparableOrderInversed() const noexcept;

  // virtual std::strong_ordering compare(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) const;

  std::optional<Arguments> compressArguments() const;

private:
  static void appendVariadicFunctionArgument(const SharedRef<IMathObject> &arg, const MathObjectClass &selfClass, Arguments &outArgs);

  static void appendVariadicFunctionArguments(const IFunction &func, const MathObjectClass &selfClass, Arguments &outArgs) noexcept;

  // void sort();
};

}
