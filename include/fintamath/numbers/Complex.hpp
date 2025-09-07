#pragma once

#include <optional>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Complex : public INumber, public IWithArithmeticOperators<Complex>, public IWithEqualsOperators<Complex> {
  FINTAMATH_CLASS_BODY(Complex, INumber)

public:
  Complex();

  Complex(const Integer &rhs);

  Complex(const Rational &rhs);

  Complex(const Real &rhs);

  Complex(std::integral auto rhs)
      : re(makeShared<Integer>(rhs)),
        im(Integer::getZero()) {}

  explicit Complex(std::integral auto inReal, std::integral auto inImag)
      : re(makeShared<Integer>(inReal)),
        im(makeShared<Integer>(inImag)) {}

  explicit Complex(const INumber &inReal, const INumber &inImag);

  explicit Complex(const SharedRef<INumber> &inReal, const SharedRef<INumber> &inImag);

  explicit Complex(const std::string &str);

  std::string toString() const noexcept override;

  SharedPtr<IMathObject> unwrapp() const noexcept override;

  std::optional<unsigned> getPrecision() const noexcept override;

  bool isZero() const noexcept override;

  bool isComplex() const noexcept override;

  const SharedRef<INumber> &real() const noexcept;

  const SharedRef<INumber> &imag() const noexcept;

protected:
  bool equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept override;

  bool equals(const Complex &rhs) const noexcept override;

  Complex &add(const Complex &rhs) override;

  Complex &sub(const Complex &rhs) override;

  Complex &mul(const Complex &rhs) override;

  Complex &div(const Complex &rhs) override;

  Complex &neg() override;

private:
  static SharedRef<INumber> parseNonComplexNumber(const std::string &str);

private:
  SharedRef<INumber> re;

  SharedRef<INumber> im;
};

}
