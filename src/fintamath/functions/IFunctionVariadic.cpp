#include "fintamath/functions/IFunctionVariadic.hpp"

#include <cctype>
#include <cstddef>
#include <string>

#include <fmt/format.h>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunctionVariadic)

std::string IFunctionVariadic::ArgumentStringData::join() && {
  delimiter += argumentString;
  return delimiter;
}

std::string IFunctionVariadic::toString() const noexcept {
  const IFunction::Declaration &selfDecl = getDeclaration();
  const Arguments &selfArgs = getArguments();

  std::string argsStr = getArgumentStringData(selfArgs.front(), nullptr).join();

  if (!selfDecl.operatorDeclaration) {
    for (size_t i = 1; i < selfArgs.size(); i++) {
      argsStr += getArgumentStringData(selfArgs[i], selfArgs[i - 1]).join();
    }

    return fmt::format("{}({})", selfDecl.name, argsStr);
  }

  for (size_t i = 1; i < selfArgs.size(); i++) {
    argsStr += getArgumentStringData(selfArgs[i], selfArgs[i - 1]).join();

    // TODO!!!
    // if (argStr.size() > 2 && argStr[0] == ' ' && std::isdigit(argStr[1]) && std::isdigit(argsStr.back())) {
    //   resStr += MulOper{}.toString() + childStr.substr(1);
    // }
  }

  return argsStr;
}

IFunctionVariadic::ArgumentStringData IFunctionVariadic::getArgumentStringData(const SharedRef<IMathObject> &arg, const SharedPtr<IMathObject> &prevArg) const {
  using detail::argumentToString;

  const IFunction::Declaration &decl = getDeclaration();

  std::string delimiter;
  if (prevArg) {
    if (decl.operatorDeclaration) {
      delimiter = fmt::format(" {} ", decl.name);
    }
    else {
      delimiter = ", ";
    }
  }

  std::string argStr = argumentToString(decl, arg);

  return {
    .delimiter = std::move(delimiter),
    .argumentString = std::move(argStr),
  };
}

IFunctionVariadic::SimplifyFunctions IFunctionVariadic::getFunctionsForPreSimplify() const {
  return {};
}

IFunctionVariadic::SimplifyFunctions IFunctionVariadic::getFunctionsForSimplify() const {
  return {};
}

SharedPtr<IMathObject> IFunctionVariadic::compressSelf() const {
  if (std::optional compressedArgs = compressArguments()) {
    return makeSelf(std::move(*compressedArgs));
  }
  return nullptr;
}

SharedPtr<IMathObject> IFunctionVariadic::preSimplifySelf() const {
  return nullptr;

  // using detail::useSimplifyFunctions;
  // return useSimplifyFunctions(getFunctionsForPreSimplify(), getArguments());
}

SharedPtr<IMathObject> IFunctionVariadic::simplifySelf() const {
  return nullptr;
  // using detail::useSimplifyFunctions;
  // return useSimplifyFunctions(getFunctionsForSimplify(), getArguments());
}

SharedPtr<IMathObject> IFunctionVariadic::unwrappSelf() const noexcept {
  const Arguments &selfArgs = getArguments();

  if (selfArgs.size() == 1) {
    return selfArgs.front();
  }

  return nullptr;
}

void IFunctionVariadic::registerDefaultObject() const {
  Super::registerDefaultObject();

  [[maybe_unused]] const auto &decl = getDeclaration();
  assert(decl.argumentClasses.size() == 1 && decl.isVariadic);
}

std::optional<IFunction::Arguments> IFunctionVariadic::compressArguments() const {
  const MathObjectClass selfClass = getClass();
  const Arguments &selfArgs = getArguments();
  size_t selfArgIndex = 0;
  std::optional<Arguments> outArgs;

  for (; selfArgIndex < selfArgs.size(); selfArgIndex++) {
    const SharedRef<IMathObject> &arg = selfArgs[selfArgIndex];

    if (is(selfClass, arg->getClass())) {
      outArgs = Arguments(
        selfArgs.begin(),
        selfArgs.begin() + static_cast<ptrdiff_t>(selfArgIndex)
      );

      appendVariadicFunctionArguments(castChecked<IFunction>(*arg), selfClass, *outArgs);

      break;
    }
  }

  if (!outArgs) {
    return outArgs;
  }

  selfArgIndex++;

  for (; selfArgIndex < selfArgs.size(); selfArgIndex++) {
    appendVariadicFunctionArgument(selfArgs[selfArgIndex], selfClass, *outArgs);
  }

  return outArgs;
}

// SharedRef<IMathObject> IFunctionVariadic::preSimplify() const {
//   auto simpl = cast<IFunctionVariadic>(clone());

//   simpl->simplifyChildren(false);
//   simpl->simplifyRec(false);

//   if (simpl->children.size() == 1) {
//     return simpl->children.front();
//   }

//   return simpl;
// }

// SharedRef<IMathObject> IFunctionVariadic::postSimplify() const {
//   auto simpl = cast<IFunctionVariadic>(clone());

//   simpl->simplifyChildren(true);
//   simpl->simplifyRec(true);

//   if (simpl->children.size() == 1) {
//     return simpl->children.front();
//   }

//   return simpl;
// }

// void IFunctionVariadic::simplifyRec(const bool isPostSimplify) {
//   compressSelf();
//   sort();

//   bool isExprSimplified = true;

//   // TODO: refactor this loop
//   for (size_t i = 1; i < children.size(); i++) {
//     const SharedRef<IMathObject> &lhs = children[i - 1];
//     const SharedRef<IMathObject> &rhs = children[i];

//     if (auto res = simplifyUndefined(*func, lhs, rhs)) {
//       children = {res};
//       break;
//     }

//     SharedRef<IMathObject> res = callFunction(*func, {lhs, rhs});
//     const bool isResSimplified = res != nullptr;

//     if (!res) {
//       res = isPostSimplify ? useSimplifyFunctions(getFunctionsForPostSimplify(), *func, children[i - 1], children[i])
//                            : useSimplifyFunctions(getFunctionsForPreSimplify(), *func, children[i - 1], children[i]);
//     }

//     if (!res) {
//       continue;
//     }

//     if (!isResSimplified) {
//       const SharedRef<IMathObject> prevExpr = makeExpr(*getFunction(), lhs, rhs);

//       if (isPostSimplify) {
//         postSimplifyChild(res);
//       }
//       else {
//         preSimplifyChild(res);
//       }

//       if (*prevExpr == *res) {
//         continue;
//       }
//     }

//     children.erase(children.begin() + static_cast<ptrdiff_t>(i) - 1);
//     children.erase(children.begin() + static_cast<ptrdiff_t>(i) - 1);
//     children.emplace_back(res);

//     i--;
//     isExprSimplified = false;
//   }

//   if (!isExprSimplified) {
//     simplifyRec(isPostSimplify);
//   }
// }

// void IFunctionVariadic::simplifyChildren(const bool isPostSimplify) {
//   Arguments oldChildren = children;

//   children.clear();

//   for (auto &child : oldChildren) {
//     if (isPostSimplify) {
//       postSimplifyChild(child);
//     }
//     else {
//       preSimplifyChild(child);
//     }

//     children.emplace_back(child);
//   }
// }

// IFunctionVariadic::SimplifyFunctionVector IFunctionVariadic::getFunctionsForPreSimplify() const {
//   return {};
// }

// IFunctionVariadic::SimplifyFunctionVector IFunctionVariadic::getFunctionsForPostSimplify() const {
//   return {};
// }

void IFunctionVariadic::appendVariadicFunctionArgument(const SharedRef<IMathObject> &arg, const MathObjectClass &selfClass, Arguments &outArgs) {
  if (is(selfClass, arg->getClass())) {
    appendVariadicFunctionArguments(castChecked<IFunction>(*arg), selfClass, outArgs);
  }
  else {
    outArgs.emplace_back(arg);
  }
}

void IFunctionVariadic::appendVariadicFunctionArguments(const IFunction &func, const MathObjectClass &selfClass, Arguments &outArgs) noexcept {
  const Arguments &args = func.getArguments();

  outArgs.reserve(outArgs.size() + args.size());

  for (const auto &arg : args) {
    appendVariadicFunctionArgument(arg, selfClass, outArgs);
  }
}

// bool IFunctionVariadic::isTermOrderInversed() const noexcept {
//   return false;
// }

// bool IFunctionVariadic::isComparableOrderInversed() const noexcept {
//   return false;
// }

// std::strong_ordering IFunctionVariadic::compare(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) const {
//   const ComparatorOptions options = {
//       .termOrderInversed = isTermOrderInversed(),
//       .comparableOrderInversed = isComparableOrderInversed(),
//   };
//   return fintamath::compare(lhs, rhs, options);
// }

// void IFunctionVariadic::sort() {
//   std::ranges::stable_sort(children, [this](const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) {
//     return compare(lhs, rhs) == std::strong_ordering::greater;
//   });
// }
}
