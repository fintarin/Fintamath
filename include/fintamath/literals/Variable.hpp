#pragma once

#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable : public ILiteralCRTP<Variable> {
public:
  explicit Variable(std::string inName);

  explicit Variable(std::string inName, Integer inIndex);

  std::string toString() const override;

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Variable);
  }

private:
  std::string name;

  Integer index = -1;
};

}