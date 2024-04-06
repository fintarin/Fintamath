#pragma once

#include <concepts>
#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/Parser.hpp"

namespace fintamath {

class ILiteral : public IMathObject {
  FINTAMATH_PARENT_CLASS_BODY(ILiteral, IMathObject)
};

template <typename Derived>
class ILiteralCRTP : public ILiteral {
#define I_LITERAL_CRTP ILiteralCRTP<Derived>
#include "fintamath/literals/ILiteralCRTP.hpp"
#undef I_LITERAL_CRTP
};

}