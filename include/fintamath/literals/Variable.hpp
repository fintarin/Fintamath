#pragma once

#include <string>

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable : public ILiteral {
  FINTAMATH_CHILD_CLASS_BODY(Variable, ILiteral)

public:
  explicit Variable(std::string_view inName);

  explicit Variable(std::string_view inName, Integer inIndex);

  std::string toString() const noexcept override;

private:
  std::string name;

  Integer index = -1;
};

}