#include "fintamath/functions/IFunction.hpp"

#include "fintamath/core/Tokenizer.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunction)

IFunction::IFunction(Arguments inArgs) : args(std::move(inArgs)) {
}

std::string IFunction::toString() const noexcept {
  std::string outStr(getFunctionDeclaration().name);
  for (const auto &arg : getArguments()) {
    outStr += " " + arg->toString();
  }
  return outStr;
}

const IFunction::Arguments &IFunction::getArguments() const noexcept {
  return args;
}

const IFunction::FunctionMakers *IFunction::parseFunctionMakers(const std::string &str) {
  const NameToFunctionMakersMap &nameToFunctionMakersMap = getNameToFunctionMakersMap();
  const auto parsedConstantIter = nameToFunctionMakersMap.find(str);
  return parsedConstantIter != nameToFunctionMakersMap.end() ? &parsedConstantIter->second : nullptr;
}

void IFunction::registerDefaultObject() const {
  const FunctionDeclaration &declaration = getFunctionDeclaration();
  detail::Tokenizer::registerToken(declaration.name);

  const auto selfMaker = [this](Arguments inArgs) {
    return makeFunctionSelf(std::move(inArgs));
  };
  FunctionMakers &functionMakers = getNameToFunctionMakersMap()[declaration.name];
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
