#if !defined(I_FUNCTION_CRTP) && !defined(NDEBUG)

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

template <typename Return, typename Derived, typename... Args>
class IFunctionCRTP_ : public IFunction {

#endif // I_FUNCTION_CRTP

#define I_MATH_OBJECT_CRTP I_FUNCTION_CRTP
#include "fintamath/core/IMathObjectCRTP.hpp"
#undef I_MATH_OBJECT_CRTP

public:
  IFunction::Type getFunctionType() const final {
    return type;
  }

  MathObjectType getReturnType() const final {
    return Return::getTypeStatic();
  }

  ArgumentTypeVector getArgTypes() const final {
    ArgumentTypeVector argTypes;
    getArgTypes<0, Args...>(argTypes);
    return argTypes;
  }

  bool doArgsMatch(const ArgumentRefVector &argsVect) const override {
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

  bool isEvaluatable() const final {
    return isEvaluatableFunc;
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const = 0;

  std::unique_ptr<IMathObject> callAbstract(const ArgumentRefVector &argsVect) const final {
    validateArgsSize(argsVect);

    if (doArgsMatch(argsVect)) {
      try {
        if (auto res = call(argsVect)) {
          return res;
        }

        return makeExpr(*this, argsVect);
      }
      catch (const UndefinedException &) {
        return makeExpr(*this, argsVect);
      }
    }

    return makeExpr(*this, argsVect)->toMinimalObject();
  }

private:
  template <size_t i, typename Head, typename... Tail>
  void getArgTypes(ArgumentTypeVector &outArgsTypes) const {
    outArgsTypes.emplace_back(Head::getTypeStatic());
    getArgTypes<i + 1, Tail...>(outArgsTypes);
  }

  template <size_t>
  void getArgTypes(ArgumentTypeVector & /*outArgTypes*/) const {
    // The end of unpacking.
  }

  template <size_t i, typename Head, typename... Tail>
  bool doArgsMatch(const ArgumentRefVector &argsVect) const {
    if (!is<Head>(argsVect[i]) || isExpression(argsVect[i])) {
      return false;
    }

    return doArgsMatch<i + 1, Tail...>(argsVect);
  }

  template <size_t>
  bool doArgsMatch(const ArgumentRefVector & /*unused*/) const {
    return true;
  }

  bool doAnyArgsMatch(const ArgumentRefVector &argsVect) const {
    using AnyArgsType = typename std::tuple_element_t<0, std::tuple<Args...>>;

    return std::ranges::all_of(argsVect, [](const auto &arg) {
      return is<AnyArgsType>(arg);
    });
  }

  void validateArgsSize(const ArgumentRefVector &argsVect) const {
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

  void throwInvalidInputFunctionException(const ArgumentRefVector &argsVect) const {
    std::vector<std::string> argNamesVect(argsVect.size());

    for (auto i : std::views::iota(0U, argNamesVect.size())) {
      argNamesVect[i] = argsVect[i].get().toString();
    }

    throw InvalidInputFunctionException(toString(), argNamesVect);
  }

private:
  IFunction::Type type;

  bool isEvaluatableFunc;

private:
#if !defined(I_FUNCTION_CRTP) && !defined(NDEBUG)
};
}

#endif // I_FUNCTION_CRTP
