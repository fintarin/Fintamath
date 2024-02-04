#pragma once

#include <string>

#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable final : public ILiteralCRTP<Variable> {
public:
  explicit Variable(std::string inName);

  explicit Variable(std::string inName, Integer inIndex);

  std::string toString() const override;

  static MathObjectType getTypeStatic() {
    return MathObjectType::Variable;
  }

private:
  std::string name;

  Integer index = -1;
};

}