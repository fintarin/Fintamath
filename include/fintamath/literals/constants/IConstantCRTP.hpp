#ifndef FINTAMATH_I_CONSTANT_CRTP

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

template <typename Return, typename Derived>
class IConstantCRTP_ : public IConstant {

#endif // FINTAMATH_I_CONSTANT_CRTP

#define FINTAMATH_I_LITERAL_CRTP FINTAMATH_I_CONSTANT_CRTP
#include "fintamath/literals/ILiteralCRTP.hpp"
#undef FINTAMATH_I_LITERAL_CRTP

public:
  MathObjectType getReturnType() const final {
    return Return::getTypeStatic();
  }

private:
#ifndef FINTAMATH_I_CONSTANT_CRTP
};
}

#endif // FINTAMATH_I_CONSTANT_CRTP
