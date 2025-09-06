#pragma once

#include <compare>
#include <concepts>
#include <cstddef>
#include <string>
#include <string_view>

#include <boost/multiprecision/fwd.hpp>
#include <boost/multiprecision/gmp.hpp>

#include "fintamath/core/Hash.hpp"
#include "fintamath/core/IWithArithmeticOperators.hpp"
#include "fintamath/core/IWithCompareOperators.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Integer : public INumber, public IWithArithmeticOperators<Integer>, public IWithCompareOperators<Integer> {
  FINTAMATH_CLASS_BODY(Integer, INumber)

public:
  using Backend = boost::multiprecision::mpz_int;

public:
  Integer() = default;

  Integer(std::integral auto rhs) : backend(rhs) {}

  Integer(Backend inBackend);

  explicit Integer(std::string_view str);

  std::string toString() const noexcept override;

  int sign() const;

  const Backend &getBackend() const noexcept;

  template <std::integral T>
  explicit operator T() const {
    return backend.convert_to<T>();
  }

  Integer &operator%=(const Integer &rhs);

  Integer &operator&=(const Integer &rhs);

  Integer &operator|=(const Integer &rhs);

  Integer &operator^=(const Integer &rhs);

  Integer &operator<<=(const Integer &rhs);

  Integer &operator>>=(const Integer &rhs);

  Integer operator%(const Integer &rhs) const;

  Integer operator&(const Integer &rhs) const;

  Integer operator|(const Integer &rhs) const;

  Integer operator^(const Integer &rhs) const;

  Integer operator<<(const Integer &rhs) const;

  Integer operator>>(const Integer &rhs) const;

  Integer operator~() const;

  Integer &operator++();

  Integer &operator--();

  Integer operator++(int);

  Integer operator--(int);

protected:
  bool equals(const Integer &rhs) const override;

  std::strong_ordering compare(const Integer &rhs) const override;

  Integer &add(const Integer &rhs) override;

  Integer &substract(const Integer &rhs) override;

  Integer &multiply(const Integer &rhs) override;

  Integer &divide(const Integer &rhs) override;

  Integer &negate() override;

  Integer &mod(const Integer &rhs);

  Integer &bitAnd(const Integer &rhs);

  Integer &bitOr(const Integer &rhs);

  Integer &bitXor(const Integer &rhs);

  Integer &bitLeftShift(const Integer &rhs);

  Integer &bitRightShift(const Integer &rhs);

  Integer &bitNot();

  Integer &increase();

  Integer &decrease();

private:
  Backend backend;
};

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer &operator%=(Integer &lhs, const Rhs &rhs) {
  return lhs %= Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer &operator&=(Integer &lhs, const Rhs &rhs) {
  return lhs &= Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer &operator|=(Integer &lhs, const Rhs &rhs) {
  return lhs |= Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer &operator^=(Integer &lhs, const Rhs &rhs) {
  return lhs ^= Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer &operator<<=(Integer &lhs, const Rhs &rhs) {
  return lhs <<= Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer &operator>>=(Integer &lhs, const Rhs &rhs) {
  return lhs >>= Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer operator%(const Integer &lhs, const Rhs &rhs) {
  return lhs % Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Lhs>
Integer operator%(const Lhs &lhs, const Integer &rhs) {
  return Integer(lhs) % rhs;
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer operator&(const Integer &lhs, const Rhs &rhs) {
  return lhs & Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Lhs>
Integer operator&(const Lhs &lhs, const Integer &rhs) {
  return Integer(lhs) & rhs;
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer operator|(const Integer &lhs, const Rhs &rhs) {
  return lhs | Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Lhs>
Integer operator|(const Lhs &lhs, const Integer &rhs) {
  return Integer(lhs) | rhs;
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer operator^(const Integer &lhs, const Rhs &rhs) {
  return lhs ^ Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Lhs>
Integer operator^(const Lhs &lhs, const Integer &rhs) {
  return Integer(lhs) ^ rhs;
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer operator<<(const Integer &lhs, const Rhs &rhs) {
  return lhs << Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Lhs>
Integer operator<<(const Lhs &lhs, const Integer &rhs) {
  return Integer(lhs) << rhs;
}

template <ConvertibleToAndNotSameAs<Integer> Rhs>
Integer operator>>(const Integer &lhs, const Rhs &rhs) {
  return lhs >> Integer(rhs);
}

template <ConvertibleToAndNotSameAs<Integer> Lhs>
Integer operator>>(const Lhs &lhs, const Integer &rhs) {
  return Integer(lhs) >> rhs;
}

}

template <>
struct std::hash<fintamath::Integer> {
  size_t operator()(const fintamath::Integer &rhs) const noexcept {
    using fintamath::detail::Hash;

    return Hash<fintamath::Integer::Backend>{}(rhs.getBackend());
  }
};
