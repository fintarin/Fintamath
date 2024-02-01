#include "fintamath/core/Converter.hpp"

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

Converter::ConverterMultiMethod &Converter::getConverter() {
  static ConverterMultiMethod converter;
  return converter;
}

}
