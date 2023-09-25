#include "fintamath/functions/other/Comma.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Comma::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = argsVect.front().get();
  const auto &rhs = argsVect.back().get();

  throw InvalidInputBinaryOperatorException(toString(), lhs.toString(), rhs.toString());
}

}
