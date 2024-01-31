#include "fintamath/functions/other/Comma.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Comma::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = argVect.front().get();
  const auto &rhs = argVect.back().get();

  throw InvalidInputBinaryOperatorException(toString(), lhs.toString(), rhs.toString());
}

}
