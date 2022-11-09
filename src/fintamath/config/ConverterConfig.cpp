#include "fintamath/config/ConverterConfig.hpp"

#include "fintamath/helpers/Converter.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath::helpers;

namespace fintamath {
  MultiMethod<MathObjectPtr(const IMathObject &, const IMathObject &)> Converter::converter;
}

namespace fintamath::config {
  ConverterConfig::ConverterConfig() {
    Converter::add<Integer, Integer>(
        [](const Integer &value, const Integer & /*type*/) { return std::make_unique<Integer>(value); });
    Converter::add<Rational, Rational>(
        [](const Rational &value, const Rational & /*type*/) { return std::make_unique<Rational>(value); });
    Converter::add<Integer, Rational>(
        [](const Integer &value, const Rational & /*type*/) { return std::make_unique<Rational>(value); });
  }

  static const ConverterConfig config;
}
