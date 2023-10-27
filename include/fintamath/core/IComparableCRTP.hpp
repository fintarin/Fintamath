#if !defined(I_COMPARABLE_CRTP) && !defined(NDEBUG)

#include "fintamath/core/IComparable.hpp"

namespace fintamath {

template <typename Derived>
class IComparableCRTP_ : public IComparable {

#endif // I_COMPARABLE_CRTP

#define I_ARITHMETIC_CRTP I_COMPARABLE_CRTP
#include "fintamath/core/IArithmeticCRTP.hpp"
#undef I_ARITHMETIC_CRTP

public:
  std::strong_ordering operator<=>(const I_COMPARABLE_CRTP &rhs) const {
    return compare(cast<Derived>(rhs));
  }

protected:
  virtual std::strong_ordering compare(const Derived &rhs) const = 0;

  std::strong_ordering compareAbstract(const IComparable &rhs) const override {
    if (const auto *rhsPtr = cast<Derived>(&rhs)) {
      return compare(*rhsPtr);
    }

    if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
      return compare(cast<Derived>(*rhsPtr));
    }

    if (isConvertible(rhs, *this)) {
      return 0 <=> (rhs <=> *this);
    }

    throw InvalidInputBinaryOperatorException("<=>", toString(), rhs.toString());
  }

private:
#if !defined(I_COMPARABLE_CRTP) && !defined(NDEBUG)
};
}

#endif // I_COMPARABLE_CRTP
