#pragma once

#include "fintamath/core/Summable.hpp"
#include "fintamath/expressions/Expression.hpp"

namespace fintamath {
  class Function : virtual public MathObject {
  public:
    ~Function() override = default;

    template <typename... Args>
    std::unique_ptr<MathObject> operator()(const Args &...args) const {
      std::vector<std::shared_ptr<MathObject>> argsVect = {args.clone()...};
      return call(argsVect);
    }

  protected:
    virtual std::unique_ptr<MathObject> call(const std::vector<std::shared_ptr<MathObject>> &argsVect) const = 0;
  };

  template <typename Derived>
  class FunctionImpl : virtual public Function, virtual public MathObjectImpl<Derived> {
  public:
    ~FunctionImpl() override = default;
  };
}
