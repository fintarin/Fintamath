#pragma once

#include <string>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class Boolean final : public ILiteralCRTP<Boolean> {
public:
  Boolean();

  explicit Boolean(std::string_view inVal);

  Boolean(bool inVal);

  std::string toString() const override;

  operator bool() const;

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Boolean, "Boolean"};
  }

private:
  std::string_view val;
};

}
