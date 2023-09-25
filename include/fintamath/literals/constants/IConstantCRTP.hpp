#if !defined(I_CONSTANT_CRTP) && !defined(NDEBUG)

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

template <typename Return, typename Derived>
class IConstantCRTP_ : public IConstant {

#endif // I_CONSTANT_CRTP

#define I_LITERAL_CRTP I_CONSTANT_CRTP
#include "fintamath/literals/ILiteralCRTP.hpp"
#undef I_LITERAL_CRTP

public:
  MathObjectType getReturnType() const final {
    return Return::getTypeStatic();
  }

private:
#if !defined(I_CONSTANT_CRTP) && !defined(NDEBUG)
};
}

#endif // I_CONSTANT_CRTP
