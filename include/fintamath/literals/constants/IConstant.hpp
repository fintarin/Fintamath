#pragma once

#include <concepts>
#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class IConstant : public ILiteral {
  FINTAMATH_PARENT_CLASS_BODY(IConstant)

public:
  virtual MathObjectClass getReturnClass() const = 0;

  std::unique_ptr<IMathObject> operator()() const {
    return call();
  }

protected:
  virtual std::unique_ptr<IMathObject> call() const = 0;
};

template <typename Return, typename Derived>
class IConstantCRTP : public IConstant {
#define I_CONSTANT_CRTP IConstantCRTP<Return, Derived>
#include "fintamath/literals/constants/IConstantCRTP.hpp"
#undef I_CONSTANT_CRTP
};

}
