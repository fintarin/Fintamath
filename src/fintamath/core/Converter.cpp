#include "fintamath/core/Converter.hpp"

#include "fintamath/core/IMathObject.hpp"

namespace fintamath::detail {

std::unique_ptr<IMathObject> Converter::convert(const IMathObject &to, const IMathObject &from) {
  return getConverter()(to, from);
}

Converter::ConverterMultiMethod &Converter::getConverter() {
  static ConverterMultiMethod converter;
  return converter;
}

}