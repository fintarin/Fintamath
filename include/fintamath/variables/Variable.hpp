#pragma once

#include <string>

#include "fintamath/core/ClassBody.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Variable : public IMathObject, IWithEqualsOperators<Variable> {
  FINTAMATH_CLASS_BODY(Variable, IMathObject)

public:
  Variable() = default;

  explicit Variable(std::string_view inName);

  explicit Variable(std::string_view inName, Integer inIndex);

  std::string toString() const noexcept override;

protected:
  bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept override;

  bool equals(const Variable &rhs) const noexcept override;

private:
  char name = 'x';

  std::optional<Integer> index;
};

}