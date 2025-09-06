// #include "fintamath/numbers/Complex.hpp"

// #include <string>
// #include <utility>

// #include <fmt/core.h>

// #include "fintamath/exceptions/InvalidInputException.hpp"
// #include "fintamath/exceptions/UndefinedException.hpp"
// #include "fintamath/numbers/INumber.hpp"
// #include "fintamath/numbers/Integer.hpp"
// #include "fintamath/numbers/Rational.hpp"
// #include "fintamath/numbers/Real.hpp"

// namespace fintamath {

// FINTAMATH_CHILD_CLASS_IMPLEMENTATION(Complex)

// Complex::Complex(const Integer &rhs) : re(rhs) {
// }

// Complex::Complex(const Rational &rhs) : re(rhs.denominator() != 1 ? rhs : rhs.numerator()) {
// }

// Complex::Complex(const Real &rhs) : re(rhs) {
// }

// Complex::Complex(InnerNumber inReal, InnerNumber inImag)
//     : re(std::move(inReal)),
//       im(std::move(inImag)) {
// }

// Complex::Complex(const std::string &str) try {
//   if (!str.empty() && str.back() == 'I') {
//     im = InnerNumber(str.substr(0, str.size() - 1));
//   }
//   else {
//     re = InnerNumber(str);
//   }
// }
// catch (const InvalidInputException &) {
//   throw InvalidInputException(fmt::format(
//       R"(Unable to parse {} from "{}")",
//       getClassStatic()->getName(),
//       str));
// }

// std::string Complex::toString() const noexcept {
//   std::string res;

//   if (re != Integer(0)) {
//     res += re.getNumber().toString();
//   }

//   if (im != Integer(0)) {
//     std::string imStr = im.getNumber().toString();
//     bool isImNeg = false;

//     if (imStr.front() == '-') {
//       imStr = imStr.substr(1);
//       isImNeg = true;
//     }

//     if (im == Integer(1) || im == Integer(-1)) {
//       imStr.clear();
//     }
//     else {
//       imStr += " ";
//     }

//     if (!res.empty()) {
//       res += isImNeg ? " - " : " + ";
//     }
//     else if (isImNeg) {
//       res += "-";
//     }

//     res += imStr + "I";
//   }

//   if (res.empty()) {
//     res = "0";
//   }

//   return res;
// }

// std::optional<unsigned> Complex::getPrecision() const noexcept {
//   std::optional<unsigned> rePrecision = re.getNumber().getPrecision();
//   std::optional<unsigned> imPrecision = im.getNumber().getPrecision();

//   if (rePrecision && imPrecision) {
//     return std::min(*rePrecision, *imPrecision);
//   }

//   if (rePrecision) {
//     return *rePrecision;
//   }

//   if (imPrecision) {
//     return *imPrecision;
//   }

//   return {};
// }

// bool Complex::isComplex() const noexcept {
//   return im != Integer(0);
// }

// const Complex::InnerNumber &Complex::real() const noexcept {
//   return re;
// }

// const Complex::InnerNumber &Complex::imag() const noexcept {
//   return im;
// }

// bool Complex::equals(const Complex &rhs) const {
//   return re == rhs.re && im == rhs.im;
// }

// Complex &Complex::add(const Complex &rhs) {
//   re = re + rhs.re;
//   im = im + rhs.im;

//   return *this;
// }

// Complex &Complex::substract(const Complex &rhs) {
//   re = re - rhs.re;
//   im = im - rhs.im;

//   return *this;
// }

// // https://en.wikipedia.org/wiki/Complex_number#Multiplication_and_square
// Complex &Complex::multiply(const Complex &rhs) {
//   const Complex lhs = *this;

//   const auto &x = lhs.re;
//   const auto &y = lhs.im;
//   const auto &u = rhs.re;
//   const auto &v = rhs.im;

//   re = (x * u) - (y * v);
//   im = (x * v) + (y * u);

//   return *this;
// }

// // https://en.wikipedia.org/wiki/Complex_number#Reciprocal_and_division
// Complex &Complex::divide(const Complex &rhs) {
//   const Complex lhs = *this;

//   const auto &x = lhs.re;
//   const auto &y = lhs.im;
//   const auto &u = rhs.re;
//   const auto &v = rhs.im;

//   auto divisor = (u * u) + (v * v);

//   if (const Integer *intDivisor = std::get_if<Integer>(&divisor)) {
//     divisor = Rational(*intDivisor);
//   }

//   try {
//     re = ((x * u) + (y * v)) / divisor;
//     im = ((y * u) - (x * v)) / divisor;
//   }
//   catch (const UndefinedException &) {
//     throw UndefinedException(fmt::format(
//         R"(div({}, {}) is undefined (division by zero))",
//         toString(),
//         rhs.toString()));
//   }

//   return *this;
// }

// Complex &Complex::negate() {
//   re = -(re);
//   im = -(im);
//   return *this;
// }

// }
