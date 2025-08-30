#include "fintamath/functions/IFunction.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunction)

IFunction::FunctionMaker::FunctionMaker(const IFunction &inDefaultFunc) : defaultFunc(inDefaultFunc) {
}

std::unique_ptr<IFunction> IFunction::FunctionMaker::makeFunction(Arguments inArgs) {
  return defaultFunc.get().makeSelf(std::move(inArgs));
}

std::unique_ptr<IFunction> IFunction::FunctionMaker::doArgumentsMatch(Arguments inArgs) {
  return defaultFunc.get().makeSelf(std::move(inArgs));
}

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

  FunctionMakers &functionMakers = getNameToFunctionMakersMap()[declaration.name];
  functionMakers.emplace_back(cast<IFunction>(getDefaultObject()));
}

bool IFunction::doArgumentsMatch(Arguments inArgs) const {
  return true;
}

IFunction::NameToFunctionMakersMap &IFunction::getNameToFunctionMakersMap() {
  static NameToFunctionMakersMap nameToFunctionMakerMap;
  return nameToFunctionMakerMap;
}

}
