#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class False final : public IConstantCRTP<Boolean, False> {
public:
  std::string toString() const override {
    return Boolean(false).toString();
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::False;
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
