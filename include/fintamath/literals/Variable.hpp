#pragma once

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable : public ILiteralCRTP<Variable> {
public:
  explicit Variable(std::string inName);

  explicit Variable(std::string inName, const Integer &inIndex);

  std::string toString() const override;

private:
  std::string name;

  Integer index;
};

}