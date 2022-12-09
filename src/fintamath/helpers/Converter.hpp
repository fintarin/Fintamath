#pragma once

#include <memory>

#include "fintamath/helpers/MultiMethod.hpp"

namespace fintamath {
  class IMathObject;
  using MathObjectPtr = std::unique_ptr<IMathObject>;
}

namespace fintamath::helpers {
  class Converter {
  public:
    template <typename Value, typename Type>
    static void add(const std::function<MathObjectPtr(const Value &value, const Type &type)> &convertFunc) {
      converter.add<Value, Type>(convertFunc);
    }

    static MathObjectPtr convert(const IMathObject &value, const IMathObject &type) {
      return converter(value, type);
    }

    template <typename T>
    static T convert(const IMathObject &value) {
      return convert(value, T())->template to<T>();
    }

  private:
    static MultiMethod<MathObjectPtr(const IMathObject &, const IMathObject &)> converter;
  };
}
