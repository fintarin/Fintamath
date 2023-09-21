#if !defined(I_MATH_OBJECT_CRTP) && !defined(NDEBUG)

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

template <typename Derived>
class IMathObjectCRTP_ : public IMathObject {

#endif // I_MATH_OBJECT_CRTP

public:
  std::unique_ptr<IMathObject> clone() const & final {
    return std::make_unique<Derived>(cast<Derived>(*this));
  }

  std::unique_ptr<IMathObject> clone() && final {
    return std::make_unique<Derived>(std::move(cast<Derived>(*this)));
  }

  bool operator==(const I_MATH_OBJECT_CRTP &rhs) const {
    return equals(cast<Derived>(rhs));
  }

  MathObjectType getType() const override {
    return Derived::getTypeStatic();
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
#if !defined(I_MATH_OBJECT_CRTP) && !defined(NDEBUG)
};
}

#endif // I_MATH_OBJECT_CRTP
