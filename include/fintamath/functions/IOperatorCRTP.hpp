#if !defined(FINTAMATH_I_OPERATOR_CRTP) && !defined(NDEBUG)

#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

template <typename Return, typename Derived, typename... Args>
class IOperatorCRTP_ : public IOperator {

#endif // FINTAMATH_I_OPERATOR_CRTP

#define FINTAMATH_I_FUNCTION_CRTP FINTAMATH_I_OPERATOR_CRTP
#include "fintamath/functions/IFunctionCRTP.hpp"
#undef FINTAMATH_I_FUNCTION_CRTP

public:
  IOperator::Priority getOperatorPriority() const final {
    return priority;
  }

  bool isAssociative() const final {
    return isAssociativeOper;
  }

private:
  IOperator::Priority priority;

  bool isAssociativeOper;

private:
#if !defined(FINTAMATH_I_OPERATOR_CRTP) && !defined(NDEBUG)
};
}

#endif // FINTAMATH_I_OPERATOR_CRTP
