#include "fintamath/variables/Variable.hpp"

#include <string>
#include <string_view>
#include <utility>

#include <fmt/core.h>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Variable)

Variable::Variable(std::string_view inName) {
  if (inName.size() != 1 || inName.front() < 'a' || inName.front() > 'z') {
    throw InvalidInputException(fmt::format(
      "Unable to parse {} name from \"{}\" (expected single English lowercase letter)",
      getClassStatic()->getName(),
      inName
    ));
  }

  name = std::string(inName);
}

Variable::Variable(std::string_view inName, Integer inIndex) : Variable(inName) {
  if (inIndex < 0) {
    throw InvalidInputException(fmt::format(
      "Negative {} index {} is not allowed",
      getClassStatic()->getName(),
      inIndex.toString()
    ));
  }

  index = std::move(inIndex);
}

std::string Variable::toString() const noexcept {
  if (index) {
    return fmt::format("{}_{}", name, index->toString());
  }
  return name;
}

bool Variable::equals(const SharedRef<IMathObject> & /*self*/, const SharedRef<IMathObject> &rhs) const noexcept {
  if (const auto rhsVar = cast<Variable>(rhs)) {
    return equals(*rhsVar);
  }

  return false;
}

bool Variable::equals(const Variable &rhs) const noexcept {
  return name == rhs.name && index == rhs.index;
}

}
