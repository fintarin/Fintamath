#if !defined(I_ARITHMETIC_CRTP) && !defined(NDEBUG)

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

template <typename Derived>
class IArithmeticCRTP_ : public IArithmetic {

#endif // I_ARITHMETIC_CRTP

#define I_MATH_OBJECT_CRTP I_ARITHMETIC_CRTP
#include "fintamath/core/IMathObjectCRTP.hpp"
#undef I_MATH_OBJECT_CRTP

public:
  Derived &operator+=(const Derived &rhs) {
    return add(rhs);
  }

  Derived &operator-=(const Derived &rhs) {
    return substract(rhs);
  }

  Derived &operator*=(const Derived &rhs) {
    return multiply(rhs);
  }

  Derived &operator/=(const Derived &rhs) {
    return divide(rhs);
  }

  Derived operator+(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) += rhs;
  }

  Derived operator-(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) -= rhs;
  }

  Derived operator*(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) *= rhs;
  }

  Derived operator/(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) /= rhs;
  }

  Derived operator+() const {
    return Derived(cast<Derived>(*this));
  }

  Derived operator-() const {
    Derived tmp = Derived(cast<Derived>(*this));
    return cast<I_ARITHMETIC_CRTP>(tmp).negate();
  }

protected:
  virtual Derived &add(const Derived &rhs) = 0;

  virtual Derived &substract(const Derived &rhs) = 0;

  virtual Derived &multiply(const Derived &rhs) = 0;

  virtual Derived &divide(const Derived &rhs) = 0;

  virtual Derived &negate() = 0;

  std::unique_ptr<IArithmetic> addAbstract(const IArithmetic &inRhs) const final {
    return executeAbstract(
        inRhs, "+",
        [](I_ARITHMETIC_CRTP &lhs, const Derived &rhs) {
          return lhs.add(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs + rhs;
        });
  }

  std::unique_ptr<IArithmetic> substractAbstract(const IArithmetic &inRhs) const final {
    return executeAbstract(
        inRhs, "-",
        [](I_ARITHMETIC_CRTP &lhs, const Derived &rhs) {
          return lhs.substract(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs - rhs;
        });
  }

  std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &inRhs) const final {
    return executeAbstract(
        inRhs, "*",
        [](I_ARITHMETIC_CRTP &lhs, const Derived &rhs) {
          return lhs.multiply(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs * rhs;
        });
  }

  std::unique_ptr<IArithmetic> divideAbstract(const IArithmetic &inRhs) const final {
    return executeAbstract(
        inRhs, "/",
        [](I_ARITHMETIC_CRTP &lhs, const Derived &rhs) {
          return lhs.divide(rhs);
        },
        [](const IArithmetic &lhs, const IArithmetic &rhs) {
          return lhs / rhs;
        });
  }

  std::unique_ptr<IArithmetic> negateAbstract() const final {
    return std::make_unique<Derived>(-(*this));
  }

  std::unique_ptr<IArithmetic> unaryPlusAbstract() const final {
    return std::make_unique<Derived>(+(*this));
  }

private:
  std::unique_ptr<IArithmetic> executeAbstract(const IArithmetic &rhs,
                                               const std::string &oper,
                                               std::invocable<I_ARITHMETIC_CRTP &, const Derived &> auto funcCommonTypes,
                                               std::invocable<const IArithmetic &, const IArithmetic &> auto funcDifferentTypes) const {

    if (const auto *rhpPtr = cast<Derived>(&rhs)) {
      auto lhsPtr = cast<Derived>(clone());
      return cast<IArithmetic>(funcCommonTypes(*lhsPtr, *rhpPtr).toMinimalObject());
    }

    if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
      auto lhsPtr = cast<Derived>(clone());
      return cast<IArithmetic>(funcCommonTypes(*lhsPtr, cast<Derived>(*rhsPtr)).toMinimalObject());
    }

    if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this)) {
      return cast<IArithmetic>(funcDifferentTypes(cast<IArithmetic>(*lhsPtr), rhs)->toMinimalObject());
    }

    throw InvalidInputBinaryOperatorException(oper, toString(), rhs.toString());
  }

private:
#if !defined(I_ARITHMETIC_CRTP) && !defined(NDEBUG)
};
}

#endif // I_ARITHMETIC_CRTP
