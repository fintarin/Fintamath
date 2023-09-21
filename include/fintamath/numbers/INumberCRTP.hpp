#if !defined(I_NUMBER_CRTP) && !defined(NDEBUG)

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

template <typename Derived>
class INumberCRTP_ : public INumber {

#endif // I_NUMBER_CRTP

#define I_COMPARABLE_CRTP I_NUMBER_CRTP
#include "fintamath/core/IComparableCRTP.hpp"
#undef I_COMPARABLE_CRTP

private:
#if !defined(I_NUMBER_CRTP) && !defined(NDEBUG)
};
}

#endif // I_NUMBER_CRTP
