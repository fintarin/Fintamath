#ifndef FINTAMATH_I_LITERAL_CRTP

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

template <typename Derived>
class ILiteralCRTP_ : public ILiteral {

#endif // FINTAMATH_I_LITERAL_CRTP

#define FINTAMATH_I_MATH_OBJECT_CRTP FINTAMATH_I_LITERAL_CRTP
#include "fintamath/core/IMathObjectCRTP.hpp"
#undef FINTAMATH_I_MATH_OBJECT_CRTP

private:
#ifndef FINTAMATH_I_LITERAL_CRTP
};
}

#endif // FINTAMATH_I_LITERAL_CRTP
