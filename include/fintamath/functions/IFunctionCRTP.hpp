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
  static constexpr auto getArgumentClassesStatic() noexcept {
    return std::array{Args::getClassStatic()...};
  }

  const std::vector<MathObjectClass> &getArgumentClasses() const noexcept final {
    constexpr auto argClassesArr = getArgumentClassesStatic();
    static const std::vector<MathObjectClass> argClassesVect(argClassesArr.begin(), argClassesArr.end());
    return argClassesVect;
  }

  static constexpr MathObjectClass getReturnClassStatic() noexcept {
    return Return::getClassStatic();
  }

  MathObjectClass getReturnClass() const noexcept final {
    return getReturnClassStatic();
  }

  bool doArgsMatch(const ArgumentRefVector &argVect) const override {
    if constexpr (Derived::isVariadicStatic()) {
      return doVariadicArgsMatch(argVect);
    }
    else {
      if (argVect.size() != getArgumentClassesStatic().size()) {
        return false;
      }

      return doArgsMatch<0, Args...>(argVect);
    }
  }

  bool isVariadic() const final {
    return Derived::isVariadicStatic();
  }

  static constexpr bool isVariadicStatic() {
    return false;
  }

  bool isEvaluatable() const final {
    return Derived::isEvaluatableStatic();
  }

  static constexpr bool isEvaluatableStatic() {
    return true;
  }

protected:
  virtual std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const = 0;

  std::unique_ptr<IMathObject> callAbstract(const ArgumentRefVector &argVect) const override {
    if (doArgsMatch(argVect)) {
      try {
        if (auto res = call(argVect)) {
          return res;
        }

        return detail::makeExpr(*this, argVect);
      }
      catch (const UndefinedException &) {
        return detail::makeExpr(*this, argVect);
      }
    }

    return detail::makeExpr(*this, argVect)->toMinimalObject();
  }

private:
  template <size_t i, typename Head, typename... Tail>
  static bool doArgsMatch(const ArgumentRefVector &argVect) {
    if (!doArgMatch<Head>(argVect[i])) {
      return false;
    }

    return doArgsMatch<i + 1, Tail...>(argVect);
  }

  template <size_t>
  static bool doArgsMatch(const ArgumentRefVector &) {
    return true;
  }

  static bool doVariadicArgsMatch(const ArgumentRefVector &argVect) {
    if (argVect.empty()) {
      return false;
    }

    using ExpectedArg = typename std::tuple_element_t<0, std::tuple<Args...>>;

    return std::ranges::all_of(argVect, [](const auto &arg) {
      return doArgMatch<ExpectedArg>(arg);
    });
  }

  template <typename Expected>
  static bool doArgMatch(const ArgumentRef &arg) {
    return is<Expected>(arg);
  }

private:
#if !defined(I_FUNCTION_CRTP) && !defined(NDEBUG)
};
}

#endif // I_FUNCTION_CRTP
