#include "fintamath/functions/other/Comma.hpp"

#include <memory>

#include <fmt/core.h>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Comma)

std::unique_ptr<IMathObject> Comma::call(const ArgumentRefVector & /*argVect*/) const {
  throw InvalidInputException(fmt::format(
      R"(Calling {} directly is not allowed)",
      getClassStatic()->getName()));
}

}
