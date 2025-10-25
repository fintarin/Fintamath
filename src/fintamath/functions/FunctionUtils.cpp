#include "fintamath/functions/FunctionUtils.hpp"

#include <fmt/format.h>
#include <string>

#include "fintamath/constants/ComplexInf.hpp"
#include "fintamath/constants/Inf.hpp"
#include "fintamath/constants/NegInf.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath::detail {

bool isInfinity(const SharedRef<IMathObject> &arg) {
  return is<Inf>(arg) || is<NegInf>(arg) || is<ComplexInf>(arg);
}

// bool isMulInfinity(const SharedRef<IMathObject> &arg) {
//   auto [rate, value] = splitMulExpr(arg);
//   return isInfinity(rate) || isInfinity(value);
// }

// bool isNegated(const SharedRef<IMathObject> &arg) {
//   if (isNumberNegated(arg)) {
//     return true;
//   }

//   const auto expr = cast<IExpression>(arg);
//   if (!expr) {
//     return false;
//   }

//   if (is<Add>(expr->getFunction()) || is<Div>(expr->getFunction())) {
//     return isNegated(expr->getChildren().front());
//   }

//   if (is<Mul>(expr->getFunction())) {
//     return isNumberNegated(expr->getChildren().front());
//   }

//   return false;
// }

bool isNumberNegated(const SharedRef<IMathObject> &arg) {
  // TODO!!! move to INumber

  if (const auto argComplex = cast<Complex>(arg)) {
    const auto &re = argComplex->real();
    const auto &im = argComplex->real();
    return re->isZero() ? isNumberNegated(im) : isNumberNegated(re);
  }

  const auto argNum = cast<INumber>(arg);
  return argNum && less(argNum.toRef(), Integer::getZero());
}

bool isComplexNumber(const SharedRef<IMathObject> &arg) {
  const auto num = cast<INumber>(arg);
  return num && num->isComplex();
}

// bool containsIf(const SharedRef<IMathObject> &arg, const std::function<bool(const SharedRef<IMathObject> &)> &comp) {
//   if (comp(arg)) {
//     return true;
//   }

//   const auto expr = cast<IExpression>(arg);
//   if (!expr) {
//     return false;
//   }

//   const Arguments &children = expr->getChildren();

//   return std::ranges::any_of(children, [&comp](const auto &child) {
//     bool res = false;

//     if (containsIf(child, comp)) {
//       res = true;
//     }

//     return res;
//   });
// }

// bool containsChild(const SharedRef<IMathObject> &arg, const SharedRef<IMathObject> &child) {
//   return containsIf(arg, [&child](const SharedRef<IMathObject> &compArg) {
//     return *compArg == *child;
//   });
// }

// bool containsVariable(const SharedRef<IMathObject> &arg) {
//   return containsIf(arg, [](const SharedRef<IMathObject> &compArg) {
//     return is<Variable>(compArg);
//   });
// }

// bool containsVariable(const SharedRef<IMathObject> &arg, const Variable &var) {
//   return containsIf(arg, [&var](const SharedRef<IMathObject> &compArg) {
//     return *compArg == var;
//   });
// }

// bool containsInfinity(const SharedRef<IMathObject> &arg) {
//   return containsIf(arg, [](const SharedRef<IMathObject> &compArg) {
//     return isInfinity(compArg);
//   });
// }

// bool containsComplex(const SharedRef<IMathObject> &arg) {
//   return containsIf(arg, [](const SharedRef<IMathObject> &compArg) {
//     return isComplexNumber(compArg);
//   });
// }

// std::pair<SharedRef<IMathObject>, SharedRef<IMathObject>> splitMulExpr(const SharedRef<IMathObject> &inChild, const bool checkVariables) {
//   const auto mulExprChild = cast<IExpression>(inChild);

//   if (!mulExprChild || !is<Mul>(mulExprChild->getFunction())) {
//     return {one, inChild};
//   }

//   const Arguments &mulExprChildren = mulExprChild->getChildren();
//   size_t i = 0;

//   if (checkVariables) {
//     for (; i < mulExprChildren.size(); i++) {
//       if (containsVariable(mulExprChildren[i])) {
//         break;
//       }
//     }
//   }
//   else {
//     for (; i < mulExprChildren.size(); i++) {
//       if (!is<INumber>(mulExprChildren[i])) {
//         break;
//       }
//     }
//   }

//   if (i == 0) {
//     return {one, inChild};
//   }

//   if (i >= mulExprChildren.size()) {
//     return {inChild, one};
//   }

//   SharedRef<IMathObject> rate = mulExpr(Arguments(mulExprChildren.begin(), mulExprChildren.begin() + static_cast<ptrdiff_t>(i)));
//   SharedRef<IMathObject> value = mulExpr(Arguments(mulExprChildren.begin() + static_cast<ptrdiff_t>(i), mulExprChildren.end()));
//   return {rate, value};
// }

// std::pair<SharedRef<IMathObject>, SharedRef<IMathObject>> splitPowExpr(const SharedRef<IMathObject> &rhs) {
//   if (const auto &powExpr = cast<IExpression>(rhs); powExpr && is<Pow>(powExpr->getFunction())) {
//     const Arguments &powExprChildren = powExpr->getChildren();
//     return {powExprChildren[0], powExprChildren[1]};
//   }

//   return {rhs, one};
// }

// std::pair<SharedRef<IMathObject>, SharedRef<IMathObject>> splitRational(const SharedRef<IMathObject> &arg) {
//   if (const auto rat = cast<Rational>(arg)) {
//     return {rat->numerator().clone(), rat->denominator().clone()};
//   }

//   if (const auto complex = cast<Complex>(arg)) {
//     SharedRef<IMathObject> reNumerator;
//     SharedRef<IMathObject> imNumerator;
//     Integer denominator = 1;

//     const auto *reRat = cast<Rational>(&complex->real());
//     const auto *imRat = cast<Rational>(&complex->imag());

//     if (reRat && imRat) {
//       denominator = lcm(reRat->denominator(), imRat->denominator());
//       reNumerator = (denominator / reRat->denominator() * reRat->numerator()).clone();
//       imNumerator = (denominator / imRat->denominator() * imRat->numerator()).clone();
//     }
//     else if (reRat) {
//       denominator = reRat->denominator();
//       reNumerator = reRat->numerator().clone();
//       imNumerator = complex->imag() * denominator;
//     }
//     else if (imRat) {
//       denominator = imRat->denominator();
//       reNumerator = complex->real() * denominator;
//       imNumerator = imRat->numerator().clone();
//     }

//     const auto reNumeratorNum = cast<INumber>(reNumerator);
//     const auto imNumeratorNum = cast<INumber>(imNumerator);

//     if (denominator != 1 && reNumeratorNum && imNumeratorNum) {
//       return {Complex(*reNumeratorNum, *imNumeratorNum).clone(), denominator.clone()};
//     }
//   }

//   return {arg, Integer(1).clone()};
// }

// SharedRef<IMathObject> negate(const SharedRef<IMathObject> &arg) {
//   if (const auto expr = cast<IExpression>(arg)) {
//     if (is<Add>(expr->getFunction())) {
//       Arguments negChildren = expr->getChildren();
//       std::ranges::transform(negChildren, negChildren.begin(), &negate);
//       return addExpr(std::move(negChildren));
//     }

//     if (is<Mul>(expr->getFunction())) {
//       if (const auto firstChildNum = cast<INumber>(expr->getChildren().front())) {
//         if (*firstChildNum == Integer(-1)) {
//           Arguments negChildren(expr->getChildren().begin() + 1, expr->getChildren().end());
//           return mulExpr(std::move(negChildren));
//         }

//         Arguments negChildren = expr->getChildren();
//         negChildren.front() = (*firstChildNum) * Integer(-1);
//         return mulExpr(std::move(negChildren));
//       }
//     }
//   }
//   else if (const auto arithm = cast<IArithmetic>(arg)) {
//     return (*arithm) * Integer(-1);
//   }

//   return mulExpr(Integer(-1).clone(), arg);
// }

// SharedRef<IMathObject> invert(const SharedRef<IMathObject> &arg) {
//   if (const auto num = cast<INumber>(arg)) {
//     return Integer(1) / (*num);
//   }

//   if (const auto expr = cast<IExpression>(arg); expr && is<Div>(expr->getFunction())) {
//     if (*expr->getChildren().front() == Integer(1)) {
//       return expr->getChildren().back();
//     }

//     return divExpr(expr->getChildren().back(), expr->getChildren().front());
//   }

//   return divExpr(Integer(1).clone(), arg);
// }

// Arguments getPolynomChildren(const IFunction &func, const SharedRef<IMathObject> &arg) {
//   if (const auto expr = cast<IExpression>(arg); expr && *expr->getFunction() == func) {
//     return expr->getChildren();
//   }

//   return {arg};
// }

namespace {

struct ArgumentOperatorData {
  size_t argsCount;
  OperatorPriority priority;
};

std::optional<ArgumentOperatorData> getArgumentOperatorData(const SharedRef<IMathObject> &arg, const std::string_view argStr) {
  if (const auto childFunc = cast<IFunction>(arg)) {
    const IFunction::Declaration &decl = childFunc->getDeclaration();
    if (!decl.operatorDeclaration) {
      return std::nullopt;
    }

    return ArgumentOperatorData{
      .argsCount = decl.argClasses.size(),
      .priority = decl.operatorDeclaration->priority,
    };
  }

  if (argStr.starts_with('+') || argStr.starts_with('-')) {
    // Negation or UnaryPlus
    return ArgumentOperatorData{
      .argsCount = 1,
      .priority = OperatorPriority::PrefixUnary,
    };
  }

  std::optional<ArgumentOperatorData> argOperData;

  for (size_t i = 1; i < argStr.size(); i++) {
    if (argStr[i] == '+' || argStr[i] == '-') {
      // Add or Sub
      argOperData = {
        .argsCount = 2,
        .priority = OperatorPriority::Addition,
      };
      break;
    }

    if (argStr[i] == '*' || argStr[i] == '/') {
      // Mul or Div
      argOperData = {
        .argsCount = 2,
        .priority = OperatorPriority::Multiplication,
      };
    }
  }

  return argOperData;
}

}

std::string argumentToString(const IFunction::Declaration &decl, const SharedRef<IMathObject> &arg) noexcept {
  std::string argStr = arg->toString();

  const auto &operDecl = decl.operatorDeclaration;
  if (!operDecl) {
    return argStr;
  }

  std::optional<ArgumentOperatorData> argOperData = getArgumentOperatorData(arg, argStr);
  if (!argOperData) {
    return argStr;
  }

  bool shouldPutInBrackets = false;

  switch (argOperData->priority) {
    case OperatorPriority::PrefixUnary: {
      shouldPutInBrackets = argOperData->priority >= operDecl->priority;
      break;
    }
    case OperatorPriority::PostfixUnary: {
      shouldPutInBrackets = true;
      break;
    }
    default: {
      shouldPutInBrackets = argOperData->priority > operDecl->priority || !operDecl->isAssociative;
    }
  }

  if (shouldPutInBrackets) {
    return fmt::format("({})", argStr);
  }

  return argStr;
}

}
