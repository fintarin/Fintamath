#pragma once

#include <string>

#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class FINTAMATH_EXPORT Variable : public IMathObject {
  FINTAMATH_CLASS_BODY(Variable, IMathObject)

protected:
  Variable() = default;

public:
  explicit Variable(std::string_view inName);

  explicit Variable(std::string_view inName, Integer inIndex);

  std::string toString() const noexcept override;

private:
  std::string name;

  Integer index = -1;
};

}