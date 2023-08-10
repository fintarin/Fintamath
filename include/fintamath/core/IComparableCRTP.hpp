#if !defined(FINTAMATH_I_COMPARABLE_CRTP) && !defined(NDEBUG)

#include "fintamath/core/IComparable.hpp"

namespace fintamath {

template <typename Derived>
class IComparableCRTP_ : public IComparable {

#endif // FINTAMATH_I_COMPARABLE_CRTP

#define FINTAMATH_I_ARITHMETIC_CRTP FINTAMATH_I_COMPARABLE_CRTP
#include "fintamath/core/IArithmeticCRTP.hpp"
#undef FINTAMATH_I_ARITHMETIC_CRTP

public:
  bool operator<(const Derived &rhs) const {
    return less(rhs);
  }

  bool operator>(const Derived &rhs) const {
    return more(rhs);
  }

  bool operator<=(const Derived &rhs) const {
    return !more(rhs);
  }

  bool operator>=(const Derived &rhs) const {
    return !less(rhs);
  }

protected:
  virtual bool less(const Derived &rhs) const = 0;

  virtual bool more(const Derived &rhs) const = 0;

  bool lessAbstract(const IComparable &inRhs) const final {
    return executeAbstract(
        inRhs, "<",
        [](const FINTAMATH_I_COMPARABLE_CRTP &lhs, const Derived &rhs) {
          return lhs.less(rhs);
        },
        [](const IComparable &lhs, const IComparable &rhs) {
          return lhs < rhs;
        });
  }

  bool moreAbstract(const IComparable &inRhs) const final {
    return executeAbstract(
        inRhs, ">",
        [](const FINTAMATH_I_COMPARABLE_CRTP &lhs, const Derived &rhs) {
          return lhs.more(rhs);
        },
        [](const IComparable &lhs, const IComparable &rhs) {
          return lhs > rhs;
        });
  }

private:
  template <typename FunctionCommonTypes, typename FunctionDifferentTypes>
  bool executeAbstract(const IComparable &rhs,
                       const std::string &oper,
                       FunctionCommonTypes &&funcCommonTypes,
                       FunctionDifferentTypes &&funcDifferentTypes) const {

    if (const auto *rhsPtr = cast<Derived>(&rhs)) {
      return funcCommonTypes(*this, *rhsPtr);
    }

    if constexpr (IsConvertible<Derived>::value) {
      if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
        return funcCommonTypes(*this, cast<Derived>(*rhsPtr));
      }

      if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this)) {
        return funcDifferentTypes(cast<IComparable>(*lhsPtr), rhs);
      }
    }

    throw InvalidInputBinaryOperatorException(oper, toString(), rhs.toString());
  }

private:
#if !defined(FINTAMATH_I_COMPARABLE_CRTP) && !defined(NDEBUG)
};
}

#endif // FINTAMATH_I_COMPARABLE_CRTP
