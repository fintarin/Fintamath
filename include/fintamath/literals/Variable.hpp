#pragma once

#include <string>

#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable : public ILiteralCRTP<Variable> {
  FINTAMATH_CLASS_BODY(Variable, ILiteral)

public:
  explicit Variable(std::string_view inName);

  explicit Variable(std::string_view inName, Integer inIndex);

  std::string toString() const override;

private:
  std::string name;

  Integer index = -1;
};

}