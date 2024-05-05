#pragma once

#include <compare>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

#include <boost/multiprecision/fwd.hpp>
#include <boost/multiprecision/mpfr.hpp>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

class Real : public INumberCRTP<Real> {
  FINTAMATH_CLASS_BODY(Real, INumber)

public:
  using Backend = boost::multiprecision::mpfr_float;

  struct ScopedSetPrecision final {
    unsigned currPrecision = getPrecisionStatic();

  public:
    explicit ScopedSetPrecision(unsigned precision);

    ~ScopedSetPrecision();

    ScopedSetPrecision(const ScopedSetPrecision &rhs) = delete;

    ScopedSetPrecision &operator=(const ScopedSetPrecision &rhs) = delete;
  };

public:
  Real() = default;

  Real(Backend inBackend);

  Real(std::integral auto rhs) : backend(rhs) {}

  Real(const Rational &rhs);

  Real(const Integer &rhs);

  explicit Real(std::string_view str);

  std::string toString() const override;

  std::string toString(unsigned precision) const;

  int sign() const;

  bool isZero() const;

  bool isPosZero() const;

  bool isNegZero() const;

  const Backend &getBackend() const noexcept;

  std::optional<unsigned> getPrecision() const noexcept override;

  void setPrecision(unsigned precision);

  static unsigned getCalculationPrecisionStatic() noexcept;

  static unsigned getPrecisionStatic() noexcept;

  static void setPrecisionStatic(unsigned precision);

protected:
  bool equals(const Real &rhs) const override;

  bool equalsAbstract(const IMathObject &rhs) const override;

  std::strong_ordering compare(const Real &rhs) const override;

  std::strong_ordering compareAbstract(const IComparable &rhs) const override;

  Real &add(const Real &rhs) override;

  Real &substract(const Real &rhs) override;

  Real &multiply(const Real &rhs) override;

  std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &rhs) const override;

  Real &divide(const Real &rhs) override;

  Real &negate() override;

private:
  bool isFinite() const;

  void updatePrecision(const Real &rhs);

private:
  Backend backend;

  unsigned outputPrecision = getPrecisionStatic();
};

}

template <>
struct std::hash<fintamath::Real> {
  size_t operator()(const fintamath::Real &rhs) const noexcept {
    using fintamath::detail::Hash;
    using fintamath::detail::hashCombine;

    if (rhs.isZero()) {
      size_t seed = 0;
      hashCombine(seed, Hash<int>{}(rhs.sign()));
      return seed;
    }

    return Hash<fintamath::Real::Backend>{}(rhs.getBackend());
  }
};
