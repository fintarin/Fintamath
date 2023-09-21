#if !defined(I_LITERAL_CRTP) && !defined(NDEBUG)

#include "fintamath/literals/ILiteral.hpp"

namespace fintamath {

template <typename Derived>
class ILiteralCRTP_ : public ILiteral {

#endif // I_LITERAL_CRTP

#define I_MATH_OBJECT_CRTP I_LITERAL_CRTP
#include "fintamath/core/IMathObjectCRTP.hpp"
#undef I_MATH_OBJECT_CRTP

private:
#if !defined(I_LITERAL_CRTP) && !defined(NDEBUG)
};
}

#endif // I_LITERAL_CRTP
