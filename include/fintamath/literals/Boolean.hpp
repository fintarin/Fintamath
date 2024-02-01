#pragma once

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class Boolean final : public ILiteralCRTP<Boolean> {
public:
  Boolean();

  explicit Boolean(const std::string &str);

  Boolean(bool val);

  std::string toString() const override;

  operator bool() const;

  static MathObjectType getTypeStatic() {
    return MathObjectType::Boolean;
  }

private:
  std::string name;
};

}
