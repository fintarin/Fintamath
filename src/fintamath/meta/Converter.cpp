#include "fintamath/meta/Converter.hpp"

#include "fintamath/meta/MultiMethod.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath::meta {
  auto initConverter() {
    MultiMethod<MathObjectPtr(const MathObject &, const MathObject &)> converter;

    converter.add<Rational, Integer>(
        [](const Rational & /*lhs*/, const Integer &rhs) { return std::make_unique<Rational>(rhs); });

    return converter;
  }

  MathObjectPtr convertRhsToLhsType(const MathObject &lhs, const MathObject &rhs) {
    static const auto converter = initConverter();
    return converter(lhs, rhs);
  }
}
