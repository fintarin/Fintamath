#include "fintamath/functions/other/Index.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOperatorException.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Index::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<Variable>(argsVect.front().get());
  const auto &rhs = cast<Integer>(argsVect.back().get());
  return std::make_unique<Variable>(lhs.toString(), rhs);
}

}
