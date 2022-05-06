#include "fintamath/meta/Converter.hpp"

#include "fintamath/meta/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath::meta {
  auto initConverter() {
    MultiMethod<MathObjectPtr(const MathObject &, const MathObject &)> converter;

    converter.add<Rational, Rational>(
        [](const Rational & /*lhs*/, const Rational &rhs) { return std::make_unique<Rational>(rhs); });
    converter.add<Rational, Integer>(
        [](const Rational & /*lhs*/, const Integer &rhs) { return std::make_unique<Rational>(rhs); });

    return converter;
  }

  const auto converter = initConverter();

  MathObjectPtr convertRhsToLhsType(const MathObject &lhs, const MathObject &rhs) {
    return converter(lhs, rhs);
  }
}
