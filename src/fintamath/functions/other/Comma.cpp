#include "fintamath/functions/other/Comma.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Comma::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = argVect.front().get();
  const auto &rhs = argVect.back().get();

  throw InvalidInputBinaryOperatorException(toString(), lhs.toString(), rhs.toString());
}

}
