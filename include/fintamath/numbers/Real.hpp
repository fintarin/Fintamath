#pragma once

#include <compare>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

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
    unsigned currPrecision = getPrecision();

  public:
    explicit ScopedSetPrecision(unsigned precision);

    ~ScopedSetPrecision();

    ScopedSetPrecision(const ScopedSetPrecision &rhs) = delete;

    ScopedSetPrecision &operator=(const ScopedSetPrecision &rhs) = delete;
  };

public:
  Real() = default;

  Real(Backend inBackend);

  explicit Real(std::string str);

  Real(const Rational &val);

  Real(const Integer &val);

  Real(int64_t val);

  std::string toString() const override;

  std::string toString(unsigned precision) const;

  bool isPrecise() const override;

  int sign() const;

  bool isZero() const;

  const Backend &getBackend() const;

  unsigned getOutputPrecision() const;

  void setOutputPrecision(unsigned precision);

  static unsigned getCalculationPrecision();

  static unsigned getPrecision();

  static void setPrecision(unsigned precision);

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

  void validateNewPrecision(unsigned precision) const;

private:
  Backend backend;

  unsigned outputPrecision = getPrecision();

  bool isNegative = false;
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
