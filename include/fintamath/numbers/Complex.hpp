#pragma once

#include <compare>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Complex : public INumberCRTP<Complex> {
  FINTAMATH_CLASS_BODY(Complex, INumber)

public:
  Complex() = default;

  Complex(const Complex &rhs);

  Complex(Complex &&rhs) noexcept = default;

  Complex &operator=(const Complex &rhs);

  Complex &operator=(Complex &&rhs) noexcept = default;

  Complex(const Integer &rhs);

  Complex(const Rational &rhs);

  Complex(const Real &rhs);

  Complex(std::integral auto rhs) : re(std::make_unique<Integer>(rhs)) {}

  explicit Complex(std::integral auto inReal, std::integral auto inImag)
      : re(std::make_unique<Integer>(inReal)),
        im(std::make_unique<Integer>(inImag)) {}

  explicit Complex(const INumber &inReal, const INumber &inImag);

  explicit Complex(const std::string &str);

  std::string toString() const override;

  std::unique_ptr<IMathObject> toMinimalObject() const override;

  std::optional<unsigned> getPrecision() const noexcept override;

  bool isComplex() const noexcept override;

  const INumber &real() const noexcept;

  const INumber &imag() const noexcept;

protected:
  bool equals(const Complex &rhs) const override;

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
