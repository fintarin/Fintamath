// #pragma once

// #include <optional>
// #include <string>

// #include "fintamath/core/IWithArithmeticOperators.hpp"
// #include "fintamath/numbers/INumber.hpp"
// #include "fintamath/numbers/Integer.hpp"
// #include "fintamath/numbers/Rational.hpp"
// #include "fintamath/numbers/Real.hpp"
// #include "fintamath/numbers/RealNumberVariant.hpp"

// namespace fintamath {

// class Rational;
// class Real;

// class Complex : public INumber, public IWithArithmeticOperators<Complex> {
//   FINTAMATH_CHILD_CLASS_BODY(Complex, INumber)

// public:
//   using InnerNumber = RealNumberVariant<Integer, Rational, Real>;

// public:
//   Complex() = default;

//   Complex(const Integer &rhs);

//   Complex(const Rational &rhs);

//   Complex(const Real &rhs);

//   Complex(std::integral auto rhs) : re(Integer(rhs)) {}

//   explicit Complex(std::integral auto inReal, std::integral auto inImag)
//       : re(Integer(inReal)),
//         im(Integer(inImag)) {}

//   explicit Complex(InnerNumber inReal, InnerNumber inImag);

//   explicit Complex(const std::string &str);

//   std::string toString() const noexcept override;

//   std::optional<unsigned> getPrecision() const noexcept override;

//   bool isComplex() const noexcept override;

//   const InnerNumber &real() const noexcept;

//   const InnerNumber &imag() const noexcept;

// protected:
//   bool equals(const Complex &rhs) const override;

//   Complex &add(const Complex &rhs) override;

//   Complex &substract(const Complex &rhs) override;

//   Complex &multiply(const Complex &rhs) override;

//   Complex &divide(const Complex &rhs) override;

//   Complex &negate() override;

// private:
//   InnerNumber re = Integer(0);

//   InnerNumber im = Integer(0);
// };

// }
