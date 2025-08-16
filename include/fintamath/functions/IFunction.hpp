#pragma once

#include "fintamath/core/IMathObject.hpp"
#include <functional>
#include <unordered_map>

namespace fintamath {

class IFunction : public IMathObject {
  FINTAMATH_INTERFACE_BODY(IFunction, IMathObject)

public:
  using Argument = std::shared_ptr<const IMathObject>;
  using Arguments = std::vector<Argument>;

  struct FunctionDeclaration {
    MathObjectClass returnClass = {};
    std::vector<MathObjectClass> argumentClasses;
    bool isVariadic = false;
    std::string name;
  };

  struct FunctionMaker {
    std::function<std::shared_ptr<const IFunction>(Arguments args)> maker;
    std::reference_wrapper<const IFunction> defaultObject;
  };

  using FunctionMakers = std::vector<FunctionMaker>;
  using NameToFunctionMakersMap = std::unordered_map<std::string, FunctionMakers>;

protected:
  IFunction() = default;

  explicit IFunction(Arguments inArgs);

public:
  virtual const FunctionDeclaration &getFunctionDeclaration() const noexcept = 0;

  std::string toString() const noexcept override;

  const Arguments &getArguments() const noexcept;

  static const FunctionMakers *parseFunctionMakers(const std::string &str);

  template <typename T>
  friend std::unique_ptr<IFunction> makeFunction(IFunction::Arguments inArgs);

protected:
  virtual std::unique_ptr<IFunction> makeFunctionSelf(Arguments inArgs) const = 0;

  void registerDefaultObject() const override;

private:
  static NameToFunctionMakersMap &getNameToFunctionMakersMap();

private:
  Arguments args;
};

template <typename T>
std::unique_ptr<IFunction> makeFunction(IFunction::Arguments inArgs) {
  return T::getDefaultObjectStatic().makeFunctionSelf(std::move(inArgs));
}

}
