#pragma once

#include <memory>

#include <boost/multiprecision/cpp_dec_float.hpp>

#include "fintamath/core/CoreConstants.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

class Real : public INumberCRTP<Real> {

public:
  Real();

  Real(const Real &rhs);

  Real(Real &&rhs) noexcept;

  Real &operator=(const Real &rhs);

  Real &operator=(Real &&rhs) noexcept;

  ~Real() override;

  explicit Real(boost::multiprecision::cpp_dec_float_100 inBackend);

  explicit Real(std::string str);

  Real(const Rational &val);

  Real(const Integer &val);

  Real(double val);

  std::string toString() const override;

  std::unique_ptr<IMathObject> toMinimalObject() const override;

  bool isPrecise() const override;

  Real precise(uint8_t precision) const;

  int sign() const;

  bool isNearZero() const;

  const boost::multiprecision::cpp_dec_float_100 &getBackend() const;

protected:
  bool equals(const Real &rhs) const override;

  bool less(const Real &rhs) const override;

  bool more(const Real &rhs) const override;

  Real &add(const Real &rhs) override;

  Real &substract(const Real &rhs) override;

  Real &multiply(const Real &rhs) override;

  Real &divide(const Real &rhs) override;

  Real &negate() override;

private:
  boost::multiprecision::cpp_dec_float_100 backend;

  uint8_t ouputPrecision = FINTAMATH_PRECISION;

  static const boost::multiprecision::cpp_dec_float_100 DELTA;
};

}
