#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Inf final : public IConstantCRTP<INumber, Inf> {
public:
  std::string toString() const override {
    return "Inf";
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Inf, "Inf"};
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
