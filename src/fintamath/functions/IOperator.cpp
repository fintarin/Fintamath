#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IOperator)

IOperator::IOperator(Arguments inArgs) : Super(std::move(inArgs)) {
}

const IFunction::FunctionDeclaration &IOperator::getFunctionDeclaration() const noexcept {
  return getOperatorDeclaration().functionDeclarion;
}

}
