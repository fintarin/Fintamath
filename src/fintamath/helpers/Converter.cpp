#include "fintamath/helpers/Converter.hpp"

#include "fintamath/helpers/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath::meta {
  auto initConverter() {
    MultiMethod<MathObjectPtr(const IMathObject &, const IMathObject &)> converter;

    converter.add<Integer, Integer>(
        [](const Integer &value, const Integer & /*type*/) { return std::make_unique<Integer>(value); });
    converter.add<Rational, Rational>(
        [](const Rational &value, const Rational & /*type*/) { return std::make_unique<Rational>(value); });
    converter.add<Integer, Rational>(
        [](const Integer &value, const Rational & /*type*/) { return std::make_unique<Rational>(value); });

    return converter;
  }

  const auto converter = initConverter();

  MathObjectPtr convertMathObject(const IMathObject &value, const IMathObject &type) {
    return converter(value, type);
  }
}
