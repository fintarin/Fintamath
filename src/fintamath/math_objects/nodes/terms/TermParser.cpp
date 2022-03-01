#include "fintamath/math_objects/nodes/terms/TermParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/ParserInjector.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/NumberParser.hpp"

namespace fintamath {
  std::unique_ptr<Term> TermParser::parse(const std::string_view &str) {
    INJECT_PARSER(NumberParser, str)
    return nullptr;
  }
}