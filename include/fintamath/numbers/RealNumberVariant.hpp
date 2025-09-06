// #pragma once

// #include <variant>

// #include "fintamath/numbers/Integer.hpp"
// #include "fintamath/numbers/Rational.hpp"
// #include "fintamath/numbers/Real.hpp"

// namespace fintamath {

// class RealNumberVariant
//     : public std::variant<Integer, Rational, Real>,
//       public IWithArithmeticOperators<RealNumberVariant>,
//       public IWithCompareOperators<RealNumberVariant> {

// public:
//   RealNumberVariant() = default;

//   template <std::convertible_to<Real> T>
//   constexpr RealNumberVariant(T &&rhs) noexcept
//       : std::variant<Integer, Rational, Real>(std::forward<T>(rhs)) {}

//   explicit RealNumberVariant(const std::string &str) {
//     if (!construct<0, Integer, Rational, Real>(str)) {
//       throw InvalidInputException("Unable to parse a number from " + str);
//     }
//   }

//   const Number &getNumber() const {
//     return std::visit([](const auto &rhs) -> const Number & { return rhs; }, *this);
//   }

//   std::unique_ptr<Number> convertToNumber() {
//     return std::visit([]<typename T>(T &rhs) -> std::unique_ptr<Number> { return std::make_unique<T>(std::move(rhs)); }, *this);
//   }

// protected:
//   bool equals(const RealNumberVariant &rhs) const override {
//     return std::visit([](const auto &lhsVal, const auto &rhsVal) { return lhsVal == rhsVal; }, *this, rhs);
//   }

//   std::strong_ordering compare(const RealNumberVariant &rhs) const override {
//     return std::visit([](const auto &lhsVal, const auto &rhsVal) { return lhsVal <=> rhsVal; }, *this, rhs);
//   }

//   RealNumberVariant &add(const RealNumberVariant &rhs) override {
//     std::visit([this](auto &lhsVal, const auto &rhsVal) { *this = lhsVal + rhsVal; }, *this, rhs);
//     return *this;
//   }

//   RealNumberVariant &substract(const RealNumberVariant &rhs) override {
//     std::visit([this](auto &lhsVal, const auto &rhsVal) { *this = lhsVal - rhsVal; }, *this, rhs);
//     return *this;
//   }

//   RealNumberVariant &multiply(const RealNumberVariant &rhs) override {
//     std::visit([this](auto &lhsVal, const auto &rhsVal) { *this = lhsVal * rhsVal; }, *this, rhs);
//     return *this;
//   }

//   RealNumberVariant &divide(const RealNumberVariant &rhs) override {
//     std::visit([this](auto &lhsVal, const auto &rhsVal) { *this = lhsVal / rhsVal; }, *this, rhs);
//     return *this;
//   }

//   RealNumberVariant &negate() override {
//     std::visit([this](const auto &rhs) { *this = -rhs; }, *this);
//     return *this;
//   }
// };

// }
