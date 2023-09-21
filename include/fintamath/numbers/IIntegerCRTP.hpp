#if !defined(I_INTEGER_CRTP) && !defined(NDEBUG)

#include "fintamath/numbers/IInteger.hpp"

namespace fintamath {

template <typename Derived>
class IIntegerCRTP_ : public IInteger {

#endif // I_INTEGER_CRTP

#define I_NUMBER_CRTP I_INTEGER_CRTP
#include "fintamath/numbers/INumberCRTP.hpp"
#undef I_NUMBER_CRTP

public:
  Derived &operator%=(const Derived &rhs) {
    return mod(rhs);
  }

  Derived operator%(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) %= rhs;
  }

  Derived &operator&=(const Derived &rhs) {
    return bitAnd(rhs);
  }

  Derived operator&(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) &= rhs;
  }

  Derived &operator|=(const Derived &rhs) {
    return bitOr(rhs);
  }

  Derived operator|(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) |= rhs;
  }

  Derived &operator^=(const Derived &rhs) {
    return bitXor(rhs);
  }

  Derived operator^(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) ^= rhs;
  }

  Derived &operator<<=(const Derived &rhs) {
    return bitLeftShift(rhs);
  }

  Derived operator<<(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) <<= rhs;
  }

  Derived &operator>>=(const Derived &rhs) {
    return bitRightShift(rhs);
  }

  Derived operator>>(const Derived &rhs) const {
    return Derived(cast<Derived>(*this)) >>= rhs;
  }

  Derived operator~() const {
    Derived tmp = Derived(cast<Derived>(*this));
    return cast<I_INTEGER_CRTP>(tmp).bitNot();
  }

  Derived &operator++() {
    return increase();
  }

  Derived &operator--() {
    return decrease();
  }

  Derived operator++(int) {
    auto res = Derived(cast<Derived>(*this));
    increase();
    return res;
  }

  Derived operator--(int) {
    auto res = Derived(cast<Derived>(*this));
    decrease();
    return res;
  }

protected:
  virtual Derived &mod(const Derived &rhs) = 0;

  virtual Derived &bitAnd(const Derived &rhs) = 0;

  virtual Derived &bitOr(const Derived &rhs) = 0;

  virtual Derived &bitXor(const Derived &rhs) = 0;

  virtual Derived &bitLeftShift(const Derived &rhs) = 0;

  virtual Derived &bitRightShift(const Derived &rhs) = 0;

  virtual Derived &bitNot() = 0;

  virtual Derived &increase() = 0;

  virtual Derived &decrease() = 0;

  std::unique_ptr<IInteger> modAbstract(const IInteger &inRhs) const final {
    return executeAbstract(
        inRhs, "%",
        [](I_INTEGER_CRTP &lhs, const Derived &rhs) {
          return lhs.mod(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs % rhs;
        });
  }

  std::unique_ptr<IInteger> bitAndAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, "&",
        [](I_INTEGER_CRTP &lhs, const Derived &rhs) {
          return lhs.bitAnd(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs & rhs;
        });
  }

  std::unique_ptr<IInteger> bitOrAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, "|",
        [](I_INTEGER_CRTP &lhs, const Derived &rhs) {
          return lhs.bitOr(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs | rhs;
        });
  }

  std::unique_ptr<IInteger> bitXorAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, "^",
        [](I_INTEGER_CRTP &lhs, const Derived &rhs) {
          return lhs.bitXor(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs ^ rhs;
        });
  }

  std::unique_ptr<IInteger> bitLeftShiftAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, "<<",
        [](I_INTEGER_CRTP &lhs, const Derived &rhs) {
          return lhs.bitLeftShift(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs << rhs;
        });
  }

  std::unique_ptr<IInteger> bitRightShiftAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, ">>",
        [](I_INTEGER_CRTP &lhs, const Derived &rhs) {
          return lhs.bitRightShift(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs >> rhs;
        });
  }

  std::unique_ptr<IInteger> bitNotAbstract() const final {
    return std::make_unique<Derived>(~(*this));
  }

  IInteger &increaseAbstract() final {
    increase();
    return *this;
  }

  IInteger &decreaseAbstract() final {
    decrease();
    return *this;
  }

private:
  std::unique_ptr<IInteger> executeAbstract(const IInteger &rhs,
                                            const std::string &oper,
                                            std::invocable<I_INTEGER_CRTP &, const Derived &> auto funcCommonTypes,
                                            std::invocable<const IInteger &, const IInteger &> auto funcDifferentTypes) const {

    if (const auto *rhpPtr = cast<Derived>(&rhs)) {
      auto lhsPtr = cast<Derived>(clone());
      return cast<IInteger>(funcCommonTypes(*lhsPtr, *rhpPtr).toMinimalObject());
    }

    if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
      auto lhsPtr = cast<I_INTEGER_CRTP>(clone());
      return cast<IInteger>(funcCommonTypes(*lhsPtr, cast<Derived>(*rhsPtr)).toMinimalObject());
    }

    if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this)) {
      return cast<IInteger>(funcDifferentTypes(cast<IInteger>(*lhsPtr), rhs)->toMinimalObject());
    }

    throw InvalidInputBinaryOperatorException(oper, toString(), rhs.toString());
  }

private:
#if !defined(I_INTEGER_CRTP) && !defined(NDEBUG)
};
}

#endif // I_INTEGER_CRTP
