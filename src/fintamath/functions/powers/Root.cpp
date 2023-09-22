#include "fintamath/functions/powers/Root.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/I.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Root::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<INumber>(argsVect.front().get());
  const auto &rhs = cast<INumber>(argsVect.back().get());

  if (lhs == Integer(1) || rhs == Integer(1)) {
    return lhs.clone();
  }

  if (const auto *rhsIntPtr = cast<Integer>(&rhs)) {
    const auto &rhsInt = *rhsIntPtr;

    if (!lhs.isComplex() && lhs < Integer(0)) {
      if (rhsInt == Integer(2)) {
        return mulExpr(multiRootSimplify(*(-lhs), rhsInt), I()())->toMinimalObject();
      }

      // TODO: complex nth roots
      return {};
    }

    return multiRootSimplify(lhs, rhsInt);
  }

  return Pow()(lhs, *(Rational(1) / rhs));
}

std::unique_ptr<IMathObject> Root::multiRootSimplify(const INumber &lhs, const INumber &rhs) {
  static const auto multiRoot = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const INumber &)> outMultiRoot;

    outMultiRoot.add<Integer, Integer>([](const Integer &inLhs, const Integer &inRhs) {
      return rootSimplify(inLhs, inRhs);
    });

    outMultiRoot.add<Rational, Integer>([](const Rational &inLhs, const Integer &inRhs) {
      return rootSimplify(inLhs, inRhs);
    });

    outMultiRoot.add<Real, Integer>([](const Real &inLhs, const Integer &inRhs) {
      return rootSimplify(inLhs, inRhs);
    });

    return outMultiRoot;
  }();

  return multiRoot(lhs, rhs);
}

std::unique_ptr<IMathObject> Root::rootSimplify(const Integer &lhs, const Integer &rhs) {
  if (auto res = perfectRoot(lhs, rhs)) {
    return res;
  }

  ArgumentsPtrVector mulChildren;

  std::map<Integer, Integer> rootFactors = roots(lhs, rhs);

  if (rootFactors.begin()->first == 1) {
    if (rootFactors.begin()->second != 1) {
      mulChildren.emplace_back(rootFactors.begin()->second.clone());
    }

    rootFactors.erase(rootFactors.begin());
  }

  for (auto [root, factor] : rootFactors) {
    if (factor != 1) {
      mulChildren.emplace_back(rootExpr(factor, root));
    }
  }

  if (mulChildren.size() == 1) {
    return mulChildren.front()->clone();
  }

  return mulExpr(mulChildren);
}

std::map<Integer, Integer> Root::roots(const Integer &lhs, const Integer &rhs) {
  static Integer factorLimit = pow(Integer(2), 15);

  std::map<Integer, Integer> rootFactors{{1, 1}};
  std::map<Integer, Integer> factorRates = factors(lhs, factorLimit);

  for (const auto &factorRate : factorRates) {
    Rational power(factorRate.second, rhs);
    Integer factor = factorRate.first;

    if (power.denominator() == 1) {
      rootFactors[1] *= pow(factor, power.numerator());
      continue;
    }

    if (power.numerator() > power.denominator()) {
      rootFactors[1] *= pow(factor, power.numerator() / power.denominator());
    }

    factor = pow(factor, power.numerator() % power.denominator());

    if (auto rootIter = rootFactors.find(power.denominator()); rootIter != rootFactors.end()) {
      rootIter->second *= factor;
    }
    else {
      rootFactors.try_emplace(power.denominator(), factor);
    }
  }

  return rootFactors;
}

std::unique_ptr<IMathObject> Root::perfectRoot(const Integer &lhs, const Integer &rhs) {
  if (lhs == 1) {
    return lhs.clone();
  }

  if (rhs == 2) { // TODO: perfect nth-roots
    Integer remainder;
    Integer lhsSqrt = sqrt(lhs, remainder);

    if (remainder == 0) {
      return lhsSqrt.clone();
    }
  }

  return {};
}

std::unique_ptr<IMathObject> Root::rootSimplify(const Rational &lhs, const Integer &rhs) {
  if (lhs.denominator() == 1) {
    return Root()(lhs.numerator(), rhs);
  }

  if (ArgumentPtr numeratorRes = perfectRoot(lhs.numerator(), rhs)) {
    if (ArgumentPtr denominatorRes = perfectRoot(lhs.denominator(), rhs)) {
      return Rational(cast<Integer>(*numeratorRes), cast<Integer>(*denominatorRes)).toMinimalObject();
    }

    ArgumentPtr denominatorRes = Root()(lhs.denominator(), rhs);
    return divExpr(numeratorRes, denominatorRes);
  }

  if (ArgumentPtr denominatorRes = perfectRoot(lhs.denominator(), rhs)) {
    return divExpr(Root()(lhs.numerator(), rhs), denominatorRes);
  }

  ArgumentsPtrVector numeratorChildren;
  Rational denominator = 1;

  std::map<Integer, Integer> numeratorRootFactors = roots(lhs.numerator(), rhs);
  std::map<Integer, Integer> denominatorRootFactors = roots(lhs.denominator(), rhs);

  if (numeratorRootFactors.begin()->first == 1) {
    if (numeratorRootFactors.begin()->second != 1) {
      numeratorChildren.emplace_back(numeratorRootFactors.begin()->second.clone());
    }

    numeratorRootFactors.erase(numeratorRootFactors.begin());
  }

  if (denominatorRootFactors.begin()->first == 1) {
    if (denominatorRootFactors.begin()->second != 1) {
      denominator *= denominatorRootFactors.begin()->second;
    }

    denominatorRootFactors.erase(denominatorRootFactors.begin());
  }

  for (auto [root, numeratorFactor] : numeratorRootFactors) {
    if (const auto denominatorFactorIter = denominatorRootFactors.find(root);
        denominatorFactorIter != denominatorRootFactors.end()) {

      Integer denominatorFactor = denominatorFactorIter->second;

      denominatorRootFactors.erase(denominatorFactorIter);

      if (denominatorFactor != 1) {
        denominator *= denominatorFactor;

        Integer numeratorChild = numeratorFactor * pow(denominatorFactor, root - 1);
        numeratorChildren.emplace_back(rootExpr(numeratorChild, root));

        continue;
      }
    }

    if (numeratorFactor != 1) {
      numeratorChildren.emplace_back(rootExpr(numeratorFactor, root));
    }
  }

  for (const auto &[root, denominatorFactor] : denominatorRootFactors) {
    if (denominatorFactor != 1) {
      denominator *= denominatorFactor;

      Integer numeratorChild = pow(denominatorFactor, root - 1);
      numeratorChildren.emplace_back(rootExpr(numeratorChild, root));
    }
  }

  ArgumentPtr numerator;
  if (numeratorChildren.size() == 1) {
    numerator = numeratorChildren.front();
  }
  else {
    numerator = mulExpr(numeratorChildren);
  }

  return divExpr(numerator, denominator.toMinimalObject());
}

std::unique_ptr<IMathObject> Root::rootSimplify(const Real &lhs, const Integer &rhs) {
  return Pow()(lhs, Rational(1, rhs));
}

}
