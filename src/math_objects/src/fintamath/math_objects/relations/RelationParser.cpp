#include "fintamath/math_objects/relations/RelationParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/terms/TermParser.hpp"

using namespace fintamath;

std::unique_ptr<Relation> RelationParser::parse(const std::string_view & /*str*/) {
  return nullptr;
}
