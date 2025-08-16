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

  class FunctionMaker {
  public:
    FunctionMaker(const IFunction &inDefaultFunc);

    std::unique_ptr<IFunction> makeFunction(Arguments inArgs);

    std::unique_ptr<IFunction> doArgumentsMatch(Arguments inArgs);

  private:
    std::reference_wrapper<const IFunction> defaultFunc;
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

protected:
  virtual std::unique_ptr<IFunction> makeSelf(Arguments inArgs) const = 0;

  void registerDefaultObject() const override;

private:
  bool doArgumentsMatch(Arguments inArgs) const;

  static NameToFunctionMakersMap &getNameToFunctionMakersMap();

private:
  Arguments args;
};

}
