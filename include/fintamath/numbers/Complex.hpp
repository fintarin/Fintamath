#pragma once

#include <compare>
#include <cstdint>
#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Complex final : public INumberCRTP<Complex> {
  FINTAMATH_CLASS_BODY(Complex)

public:
  Complex() = default;

  Complex(const Complex &rhs);

  Complex(Complex &&rhs) noexcept = default;

  Complex &operator=(const Complex &rhs);

  Complex &operator=(Complex &&rhs) noexcept = default;

  explicit Complex(const std::string &str);

  explicit Complex(const INumber &inReal, const INumber &inImag);

  explicit Complex(int64_t inReal, int64_t inImag);

  Complex(const Integer &rhs);

  Complex(const Rational &rhs);

  Complex(const Real &rhs);

  Complex(int64_t rhs);

  std::string toString() const noexcept override;

  std::unique_ptr<IMathObject> toMinimalObject() const noexcept override;

  bool isPrecise() const override;

  bool isComplex() const override;

  const INumber &real() const;

  const INumber &imag() const;

protected:
  bool equals(const Complex &rhs) const noexcept override;

  std::strong_ordering compare(const Complex &rhs) const override;

  Complex &add(const Complex &rhs) override;

  Complex &substract(const Complex &rhs) override;

  Complex &multiply(const Complex &rhs) override;

  Complex &divide(const Complex &rhs) override;

  Complex &negate() override;

private:
  static std::unique_ptr<INumber> parseNonComplexNumber(const std::string &str);

private:
  std::unique_ptr<INumber> re = std::make_unique<Integer>(0);

  std::unique_ptr<INumber> im = std::make_unique<Integer>(0);
};

}
