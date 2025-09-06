#include "fintamath/expressions/functions/IFunction.hpp"

#include "fintamath/core/Tokenizer.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunction)

IFunction::IFunction(Children inChildren) : Super(std::move(inChildren)) {
}

const IExpression::ExpressionDeclaration &IFunction::getExpressionDeclaration() const noexcept {
  return getFunctionDeclaration().expressionDeclarion;
}

std::string IFunction::toString() const noexcept {
  std::string outStr(getFunctionDeclaration().functionName);
  for (const auto &child : getChildren()) {
    outStr += " " + child->toString();
  }
  return outStr;
}

void IFunction::registerDefaultObject() const {
  const FunctionDeclaration &declaration = getFunctionDeclaration();
  detail::Tokenizer::registerToken(declaration.functionName);

  const auto selfMaker = [this](Children inChildren) {
    return makeFunctionSelf(std::move(inChildren));
  };
  FunctionMakers &functionMakers = getNameToFunctionMakersMap()[declaration.functionName];
  functionMakers.emplace_back(FunctionMaker{
    .maker = std::move(selfMaker),
    .defaultObject = *this,
  });
}

IFunction::NameToFunctionMakersMap &IFunction::getNameToFunctionMakersMap() {
  static NameToFunctionMakersMap parseInputToFunctionMakerMap;
  return parseInputToFunctionMakerMap;
}

}
