#include "fintamath/meta/Converter.hpp"

#include "fintamath/meta/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath::meta {
  auto initConverter() {
    MultiMethod<MathObjectPtr(const MathObject &, const MathObject &)> converter;

    converter.add<Integer, Integer>(
        [](const Integer &value, const Integer & /*type*/) { return std::make_unique<Integer>(value); });
    converter.add<Rational, Rational>(
        [](const Rational &value, const Rational & /*type*/) { return std::make_unique<Rational>(value); });
    converter.add<Integer, Rational>(
        [](const Integer &value, const Rational & /*type*/) { return std::make_unique<Rational>(value); });

    return converter;
  }

  const auto converter = initConverter();

  MathObjectPtr convertMathObject(const MathObject &value, const MathObject &type) {
    return converter(value, type);
  }
}
