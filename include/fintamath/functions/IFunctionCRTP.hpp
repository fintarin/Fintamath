#ifndef FINTAMATH_I_FUNCTION_CRTP

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

template <typename Return, typename Derived, typename... Args>
class IFunctionCRTP_ : public IFunction {

#endif // FINTAMATH_I_FUNCTION_CRTP

#define FINTAMATH_I_MATH_OBJECT_CRTP FINTAMATH_I_FUNCTION_CRTP
#include "fintamath/core/IMathObjectCRTP.hpp"
#undef FINTAMATH_I_MATH_OBJECT_CRTP

public:
  IFunction::Type getFunctionType() const final {
    return type;
  }

  MathObjectType getReturnType() const final {
    return Return::getTypeStatic();
  }

  ArgumentsTypesVector getArgsTypes() const final {
    ArgumentsTypesVector argsTypes;
    getArgsTypes<0, Args...>(argsTypes);
    return argsTypes;
  }

  bool doArgsMatch(const ArgumentsRefVector &argsVect) const override {
    if (argsVect.empty()) { // TODO: support None type functions
      return false;
    }

    if constexpr (IsFunctionTypeAny<Derived>::value) {
      return doAnyArgsMatch(argsVect);
    }
    else {
      if (argsVect.size() != size_t(getFunctionType())) {
        return false;
      }

      return doArgsMatch<0, Args...>(argsVect);
    }
  }

  bool isNonExressionEvaluatable() const final {
    return isNonExressionEvaluatableFunc;
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const = 0;

  std::unique_ptr<IMathObject> callAbstract(const ArgumentsRefVector &argsVect) const final {
    validateArgsSize(argsVect);

    if (doArgsMatch(argsVect)) {
      return call(argsVect);
    }

    return makeExprChecked(*this, argsVect);
  }

private:
  template <size_t i, typename Head, typename... Tail>
  void getArgsTypes(ArgumentsTypesVector &outArgsTypes) const {
    outArgsTypes.emplace_back(Head::getTypeStatic());
    getArgsTypes<i + 1, Tail...>(outArgsTypes);
  }

  template <size_t>
  void getArgsTypes(ArgumentsTypesVector & /*outArgTypes*/) const {
    // The end of unpacking.
  }

  template <size_t i, typename Head, typename... Tail>
  bool doArgsMatch(const ArgumentsRefVector &argsVect) const {
    if (!is<Head>(argsVect[i])) {
      return false;
    }

    return doArgsMatch<i + 1, Tail...>(argsVect);
  }

  template <size_t>
  bool doArgsMatch(const ArgumentsRefVector & /*unused*/) const {
    return true;
  }

  bool doAnyArgsMatch(const ArgumentsRefVector &argsVect) const {
    using AnyArgsType = typename std::tuple_element_t<0, std::tuple<Args...>>;

    return std::all_of(argsVect.begin(), argsVect.end(), [](const auto &arg) {
      return is<AnyArgsType>(arg);
    });
  }

  void validateArgsSize(const ArgumentsRefVector &argsVect) const {
    if constexpr (IsFunctionTypeAny<Derived>::value) {
      if (argsVect.empty()) {
        throwInvalidInputFunctionException(argsVect);
      }
    }
    else {
      if (argsVect.size() != sizeof...(Args)) {
        throwInvalidInputFunctionException(argsVect);
      }
    }
  }

  void throwInvalidInputFunctionException(const ArgumentsRefVector &argsVect) const {
    std::vector<std::string> argNamesVect(argsVect.size());

    for (size_t i = 0; i < argNamesVect.size(); i++) {
      argNamesVect[i] = argsVect[i].get().toString();
    }

    throw InvalidInputFunctionException(toString(), argNamesVect);
  }

private:
  IFunction::Type type;

  bool isNonExressionEvaluatableFunc;

private:
#ifndef FINTAMATH_I_FUNCTION_CRTP
};
}

#endif // FINTAMATH_I_FUNCTION_CRTP
