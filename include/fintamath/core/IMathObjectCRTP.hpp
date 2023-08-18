#if !defined(FINTAMATH_I_MATH_OBJECT_CRTP) && !defined(NDEBUG)

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

template <typename Derived>
class IMathObjectCRTP_ : public IMathObject {

#endif // FINTAMATH_I_MATH_OBJECT_CRTP

public:
  std::unique_ptr<IMathObject> clone() const & final {
    return std::make_unique<Derived>(cast<Derived>(*this));
  }

  std::unique_ptr<IMathObject> clone() && final {
    return std::make_unique<Derived>(std::move(cast<Derived>(*this)));
  }

  bool operator==(const Derived &rhs) const {
    return equals(rhs);
  }

  bool operator!=(const Derived &rhs) const {
    return !equals(rhs);
  }

  MathObjectTypeId getTypeId() const override {
    return Derived::getTypeIdStatic();
  }

protected:
  virtual bool equals(const Derived &rhs) const {
    return toString() == rhs.toString();
  }

  bool equalsAbstract(const IMathObject &rhs) const final {
    if (const auto *rhsPtr = cast<Derived>(&rhs)) {
      return equals(*rhsPtr);
    }

    if constexpr (IsConvertible<Derived>::value) {
      if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
        return equals(cast<Derived>(*rhsPtr));
      }

      if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this)) {
        return *lhsPtr == rhs;
      }
    }

    return false;
  }

private:
#if !defined(FINTAMATH_I_MATH_OBJECT_CRTP) && !defined(NDEBUG)
};
}

#endif // FINTAMATH_I_MATH_OBJECT_CRTP
