#include "fintamath/functions/IFunction.hpp"

#include <cassert>

#include <fmt/core.h>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunction)

IFunction::FunctionMaker::FunctionMaker(const IFunction &inDefaultFunc)
    : defaultFunc(inDefaultFunc) {
}

Shared<IFunction> IFunction::FunctionMaker::make(Arguments inArgs) const {
  return defaultFunc.get().makeSelf(std::move(inArgs));
}

bool IFunction::FunctionMaker::doArgumentsMatch(const Arguments &inArgs) const noexcept {
  return IFunction::doArgumentsMatch(getDeclaration(), inArgs);
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

Shared<IMathObject> IFunction::unwrapp() const noexcept {
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

  assert(!decl.argumentClasses.empty());

  if (decl.name.empty()) {
    return;
  }

  detail::Tokenizer::registerToken(decl.name);

  FunctionMakers &makers = getNameToFunctionMakersMap()[decl.name];
  makers.emplace_back(cast<IFunction>(getDefaultObject()));
}

void IFunction::initSelf(Arguments inArgs) {
  const Declaration &decl = getDeclaration();
  validateArgumentsNonNull(inArgs);
  args = unwrappArguments(std::move(inArgs));
  validateArgumentsMatch(decl, args);
  args = compressArguments(decl, getClass(), std::move(args));
}

void IFunction::validateArgumentsNonNull(const Arguments &inArgs) {
  for (size_t i = 0; i < inArgs.size(); i++) {
    if (!inArgs[i]) {
      throw InvalidInputException(fmt::format(R"(Argument #{} is a null)", i));
    }
  }
}

void IFunction::validateArgumentsMatch(const Declaration &decl, const Arguments &inArgs) {
  if (!doArgumentsMatch(decl, inArgs)) {
    throw InvalidInputException("Invalid args"); // TODO
  }
}

bool IFunction::doArgumentsMatch(const Declaration &decl, const Arguments &inArgs) noexcept {
  return decl.isVariadic ? doArgumentsMatchVariadic(decl, inArgs)
                         : doArgumentsMatchNonVariadic(decl, inArgs);
}

bool IFunction::doArgumentsMatchNonVariadic(const Declaration &decl, const Arguments &inArgs) noexcept {
  if (decl.argumentClasses.size() != inArgs.size()) {
    return false;
  }

  for (size_t i = 0; i < inArgs.size(); i++) {
    if (!doesArgumentMatch(decl.argumentClasses[i], inArgs[i])) {
      return false;
    }
  }

  return true;
}

bool IFunction::doArgumentsMatchVariadic(const Declaration &decl, const Arguments &inArgs) noexcept {
  if (inArgs.empty()) {
    return false;
  }

  for (const auto &inArg : inArgs) {
    bool matchAny = false;
    for (const auto &declArgClass : decl.argumentClasses) {
      if (doesArgumentMatch(declArgClass, inArg)) {
        matchAny = true;
        break;
      }
    }

    if (!matchAny) {
      return false;
    }
  }

  return true;
}

bool fintamath::IFunction::doesArgumentMatch(MathObjectClass expectedClass, const Argument &inArg) noexcept {
  const MathObjectClass inArgClass = inArg->getClass();
  
  if (is(expectedClass, inArgClass)) {
    return true;
  }

  if (const auto inArgFunc = cast<IFunction>(inArg)) {
    return is(expectedClass, inArgFunc->getDeclaration().returnClass);
  }

  return false;
}

IFunction::Arguments IFunction::unwrappArguments(Arguments inArgs) noexcept {
  for (auto &arg : inArgs) {
    if (auto unwrappedArg = arg->unwrapp()) {
      arg = std::move(unwrappedArg);
    }
  }

  return inArgs;
}

IFunction::Arguments IFunction::compressArguments(const Declaration &decl, const MathObjectClass funcClass, Arguments inArgs) noexcept {
  if (!decl.isVariadic) {
    return inArgs;
  }

  Arguments outArgs;
  outArgs.reserve(inArgs.size());

  for (auto &arg : inArgs) {
    if (arg->getClass() == funcClass) {
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

IFunction::NameToFunctionMakersMap &IFunction::getNameToFunctionMakersMap() {
  static NameToFunctionMakersMap nameToFunctionMakerMap;
  return nameToFunctionMakerMap;
}

}
