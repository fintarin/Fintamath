#include "fintamath/core/Converter.hpp"

#include "fintamath/core/IMathObject.hpp"

namespace fintamath::detail {

Converter::ConverterMultiMethod &Converter::getConverter() {
  static ConverterMultiMethod converter;
  return converter;
}

}
