#pragma once

#include <string>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class Boolean final : public ILiteralCRTP<Boolean> {
  FINTAMATH_CLASS_BODY(Boolean)

public:
  Boolean();

  explicit Boolean(const std::string &str);

  Boolean(bool val);

  std::string toString() const override;

  operator bool() const;

private:
  std::string name;
};

}
