#include "fintamath/literals/Variable.hpp"

#include <string>
#include <string_view>
#include <utility>

#include <fmt/core.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

Variable::Variable(const std::string_view inName) {
  if (inName.size() != 1) {
    throw InvalidInputException(
        fmt::format(R"(Invalid {} "{}" (name expected to be 1 character))", getTypeStatic().getName(), inName));
  }

  if (const char ch = inName.front(); ch < 'a' || ch > 'z') {
    throw InvalidInputException(
        fmt::format(R"(Invalid {} "{}" (name expected to be an English lowercase letter))", getTypeStatic().getName(), inName));
  }

  name = std::string(inName);
}

Variable::Variable(const std::string_view inName, Integer inIndex) : Variable(inName) {
  if (inIndex < 0) {
    throw InvalidInputException(
        fmt::format(R"(Invalid {} "{}_{}" (expected index >= 0))", getTypeStatic().getName(), name, inIndex.toString()));
  }

  index = std::move(inIndex);
}

std::string Variable::toString() const {
  std::string indexStr = index != -1 ? fmt::format("_{}", index.toString()) : "";
  return fmt::format("{}{}", name, indexStr);
}

}
