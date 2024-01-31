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

  size_t getFunctionOrder() const final {
    static const std::string funcStr = Derived().toString();
    return getFunctionOrderMap().at(funcStr);
  }

  bool doArgsMatch(const ArgumentRefVector &argVect) const override {
    if (argVect.empty()) { // TODO: support None type functions
      return false;
    }

    if constexpr (IsFunctionTypeAny<Derived>::value) {
      return doAnyArgsMatch(argVect);
    }
    else {
      if (argVect.size() != size_t(getFunctionType())) {
        return false;
      }

      return doArgsMatch<0, Args...>(argVect);
    }
  }

  bool isEvaluatable() const final {
    return isEvaluatableFunc;
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const = 0;

  std::unique_ptr<IMathObject> callAbstract(const ArgumentRefVector &argVect) const override {
    validateArgsSize(argVect);

    if (doArgsMatch(argVect)) {
      try {
        if (auto res = call(argVect)) {
          return res;
        }

        return makeExpr(*this, argVect);
      }
      catch (const UndefinedException &) {
        return makeExpr(*this, argVect);
      }
    }

    return makeExpr(*this, argVect)->toMinimalObject();
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
  bool doArgsMatch(const ArgumentRefVector &argVect) const {
    if (!is<Head>(argVect[i]) || isExpression(argVect[i])) {
      return false;
    }

    return doArgsMatch<i + 1, Tail...>(argVect);
  }

  template <size_t>
  bool doArgsMatch(const ArgumentRefVector & /*unused*/) const {
    return true;
  }

  bool doAnyArgsMatch(const ArgumentRefVector &argVect) const {
    using AnyArgsType = typename std::tuple_element_t<0, std::tuple<Args...>>;

    return stdr::all_of(argVect, [](const auto &arg) {
      return is<AnyArgsType>(arg);
    });
  }

  void validateArgsSize(const ArgumentRefVector &argVect) const {
    if constexpr (IsFunctionTypeAny<Derived>::value) {
      if (argVect.empty()) {
        throwInvalidInputFunctionException(argVect);
      }
    }
    else {
      if (argVect.size() != sizeof...(Args)) {
        throwInvalidInputFunctionException(argVect);
      }
    }
  }

  void throwInvalidInputFunctionException(const ArgumentRefVector &argVect) const {
    std::vector<std::string> argNameVect(argVect.size());

    for (const auto i : stdv::iota(0U, argNameVect.size())) {
      argNameVect[i] = argVect[i].get().toString();
    }

    throw InvalidInputFunctionException(toString(), argNameVect);
  }

private:
  IFunction::Type type;

  bool isEvaluatableFunc;

private:
#if !defined(I_FUNCTION_CRTP) && !defined(NDEBUG)
};
}

#endif // I_FUNCTION_CRTP
