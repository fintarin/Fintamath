#if !defined(FINTAMATH_I_NUMBER_CRTP) && !defined(NDEBUG)

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

template <typename Derived>
class INumberCRTP_ : public INumber {

#endif // FINTAMATH_I_NUMBER_CRTP

#define FINTAMATH_I_COMPARABLE_CRTP FINTAMATH_I_NUMBER_CRTP
#include "fintamath/core/IComparableCRTP.hpp"
#undef FINTAMATH_I_COMPARABLE_CRTP

private:
#if !defined(FINTAMATH_I_NUMBER_CRTP) && !defined(NDEBUG)
};
}

#endif // FINTAMATH_I_NUMBER_CRTP
