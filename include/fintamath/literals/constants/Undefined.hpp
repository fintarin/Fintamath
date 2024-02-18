#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class Undefined final : public IConstantCRTP<IArithmetic, Undefined> {
public:
  std::string toString() const override {
    return "Undefined";
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Undefined, "Undefined"};
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
