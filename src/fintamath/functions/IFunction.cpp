#include "fintamath/functions/IFunction.hpp"

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunction)

IFunction::FunctionMaker::FunctionMaker(const IFunction &inDefaultFunc)
    : defaultFunc(inDefaultFunc) {
}

std::unique_ptr<IFunction> IFunction::FunctionMaker::make(Arguments inArgs) const {
  return defaultFunc.get().makeSelf(std::move(inArgs));
}

bool IFunction::FunctionMaker::doArgumentsMatch(const Arguments &inArgs) const noexcept {
  return defaultFunc.get().doArgumentsMatch(inArgs);
}

const IFunction::Declaration &IFunction::FunctionMaker::getDeclaration() const noexcept {
  return defaultFunc.get().getDeclaration();
}

MathObjectClass IFunction::FunctionMaker::getClass() const noexcept {
  return defaultFunc.get().getClass();
}

std::string IFunction::toString() const noexcept {
  std::string name = getDeclaration().name;
  if (name.empty()) {
    return Super::toString();
  }

  std::string outStr = std::move(name);

  for (const auto &arg : getArguments()) {
    outStr += " " + arg->toString();
  }

  return "(" + outStr + ")";
}

std::shared_ptr<const IMathObject> IFunction::unwrapp() const noexcept {
  if (getDeclaration().isVariadic && args.size() == 1) {
    return args.front();
  }

  return {};
}

const IFunction::Arguments &IFunction::getArguments() const noexcept {
  return args;
}

const IFunction::FunctionMakers *IFunction::parseFunctionMakers(const std::string &str) {
  const NameToFunctionMakersMap &nameToMakersMap = getNameToFunctionMakersMap();
  const auto iter = nameToMakersMap.find(str);
  return iter != nameToMakersMap.end() ? &iter->second : nullptr;
}

void IFunction::registerDefaultObject() const {
  const Declaration &decl = getDeclaration();
  if (decl.name.empty()) {
    return;
  }

  detail::Tokenizer::registerToken(decl.name);

  FunctionMakers &makers = getNameToFunctionMakersMap()[decl.name];
  makers.emplace_back(cast<IFunction>(getDefaultObject()));
}

void IFunction::initSelf(Arguments inArgs) {
  args = unwrappArguments(validateArguments(std::move(inArgs)));
}

IFunction::Arguments IFunction::validateArguments(Arguments inArgs) const {
  if (!doArgumentsMatch(inArgs)) {
    throw InvalidInputException("Invalid args"); // TODO
  }

  return inArgs;
}

IFunction::Arguments IFunction::unwrappArguments(Arguments inArgs) const {
  for (auto &arg : inArgs) {
    if (auto unwrappedArg = arg->unwrapp()) {
      arg = std::move(unwrappedArg);
    }
  }

  if (!getDeclaration().isVariadic) {
    return inArgs;
  }

  const MathObjectClass selfClass = getClass();

  Arguments outArgs;
  outArgs.reserve(inArgs.size());

  for (auto &arg : inArgs) {
    if (arg->getClass() == selfClass) {
      const auto &argFunc = cast<IFunction>(*arg);
      const Arguments &innerArgs = argFunc.getArguments();
      outArgs.insert(outArgs.end(), innerArgs.begin(), innerArgs.end());
    }
    else {
      outArgs.emplace_back(std::move(arg));
    }
  }

  return outArgs;
}

bool IFunction::doArgumentsMatch(const Arguments &inArgs) const noexcept {
  const auto &decl = getDeclaration();
  return decl.isVariadic ? doArgumentsMatchVariadic(decl, inArgs)
                         : doArgumentsMatchNonVariadic(decl, inArgs);
}

bool IFunction::doArgumentsMatchNonVariadic(const Declaration & /*decl*/, const Arguments & /*inArgs*/) {
  // TODO
  return true;
}

bool IFunction::doArgumentsMatchVariadic(const Declaration & /*decl*/, const Arguments & /*inArgs*/) {
  // TODO
  return true;
}

IFunction::NameToFunctionMakersMap &IFunction::getNameToFunctionMakersMap() {
  static NameToFunctionMakersMap nameToFunctionMakerMap;
  return nameToFunctionMakerMap;
}

}
