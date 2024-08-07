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
    if (this == &rhs) {
      return true;
    }

    return equals(cast<Derived>(rhs));
  }

  MathObjectClass getClass() const noexcept override {
    return Derived::getClassStatic();
  }

protected:
  virtual bool equals(const Derived &rhs) const {
    return toString() == rhs.toString();
  }

  bool equalsAbstract(const IMathObject &rhs) const override {
    if (const auto *rhsPtr = cast<Derived>(&rhs)) {
      return equals(*rhsPtr);
    }

    if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
      return equals(cast<Derived>(*rhsPtr));
    }

    if (isConvertible(rhs, *this)) {
      return rhs == *this;
    }

    return false;
  }

private:
#if !defined(I_MATH_OBJECT_CRTP) && !defined(NDEBUG)
};
}

#endif // I_MATH_OBJECT_CRTP
