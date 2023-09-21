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
  std::strong_ordering operator<=>(const FINTAMATH_I_COMPARABLE_CRTP &rhs) const {
    return compare(cast<Derived>(rhs));
  }

protected:
  virtual std::strong_ordering compare(const Derived &rhs) const = 0;

  std::strong_ordering compareAbstract(const IComparable &rhs) const final {
    if (const auto *rhsPtr = cast<Derived>(&rhs)) {
      return compare(*rhsPtr);
    }

    if constexpr (IsConvertible<Derived>::value) {
      if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
        return compare(cast<Derived>(*rhsPtr));
      }

      if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this)) {
        return cast<IComparable>(*lhsPtr) <=> rhs;
      }
    }

    throw InvalidInputBinaryOperatorException("<=>", toString(), rhs.toString());
  }

private:
#if !defined(FINTAMATH_I_COMPARABLE_CRTP) && !defined(NDEBUG)
};
}

#endif // FINTAMATH_I_COMPARABLE_CRTP
