#pragma once

#include <compare>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include <boost/container_hash/hash.hpp>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Rational final : public INumberCRTP<Rational> {
public:
  Rational() = default;

  explicit Rational(const std::string &str);

  explicit Rational(Integer inNumer, Integer inDenom);

  Rational(Integer rhs);

  Rational(int64_t rhs);

  std::string toString() const override;

  std::unique_ptr<IMathObject> toMinimalObject() const override;

  int sign() const;

  const Integer &numerator() const;

  const Integer &denominator() const;

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Rational, "Rational"};
  }

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

  Integer numer = 0;
  Integer denom = 1;
};

inline size_t hash_value(const Rational &rhs) noexcept {
  size_t seed = 0;
  boost::hash_combine(seed, boost::hash<Integer>{}(rhs.numerator()));
  boost::hash_combine(seed, boost::hash<Integer>{}(rhs.denominator()));
  return seed;
}

}
