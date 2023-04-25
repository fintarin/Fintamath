#pragma once

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable : public ILiteralCRTP<Variable> {
public:
  explicit Variable(string inName);

  explicit Variable(string inName, Integer index);

  string toString() const override;

private:
  string name;

  Integer index;
};

}