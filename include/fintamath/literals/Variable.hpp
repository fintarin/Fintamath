#pragma once

#include <string>
#include <string_view>

#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/literals/ILiteral.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable final : public ILiteralCRTP<Variable> {
public:
  explicit Variable(std::string_view inName);

  explicit Variable(std::string_view inName, Integer inIndex);

  std::string toString() const override;

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Variable, "Variable"};
  }

private:
  std::string name;

  Integer index = -1;
};

}