#pragma once

#include <string>

#include "fintamath/literals/Literal.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable : public Literal {
  FINTAMATH_CLASS_BODY(Variable, Literal)

public:
  explicit Variable(std::string_view inName);

  explicit Variable(std::string_view inName, Integer inIndex);

  std::string toString() const noexcept override;

protected:
  Variable() = default;

private:
  std::string name;

  Integer index = -1;
};

}