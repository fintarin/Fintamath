#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "fintamath/core/Constants.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

class RealImpl;

class Real : public INumberCRTP<Real> {
public:
  Real();

  Real(const Real &rhs);

  Real(Real &&rhs) noexcept;

  Real &operator=(const Real &rhs);

  Real &operator=(Real &&rhs) noexcept;

  ~Real() override;

  Real(const RealImpl &impl);

  explicit Real(std::string str);

  Real(const Rational &val);

  Real(const Integer &val);

  Real(double val);

  std::string toString() const override;

  MathObjectPtr simplify() const override;

  bool isPrecise() const override;

  Real precise(uint8_t precision) const;

  int sign() const;

  bool isNearZero() const;

  const std::unique_ptr<RealImpl> &getImpl() const;

protected:
  bool equals(const Real &rhs) const override;

  bool less(const Real &rhs) const override;

  bool more(const Real &rhs) const override;

  Real &add(const Real &rhs) override;

  Real &substract(const Real &rhs) override;

  Real &multiply(const Real &rhs) override;

  Real &divide(const Real &rhs) override;

  Real &negate() override;

  Real &increase() override;

  Real &decrease() override;

private:
  std::unique_ptr<RealImpl> impl;

  uint8_t ouputPrecision = FINTAMATH_ROUND_PRECISION;

  static const RealImpl DELTA;
};

}
