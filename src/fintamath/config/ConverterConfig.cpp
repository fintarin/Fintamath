#include "ConverterConfig.hpp"

#include "fintamath/helpers/Converter.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

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

  Converter::add<Real, Real>([](const Real &value, const Real & /*type*/) { return std::make_unique<Real>(value); });
  Converter::add<Integer, Real>(
      [](const Integer &value, const Real & /*type*/) { return std::make_unique<Real>(value); });
  Converter::add<Rational, Real>(
      [](const Rational &value, const Real & /*type*/) { return std::make_unique<Real>(value); });
}

static const ConverterConfig config;

}
