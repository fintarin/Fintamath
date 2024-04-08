#pragma once

#include <compare>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Rational : public INumberCRTP<Rational> {
  FINTAMATH_CLASS_BODY(Rational, INumber)

public:
  Rational() = default;

  Rational(std::integral auto rhs) : numer(rhs) {}

  Rational(Integer rhs);

  explicit Rational(Integer inNumer, Integer inDenom);

  explicit Rational(const std::string &str);

  std::string toString() const override;

  std::unique_ptr<IMathObject> toMinimalObject() const override;

  int sign() const;

  const Integer &numerator() const;

  const Integer &denominator() const;

protected:
  bool equals(const Rational &rhs) const override;

  std::strong_ordering compare(const Rational &rhs) const override;

  Rational &add(const Rational &rhs) override;

  Rational &substract(const Rational &rhs) override;

  Rational &multiply(const Rational &rhs) override;

  std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &rhs) const override;

  Rational &divide(const Rational &rhs) override;

  std::unique_ptr<IArithmetic> divideAbstract(const IArithmetic &rhs) const override;

  Rational &negate() override;

private:
  void toIrreducibleRational();

  static void toCommonDenominators(Rational &lhs, Rational &rhs);

private:
  Integer numer = 0;

  Integer denom = 1;
};

}

template <>
struct std::hash<fintamath::Rational> {
  size_t operator()(const fintamath::Rational &rhs) const noexcept {
    using fintamath::detail::Hash;
    using fintamath::detail::hashCombine;

    size_t seed = 0;
    hashCombine(seed, Hash<fintamath::Integer>{}(rhs.numerator()));
    hashCombine(seed, Hash<fintamath::Integer>{}(rhs.denominator()));
    return seed;
  }
};
