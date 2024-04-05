#if !defined(I_MATH_OBJECT_CRTP) && !defined(NDEBUG)

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

template <typename Derived>
class IMathObjectCRTP_ : public IMathObject {

#endif // I_MATH_OBJECT_CRTP

public:
  std::unique_ptr<IMathObject> clone() const & noexcept final {
    return std::make_unique<Derived>(cast<Derived>(*this));
  }

  std::unique_ptr<IMathObject> clone() && noexcept final {
    return std::make_unique<Derived>(std::move(cast<Derived>(*this)));
  }

  MathObjectClass getClass() const noexcept final {
    return Derived::getClassStatic();
  }

  bool operator==(const I_MATH_OBJECT_CRTP &rhs) const noexcept {
    return equals(cast<Derived>(rhs));
  }

protected:
  virtual bool equals(const Derived &rhs) const noexcept {
    return toString() == rhs.toString();
  }

  bool equalsAbstract(const IMathObject &rhs) const noexcept override {
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
