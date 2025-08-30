#include "fintamath/variables/Variable.hpp"

#include <string>
#include <string_view>
#include <utility>

#include <fmt/core.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Variable)

Variable::Variable(std::string_view inName) {
  if (inName.size() != 1 || inName.front() < 'a' || inName.front() > 'z') {
    throw InvalidInputException(fmt::format(
      R"(Unable to parse {} name from "{}" (expected single English lowercase letter))",
      getClassStatic()->getName(),
      inName
    ));
  }

  name = std::string(inName);
}

Variable::Variable(std::string_view inName, Integer inIndex) : Variable(inName) {
  if (inIndex < 0) {
    throw InvalidInputException(fmt::format(
      R"(Negative {} index {} is not allowed)",
      getClassStatic()->getName(),
      inIndex.toString()
    ));
  }

  index = std::move(inIndex);
}

std::string Variable::toString() const noexcept {
  std::string indexStr = index != -1 ? fmt::format("_{}", index.toString()) : "";
  return fmt::format("{}{}", name, indexStr);
}

}
