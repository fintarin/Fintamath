#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

class I final : public IConstantCRTP<Complex, I> {
public:
  std::string toString() const override {
    return "I";
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::I, "I"};
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
