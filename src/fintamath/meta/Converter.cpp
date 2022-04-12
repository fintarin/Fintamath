#include "fintamath/meta/Converter.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath::meta {
  MultiMethod<std::unique_ptr<MathObject>(const MathObject &, const MathObject &)> initConverter() {
    MultiMethod<std::unique_ptr<MathObject>(const MathObject &, const MathObject &)> converter;

    converter.add<Rational, Integer>(
        [](const Rational & /*lhs*/, const Integer &rhs) { return std::make_unique<Rational>(rhs); });

    return converter;
  }
}
