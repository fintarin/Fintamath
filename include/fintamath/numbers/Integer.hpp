#pragma once

#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include <boost/container_hash/hash.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <boost/multiprecision/gmp.hpp>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/numbers/IInteger.hpp"

namespace fintamath {

class Integer final : public IIntegerCRTP<Integer> {
public:
  using Backend = boost::multiprecision::mpz_int;

public:
  Integer() = default;

  Integer(Backend inBackend);

  explicit Integer(std::string str);

  explicit Integer(std::integral auto val) : backend(val) {
  }

  Integer(int64_t val);

  std::string toString() const override;

  int sign() const;

  const Backend &getBackend() const;

  template <std::integral T>
  explicit operator T() const {
    return backend.convert_to<T>();
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::Integer, "Integer"};
  }

protected:
  bool equals(const Integer &rhs) const override;

  std::strong_ordering compare(const Integer &rhs) const override;

  Integer &add(const Integer &rhs) override;

  Integer &substract(const Integer &rhs) override;

  Integer &multiply(const Integer &rhs) override;

  std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &rhs) const override;

  Integer &divide(const Integer &rhs) override;

  std::unique_ptr<IArithmetic> divideAbstract(const IArithmetic &rhs) const override;

  Integer &mod(const Integer &rhs) override;

  Integer &bitAnd(const Integer &rhs) override;

  Integer &bitOr(const Integer &rhs) override;

  Integer &bitXor(const Integer &rhs) override;

  Integer &bitLeftShift(const Integer &rhs) override;

  Integer &bitRightShift(const Integer &rhs) override;

  Integer &bitNot() override;

  Integer &negate() override;

  Integer &increase() override;

  Integer &decrease() override;

private:
  Backend backend;
};

inline size_t hash_value(const Integer &rhs) noexcept {
  return boost::hash<Integer::Backend>{}(rhs.getBackend());
}

}
