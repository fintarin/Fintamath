#include "fintamath/meta/Converter.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

MultiMethod<unique_ptr<IMathObject>(const IMathObject &, const IMathObject &)> Converter::converter;

}

using namespace fintamath;

namespace {

struct ConverterConfig {
  ConverterConfig() {
    Converter::add<Integer, Integer>([](const Integer & /*type*/, const Integer &value) {
      return make_unique<Integer>(value);
    });

    Converter::add<Rational, Rational>([](const Rational & /*type*/, const Rational &value) {
      return make_unique<Rational>(value);
    });
    Converter::add<Rational, Integer>([](const Rational & /*type*/, const Integer &value) {
      return make_unique<Rational>(value);
    });

    Converter::add<Real, Real>([](const Real & /*type*/, const Real &value) {
      return make_unique<Real>(value);
    });
    Converter::add<Real, Integer>([](const Real & /*type*/, const Integer &value) {
      return make_unique<Real>(value);
    });
    Converter::add<Real, Rational>([](const Real & /*type*/, const Rational &value) {
      return make_unique<Real>(value);
    });
  }
};

const ConverterConfig config;

}
