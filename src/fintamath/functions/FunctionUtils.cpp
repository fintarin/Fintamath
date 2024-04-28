#include "fintamath/functions/FunctionUtils.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> detail::makeExpr(const IFunction &func, const ArgumentRefVector &args) {
  return makeExpr(func, argumentRefVectorToArgumentPtrVector(args));
}

std::unique_ptr<IMathObject> detail::makeExprWithValidation(const IFunction &func, const ArgumentRefVector &args) {
  return makeExprWithValidation(func, argumentRefVectorToArgumentPtrVector(args));
}

ArgumentPtrVector detail::argumentRefVectorToArgumentPtrVector(const ArgumentRefVector &args) {
  ArgumentPtrVector argsPtrVect;

  for (const auto &arg : args) {
    argsPtrVect.emplace_back(arg.get().clone());
  }

  return argsPtrVect;
}

}
