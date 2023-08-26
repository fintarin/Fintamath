#include "fintamath/core/Converter.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

MultiMethod<std::unique_ptr<IMathObject>(const IMathObject &, const IMathObject &)> &Converter::getConverter() {
  static MultiMethod<std::unique_ptr<IMathObject>(const IMathObject &, const IMathObject &)> converter;
  return converter;
}

}

using namespace fintamath;

namespace {

struct ConverterConfig {
  ConverterConfig() {
    Converter::add<Integer, Integer>([](const Integer & /*type*/, const Integer &value) {
      return Integer(value).clone();
    });

    Converter::add<Rational, Rational>([](const Rational & /*type*/, const Rational &value) {
      return Rational(value).clone();
    });
    Converter::add<Rational, Integer>([](const Rational & /*type*/, const Integer &value) {
      return Rational(value).clone();
    });

    Converter::add<Real, Real>([](const Real & /*type*/, const Real &value) {
      return Real(value).clone();
    });
    Converter::add<Real, Integer>([](const Real & /*type*/, const Integer &value) {
      return Real(value).clone();
    });
    Converter::add<Real, Rational>([](const Real & /*type*/, const Rational &value) {
      return Real(value).clone();
    });
  }
};

const ConverterConfig config;

}
