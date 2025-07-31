#include "fintamath/expressions/functions/IOperator.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IOperator)

IOperator::IOperator(Children inChildren) : Super(std::move(inChildren)) {
}

const IFunction::FunctionDeclaration &IOperator::getFunctionDeclaration() const noexcept {
  return getOperatorDeclaration().functionDeclarion;
}

}
