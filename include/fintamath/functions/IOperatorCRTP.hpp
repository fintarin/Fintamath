#ifndef FINTAMATH_I_OPERATOR_CRTP

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
#ifndef FINTAMATH_I_OPERATOR_CRTP
};
}

#endif // FINTAMATH_I_OPERATOR_CRTP
