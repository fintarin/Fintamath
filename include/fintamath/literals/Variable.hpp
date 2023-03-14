#pragma once

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

class Variable : public ILiteralCRTP<Variable> {
public:
  explicit Variable(const string &str);

  string toString() const override;

private:
  string name;
};

}